#include "anti_Fword_basic.h"

void AntiFBasic::store_count_info(int64_t group_id)
{
	AntiFBasic::Fword_msg_count[AntiFBasic::length][0] = group_id;
	length++;
	int n = length + 1;
	Fword_msg_count.resize(n);
}

int AntiFBasic::find_subscript(int64_t group_id)
{
	for (unsigned int i = 0; i < AntiFBasic::Fword_msg_count.size(); i++)
	{
		if (AntiFBasic::Fword_msg_count[i][0] == group_id)
			return i;
	}
	return -1;
}

void AntiFBasic::set_repeat_count(int length)
{
	AntiFBasic::Fword_msg_count[length][1]++;
	if (Fword_msg_count[length][1] == 10)
		Fword_msg_count[length][1] = 0;
}

int AntiFBasic::return_count_num(int no)
{
	return AntiFBasic::Fword_msg_count[no][1];
}
