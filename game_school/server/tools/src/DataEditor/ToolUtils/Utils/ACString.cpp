#include "ACString.h"

BEGIN_NS_AC

void SplitStlString(const std::string& strSrc, std::vector<std::string>& vtDst, char cSep)
{
	if(strSrc.empty())
		return ;

	std::string::size_type spos = 0;
	std::string::size_type epos = 0;

	while((epos = strSrc.find_first_of(cSep, spos)) != std::string::npos)
	{
		std::string strTemp = strSrc.substr(spos, epos - spos);

		vtDst.push_back(strTemp);
		spos = epos + 1;
	}    

	vtDst.push_back(&strSrc[spos]);
};

CString StlStringToCString(const std::string& stlstr)
{
	int nLength = stlstr.length();
	TCHAR* pszBuffer = new TCHAR[nLength + 1];
	mbstowcs(pszBuffer, stlstr.c_str(), nLength + 1);
	CString cstr = pszBuffer;
	delete[] pszBuffer;
	return cstr;
}

std::string CStringToStlString(const CString& cstr)
{
	int nLength = wcslen(cstr.GetString()) * 2;
	char* pszBuffer = new char[nLength + 1];
	wcstombs(pszBuffer, cstr.GetString(), nLength + 1);
	std::string stlstr = pszBuffer;
	delete[] pszBuffer;
	return stlstr;
}

int ACAtoi(const char* sz)
{
	if(sz == NULL)
	{
		CString strErr = StlStringToCString(sz);
		ErrorMessageBox(strErr);
		return -1;
	}

	const char* pStr = sz;
	if(*pStr == '-' || *pStr == '+')
		pStr++;

	while(*pStr != '\0')
	{
		if(*pStr < '0' || *pStr > '9')
		{
			CString strErr = StlStringToCString(sz);
			ErrorMessageBox(strErr);
			return -1;
		}

		pStr++;
	}

	return atoi(sz);
}

double ACAtof(const char* sz)
{
	return atof(sz);
}

void SplitCString(const CString& strSrc,std::vector<CString>& vtDst,const CString& cSep)
{
	CString str;
	int nPos = 0;
	//数组通过,隔开
	str = strSrc.Tokenize(cSep,nPos);
	while (str != _T(""))
	{
		vtDst.push_back(str);
		str = strSrc.Tokenize(cSep, nPos);
	};
}

void JoinCString(CString& strDst,const std::vector<CString>& vtSrc,const CString& cSep)
{
	bool bFirst = true;
	strDst = _T("");
	for(size_t i = 0; i < vtSrc.size(); ++i)
	{
		if(bFirst)
		{
			bFirst = false;
		}
		else
		{
			strDst.Append(cSep);
		}

		strDst.Append(vtSrc[i]);
	}
}

END_NS_AC