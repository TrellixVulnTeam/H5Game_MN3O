#ifndef _AC_STRING_H_
#define _AC_STRING_H_

#include "ACDef.h"
#include <string>
#include <vector>
#include <afxwin.h>

BEGIN_NS_AC

void SplitStlString( const std::string& strSrc ,std::vector<std::string>& vtDst ,char cSep );
CString StlStringToCString(const std::string& stlstr);
std::string CStringToStlString(const CString& cstr);

int ACAtoi(const char* sz);
double ACAtof(const char* sz);

void SplitCString(const CString& strSrc,std::vector<CString>& vtDst,const CString& cSep);
void JoinCString(CString& strDst,const std::vector<CString>& vtSrc,const CString& cSep);

END_NS_AC

#endif