#include "pw_arcgames.h"
#include "curl/curl.h"
#include "pw_server_group.h"
#include "openssl/hmac.h"
#include "openssl/sha.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwngs
{
	void ArcGames::MakeSig( std::string& result,const unsigned char* key,size_t keylen,const unsigned char* text,size_t textlen)
	{
		char				 digest[100] = {0};
		unsigned char        md[20];
		unsigned char        mdkey[20];
		unsigned char        k_ipad[64],k_opad[64];
		unsigned int    i;
		char            s[3];

		if (keylen > 64) {
			SHA_CTX         ctx;

			SHA1_Init(&ctx);
			SHA1_Update(&ctx, key, keylen);
			SHA1_Final(mdkey, &ctx);
			keylen = 20;

			key = mdkey;
		}

		memcpy(k_ipad, key, keylen);
		memcpy(k_opad, key, keylen);
		memset(k_ipad + keylen, 0, 64 - keylen);
		memset(k_opad + keylen, 0, 64 - keylen);

		for (i = 0; i < 64; i++) {
			k_ipad[i] ^= 0x36;
			k_opad[i] ^= 0x5c;
		}

		SHA_CTX         ctx;

		SHA1_Init(&ctx);
		SHA1_Update(&ctx, k_ipad, 64);
		SHA1_Update(&ctx, text, textlen);
		SHA1_Final(md, &ctx);

		SHA1_Init(&ctx);
		SHA1_Update(&ctx, k_opad, 64);
		SHA1_Update(&ctx, md, 20);
		SHA1_Final(md, &ctx);

		for (i = 0; i < 20; i++) {
			snprintf(s, 3, "%02x", md[i]);
			digest[2 * i] = s[0];
			digest[2 * i + 1] = s[1];
		}

		digest[40] = '\0';

		result = digest;
	}

	size_t fnCurlWrite( void* buf,size_t len,size_t num,void* user )
	{
		std::string* buffer = (std::string*)user;
		buffer->append((char*)buf,len * num);
		return len * num;
	}

	void ArcGames::PerformRequest( std::string& result,const std::string& request )
	{
		const int MAX_URL = 2048;

		//init params
		const char* key             =   pwngs::g_strArcGameSecret.c_str();
		const char* host            =   pwngs::g_strArcGameUrl.c_str();
		char rand[60]				=   {0};
		const char* game			=   pwngs::g_strArcGameAbbr.c_str();
		const char format[]         =   "json";
		const unsigned int  version =   2;

		int t = (int )time(NULL);

		pwutils::make_random_pswd(rand,6);

		char code[4096] = {0};
		snprintf(code, sizeof(code) - 1, "%s%d%u%s%s", rand,t,version,game,request.c_str());

		gDebugStream(__FUNCTION__ << " sign source=" << code);

		std::string sig;
		MakeSig(sig, (const unsigned char*)key, strlen(key), (const unsigned char*)code, strlen(code));

		char url[MAX_URL];
		snprintf(url, sizeof(url) - 1, "http://%s/?f=%s&r=%s&t=%d&v=%u&g=%s&sig=%s",host, format, rand, t, version, game, sig.c_str());
		url[MAX_URL - 1] = 0;

		CURL* curl;
		curl = curl_easy_init();
		if (curl == NULL) {
			result.append("curl_easy_init failed");
			return;
		}

		gDebugStream(__FUNCTION__ << " url=" << url);

		std::string response;

		//set curl options
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L); 
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 8L); //timeout 30s
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &fnCurlWrite); //register callback function
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //register callback data
		curl_easy_setopt(curl, CURLOPT_POST, 1); //use post
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.c_str());
		CURLcode rc = curl_easy_perform(curl);

		if (rc != CURLE_OK) {
			result.append("curl_easy_perform() result = ").append(pwutils::itoa2(rc)).append(":").append(curl_easy_strerror(rc));
		} else {
			result = response;
		}

		curl_easy_cleanup(curl);
	}

}