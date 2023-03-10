#include <iostream>
#include <thread>
#include <mutex>
struct SharedResource
{
	static const int N = 5;
	SharedResource() :
		recMtx()
	{


	}
	//Shared resource and mutex should be kept together
	std::recursive_mutex recMtx;
	int buffer{ 0 };
	
};

void recursion(char threadID, int counter, SharedResource& sharedresource)
{
	//counter is a local variable and doesn't have to be mutex protected; it is local to each thread and is not shared among them
	if (counter >= SharedResource::N)
	{

		return;
	}

	std::unique_lock<std::recursive_mutex> lock(sharedresource.recMtx);

	std::cout << "Thread " << threadID << " :  " << sharedresource.buffer << '\n';
	++sharedresource.buffer;
	recursion(threadID, counter + 1, sharedresource);
	//We need the follwoing line to be mutex protected or we would have a messy output when another thread starts to print out on the console
	std::cout << "Thread " << threadID << " :  unlocking " << '\n';
	lock.unlock();


}

int main()
{
	int i = 1;
	SharedResource sharedresource; //Shared data
	constexpr char t1 = '1';
	constexpr char t2 = '2';
	constexpr char t3 = '3';
	constexpr char t4 = '4';
	std::thread th1(&recursion, t1, i, std::ref(sharedresource)); //passing by reference
	std::thread th2(&recursion, t2, i, std::ref(sharedresource));
	std::thread th3(&recursion, t3, i, std::ref(sharedresource));
	std::thread th4(&recursion, t4, i, std::ref(sharedresource));
	th1.join();
	th2.join();
	th3.join();
	th4.join();
}