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
		cout << "Событие отправлено " << buffer << endl;
		second_semaphore.release();
		first_semaphore.acquire();
	}
}

int main() {
	buffer = "";
	setlocale(LC_ALL, "ru");
	thread thread1(thread_send);
	thread1.detach();

	while (true) {
		second_semaphore.acquire();
		cout << "Событие обработано " << buffer << endl;
		buffer = "";
		first_semaphore.release();
	}

	return 0;
}