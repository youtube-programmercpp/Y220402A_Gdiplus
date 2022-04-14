#pragma once
#include "GdiplusShutdown.h"
namespace StaticLib1 {
	namespace RAII {
        inline auto GdiplusStartup()->GdiplusShutdown
        {
            Gdiplus::GdiplusStartupInput gdiplusStartupInput;
            ULONG_PTR gdiplusToken;
            const auto status = Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
            return { status, gdiplusToken };
        }
	}
}
