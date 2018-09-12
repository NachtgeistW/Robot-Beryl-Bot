#pragma once
#include <chrono>
#include <iomanip> //put_time
using namespace std::chrono;

class urge_sleep {
private:
	int send_msg_time = 0;
	system_clock::time_point sleep_time_begin;
	system_clock::time_point now = system_clock::now();
	std::vector<std::string>message;
public:
	void set_begin_time(system_clock::time_point &time);
	void check_send_time(void);
	int check_time_duration(system_clock::time_point time);
};