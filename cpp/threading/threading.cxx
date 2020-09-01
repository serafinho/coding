#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <climits>

#include "Philosopher.h"

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
array<int, 32> buffer;
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

const int numPhil = 10;
vector<int> forks(numPhil);
vector<shared_ptr<Philosopher>> philosophers;
vector<thread*> threads;

void initDiningTable()
{
	for (int i = 0; i < numPhil; i++)
	{
		int leftFork = i;
		int rightFork = i + 1;
		if (rightFork >= numPhil)
		{
			rightFork = 0;
		}
		philosophers.push_back(make_shared<Philosopher>(i, leftFork, rightFork));
		forks[i] = -1;
	}
}

void startEating()
{
	for (int i = 0; i < numPhil; i++)
	{
		threads.push_back(new thread(&Philosopher::eat, philosophers[i], forks));
	}
}

void waitUntilFinished()
{
	for (int i = 0; i < numPhil; i++)
	{
		threads[i]->join();
	}
}

void diningPhilosophers()
{
	initDiningTable();
	startEating();
	waitUntilFinished();
}

int main()
{
	cout << "Running threading tests...\n";

	//simpleThreading();

	//busyWaiting();

	//producerConsumer();

	diningPhilosophers();
}