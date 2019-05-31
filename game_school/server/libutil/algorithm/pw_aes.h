///////////////////////////////
// http://mingcn.cnblogs.com //
//  xelz CopyRight (c) 2010  //
///////////////////////////////


#ifndef _pw_aes_
#define _pw_aes_

namespace pwutils
{
	class AES  
	{
	public:
		AES(unsigned char* key);
		virtual ~AES();
		unsigned char* encrypt(unsigned char* input);
		unsigned char* decrypt(unsigned char* input);
		void* encrypt(void* input, int length=0);
		void* decrypt(void* input, int length);

	private:
		unsigned char Sbox[256];
		unsigned char InvSbox[256];
		unsigned char w[11][4][4];

		void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);
		unsigned char FFmul(unsigned char a, unsigned char b);

		void SubBytes(unsigned char state[][4]);
		void ShiftRows(unsigned char state[][4]);
		void MixColumns(unsigned char state[][4]);
		void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);

		void InvSubBytes(unsigned char state[][4]);
		void InvShiftRows(unsigned char state[][4]);
		void InvMixColumns(unsigned char state[][4]);
	};
}
#endif // _pw_aes_
