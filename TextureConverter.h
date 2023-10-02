#pragma once
#include <string>

class TextureConverter
{
public:
	void ConvertTextureWICToDDS(const std::string& filePath);
private:
	void LoadWICTextureFromFile(const std::string& filePath);
	static std::wstring StringToWString(const std::string& mString);
};

