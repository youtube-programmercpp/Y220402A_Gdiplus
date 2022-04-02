#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct string {
	size_t length;
	char s[1];

	~string()
	{
		puts(__FUNCTION__ " Ç™åƒÇ—èoÇ≥ÇÍÇ‹ÇµÇΩÅB\n");
	}

};
string* input()
{
	char buf[256];
	if (scanf_s("%s", buf, (unsigned)sizeof buf) == 1) {
		const auto length = strlen(buf);
		if (const auto p = static_cast<string*>(malloc(offsetof(string, s[length + 1])))) {
			static_cast<char*>(memcpy(p->s, buf, p->length = length))[length] = '\0';
			return p;
		}
	}
	return nullptr;
}
#include <memory>
std::unique_ptr<string> input_v2()
{
	char buf[256];
	if (scanf_s("%s", buf, (unsigned)sizeof buf) == 1) {
		const auto length = strlen(buf);
		std::unique_ptr<string> p{ reinterpret_cast<string*>(new char[offsetof(string, s[length + 1])])};
		static_cast<char*>(memcpy(p->s, buf, p->length = length))[length] = '\0';
		return p;
	}
	else
		return {};
}
int main()
{
	//if (const auto p = input()) {
	//	puts(p->s);
	//	free(p);
	//}
	if (const auto p = input_v2())
		puts(p->s);
}
