#include <iostream>      
#include <thread>           
#include <semaphore>
#include <chrono>
#include <string>

using namespace std;
binary_semaphore first_semaphore(0);
binary_semaphore second_semaphore(0);

string buffer;

void thread_send() {
	while (true) {
		this_thread::sleep_for(chrono::seconds(1));
		buffer = "sms";
		cout << "Событие отправлено" << buffer << endl;
		second_semaphore.release();
		first_semaphore.acquire();
	}
}

void thread_recv() {
	while (true) {
		second_semaphore.acquire();
		cout << "Событие обработано" << buffer << endl;
		buffer = "";
		first_semaphore.release();
	}
}

int main() {
	buffer = "";
	setlocale(LC_ALL, "ru");
	thread thread1(thread_send);
	thread thread2(thread_recv);
	thread1.join();
	thread2.join();
	return 0;
}