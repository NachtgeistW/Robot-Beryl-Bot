#pragma once
#include "../../util/util.h"
using std::vector;
class UBSongInfo
{
protected:
	std::multimap<string, unsigned int> SongList;
	std::multimap<string, string> AliasList; //Rule: File format is that alias is ahead, standard name is behind
	std::map<string, vector<string>> Memo;
public:
	UBSongInfo() = default;
	virtual ~UBSongInfo() = default;
	void initialize(int64_t qq);
	bool load_song_list(const string path);	//load the song list and difficulty to a map
	bool search_song_list(const string name);//search the song in song list
	//search the song in alias list. If found, change the string to the standard name

	bool load_alias_list(const string path);	//load the alias list and standard name to a map
	bool search_alias_list(string name);
	bool load_local_memo(const string name, int64_t group);			//load the memo to a map

};
