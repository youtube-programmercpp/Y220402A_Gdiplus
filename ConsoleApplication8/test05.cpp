#include <algorithm>
#include <iostream>
#include <vector>
int main()
{
	const std::vector<std::string> a = { "Alpha", "Beta", "Gamma", "Delta" };
	const auto p = std::find_if(a.begin(), a.end(), [](const auto& s) {return s == "Gamma"; });
	if (p != std::end(a)) {
		std::cout << "Index = " << p - a.begin() << '\n';
	}
}
