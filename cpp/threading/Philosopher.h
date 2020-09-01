#ifndef __PHILOSOPHER_H__
#define __PHILOSOPHER_H__

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <array>

constexpr int no_of_philosophers = 5;

struct Fork
{
	std::mutex mutex;
};


struct Table
{
	std::atomic<bool> ready{ false };
	std::array<Fork, no_of_philosophers> forks;
};

class Philosopher
{
public:
	
	Philosopher(int id, Fork &leftFork, Fork &rightFork) :
		m_leftFork(leftFork), m_rightFork(rightFork), m_id(id), m_bites(0)
	{
	}

	void eat(std::vector<int>& forks)
	{
		while (m_bites<100)
		{
//			forkMutex.lock();
		//	forks[m_leftFork] = m_id;
	//		forks[m_rightFork] = m_id;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			printStatus();
//			forkMutex.unlock();
			m_bites++;
		}
		std::cout << "************ Philosopher " << m_id << " finished!\n";
	}

private:
	void printStatus()
	{
		std::cout << "Philosopher " << m_id << ", Bites: " << m_bites << std::endl;
	}

	Fork& m_leftFork;
	Fork& m_rightFork;
	int m_id;
	int m_bites;
	std::thread worker;
//	Table const& m_table;
};

//std::mutex Philosopher::forkMutex;

#endif
