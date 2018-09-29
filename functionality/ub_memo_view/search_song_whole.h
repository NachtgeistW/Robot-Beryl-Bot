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
	bool match_song_whole(const string msg, string &target);
	bool search_song_list(const string name);			//search for a specify song 
	void print_memo(int64_t qq);
private:
	string reg = "((��|��)��)?(��)(һ)?(��)(?:(.+))+(������(��|����|memo))";
};

