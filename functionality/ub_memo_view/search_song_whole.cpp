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
			CQ::sendGroupMsg(group, "好了，记得看小窗哦");
		}
		else
		{
			CQ::sendGroupMsg(group, "我没在全曲列表里找到这首歌……你等等，我再找找别名列表……");
			if (search_alias_list(target_song))
			{
				print_memo(qq);
				CQ::sendGroupMsg(group, "好了，记得看小窗哦");
			}
			else
				CQ::sendGroupMsg(group, "我也没有在别名列表里找到这首歌……你检查一下拼写，或者用反馈功能发给夜轮吧");
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

