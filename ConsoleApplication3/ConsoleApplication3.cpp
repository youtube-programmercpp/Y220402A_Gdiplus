#include <Windows.h>
#include <sstream>
int main()
{
	const std::string& s = (std::ostringstream() << "TEST" << '\n').str();
	OutputDebugStringA(s.c_str());
}


