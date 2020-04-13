#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

void pin(std::mutex& mtx) {
	while (true)
	{
		mtx.lock();
		std::cout << "Pin " << std::endl;
		std::cout << "address thread " << std::this_thread::get_id() << std::endl;
		mtx.unlock();
		
		std::this_thread::sleep_for(std::chrono::microseconds(1000000));
	}
	
}

void pong(std::mutex& mtx) {
	while (true)
	{
		mtx.lock();
		std::cout << "Pong " << std::endl;
		std::cout << "address thread " << std::this_thread::get_id() << std::endl;
		mtx.unlock();
		
		std::this_thread::sleep_for(std::chrono::microseconds(1000000));
	}
}



int main(int argc, char** argv)
{
	std::mutex mtx;
	std::thread t1(pin, ref(mtx));
	std::thread t2(pong, ref(mtx));
	
	if(t1.joinable())
	t1.join();
	if (t2.joinable())
	t2.join();

	system("pause >> NULL");
	return 0;
}