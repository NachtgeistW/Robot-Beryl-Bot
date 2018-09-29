#include "search_song_whole.h"

void WholeMemo::main(int64_t group, int64_t qq, string msg)
{
	string target_song;
	// match the song name
	if (match_song_whole(msg, target_song))
	{
		if (search_song_list(target_song))
		{
			print_memo(qq);
			CQ::sendGroupMsg(group, "���ˣ��ǵÿ�С��Ŷ");
		}
		else
		{
			CQ::sendGroupMsg(group, "��û��ȫ���б����ҵ����׸衭����ȵȣ��������ұ����б���");
			if (search_alias_list(target_song))
			{
				print_memo(qq);
				CQ::sendGroupMsg(group, "���ˣ��ǵÿ�С��Ŷ");
			}
			else
				CQ::sendGroupMsg(group, "��Ҳû���ڱ����б����ҵ����׸衭������һ��ƴд�������÷������ܷ���ҹ�ְ�");
		}
	}
}

bool WholeMemo::match_song_whole(const string msg, string &target)
{
	std::regex search_cmd(reg);
	std::smatch to_be_search;
	if (std::regex_match(msg, to_be_search, search_cmd))
	{
		target = to_be_search[5].str();
		return true;
	}
	else
		return false;
}

