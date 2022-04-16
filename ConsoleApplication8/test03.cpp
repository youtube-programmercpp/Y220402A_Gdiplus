#include <iostream>

namespace A {
	struct sample {
		int value;
	};
	std::ostream& operator<<(std::ostream& ostm, const sample& r)
	{
		return ostm << __FUNCTION__ ": " << r.value;
	}
}
namespace B {
	struct sample {
		int value;
	};
	std::ostream& operator<<(std::ostream& ostm, const sample& r)
	{
		return ostm << __FUNCTION__ ": " << r.value;
	}
}
#include <fstream>
#include <sstream>
#include <Windows.h>
int main()
{
	std::string s;
	s  = (std::ostringstream() << A::sample{ 12345 } << '\n').str();
	s += (std::ostringstream() << B::sample{ 12345 } << '\n').str();
	MessageBoxA(nullptr, s.c_str(), "TEST", 0);
}
