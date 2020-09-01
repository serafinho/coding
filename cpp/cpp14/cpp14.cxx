#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
#include <vector>

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

void printVector(const vector<int>& v) {
	for_each(v.begin(), v.end(), [](int e) { cout << e << " "; });
	cout << endl;
}

void listTests() {
	list <int> l;
	l.push_back(1);
	l.push_front(2);
	l.push_front(3);
	l.push_back(3);
	printList(l);

	l.sort();
	printList(l);

	reverse(l.begin(), l.end());
	printList(l);

	cout << "Sum: " << accumulate(l.begin(), l.end(), 5) << endl;

	auto minMax = minmax_element(l.begin(), l.end());
	cout << "Min/max: (" << *minMax.first << ", " << *minMax.second << ")" << endl;

	cout << "Count 3s: " << count(l.begin(), l.end(), 3) << endl;	

	printList(l);
	cout << "Lower bound 2: " << *lower_bound(l.begin(), l.end(), 1) << endl;	

	cout << "All of >0? " << any_of(l.begin(), l.end(), [](int x) { return x>0;}) << endl;
	cout << "Any of %2? " << any_of(l.begin(), l.end(), [](int x) { return x%2;}) << endl;
	cout << "None of <0? " << none_of(l.begin(), l.end(), [](int x) { return x<0;}) << endl;

	vector<int> v(10);
	iota(v.begin(), v.end(), -1);
	printVector(v);

	vector<int> v2(8);
	copy_n(v.begin(), 8, v2.begin());
	printVector(v2);

	cout << "Binary Search 2: " << binary_search(v.begin(), v.end(), 2) << endl;

	auto it = find(v.begin(), v.end(), 3);
	cout << "Find 3: " << *it << endl;	

	partition(v.begin(), v.end(), [](int x) { return x%2;});
	cout << "Partition: ";
	printVector(v);

	stable_partition(v2.begin(), v2.end(), [](int x) { return x%2;});
	cout << "Stable partition: ";
	printVector(v2);

	auto point = partition_point(v2.begin(), v2.end(), [](int x) { return x%2;});
	cout << "Partition point: " << *point << endl;


}

int main()
{
	cout << "Some simple Cpp14 tests...\n";

	simpleTests();

	listTests();
}
