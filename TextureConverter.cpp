#include "TextureConverter.h"
#include <windows.h>
#include <vector>
#include <DirectXTex.h>

using namespace std;
using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{
	LoadWICTextureFromFile(filePath);
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	wstring wfilePath = StringToWString(filePath);


}

std::wstring TextureConverter::StringToWString(const std::string& mString)
{
	// SJIS → wstring
	int32_t iBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str()
		, -1, (wchar_t*)NULL, 0);

	// バッファの取得
	std::vector<wchar_t>buff;
	buff.resize(iBufferSize);

	// SJIS → wstring
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, buff.data()
		, iBufferSize);

	// stringの生成
	std::wstring oRet(buff.data(), buff.data() + iBufferSize - 1);

	return(oRet);
}
