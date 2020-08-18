#include <iostream>

using namespace std;

template<typename T>
auto inc(const T i)
{
	return i + 1;
}

int main()
{
	cout << "Some simple Cpp14 tests...\n";
	auto x = 5.0;

	auto y = inc(x);
	cout << "Result: " << y << endl;

	auto l = [](const auto i) { return i + 1; };
	cout << "Result2: " << l(5) << endl;

}