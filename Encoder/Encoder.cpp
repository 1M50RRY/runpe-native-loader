// Encoder.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Encoder.h"


#include <Windows.h>
#include <winternl.h>
#include <iostream>
#include <string>
#include <fstream>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	FILE * file = fopen("in.exe", "rb");
	if (file == NULL) return 0;
	fseek(file, 0, SEEK_END);
	long int size = ftell(file);
	fclose(file);
	file = fopen("in.exe", "rb");
	unsigned char * in = (unsigned char *)malloc(size);
	int bytes_read = fread(in, sizeof(unsigned char), size, file);
	fclose(file);
	for (int i = 0; i < size; i++) {
		in[i] -= 0x56;
	}

	file = fopen("out.exe", "wb");
	int bytes_written = fwrite(in, sizeof(unsigned char), size, file);
	fclose(file);
	for (int i = 0; i < size; i++) {
		in[i] += 0x56;
	}
	file = fopen("decrypted.exe", "wb");
	bytes_written = fwrite(in, sizeof(unsigned char), size, file);
	fclose(file);
	return 0;
}

