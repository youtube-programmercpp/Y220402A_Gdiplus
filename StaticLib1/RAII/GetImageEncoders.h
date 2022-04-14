#pragma once
#include "GdiplusShutdown.h"
namespace StaticLib1 {
    namespace RAII {
        struct ImageEncoders {
            UINT  num;        // number of image encoders
            Gdiplus::ImageCodecInfo p[1];

            Gdiplus::ImageCodecInfo* begin() noexcept
            {
                return p;
            }
            Gdiplus::ImageCodecInfo* end() noexcept
            {
                return &p[num];
            }
        };


        inline auto GetImageEncoders()->std::unique_ptr<ImageEncoders>
        {
            UINT  num;        // number of image encoders
            UINT  size;       // size, in bytes, of the image encoder array
            Gdiplus::GetImageEncodersSize(&num, &size);


            // How many encoders are there?
            // How big (in bytes) is the array of all ImageCodecInfo objects?

            // Create a buffer large enough to hold the array of ImageCodecInfo
            // objects that will be returned by GetImageEncoders.
            std::unique_ptr<ImageEncoders> pImageCodecInfo
            { reinterpret_cast<ImageEncoders*>(new char[size + sizeof (UINT)]) };

            // GetImageEncoders creates an array of ImageCodecInfo objects
            // and copies that array into a previously allocated buffer. 
            // The third argument, imageCodecInfo, is a pointer to that buffer. 
            Gdiplus::GetImageEncoders(num, size, pImageCodecInfo->p);
            pImageCodecInfo->num = num;
            return pImageCodecInfo;
        }
    }
}
