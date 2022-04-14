#include "pch.h"
#include "RAII/GdiplusShutdown.h"
StaticLib1::RAII::GdiplusShutdown::GdiplusShutdown(Gdiplus::Status status, ULONG_PTR gdiplusToken) noexcept
	: status(status)
	, gdiplusToken(gdiplusToken)
{
}
StaticLib1::RAII::GdiplusShutdown::~GdiplusShutdown()
{
	if (status == Gdiplus::Ok) {
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}
}

StaticLib1::RAII::GdiplusShutdown::GdiplusShutdown(GdiplusShutdown&& r) noexcept
	: /*Gdiplus::Status ;*/status      {r.status      }
	, /*ULONG_PTR       ;*/gdiplusToken{r.gdiplusToken}
{
	r.status       = Gdiplus::GdiplusNotInitialized;
	r.gdiplusToken = {};
}
auto StaticLib1::RAII::GdiplusShutdown::operator=(GdiplusShutdown&& r) noexcept->StaticLib1::RAII::GdiplusShutdown&
{
	std::swap(status      , r.status      );
	std::swap(gdiplusToken, r.gdiplusToken);
	return *this;
}

