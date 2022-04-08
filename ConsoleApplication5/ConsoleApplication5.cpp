#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi")
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
#include <iostream>
#include <fstream>

#include <string>
std::wstring ContentTypeForExtension(const wchar_t* pszExtension)
{
	std::wstring s;

	HKEY hKey;
	if (RegOpenKeyW(HKEY_CLASSES_ROOT, pszExtension, &hKey) == ERROR_SUCCESS) {
		wchar_t szData[256];
		DWORD cbData = sizeof szData;
		if (RegQueryValueExW(hKey, L"Content Type", nullptr, nullptr, LPBYTE(szData), &cbData) == ERROR_SUCCESS) {
			s = szData;
		}
		RegCloseKey(hKey);
	}

	return s;
}
CLSID codec_for(LPCWSTR MimeType)
{
	UINT  num;        // number of image encoders
	UINT  size;       // size, in bytes, of the image encoder array
	Gdiplus::GetImageEncodersSize(&num, &size);
	const std::unique_ptr<Gdiplus::ImageCodecInfo> pImageCodecInfo{ reinterpret_cast<Gdiplus::ImageCodecInfo*>(new char[size]) };
	Gdiplus::GetImageEncoders(num, size, &*pImageCodecInfo);
	const auto end = &pImageCodecInfo.get()[num];
	const auto found = std::find_if(&*pImageCodecInfo, end, [MimeType](const Gdiplus::ImageCodecInfo& r)->bool
		{
			return lstrcmpW(r.MimeType, MimeType) == 0;
		});
	if (found == end)
		throw std::runtime_error("codec が見つかりませんでした。");
	else
		return found->Clsid;
}

#include "Stream.h"
#include <comip.h>
void test
( Gdiplus::Bitmap&& bmpSrc
, const CLSID& clsid
, std::ofstream&& file
)
{
	Gdiplus::Bitmap bmpDst(bmpSrc.GetWidth(), bmpSrc.GetHeight());
	bmpDst.SetResolution(bmpSrc.GetHorizontalResolution(), bmpSrc.GetVerticalResolution());
	Gdiplus::Graphics g(&bmpDst);
	g.DrawImage(&bmpSrc, 0, 0);

	_com_ptr_t<_com_IIID<IStream, &__uuidof(IStream)>> stm(Stream::New(std::move(file)), false);
	bmpDst.Save(stm, &clsid);
}

int main()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	try {
		const wchar_t output_filename[] = L"test.jpg";
		test
		( Gdiplus::Bitmap(LR"(V:\YouTube\Scenarios\2022\04\02\title.png)")
		, codec_for(ContentTypeForExtension(PathFindExtensionW(output_filename)).c_str())
		, std::ofstream(output_filename, std::ios_base::binary)
		);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
}
