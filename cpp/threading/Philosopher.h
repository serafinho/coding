#ifndef __PHILOSOPHER_H__
#define __PHILOSOPHER_H__

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

class Philosopher
{
public:
	
	Philosopher(int id, int leftFork, int rightFork) :
		m_leftFork(leftFork), m_rightFork(rightFork), m_id(id), m_bites(0)
	{
	}

	void eat(std::vector<int>& forks)
	{
		while (m_bites<100)
		{
			forkMutex.lock();
			forks[m_leftFork] = m_id;
			forks[m_rightFork] = m_id;
			forkMutex.unlock();
			m_bites++;
			printStatus();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		std::cout << "************ Philosopher " << m_id << " finished!\n";
	}

private:
	void printStatus()
	{
		std::cout << "Philosopher " << m_id << ", Bites: " << m_bites << std::endl;
	}

	int m_leftFork;
	int m_rightFork;
	int m_id;
	int m_bites;
	static std::mutex forkMutex;
};

std::mutex Philosopher::forkMutex;

#endif
