#include <iostream>
#include <windows.h>
#include <string>
#include <stdexcept>

HANDLE open_file()
{
	const auto hFile = /*WINBASEAPI HANDLE WINAPI*/CreateFileW
	( /*_In_     LPCWSTR                lpFileName           */L"not_exists.txt"
	, /*_In_     DWORD                  dwDesiredAccess      */GENERIC_READ
	, /*_In_     DWORD                  dwShareMode          */FILE_SHARE_READ
	, /*_In_opt_ LPSECURITY_ATTRIBUTES  lpSecurityAttributes */nullptr
	, /*_In_     DWORD                  dwCreationDisposition*/OPEN_EXISTING
	, /*_In_     DWORD                  dwFlagsAndAttributes */0
	, /*_In_opt_ HANDLE                 hTemplateFile        */nullptr
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		const auto e = GetLastError();
		std::string errmsg(1024, '\0');
		errmsg.resize(/*WINBASEAPI _Success_(return != 0) DWORD WINAPI*/FormatMessageA
		( /*_In_     DWORD     dwFlags     */FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK
		, /*_In_opt_ LPCVOID   lpSource    */nullptr
		, /*_In_     DWORD     dwMessageId */e
		, /*_In_     DWORD     dwLanguageId*/0
		, /*_When_((dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) != 0, _At_((LPSTR*)lpBuffer, _Outptr_result_z_))*/
		  /*_When_((dwFlags & FORMAT_MESSAGE_ALLOCATE_BUFFER) == 0, _Out_writes_z_(nSize)                    )*/
		  /*         LPSTR     lpBuffer    */&errmsg.front()
		, /*_In_     DWORD     nSize       */static_cast<DWORD>(errmsg.size() + 1)
		, /*_In_opt_ va_list * Arguments   */nullptr
		));
		throw std::runtime_error(errmsg);
	}
	else
		return hFile;
}


int main()
{
	try {
		const auto hFile = open_file();
		CloseHandle(hFile);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
