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
			GdiplusShutdown(GdiplusShutdown&& r) noexcept;//�ړ��R���X�g���N�^
			auto operator=(GdiplusShutdown&& r) noexcept->GdiplusShutdown&;//�ړ�������Z�q
		};
	}
}