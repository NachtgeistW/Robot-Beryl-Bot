#pragma once
#include "../../util/util.h"
#include "store_memo.h"

//search and print memo
class WholeMemo : public UBSongInfo
{
public:
	WholeMemo() = default;
	~WholeMemo() = default;
	void main(int64_t group, int64_t qq, string msg);
	bool match_song_whole(string msg, string &target);
	bool search_song_list(string name);			//search for a specify song 
	void print_memo(void);
private:

};

