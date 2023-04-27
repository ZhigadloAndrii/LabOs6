#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <cmath>

std::mutex amut;

void f(int* a){
	int step = pow(10, 6);
	for (int i = 0; i < step; i++){
		amut.lock();
		(*a)++;
		amut.unlock();
	}
}

int main(){

	int* a = new int;
	*a = 0;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	std::thread th1(f,a);
	std::thread th2(f,a);

	th1.join();
	th2.join();

	std::cout << "Result: "<< (*a) << std::endl;

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[ms]" << std::endl;

	return 0;
}
