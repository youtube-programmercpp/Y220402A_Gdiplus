#include <system_error>
#include <Windows.h>
#include <iostream>
namespace WindowsApi {
	enum class errc;
	class error_category : public std::error_category {
	public:
		_NODISCARD virtual const char* name() const noexcept override
		{
			return "Windows API Error";
		}
		_NODISCARD virtual std::string message(int _Errval) const override
		{
			std::string errmsg(1024, '\0');
			errmsg.resize(/*WINBASEAPI _Success_(return != 0) DWORD WINAPI*/FormatMessageA
			( /*_In_     DWORD     dwFlags     */FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK
			, /*_In_opt_ LPCVOID   lpSource    */nullptr
			, /*_In_     DWORD     dwMessageId */_Errval
			, /*_In_     DWORD     dwLanguageId*/0
			, /*_When_((dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) != 0, _At_((LPSTR*)lpBuffer, _Outptr_result_z_))*/
			  /*_When_((dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) == 0, _Out_writes_z_(nSize)                    )*/
			  /*         LPSTR     lpBuffer    */&errmsg.front()
			, /*_In_     DWORD     nSize       */static_cast<DWORD>(errmsg.size() + 1)
			, /*_In_opt_ va_list * Arguments   */nullptr
			));
			return errmsg;
		}
		static const error_category& singleton() noexcept
		{
			static error_category single_instance;
			return single_instance;
		}
	};
	std::error_code make_error_code(errc e) noexcept
	{
		return { static_cast<int>(e), error_category::singleton() };
	}
}
template<>struct std::is_error_code_enum<WindowsApi::errc> : public std::true_type {
};

#include <gdiplus.h>
namespace Gdiplus {
	typedef Gdiplus::Status errc;
	class error_category : public std::error_category {
	public:
		_NODISCARD virtual const char* name() const noexcept override
		{
			return "GDI+ Error";
		}
		_NODISCARD virtual std::string message(int _Errval) const override
		{
			switch (_Errval) {
#define	ERRMSG(code, value) case value: return #code;
#include "gdiplus_errc.h"
#undef	ERRMSG
			default:
				return "?";
			}
			;
		}
		static const error_category& singleton() noexcept
		{
			static error_category single_instance;
			return single_instance;
		}
	};
	std::error_code make_error_code(errc e) noexcept
	{
		return { static_cast<int>(e), error_category::singleton() };
	}
}
template<>struct std::is_error_code_enum<Gdiplus::errc> : public std::true_type {
};



int main()
{
	try {
		//throw std::system_error(WindowsApi::errc(5));
		throw std::system_error(Gdiplus::Status::GdiplusNotInitialized);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	;


}
