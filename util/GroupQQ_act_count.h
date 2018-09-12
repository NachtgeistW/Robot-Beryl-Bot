#pragma once
#include <vector>
#include <string>
#include <map>
using std::map;
class DataStore {
private:
	map<int64_t, map<int64_t, int>> data;//group, (qq, action count)
public:
	DataStore() = default;
	//DataStore(int num) { std::vector<std::vector<std::pair<int64_t, int>>> data(num); };
	void addData(int64_t group, int64_t qq)	{	data[group][qq] = 0;};	//https://stackoverflow.com/questions/4479017/storing-std-map-in-map
	void addData(int64_t group) { data[group][0] = 0; };
	int getValue(int64_t group, int64_t qq) {	return data[group][qq];	};
	int getValue(int64_t group) { return data[group][0]; };//when the action of qq can be ignored
	bool findValue(int64_t group, int64_t qq);
	bool findValue(int64_t group);//when the action of qq can be ignored
	void addValue(int64_t group, int64_t qq);
	void addValue(int64_t group);
	void clearValue(int64_t group, int64_t qq) { data[group][qq] = 0; }
	void clearValue(int64_t group) { data[group].clear(); }
	~DataStore() = default;
};
