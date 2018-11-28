#pragma once
#include "../util/util.h"
using namespace std::chrono;

class UrgeSleep {
private:
	int urge_time_ = 0;
	system_clock::time_point tp_sleep_begin_ = Tm(2018, 11, 28, 22, 20, 0, 0).to_time_point();
	system_clock::time_point tp_sleep_end_ = Tm(2018, 11, 29, 0, 0, 0, 0).to_time_point();
	system_clock::time_point tp_now_ = system_clock::now();
public:
	UrgeSleep() = default;
	~UrgeSleep() = default;

	system_clock::time_point getCurTime(void) {	return tp_now_;	};
	bool isTimeToSleep(void) { return (tp_now_ >= tp_sleep_begin_ || tp_now_ <= tp_sleep_end_); }
	string urgeSleep(int64_t qq);
	string testUpdate(string msg);
};