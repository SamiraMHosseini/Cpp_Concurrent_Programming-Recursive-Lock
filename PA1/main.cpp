#include <iostream>
#include <thread>
#include <mutex>


std::recursive_mutex recMtx;
int buffer{ 0 };
void recursion(char threadID, int counter)
{

	if (counter >= 4) //counter is a local variable and doesn't have to be protected
	{

		return;
	}


	std::unique_lock<std::recursive_mutex> lock(recMtx);

	std::cout << "Thread " << threadID << " :  " << buffer << '\n';
	++buffer;
	recursion(threadID, counter + 1);
	std::cout << "Thread " << threadID << " :  unlocking "<< '\n';
	lock.unlock();
	

}

int main()
{
	int i = 1;
	constexpr char t1 = '1';
	constexpr char t2 = '2';
	constexpr char t3 = '3';
	constexpr char t4 = '4';
	std::thread th1(&recursion, t1, i);
	std::thread th2(&recursion, t2, i);
	std::thread th3(&recursion, t3, i);
	std::thread th4(&recursion, t4, i);
	th1.join();
	th2.join();
	th3.join();
	th4.join();
}