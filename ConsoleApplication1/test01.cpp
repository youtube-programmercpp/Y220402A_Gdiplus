#include <windows.h>
#include <gdiplus.h>
#include <iostream>
using namespace Gdiplus;

#pragma comment(lib, "StaticLib1.lib")

#include <memory>
#include <StaticLib1/RAII/GdiplusStartup.h>
#include <StaticLib1/RAII/GetImageEncoders.h>

INT main()
{
    // Initialize GDI+.
    const auto auto_shutdown = StaticLib1::RAII::GdiplusStartup();
    const auto pImageCodecInfo = StaticLib1::RAII::GetImageEncoders();
    // Display the graphics file format (MimeType)
    // for each ImageCodecInfo object.
    for (UINT j = 0; j < pImageCodecInfo->num; ++j)
    {
        std::wcout << pImageCodecInfo->p[j].MimeType << '\n';
    }
    return 0;
}
