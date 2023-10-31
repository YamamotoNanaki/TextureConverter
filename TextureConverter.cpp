#include "TextureConverter.h"
#include <windows.h>
#include <vector>
#include <iostream>

using namespace std;
using namespace DirectX;

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath, int32_t numOptions, char* options[])
{
	LoadWICTextureFromFile(filePath);

	SaveDDSTextureToFile(numOptions, options);
}

void TextureConverter::OutputUsage()
{
	cout << "�摜�t�@�C����WIC�`������DDS�`���ɕϊ����܂��B" << endl << endl;
	cout << "TextureConverter [�h���C�u:][�p�X][�t�@�C����]" << endl << endl;
	cout << "[�h���C�u:][�p�X][�t�@�C����]: �ϊ�������WIC�`���̉摜�t�@�C�����w�肵�܂��B" << endl << endl;
	cout << "[-ml level]: �~�b�v���x�����w�肵�܂��B0���w�肷���1�~1�܂ł̃t���~�b�v�}�b�v�`�F�[���𐶐����܂��B" << endl << endl;
}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	wstring wfilePath = StringToWString(filePath);

	auto hr = LoadFromWICFile(wfilePath.c_str(), WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(hr));

	SeparateFilePath(wfilePath);
}

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	wstring exceptExt;

	pos1 = filePath.rfind('.');

	if (pos1 != wstring::npos)
	{
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		exceptExt = filePath.substr(0, pos1);
	}
	else
	{
		fileExt_ = L"";
		exceptExt = filePath;
	}
	pos1 = exceptExt.rfind('\\');
	if (pos1 != wstring::npos)
	{
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	pos1 = exceptExt.rfind('/');
	if (pos1 != wstring::npos)
	{
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}
	directoryPath_ = L"";
	fileName_ = exceptExt;
}

void TextureConverter::SaveDDSTextureToFile(int32_t numOptions, char* options[])
{
	ScratchImage mipChain;

	size_t mipLevel = 0;
	for (size_t i = 0; i < numOptions; i++)
	{
		if (std::string(options[i]) == "-ml")
		{
			mipLevel = std::stoi(options[i + 1]);
			break;
		}
	}

	auto hr = GenerateMipMaps(scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(), TEX_FILTER_DEFAULT, mipLevel, mipChain);
	if (SUCCEEDED(hr))
	{
		scratchImage_ = std::move(mipChain);
		metadata_ = scratchImage_.GetMetadata();
	}

	ScratchImage converted;
	hr = Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT | TEX_COMPRESS_PARALLEL, 1.0f, converted);
	if (SUCCEEDED(hr))
	{
		scratchImage_ = std::move(converted);
		metadata_ = scratchImage_.GetMetadata();
	}

	metadata_.format = MakeSRGB(metadata_.format);

	wstring filePath = directoryPath_ + fileName_ + L".dds";

	hr = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(hr));
}

std::wstring TextureConverter::StringToWString(const std::string& mString)
{
	// SJIS �� wstring
	int32_t iBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str()
		, -1, (wchar_t*)NULL, 0);

	// �o�b�t�@�̎擾
	std::vector<wchar_t>buff;
	buff.resize(iBufferSize);

	// SJIS �� wstring
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, buff.data()
		, iBufferSize);

	// string�̐���
	std::wstring oRet(buff.data(), buff.data() + iBufferSize - 1);

	return(oRet);
}
