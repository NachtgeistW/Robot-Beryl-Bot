#include "../util/functionality.h"
string UrgeSleep::urgeSleep(int64_t qq)
{
	if (isTimeToSleep() &&	qq == util::Master)
	{

		CQ::sendPrivateMsg(util::Master, "你是不是该睡觉了？");
	}

	return "你是不是该睡觉了？";
}

string UrgeSleep::testUpdate(string msg)
{
	int count = duration_cast<minutes>(tp_now_ - tp_sleep_begin_).count();
	if (count != 0 && count % 2 == 0)
	{
		string to_be_sent = std::to_string(count) + "passed";
		CQ::sendGroupMsg(279023542, to_be_sent);
		tp_sleep_begin_ = tp_now_;
	}
	tp_now_ = system_clock::now();
	return string();
}
