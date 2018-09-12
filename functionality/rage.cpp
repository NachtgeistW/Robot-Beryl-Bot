#include "../util/functionality.h"

DataStore repeat;
std::string LastMsg;

std::string rage_main(const int64_t group, const int64_t qq, const std::string msg)
{
	std::string reply;
	if (stopWholeRepeat(group, msg) == true)
		if(util::randNum(5) == 0)
			reply = msg;
		else
			reply = "你们不要再复读了";
	if (stopMemberRepeat(group, qq, msg) == true)
		reply = CQ::code::at(qq) + "嘲讽倍率提升警告";
	return reply;
}


std::string tauntProUp(const int64_t group, const int64_t qq, const std::string message)
{
	std::string reply;
	if (repeat.getValue(group, qq) > 4)
		if (util::randNum(2) == 0)
			reply = replaceWord(message);
	else if (repeat.getValue(group, qq) <= 4)
		if(util::randNum(29) == 0)
			reply = replaceWord(message);
	return reply;
}

std::string replaceWord(const std::string message)
{
	std::regex me("(.*?)(?:我)(.*?)"), you("(.*?)(?:你)(.*?)"), wo("(.*?)(?:wori)(.*?)");
	std::string fmt1 = "$1你$3", fmt2 = "$1他$3", fmt3 = "$1niri$3";
	std::string transit, result;

	//if there are 我 and 你 in message
	if (regex_search(message, me))
	{
		if (regex_search(message, you))
		{
			//search for 你 in message and replace it with 他
			for (std::sregex_iterator it(message.begin(), message.end(), you), end_it; it != end_it; ++it)
				transit = regex_replace(message, you, fmt2);
			//Search for 我 in transit and replace it with 你
			for (std::sregex_iterator it(transit.begin(), transit.end(), me), end_it; it != end_it; ++it)
				result = regex_replace(transit, me, fmt1);
		}
		else
			//if there are 我 in message without 你
			for (std::sregex_iterator it(message.begin(), message.end(), me), end_it; it != end_it; ++it)
				result = regex_replace(message, me, fmt1);
	}
	//use this to replace "wori"
	if (regex_search(message, wo))
		for (std::sregex_iterator it(message.begin(), message.end(), wo), end_it; it != end_it; ++it)
			result = regex_replace(message, wo, fmt3);

	return result;
}
