#include <iostream>
#include <string>
#include <vector>
//�߂�l�̌^  �֐���     ��P����          , ��Q����
std::ostream& operator<<(std::ostream& ostm, const std::vector<std::string>& r)
{
	//range-based for statement
	for (const auto& s : r)
		ostm << s << '\n';
	return ostm;
}
int main()
{
	operator<<(std::cout, { "ABC", "DEF", "GHI" });
	std::cout << std::vector<std::string>{ "ABC", "DEF", "GHI" };

}