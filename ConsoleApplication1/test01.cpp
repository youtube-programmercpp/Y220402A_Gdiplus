#include <windows.h>
#include <gdiplus.h>
#include <iostream>
using namespace Gdiplus;

#pragma comment(lib, "gdiplus")

#include <memory>

INT main()
{
    // Initialize GDI+.
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    UINT  num;        // number of image encoders
    UINT  size;       // size, in bytes, of the image encoder array
    GetImageEncodersSize(&num, &size);


    // How many encoders are there?
    // How big (in bytes) is the array of all ImageCodecInfo objects?

    // Create a buffer large enough to hold the array of ImageCodecInfo
    // objects that will be returned by GetImageEncoders.
    const std::unique_ptr<ImageCodecInfo> pImageCodecInfo{ reinterpret_cast<ImageCodecInfo*>(new char[size]) };

    // GetImageEncoders creates an array of ImageCodecInfo objects
    // and copies that array into a previously allocated buffer. 
    // The third argument, imageCodecInfo, is a pointer to that buffer. 
    GetImageEncoders(num, size, &*pImageCodecInfo);

    // Display the graphics file format (MimeType)
    // for each ImageCodecInfo object.
    for (UINT j = 0; j < num; ++j)
    {
        std::wcout << pImageCodecInfo.get()[j].MimeType << '\n';
    }

    GdiplusShutdown(gdiplusToken);
    return 0;
}
