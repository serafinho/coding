#include <iostream>

#include <future>
#include <thread>

using namespace std;

void asyncPrint100()
{
	for (int i = 0; i < 100; i++)
	{
		cout << i << ", ";
	}
}

void asyncPrint300()
{
	for (int i = 200; i < 300; i++)
	{
		cout << i << ", ";
	}
}

int main()
{
	cout << "Running threading tests...\n";

	auto fut = async(asyncPrint100);

	thread t(asyncPrint300);

	for (int i = 100; i < 200; i++)
	{
		cout << i << ", ";
	}

	t.join();
}