#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>

using namespace std;

template<typename T>
auto inc(const T i)
{
	return i + 1;
}

void simpleTests() {
	auto x = 5.0;

	auto y = inc(x);
	cout << "Result: " << y << endl;

	auto inc = [](const auto i) { return i + 1; };
	cout << "Result2: " << inc(5) << endl;
}

void printList(const list<int>& l) {
	for_each(l.begin(), l.end(), [](int e) { cout << e << " "; });
	cout << endl;
}

void listTests() {
	list <int> l;
	l.push_back(1);
	l.push_front(2);
	l.push_front(3);
	printList(l);

	l.sort();
	printList(l);

	reverse(l.begin(), l.end());
	printList(l);

	cout << "Sum: " << accumulate(l.begin(), l.end(), 5) << endl;

	auto minMax = minmax_element(l.begin(), l.end());
	cout << "Min/max: (" << *minMax.first << ", " << *minMax.second << ")" << endl;
}

int main()
{
	cout << "Some simple Cpp14 tests...\n";

	simpleTests();

	listTests();
}
