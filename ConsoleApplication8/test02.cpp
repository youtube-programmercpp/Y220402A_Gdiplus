namespace A {
	struct sample {
		int value;
	};
	void f(const sample& r)
	{
	}
}
namespace B {
	struct sample {
		double value;
	};
	void f(const sample& r)
	{
	}
}
int main()
{
	f(A::sample{ 12345 });
	f(B::sample{ 12345. });
}
