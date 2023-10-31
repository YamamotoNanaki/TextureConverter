#pragma once
#include <string>
#include <DirectXTex.h>

class TextureConverter
{
public:
	void ConvertTextureWICToDDS(const std::string& filePath, int32_t numOptions = 0, char* options[] = nullptr);
	static void OutputUsage();
private:
	void LoadWICTextureFromFile(const std::string& filePath);
	void SeparateFilePath(const std::wstring& filePath);
	void SaveDDSTextureToFile(int32_t numOptions, char* options[]);
	static std::wstring StringToWString(const std::string& mString);

private:
	DirectX::TexMetadata metadata_;
	DirectX::ScratchImage scratchImage_;
	std::wstring directoryPath_;
	std::wstring fileName_;
	std::wstring fileExt_;
};

