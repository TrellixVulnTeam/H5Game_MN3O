#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include <iconv.h>

#ifdef _WIN32
#include <windows.h>

void ShowErrorMessage(DWORD error)
{
	LPVOID lpMsgBuf;
	FormatMessage(
	    FORMAT_MESSAGE_ALLOCATE_BUFFER |
	    FORMAT_MESSAGE_FROM_SYSTEM |
	    FORMAT_MESSAGE_IGNORE_INSERTS,
	    NULL,
	    error, // GetLastError(),
	    0, // Default language
	    (LPTSTR) &lpMsgBuf,
	    0,
	    NULL
	);

	MessageBoxA( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );

	LocalFree( lpMsgBuf );
}

void FindFileInDir(const char* _path,std::vector<std::string>& files,const char* spec = "")
{
	char path[256] = "";
	char findpath[256] = "";
	char* part = NULL;

	::GetFullPathNameA(_path,sizeof(path)/sizeof(path[0]),path,&part);

	size_t n = strlen(path);
	if(path[n-1] != '\\')
		strcat(path,"\\");

	sprintf(findpath,"%s\\*.*",path);

	WIN32_FIND_DATA data = {0};
	HANDLE hFind = ::FindFirstFile(findpath,&data);
	if(hFind == INVALID_HANDLE_VALUE) {
		ShowErrorMessage(GetLastError());
		return ;
	}

	do {
		if(!strcmp(data.cFileName,".") || !strcmp(data.cFileName,".."))
			continue;

		char file[256];
		sprintf(file,"%s%s",path,data.cFileName);

		if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			FindFileInDir(file,files,spec);
		} else if(strcmp(spec,"") == 0 || strstr(data.cFileName,spec) != NULL) {
			files.push_back(file);
		}

	} while(FindNextFile(hFind,&data));

	FindClose(hFind);
}
#else
#include <sys/types.h>
#include <dirent.h>

void FindFileInDir(const char* path,std::vector<std::string>& files,const char* spec = "")
{
	DIR* dir = opendir(path);
	while(dirent* d = readdir(dir)) {
		if(!strcmp(d->d_name,".") || !strcmp(d->d_name,".."))
			continue;

		char file[256];
		sprintf(file,"%s/%s",path,d->d_name);

		if(d->d_type == DT_DIR) {
			FindFileInDir(file,files,spec);
		} else if(d->d_type == DT_REG) {
			if(strcmp(spec,"") == 0 || strstr(d->d_name,spec) != NULL)
				files.push_back(file);
		}
	}
	
	closedir(dir);
}
#endif


int ConvertUtf8Nbom2Utf8(const char* filename,const char* targetfile)
{
	FILE* rf = fopen(filename,"r");
	if(rf == NULL)
		return -1;

	fseek(rf,0,SEEK_END);
	int size = ftell(rf);
	fseek(rf,0,SEEK_SET);

	char* buf1 = new char[size];
	memset(buf1,0,size);
//	char* buf2 = new char[size * 2];

	fread(buf1,size,1,rf);

	fclose(rf);

	char bom[3] = {239,187,191};
	if(memcmp(bom,buf1,3) != 0) {
		FILE* wf = fopen(targetfile,"w");
		if(wf != NULL) {
			fwrite(bom,3,1,wf);
			fwrite(buf1,size,1,wf);
			fclose(wf);
		}
	} else {
		printf("error input to utf8: %s\n",filename);
	}
	delete [] buf1;
//	delete [] buf2;

	return 0;
}

int ConvertUtf82Utf8Nbom(const char* filename,const char* targetfile)
{
	FILE* rf = fopen(filename,"r");
	if(rf == NULL)
		return -1;

	fseek(rf,0,SEEK_END);
	int size = ftell(rf);
	fseek(rf,0,SEEK_SET);

	char* buf1 = new char[size];
//	char* buf2 = new char[size * 2];

	fread(buf1,size,1,rf);

	fclose(rf);

	char bom[3] = {239,187,191};

	if(memcmp(bom,buf1,3) == 0) {
		FILE* wf = fopen(targetfile,"w");
		if(wf != NULL) {
			fwrite(&buf1[3],size - 3,1,wf);
			fclose(wf);
		}
	} else {
		printf("error input to utf8-nobom: %s\n",filename);
	}
	delete [] buf1;
//	delete [] buf2;

	return 0;
}

int ConvertUtf8Nbom2Utf8_Directory(const char* directory,const char* spec)
{
	std::vector<std::string> files;
	FindFileInDir(directory,files,spec);
	for(size_t i = 0; i < files.size(); ++i) {
		ConvertUtf8Nbom2Utf8(files[i].c_str(),files[i].c_str());
	}
	return 0;
}

int ConvertUtf82Utf8Nbom_Directory(const char* directory,const char* spec)
{
	std::vector<std::string> files;
	FindFileInDir(directory,files,spec);
	for(size_t i = 0; i < files.size(); ++i) {
		ConvertUtf82Utf8Nbom(files[i].c_str(),files[i].c_str());
	}
	return 0;
}

int main(int argc, char **argv)
{
	for(int i = 1; i < argc; ++i)
		printf("args(%d) = %s\n",i,argv[i]);

	if(argc == 4) {
		if(strcmp(argv[3],"bom") == 0)
			ConvertUtf8Nbom2Utf8_Directory(argv[1],argv[2]);
		else if(strcmp(argv[3],"nobom") == 0)
			ConvertUtf82Utf8Nbom_Directory(argv[1],argv[2]);
		else if(strcmp(argv[3],"list") == 0) {
			std::vector<std::string> files;
			FindFileInDir(argv[1],files,argv[2]);
			for(size_t i = 0; i < files.size(); ++i)
				printf("%s\n",files[i].c_str());
		} else
			return 2;
		return 0;
	}
	return 1;
}
