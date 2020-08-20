#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <climits>

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

auto asyncAdd(const int x, const int y)
{
	return x + y;
}

// Demonstrate simple threading
void simpleThreading()
{
	auto fut = async(asyncPrint100);

	thread t(asyncPrint300);
	auto futAdd = async(asyncAdd, 4, 5);

	for (int i = 100; i < 200; i++)
	{
		cout << i << ", ";
	}
	cout << "Result: " << futAdd.get() << endl;

	t.join();
}


// Demonstrate busy waiting
bool isRunning = false;
void asyncPrint400()
{
	for (int i = 300; i < 400; i++)
	{
		cout << i << ", ";
	}
	isRunning = false;
}

void busyWaiting()
{
	isRunning = true;
	thread t(asyncPrint400);
	while (isRunning)
	{
		cout << ".";
//		this_thread::sleep_for(chrono::milliseconds(1));
	}
	t.join();
}


// Demonstrate producer/consumer
vector<int> buffer(32);
size_t index = 0;
mutex mutti;
void printBuffer()
{
	while (true)
	{
		mutti.lock();
		for (int i = 0; i < index; i++)
		{
			cout << buffer[i] << ", ";
		}
		cout << "\n*********************************************************\n";
		mutti.unlock();
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void producer()
{
	int value = 0;
	while (true)
	{
		mutti.lock();
		if (index < buffer.size()-1)
		{			
			buffer[index] = value;
			cout << "Pushing: " << buffer[index] << endl;
			index++;
			value = (value >= INT_MAX) ? 0 : value + 1;
		}
		mutti.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));

	}
}

void consumer()
{
	while (true)
	{
		mutti.lock();
		if (index>0)
		{
			index--;
			cout << "Popping: " << buffer[index] << endl;
		}
		mutti.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}


void producerConsumer()
{
	thread prod(producer);
	thread cons(consumer);
	thread print(printBuffer);
	prod.join();
	cons.join();
	print.join();
}

int main()
{
	cout << "Running threading tests...\n";

	//simpleThreading();

	//busyWaiting();

	producerConsumer();
}