/*
*这个功能存在的目的只是针对那一句话：“我要日了这骨折光机器人！”
*虽然这个功能让光变得更容易被调戏了，但是真的有点看不惯那句话。
*/
#pragma once
#include <CQEVE_ALL.h>
#include <CQcode.h>
#include <CQLogger.h>
#include <CQAPI_EX.h>

#include <string>
#include <fstream>
#include <regex>
#include "../Hikari_bot_fun.h"
#include "anti_Fword_basic.h"

using std::string;

class fWord {
private:
	string BlackList;
	string WhiteList;
	AntiFBasic anti_f;
public:
	fWord() = default;
	bool writeToList(std::istream& is);
	bool whiteWriteToRegex(std::regex &r);
	bool blackWriteToRegex(std::regex &FHikari, std::regex &FTairitsu, std::regex &HiFTai, std::regex &TaiFHi);
	void removeWhiteInMsg(string &message);

friend void select_msg(int count, std::string message, std::string &word,
		const std::regex FHikari, const std::regex FTairitsu, const std::regex HiFTai, const std::regex TaiFHi, const std::regex whitelist);
friend string anti_Fword_main(int64_t groupid, string message);

	~fWord() = default;
};
