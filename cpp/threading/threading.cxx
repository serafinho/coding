#include <iostream>
#include <future>
#include <thread>
#include <queue>
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

// store values in queue
queue<int> buffer;

// mutex to protect critical sections
mutex cv_m;

// flag to tell other threads when to stop
atomic<bool> prodRunning = true;

// condition variable
condition_variable cv;

/*
 Print queue
 */
void printQueue()
{
	while (prodRunning)
	{
        {
            // critical section
            lock_guard<mutex> lk(cv_m);
            cout << "***** Queue size: " << buffer.size() << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(10));
	}
}

void producer()
{
    prodRunning = true;
	int value = 0;

    for(int i=0; i<10000; i++)
	{
        {
            // critical section
            lock_guard lk(cv_m);
            buffer.push(value);
            cout << "Pushing: " << value << endl;
        }
        // notify waiting threads
        cv.notify_all();
        
        // new value
        value = (value >= INT_MAX) ? 0 : value + 1;
        
        // just wait a little before pushing next value
		this_thread::sleep_for(chrono::milliseconds(1));
	}
    prodRunning = false;
    
    // wake up threads for final processing
    cv.notify_all();
}

void consumer()
{
    unique_lock<mutex> lk(cv_m);
	while (prodRunning)
	{
        // wait for notification from producer
        cv.wait(lk);
        
        if(!buffer.empty())
        {
            cout << "Popping: " << buffer.front() << endl;
            buffer.pop();
        }
        else
        {
            cout << "Empty..." << endl;
        }
	}
}


void producerConsumer()
{
	thread prod(producer);
	thread cons(consumer);
	thread print(printQueue);
	prod.join();
	cons.join();
	print.join();
    cout << "Done." << endl;
}

int main()
{
	cout << "Running threading tests...\n";

//	simpleThreading();

//	busyWaiting();

	producerConsumer();

	//diningPhilosophers();
}
