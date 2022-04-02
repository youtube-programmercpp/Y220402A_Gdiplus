#include <memory> //std::unique_ptr クラス
#include <iostream>
struct sample {
	sample()
		: a{}
		, b{}
		, c{}
	{
		//コンストラクタ
		std::cout << __FUNCTION__ "\n";
	}
	~sample()
	{
		//デストラクタ
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
