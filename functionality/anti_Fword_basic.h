#pragma once
#include <vector>
/*
http://www.cnblogs.com/rock-doit/p/4763872.html
something about initialize using vector to create two-dimensional array
*/

class AntiFBasic {
private:
	int length = 0;
	std::vector<std::vector<int64_t>> Fword_msg_count;
public:
	AntiFBasic();
	void store_count_info(int64_t group_id);
	int find_subscript(int64_t group_id);	//find the subscript of group in array
	void set_repeat_count(int length);
	int return_count_num(int no);
	~AntiFBasic() = default;
};
inline AntiFBasic::AntiFBasic()
{
	//set widgh to 2
	Fword_msg_count.resize(2);
	for (int i = 0; i < 2; i++)
		//set length to 2
		Fword_msg_count[i].resize(2);
}
