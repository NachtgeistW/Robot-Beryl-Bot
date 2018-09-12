#include "rage_whole.h"

// use this function to change whole action count
string WholeRepeat::stopWholeRepeat(const int64_t group, const std::string msg)
{
	string reply = "";
	if (LastMsg != msg)
	{
		repeat_time[group] = 0;
		LastMsg = msg;
	}
	repeat_time[group]++;
	if (repeat_time[group] == 8)
		reply = "人类的本质就是复读机吗？懂了";
	return reply;
}
