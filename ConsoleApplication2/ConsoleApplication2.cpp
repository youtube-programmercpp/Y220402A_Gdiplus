#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
#include <memory>
#include <algorithm>
#include <stdexcept>
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
#include <iostream>
void test()
{
	Gdiplus::Image image(LR"(V:\YouTube\Scenarios\2022\04\02\title.png)");
	if (image.GetLastStatus() == Gdiplus::Ok) {
		if (std::unique_ptr<Gdiplus::Image> pThumbnail{ image.GetThumbnailImage
		( image.GetWidth () / 3
		, image.GetHeight() / 3
		, NULL
		, NULL
		) }) {
			Gdiplus::Bitmap bmpOut(pThumbnail->GetWidth(), pThumbnail->GetHeight());
			Gdiplus::Graphics graphics(&bmpOut);
			graphics.DrawImage(&*pThumbnail, 0, 0, pThumbnail->GetWidth(), pThumbnail->GetHeight());
			const auto clsid = codec_for(L"image/Jpeg");
			bmpOut.Save(L"sample.jpg", &clsid);
		}
		else
			throw std::runtime_error("GetThumbnailImage 関数が nullptr を返しました。");
	}
	else
		throw std::runtime_error("画像ファイルの読み込みに失敗しました。");
}
int main()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	try {
		test();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
}
