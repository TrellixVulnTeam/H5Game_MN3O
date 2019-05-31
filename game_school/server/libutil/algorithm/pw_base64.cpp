#include "pw_base64.h"
#include <string.h>

namespace pwutils
{
	static const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 

	static char find_pos(char ch)   
	{ 
		char *ptr = (char*)strrchr(base, ch);//the last position (the only) in base[] 
		return (ptr - base); 
	} 

	extern std::string base64_encode(const char* buf,int len)
	{
		int prepare = 0; 
		int ret_len; 
		int temp = 0; 
		int tmp = 0; 
		char changed[4]; 
		int i = 0; 
		ret_len = len / 3; 
		temp = len % 3; 
		if (temp > 0) 
		{ 
			ret_len += 1; 
		} 
		ret_len = ret_len*4 + 1; 
		
		std::string result;
		result.reserve(ret_len); 

		while (tmp < len) 
		{ 
			temp = 0; 
			prepare = 0; 
			memset(changed, 0, sizeof(changed)); 
			while (temp < 3) 
			{ 
				//printf("tmp = %d\n", tmp); 
				if (tmp >= len) 
				{ 
					break; 
				} 
				prepare = ((prepare << 8) | (buf[tmp] & 0xFF)); 
				tmp++; 
				temp++; 
			} 
			prepare = (prepare<<((3-temp)*8)); 
			for (i = 0; i < 4 ;i++ ) 
			{ 
				if (temp < i) 
				{ 
					changed[i] = 0x40; 
				} 
				else 
				{ 
					changed[i] = (prepare>>((3-i)*6)) & 0x3F; 
				} 
				result.append(1,base[changed[i]]);
			} 
		} 
		return result; 
	}

	extern std::string base64_decode(const char* buf,int len)
	{
		int ret_len = (len / 4) * 3; 
		int equal_count = 0; 
		int tmp = 0; 
		int temp = 0; 
		char need[3]; 
		int prepare = 0; 
		int i = 0; 
		if (*(buf + len - 1) == '=') 
		{ 
			equal_count += 1; 
		} 
		if (*(buf + len - 2) == '=') 
		{ 
			equal_count += 1; 
		} 
		if (*(buf + len - 3) == '=') 
		{//seems impossible 
			equal_count += 1; 
		} 
		switch (equal_count) 
		{ 
		case 0: 
			ret_len += 4;//3 + 1 [1 for NULL] 
			break; 
		case 1: 
			ret_len += 4;//Ceil((6*3)/8)+1 
			break; 
		case 2: 
			ret_len += 3;//Ceil((6*2)/8)+1 
			break; 
		case 3: 
			ret_len += 2;//Ceil((6*1)/8)+1 
			break; 
		} 

		std::string result;
		result.reserve(ret_len); 

		while (tmp < (len - equal_count)) 
		{ 
			temp = 0; 
			prepare = 0; 
			memset(need, 0, sizeof(need)); 
			while (temp < 4) 
			{ 
				if (tmp >= (len - equal_count)) 
				{ 
					break; 
				} 
				prepare = (prepare << 6) | (find_pos(buf[tmp])); 
				temp++; 
				tmp++; 
			} 
			prepare = prepare << ((4-temp) * 6); 
			for (i=0; i<3 ;i++ ) 
			{ 
				if (i == temp) 
				{ 
					break; 
				} 
				result.append(1,(char)((prepare>>((2-i)*8)) & 0xFF)); 
			} 
		} 
		return result;
	}


	/**
	// 测试好用的base64算法
	*/
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	static inline bool is_base64(unsigned char c) {
		return (isalnum(c) || (c == '+') || (c == '/'));
	}

	extern std::string EncodeB64(char const* bytes_to_encode, unsigned int in_len) 
	{
		std::string ret;
		int i = 0;
		int j = 0;
		char char_array_3[3];
		char char_array_4[4];

		while (in_len--) {
			char_array_3[i++] = *(bytes_to_encode++);
			if (i == 3) {
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (i = 0; (i <4); i++)
					ret += base64_chars[char_array_4[i]];
				i = 0;
			}
		}

		if (i)
		{
			for (j = i; j < 3; j++)
				char_array_3[j] = '\0';

			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (j = 0; (j < i + 1); j++)
				ret += base64_chars[char_array_4[j]];

			while ((i++ < 3))
				ret += '=';

		}

		return ret;

	}

	extern std::string DecodeB64(std::string const& encoded_string) 
	{
		int in_len = encoded_string.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];
		std::string ret;

		while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
			char_array_4[i++] = encoded_string[in_]; in_++;
			if (i == 4) {
				for (i = 0; i <4; i++)
					char_array_4[i] = base64_chars.find(char_array_4[i]);

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (i = 0; (i < 3); i++)
					ret += char_array_3[i];
				i = 0;
			}
		}

		if (i) {
			for (j = i; j <4; j++)
				char_array_4[j] = 0;

			for (j = 0; j <4; j++)
				char_array_4[j] = base64_chars.find(char_array_4[j]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
		}

		return ret;
	}

}