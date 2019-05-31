#ifndef MD5_H
#define MD5_H

#include <string>
#include <fstream>

namespace pwutils
{
	/* Type define */
	typedef unsigned char md5byte;
	typedef unsigned int md5uint32;

	using std::string;
	using std::ifstream;

	/* MD5 declaration. */
	class MD5 {
	public:
		MD5();
		MD5(const void* input, size_t length);
		MD5(const string& str);
		MD5(ifstream& in);
		void update(const void* input, size_t length);
		void update(const string& str);
		void update(ifstream& in);
		const md5byte* digest();
		string toString();
		void reset();

	private:
		void update(const md5byte* input, size_t length);
		void final();
		void transform(const md5byte block[64]);
		void encode(const md5uint32* input, md5byte* output, size_t length);
		void decode(const md5byte* input, md5uint32* output, size_t length);
		string bytesToHexString(const md5byte* input, size_t length);

		/* class uncopyable */
		MD5(const MD5&);
		MD5& operator=(const MD5&);

	private:
		md5uint32 _state[4];	/* state (ABCD) */
		md5uint32 _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
		md5byte _buffer[64];	/* input buffer */
		md5byte _digest[16];	/* message digest */
		bool _finished;		/* calculate finished ? */

		static const md5byte PADDING[64];	/* padding for calculate */
		static const char HEX[16];
		enum { BUFFER_SIZE = 1024 };
	};

	extern std::string Md5(const std::string& msg);
}

#endif /*MD5_H*/
