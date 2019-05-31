
// gen_csvDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "gen_csv.h"
#include "gen_csvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const size_t cst_RowForChineseName = 0;
const size_t cst_RowForName = 1;
const size_t cst_RowForType = 2;
const size_t cst_RowForSide = 3;
const size_t cst_RowForData = cst_RowForSide + 1;

// CGenCsvDlg 对话框


void FindFileInDir(const char* _path,std::vector<std::string>& files,const char* spec = "")
{
	char path[256] = "";
	char findpath[256] = "";
	char* part = NULL;

	::GetFullPathNameA(_path,sizeof(path)/sizeof(path[0]),path,&part);

	size_t n = strlen(path);
	if(path[n-1] != '\\')
		strcat(path,"\\");

	sprintf_s(findpath,"%s\\*.*",path);

	WIN32_FIND_DATA data = {0};
	HANDLE hFind = ::FindFirstFile(findpath,&data);
	if(hFind == INVALID_HANDLE_VALUE) {
		return ;
	}

	do {
		if(!strcmp(data.cFileName,".") || !strcmp(data.cFileName,".."))
			continue;

		char file[256];
		sprintf_s(file,"%s%s",path,data.cFileName);

		if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			FindFileInDir(file,files,spec);
		} else if(strcmp(spec,"") == 0 || strstr(data.cFileName,spec) != NULL) {
			files.push_back(file);
		}

	} while(FindNextFile(hFind,&data));

	FindClose(hFind);
}



CGenCsvDlg::CGenCsvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGenCsvDlg::IDD, pParent)
{

	//m_strServerDir = "E:\\workspace\\pwngs\\server";
	::GetPrivateProfileString("ServerPathInfo","Path","E:\\workspace\\pwngs\\server",m_strServerDir.GetBuffer(MAX_PATH),MAX_PATH,".\\gen_csv.ini");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGenCsvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_strServerDir);
	DDX_Control(pDX, IDC_LIST1, m_ctrlLogs);
}

