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
	//コマンドライン引数指定なし
	if (argc < NumArgument)
	{
		//使い方表示
		TextureConverter::OutputUsage();
		return 0;
	}


	for (uint32_t i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}

	assert(argc >= NumArgument);

	auto hr = CoInitializeEx(nullptr,COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;

	int32_t numOptions = argc - NumArgument;
	char** options = argv + NumArgument;

	converter.ConvertTextureWICToDDS(argv[kFilePath], numOptions, options);

	CoUninitialize();

	return 0;
}