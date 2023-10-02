#include <cstdint>
#include <iostream>
#include <DirectXTex.h>
#include <Windows.h>
#include "TextureConverter.h"

using namespace std;

enum Argument
{
	kApplicationPath,
	kFilePath,

	NumArgument
};

int32_t main(int32_t argc, char* argv[])
{
	for (uint32_t i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}

	assert(argc >= NumArgument);

	auto hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;

	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	CoUninitialize();

	system("pause");
	return 0;
}