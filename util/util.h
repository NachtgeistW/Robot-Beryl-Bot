#pragma once
#include <CQAPI_EX.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <stdlib.h>
#include <regex>
#include <map>
#include <chrono>

using std::string;
namespace util {
	const int64_t Beryl = 3276553814;		//机器人的QQ号
	const int64_t Master = 562231326;	//主人的QQ号
	const std::string path = "conf\\";

	int RandInt_uniform(int begin, int end);

	static std::vector<int64_t> Robot{ 2718434132, 3304584594, 3461119188, 2748920600, 2130638764,530752474 };
	//bool getBot(std::vector<int64_t>& bot);
	bool checkBot(int64_t QQID, std::vector<int64_t>bot);

	std::string int64_ttos(int64_t num);
}

struct Tm : std::tm {
	int tm_usecs; // [0, 999999] micros after the sec

	Tm(const int year, const int month, const int mday, const int hour,
		const int min, const int sec, const int usecs, const int isDST = -1)
		: tm_usecs{ usecs } {
		tm_year = year - 1900; // [0, 60] since 1900
		tm_mon = month - 1;    // [0, 11] since Jan
		tm_mday = mday;        // [1, 31]
		tm_hour = hour;        // [0, 23] since midnight
		tm_min = min;          // [0, 59] after the hour
		tm_sec = sec;          // [0, 60] after the min
							   //         allows for 1 positive leap second
		tm_isdst = isDST;      // [-1...] -1 for unknown, 0 for not DST,
							   //         any positive value if DST.
	}

	template <typename Clock_t = std::chrono::system_clock,
		typename MicroSecond_t = std::chrono::microseconds>
		auto to_time_point() -> typename Clock_t::time_point {
		auto time_c = mktime(this);
		return Clock_t::from_time_t(time_c) + MicroSecond_t{ tm_usecs };
	}
};
