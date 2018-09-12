#include "functionality.h"

//find group and qq
bool DataStore::findValue(int64_t group, int64_t qq)
{
	auto data_end = data.end();
	if (data.find(group) == data_end || data.find(qq) == data_end)
		return false;
	return true;
}

//find group
bool DataStore::findValue(int64_t group)
{
	auto data_end = data.end();
	if (data.find(group) == data_end)
		return false;
	return true;
}

void DataStore::addValue(int64_t group, int64_t qq)
{
	if (DataStore::findValue(group, qq) == true)
		data[group][qq]++;
}

void DataStore::addValue(int64_t group)
{
	if (DataStore::findValue(group) == true)
		data[group][0]++;
}

