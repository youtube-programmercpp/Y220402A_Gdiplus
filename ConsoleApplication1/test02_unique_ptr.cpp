#include <memory> //std::unique_ptr �N���X
#include <iostream>
struct sample {
	sample()
		: a{}
		, b{}
		, c{}
	{
		//�R���X�g���N�^
		std::cout << __FUNCTION__ "\n";
	}
	~sample()
	{
		//�f�X�g���N�^
		std::cout << __FUNCTION__ "\n";
	}
	int a;
	int b;
	int c;
};
int main()
{
	sample x;
}
