#include <stdio.h>
#include <stdlib.h>
#include <Shlwapi.h>
#include "base64.h"

#pragma comment(lib,"shlwapi.lib")

int SaveToFile(const std::string & strData,bool bEncode)
{
	if (strData.empty())
	{
		printf("No File OutPut! \n");
		return -1;
	}
	
	const wchar_t* pFileName = NULL;
	if (bEncode)
	{
		pFileName = L"base64_encode.dat";
	}
	else
	{
		pFileName = L"base64_decode.dat";
	}
	FILE* pFile = _wfopen(pFileName,L"wb");
	if (pFile)
	{
		fwrite(strData.c_str(),1,strData.length(),pFile);
		fclose(pFile);
		return 0;
	}
	return -1;
}

int main(int agrc,char* agrv[])
{
	char* pAgr0 = agrv[0];
	char* pAgr1 = agrv[1];
	char* pAgr2 = agrv[2];
	char* pAgr3 = agrv[3];

	if (agrc <1)
	{
		wprintf(L"No argv,Exit \n");
		return 0;
	}
	
	FILE* pFile = fopen(agrv[1],"rb");
	if (pFile == NULL)
	{
		wprintf(L"Open %s  failed! \n",agrv[0]);
		return -1;
	}

	fseek(pFile, 0, SEEK_END);
	long nLen = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	// 预留100空间作为越界保护
	char * pbuf = (char*)malloc(nLen + 100);
	memset(pbuf, 0, nLen + 100);
	nLen = fread(pbuf, 1, nLen, pFile);
	fclose(pFile);

	if(StrStrIW((LPCWSTR)agrv[2],L"en"))
	{
		std::string result = base64_encode(pbuf,nLen);
		SaveToFile(result,true);
	}
	else
	{
		std::string strIn;
		strIn.append(pbuf,nLen);
		std::string result = base64_decode(strIn);
		SaveToFile(result,false);
	}
	free(pbuf);
	return 0;
}
