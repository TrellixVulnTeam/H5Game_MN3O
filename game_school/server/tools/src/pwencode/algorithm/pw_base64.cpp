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
}