#pragma once
#include "../../util/util.h"
using std::vector;
class UBSongInfo
{
protected:
	std::map<string, vector<string>> Memo;
	std::multimap<string, unsigned int> SongList;
public:
	UBSongInfo() = default;
	virtual ~UBSongInfo() = default;
	void initialize(int64_t qq);
	bool load_local_memo(const string name, int64_t group);			//load the memo to a map
	bool load_song_list(const string path);	//load the song list and difficulty to a map

};
