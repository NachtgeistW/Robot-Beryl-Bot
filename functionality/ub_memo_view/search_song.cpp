#include "search_song.h"

void WholeMemo::main(int64_t group, int64_t qq, string msg)
{
	string target_song;
	if (match_song_whole(msg, target_song))
		CQ::sendGroupMsg(group, "对不起，我找不到这首歌的谱面……");
}

bool WholeMemo::match_song_whole(string msg, string &target)
{
	std::regex search_cmd(string("((给|帮)我)?(查)(一)?(下)(?:(.+))+(的完整(谱|谱面|memo))"));
	std::smatch to_be_search;
	if (std::regex_match(msg, to_be_search, search_cmd))
	{
		target = to_be_search[5].str();
		return true;
	}
	else
		return false;
}

