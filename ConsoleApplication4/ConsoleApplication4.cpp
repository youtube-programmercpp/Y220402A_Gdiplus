#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi")
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
#include <iostream>

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

void test(LPCWSTR pszSourceImagePathName, LPCWSTR pszTargetImagePathNameW)
{
	const auto p = PathFindExtensionW(pszTargetImagePathNameW);
	const auto s = ContentTypeForExtension(p);
	const auto codec = codec_for(s.c_str());

	Gdiplus::Bitmap bmpSrc(pszSourceImagePathName);
	Gdiplus::Bitmap bmpDst(bmpSrc.GetWidth(), bmpSrc.GetHeight());
	bmpDst.SetResolution(bmpSrc.GetHorizontalResolution(), bmpSrc.GetVerticalResolution());
	Gdiplus::Graphics g(&bmpDst);
	g.DrawImage(&bmpSrc, 0, 0);
	bmpDst.Save(pszTargetImagePathNameW, &codec);
}

int main()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	try {
		test(LR"(V:\YouTube\Scenarios\2022\04\02\title.png)", L".\\test.bmp");
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
}