BEGIN_MESSAGE_MAP(CGenCsvDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CGenCsvDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGenCsvDlg 消息处理程序

BOOL CGenCsvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGenCsvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGenCsvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void GetStringFromCellRaw(BasicExcelWorksheet* sheet,size_t row,size_t col,char* outbuf,size_t outlen)
{
	BasicExcelCell* cell = sheet->Cell(row,col);
	ASSERT(cell);

	memset(outbuf,0,outlen);
	switch(cell->Type())
	{
	case BasicExcelCell::STRING:
		{
			strncpy(outbuf,cell->GetString(),outlen);
		}
		break;
	case BasicExcelCell::WSTRING:
		{
			const wchar_t* str = cell->GetWString();
			size_t len = wcslen(str);
			::WideCharToMultiByte(CP_ACP,0,str,len,outbuf,outlen,NULL,NULL);
		}
		break;
	case BasicExcelCell::DOUBLE:
		{
			sprintf_s(outbuf,outlen,"%f",(float)cell->GetDouble());			
		}
		break;
	case BasicExcelCell::INT:
		{
			sprintf_s(outbuf,outlen,"%f",(float)cell->GetInteger());			
		}
		break;
	case BasicExcelCell::UNDEFINED:
		return ;
	}

	size_t slen  = strlen(outbuf);
	for(size_t i = 0; i < slen; ++i)
	{
		if(outbuf[i] == '\n' || outbuf[i] == '\r')
			outbuf[i] = ' ';
	}
}

void GetStringFromCell(BasicExcelWorksheet* sheet,size_t row,size_t col,char* outbuf,size_t outlen)
{
	BasicExcelCell* cell = sheet->Cell(row,col);
	ASSERT(cell);

	memset(outbuf,0,outlen);
	switch(cell->Type())
	{
	case BasicExcelCell::STRING:
		{
			strncpy(outbuf,cell->GetString(),outlen);
		}
		break;
	case BasicExcelCell::WSTRING:
		{
			const wchar_t* str = cell->GetWString();
			size_t len = wcslen(str);
			::WideCharToMultiByte(CP_ACP,0,str,len,outbuf,outlen,NULL,NULL);
		}
		break;
	case BasicExcelCell::DOUBLE:
		{
			char type[256] = "";

			GetStringFromCell(sheet,cst_RowForType,col,type,_countof(type));

			if(stricmp(type,"int") == 0 || stricmp(type,"long") == 0)
				sprintf_s(outbuf,outlen,"%I64d",(__int64)cell->GetDouble());
			else if(stricmp(type,"float") == 0 || stricmp(type,"double") == 0)
				sprintf_s(outbuf,outlen,"%f",cell->GetDouble());
			else if(stricmp(type,"bool") == 0)
				sprintf_s(outbuf,outlen,"%d",((int)cell->GetDouble()) == 1);
			else if(stricmp(type,"string") == 0)
				sprintf_s(outbuf,outlen,"%f",(float)cell->GetDouble());
			else if(stricmp(type,"int[]") == 0)
				sprintf_s(outbuf,outlen,"%d",(int)cell->GetDouble());
			else if(stricmp(type,"float[]") == 0 
				|| stricmp(type,"string[]") == 0)
			{
				sprintf_s(outbuf,outlen,"%f",(float)cell->GetDouble());			
			}
			else
			{
				::AfxGetMainWnd()->MessageBox(type,"Error Type");
				ASSERT(false);
			}
		}
		break;
	case BasicExcelCell::INT:
		{
			char type[256] = "";

			GetStringFromCell(sheet,cst_RowForType,col,type,_countof(type));

			if(stricmp(type,"int") == 0 || stricmp(type,"long") == 0)
				sprintf_s(outbuf,outlen,"%d",(__int64)cell->GetInteger());
			else if(stricmp(type,"float") == 0 || stricmp(type,"double") == 0)
				sprintf_s(outbuf,outlen,"%d",cell->GetInteger());
			else if(stricmp(type,"bool") == 0)
				sprintf_s(outbuf,outlen,"%d",((int)cell->GetInteger()) == 1);
			else if(stricmp(type,"string") == 0)
				sprintf_s(outbuf,outlen,"%d",(float)cell->GetInteger());
			else if( stricmp(type,"int[]") == 0)
				sprintf_s(outbuf,outlen,"%d",(int)cell->GetDouble());
			else if(stricmp(type,"float[]") == 0 
				|| stricmp(type,"string[]") == 0)
			{
				sprintf_s(outbuf,outlen,"%f",(float)cell->GetInteger());			
			}
			else
			{
				::AfxGetMainWnd()->MessageBox(type,"Error Type");
				ASSERT(false);
			}
		}
		break;
	case BasicExcelCell::UNDEFINED:
		return ;
	}

	size_t slen  = strlen(outbuf);
	for(size_t i = 0; i < slen; ++i)
	{
		if(outbuf[i] == '\n' || outbuf[i] == '\r')
			outbuf[i] = ' ';
	}
}

const char* GetStringFromCell(BasicExcelWorksheet* sheet,size_t row,size_t col)
{
	static char s_buf[256] = "";
	GetStringFromCell(sheet,row,col,s_buf,_countof(s_buf));
	return s_buf;
}


void CGenCsvDlg::OnBnClickedButton1()
{

	this->UpdateData();

	CString strSearchDir;
	CString strCppsDir;
	CString strCsvsDir;

	if(m_strServerDir.GetLength() <= 0 || m_strServerDir.GetLength() <= 0)
	{
		this->MessageBox("Invalid Input");
		return ;
	}

	if(m_strServerDir.GetAt(m_strServerDir.GetLength() - 1) != '\\')
		m_strServerDir = m_strServerDir + "\\";

	strSearchDir = m_strServerDir + "..\\shared\\config\\";
	strCppsDir = m_strServerDir + "pwworldsrv\\conf\\";
	strCsvsDir = m_strServerDir + "bin\\data\\csv\\";

	this->UpdateData(FALSE);

	std::vector<std::string> files;

	FindFileInDir(strSearchDir,files,".xls");

	std::string cppdir(strCppsDir);
	std::string csvdir(strCsvsDir);

	while(m_ctrlLogs.GetCount() > 0)
		m_ctrlLogs.DeleteString(m_ctrlLogs.GetCount() - 1);

	for(size_t i = 0; i < files.size(); ++i)
	{
		std::string& file = files[i];
		const char* _name = PathFindFileNameA(file.c_str());
		const char* extension = PathFindExtension(file.c_str());
		std::string name;
		if(strstr(_name,"Config") != NULL)
			name = std::string(_name,extension - _name - strlen("config"));
		else
			name = std::string(_name,extension - _name);

		std::string hppfile = cppdir + "pwconf_" + name + ".h";
		std::string cppfile = cppdir + "pwconf_" + name + ".cpp";

		const char* __name = name.c_str();

		OutputDebugStringA(name.c_str());
		OutputDebugStringA("\r\n");
		Generate(name,files[i],hppfile,cppfile,csvdir + "pwconf_" + name + ".csv");

		std::string log = std::string("Generated : ") + file;
		m_ctrlLogs.InsertString(-1,log.c_str());
	}
	m_ctrlLogs.InsertString(-1,"Generate Completed.");

	::WritePrivateProfileString("ServerPathInfo","Path",m_strServerDir,".\\gen_csv.ini");
}

void CGenCsvDlg::Generate(const std::string& name,const std::string& file,const std::string& hpp_file,const std::string& cpp_file,const std::string& csv_file)
{
	DeleteFile(csv_file.c_str());

	CFile stream(csv_file.c_str(),CFile::modeCreate | CFile::modeWrite);

	BasicExcel excel;

	if(!excel.Load(file.c_str()))
	{
		std::string error = std::string("Error Open File:") + file;
		this->m_ctrlLogs.InsertString(-1,error.c_str());
		return ;
	}

// 	ASSERT(excel.GetTotalWorkSheets() > 0);

// 	char name[256] = "";
// 	excel.GetWorksheet((size_t)0)->GetSheetName(name);

	for(size_t i = 0; i < excel.GetTotalWorkSheets(); ++i)
	{
		BasicExcelWorksheet* sheet = excel.GetWorksheet(i);

		if(i == 0)
		{
			this->GenerateCsvHeader(sheet,stream);

			DWORD attr1 = GetFileAttributesA(hpp_file.c_str());
			DWORD attr2 = GetFileAttributesA(hpp_file.c_str());

			if(attr1 != 0xFFFFFFFF && attr2 != 0xFFFFFFFF)
			{
				std::string log = std::string("Ignore generate(Hpp,Cpp): ") + name;
				m_ctrlLogs.InsertString(-1,log.c_str());
			}
			else
			{
				this->GenerateHpp(sheet,hpp_file,name);
				this->GenerateCpp(sheet,cpp_file,name);
			}
		}

		this->GenerateCsv(sheet,stream);
	}
}

#define W2F(tabcount,sprintf_params) \
	{ \
		for(int i = 0; i < tabcount; ++i) \
		stream.Write("\t",1); \
		sprintf_s sprintf_params;\
		stream.Write(buf,strlen(buf)); \
	}

void CGenCsvDlg::GenerateHpp(BasicExcelWorksheet* sheet,const std::string& hpp_file,const std::string& name)
{
	char buf[10240] = "";

	char classname[256] = "";
	sprintf_s(classname,"%s",name.c_str());

	const char* filename = PathFindFileName(hpp_file.c_str());

	char structname[256] = "";
	sprintf_s(structname,"S%s",name.c_str());

	DeleteFile(hpp_file.c_str());

	CFile stream(hpp_file.c_str(),CFile::modeCreate | CFile::modeWrite);

	W2F(0,(buf,"#ifndef _config_%s_included_\r\n",name.c_str()))
	W2F(0,(buf,"#define _config_%s_included_\r\n",name.c_str()))
	W2F(0,(buf,"\r\n"))
	W2F(0,(buf,"#include \"pw_def.h\"\r\n"))
// 	W2F(0,(buf,"#include <string>\r\n"))
// 	W2F(0,(buf,"#include <vector>\r\n"))
	W2F(0,(buf,"\r\n"))

	W2F(0,(buf,"namespace pwconf\r\n"));
	W2F(0,(buf,"{\r\n"))
	W2F(0,(buf,"\r\n"))
		W2F(1,(buf,"struct %s\r\n",structname))
		W2F(1,(buf,"{\r\n"))
			for(size_t i = 0; i < sheet->GetTotalCols(); ++i)
			{
				char colname[256] = "";
				char typname[256] = "";
				char cnname[256] = "";
				
				GetStringFromCell(sheet,cst_RowForName,i,colname,_countof(colname));
				GetStringFromCell(sheet,cst_RowForType,i,typname,_countof(typname));
				GetStringFromCell(sheet,cst_RowForChineseName,i,cnname,_countof(cnname));

// 				colname[0] = ::tolower(colname[0]);

				if(stricmp(typname,"int") == 0)
					W2F(2,(buf,"int32 %s;\t// %s\r\n",colname,cnname))
				else if(stricmp(typname,"long") == 0)
					W2F(2,(buf,"int64 %s;\t// %s\r\n",colname,cnname))
				else if(stricmp(typname,"float") == 0)
					W2F(2,(buf,"float %s;\t// %s\r\n",colname,cnname))
				else if(stricmp(typname,"double") == 0)
					W2F(2,(buf,"double %s;\t// %s\r\n",colname,cnname))
				else if(stricmp(typname,"string") == 0)
					W2F(2,(buf,"std::string %s;\t// %s\r\n",colname,cnname))
				else if(stricmp(typname,"bool") == 0)
					W2F(2,(buf,"bool %s;\t// %s\r\n",colname,cnname))
				else if(stricmp(typname,"string[]") == 0)
					W2F(2,(buf,"std::vector<std::string> %s;\t// %s\r\n",colname,cnname))
				else if(stricmp(typname,"float[]") == 0)
					W2F(2,(buf,"std::vector<float> %s;\t// %s\r\n",colname,cnname))
				else if(stricmp(typname,"int[]") == 0)
					W2F(2,(buf,"std::vector<int32> %s;\t// %s\r\n",colname,cnname))
				else if(stricmp(typname,"") == 0)
					continue;
				else
					ASSERT(false && "invalid_configure");
			}
		W2F(1,(buf,"};\r\n"));
		W2F(1,(buf,"\r\n"))

		char datestr[100] = "";
		time_t tt;
		time(&tt);
		struct tm* _tm = localtime(&tt);
		sprintf_s(datestr,"%d-%d-%d %d:%d:%d",_tm->tm_year + 1900,_tm->tm_mon + 1,_tm->tm_mday,_tm->tm_hour,_tm->tm_min,_tm->tm_sec);

		const char cls_comment_fmt[] = \
"\
/* \r\n\
	@class %s \r\n\
	@author tool GenCSV\r\n\
	@date %s\r\n\
	@file %s\r\n\
	@brief 从%s文件中自动生成的配置类\r\n\
	*/ \r\n\
";

		W2F(1,(buf,cls_comment_fmt,classname,datestr,filename,name.c_str()))

		W2F(1,(buf,"class %s\r\n",classname))
		W2F(1,(buf,"{\r\n"))
			W2F(1,(buf,"public:\r\n"))
				W2F(2,(buf,"bool LoadFrom(const char* filename);\r\n"))
				// LoadFrom
				W2F(2,(buf,"bool LoadFrom(const std::string& filename)\r\n"))
				W2F(2,(buf,"{\r\n"))
					W2F(3,(buf,"return LoadFrom(filename.c_str());\r\n"))
				W2F(2,(buf,"}\r\n"))

			W2F(1,(buf,"public:\r\n"))
				W2F(2,(buf,"%s& Get(size_t);\r\n",structname))
			W2F(1,(buf,"public:\r\n"))
				W2F(2,(buf,"inline size_t Count()\r\n"))
				W2F(2,(buf,"{\r\n"))
					W2F(3,(buf,"return m_vtConfigures.size();\r\n"))
				W2F(2,(buf,"}\r\n"))
			W2F(1,(buf,"private:\r\n"))
				W2F(2,(buf,"typedef std::vector<%s> CollectionConfiguresT;\r\n",structname))
			W2F(1,(buf,"private:\r\n"))
				W2F(2,(buf,"CollectionConfiguresT m_vtConfigures;\r\n",structname))
		W2F(1,(buf,"};\r\n"))
	W2F(0,(buf,"}\r\n"))

	W2F(0,(buf,"#endif // _config_%s_included_\r\n",name.c_str()))
}

void CGenCsvDlg::GenerateCpp(BasicExcelWorksheet* sheet,const std::string& cpp_file,const std::string& name)
{
	char buf[10240] = "";

	char classname[256] = "";
	sprintf_s(classname,"%s",name.c_str());

	char structname[256] = "";
	sprintf_s(structname,"S%s",name.c_str());

	DeleteFile(cpp_file.c_str());

	CFile stream(cpp_file.c_str(),CFile::modeCreate | CFile::modeWrite);

	W2F(0,(buf,"#include \"pwconf_%s.h\"\r\n",name.c_str()))
	W2F(0,(buf,"#include \"pw_csv.h\"\r\n"))
	W2F(0,(buf,"#include \"tokenizer.h\"\r\n"))
	W2F(0,(buf,"#include \"pw_utils.h\"\r\n"))
	W2F(0,(buf,"#include \"pw_logger.h\"\r\n"))
	W2F(0,(buf,"\r\n"))

	W2F(0,(buf,"namespace pwconf\r\n"));

	W2F(0,(buf,"{\r\n"))
			
		// LoadFrom
		W2F(1,(buf,"bool %s::LoadFrom(const char* filename)\r\n",classname))
		W2F(1,(buf,"{\r\n"))
			W2F(2,(buf,"pwutils::CSVReader csv;\r\n"))
			W2F(2,(buf,"if(csv.load(filename) != 0)\r\n"))
				W2F(3,(buf,"return false;\r\n"))
			for(size_t col = 0; col < sheet->GetTotalCols(); ++col)
			{
				char colname[256] = "";
				char cnname[256] = "";

				GetStringFromCell(sheet,cst_RowForName,col,colname,_countof(colname));
				GetStringFromCell(sheet,cst_RowForChineseName,col,cnname,_countof(cnname));
				if(stricmp(colname,"") == 0 || stricmp(cnname,"") == 0)
					continue;

// 				colname[0] = ::tolower(colname[0]);

				W2F(2,(buf,"size_t index_%s = csv.index(\"%s\",%d);\r\n", colname, colname,cst_RowForName));
				W2F(2,(buf,"pwassertn(index_%s != (size_t)-1);\r\n", colname));
				W2F(2,(buf,"\r\n"));
			}

			W2F(2,(buf,"\r\n"))
			W2F(2,(buf,"for(size_t row = %d; row < csv.count(); ++row)\r\n",cst_RowForData - 1));
			W2F(2,(buf,"{\r\n"));
				W2F(3,(buf,"%s conf;\r\n",structname));
				for(size_t col = 0; col < sheet->GetTotalCols(); ++col)
				{
					char colname[256] = "";
					char typname[256] = "";

					GetStringFromCell(sheet,cst_RowForName,col,colname,_countof(colname));
					GetStringFromCell(sheet,cst_RowForType,col,typname,_countof(typname));

					if(stricmp(colname,"") == 0 || stricmp(typname,"") == 0)
						continue;

// 					colname[0] = ::tolower(colname[0]);

					if(stricmp(typname,"int") == 0)
						W2F(3,(buf,"conf.%s = csv.get_i32(row,index_%s);\r\n",colname,colname))
					else if(stricmp(typname,"long") == 0)
						W2F(3,(buf,"conf.%s = csv.get_i64(row,index_%s);\r\n",colname,colname))
					else if(stricmp(typname,"float") == 0)
						W2F(3,(buf,"conf.%s = (float)csv.get_dec(row,index_%s);\r\n",colname,colname))
					else if(stricmp(typname,"double") == 0)
						W2F(3,(buf,"conf.%s = csv.get_dec(row,index_%s);\r\n",colname,colname))
					else if(stricmp(typname,"string") == 0)
						W2F(3,(buf,"conf.%s = csv.get_str(row,index_%s);\r\n",colname,colname))
					else if(stricmp(typname,"bool") == 0)
						W2F(3,(buf,"conf.%s = csv.get_bool(row,index_%s);\r\n",colname,colname))
					else if(stricmp(typname,"string[]") == 0)
					{
						W2F(3,(buf,"{\r\n"));
							W2F(4,(buf,"const char* __tmp = csv.get_str(row,index_%s);\r\n",colname))
							W2F(4,(buf,"tokenize(__tmp,conf.%s,\"\,\",\"\",\"\\\"\");;\r\n",colname))
						W2F(3,(buf,"}\r\n"));
					}
					else if(stricmp(typname,"float[]") == 0)
					{
						W2F(3,(buf,"{\r\n"));
							W2F(4,(buf,"std::vector<std::string> vals;\r\n"))
							W2F(4,(buf,"const char* __tmp = csv.get_str(row,index_%s);\r\n",colname))
							W2F(4,(buf,"tokenize(__tmp,vals,\"\,\",\"\",\"\\\"\");;\r\n"))
							W2F(4,(buf,"for(size_t i = 0; i < vals.size(); ++i)\r\n"))
								W2F(5,(buf,"conf.%s.push_back(pwutils::atof(vals[i].c_str()));\r\n",colname))
						W2F(3,(buf,"}\r\n"));
					}
					else if(stricmp(typname,"int[]") == 0)
					{
						W2F(3,(buf,"{\r\n"));
						W2F(4,(buf,"std::vector<std::string> vals;\r\n"))
							W2F(4,(buf,"const char* __tmp = csv.get_str(row,index_%s);\r\n",colname))
							W2F(4,(buf,"tokenize(__tmp,vals,\"\,\",\"\",\"\\\"\");;\r\n"))
							W2F(4,(buf,"for(size_t i = 0; i < vals.size(); ++i)\r\n"))
							W2F(5,(buf,"conf.%s.push_back(pwutils::atoi(vals[i].c_str()));\r\n",colname))
							W2F(3,(buf,"}\r\n"));
					}
				}
				W2F(3,(buf,"m_vtConfigures.push_back(conf);\r\n"))
			W2F(2,(buf,"}\r\n"))
			W2F(2,(buf,"return true;\r\n"))
		W2F(1,(buf,"}\r\n"))

		W2F(1,(buf,"\r\n"))
		// Get
		W2F(1,(buf,"%s& %s::Get(size_t row)\r\n",structname,classname))
		W2F(1,(buf,"{\r\n"))
			W2F(2,(buf,"return m_vtConfigures.at(row);\r\n"))
		W2F(1,(buf,"}\r\n"))

	W2F(0,(buf,"}\r\n"))
}


void CGenCsvDlg::GenerateCsvHeader(BasicExcelWorksheet* sheet,CFile& csvfile)
{
	size_t cols = sheet->GetTotalCols();
	size_t rows = sheet->GetTotalRows();

	ASSERT(rows > cst_RowForSide);

	for(size_t row = 0; row < cst_RowForData; ++row)
	{
		CString line = "";
		for(size_t col = 0; col < cols; ++col)
			line = line + "\"" + GetStringFromCell(sheet,row,col) + "\"\t";
		line = line + "\n";
		csvfile.Write(line,line.GetLength());
	}
}

void CGenCsvDlg::GenerateCsv(BasicExcelWorksheet* sheet,CFile& csvfile)
{
	size_t cols = sheet->GetTotalCols();
	size_t rows = sheet->GetTotalRows();

	for(size_t row = cst_RowForData; row < rows; ++row)
	{
		bool allempty = true;
		CString line = "";
		for(size_t col = 0; col < cols; ++col)
		{
			const char* str = GetStringFromCell(sheet,row,col);
			if(stricmp(str,"") != 0)
				allempty = false;
			else
				printf("111");
			line = line + "\"" +  str + "\"\t";
		}
		line = line + "\n";
		if(!allempty)
			csvfile.Write(line,line.GetLength());
	}
}