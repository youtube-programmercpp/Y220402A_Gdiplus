#pragma once
#include <gdiplus.h>
namespace StaticLib1 {
	namespace RAII {
		class GdiplusShutdown {
			Gdiplus::Status status      ;
			ULONG_PTR       gdiplusToken;
		public:
			GdiplusShutdown(Gdiplus::Status status, ULONG_PTR gdiplusToken) noexcept;
			~GdiplusShutdown();
			GdiplusShutdown(GdiplusShutdown&& r) noexcept;//移動コンストラクタ
			auto operator=(GdiplusShutdown&& r) noexcept->GdiplusShutdown&;//移動代入演算子
		};
	}
}