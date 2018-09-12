
// use this function to change member action count
bool stopMemberRepeat(const int64_t group, const int64_t qq, const std::string msg)
{
	if (!repeat.findValue(group, qq))
	{
		LastMsg = msg;
		repeat.addData(group, qq);
		repeat.addValue(group, qq);
	}
	else if (repeat.findValue(group, qq) && msg == LastMsg)
	{
		repeat.addValue(group, qq);
		if (repeat.getValue(group, qq) == 4)
			return true;
	}
	else if (repeat.findValue(group, qq) && repeat.getValue(group, qq) > 4)
	{
		repeat.addValue(group, qq);
		if (repeat.getValue(group, qq) == 10)
			repeat.clearValue(group, qq);
	}
	else
		repeat.clearValue(group);
	return false;
}
