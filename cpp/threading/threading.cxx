#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <climits>

//#include "Philosopher.h"

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
size_t my_index = 0;
mutex mutti;
bool prodRunning = true;
void printBuffer()
{
	while (prodRunning)
	{
		mutti.lock();
		for (int i = 0; i < my_index; i++)
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
    prodRunning = true;
	int value = 0;
    
    for(int i=0; i<10000; i++)
	{
		mutti.lock();
		if (my_index < buffer.size()-1)
		{			
			buffer[my_index] = value;
			cout << "Pushing: " << buffer[my_index] << endl;
			my_index++;
			value = (value >= INT_MAX) ? 0 : value + 1;
		}
		mutti.unlock();
//		this_thread::sleep_for(chrono::milliseconds(1));
        this_thread::yield();
	}
    prodRunning = false;
}

void consumer()
{
	while (prodRunning || my_index>0)
	{
		mutti.lock();
		if (my_index>0)
		{
			my_index--;
			cout << "Popping: " << buffer[my_index] << endl;
            mutti.unlock();
            this_thread::yield();
		}
        else
        {
            cout << "Empty..." << endl;
            mutti.unlock();
            this_thread::sleep_for(chrono::milliseconds(1));
        }
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
    cout << "Done." << endl;
}

int main()
{
	cout << "Running threading tests...\n";

	simpleThreading();

	busyWaiting();

	producerConsumer();

	//diningPhilosophers();
}
