/*
*������ܴ��ڵ�Ŀ��ֻ�������һ�仰������Ҫ��������۹�����ˣ���
*��Ȼ��������ù��ø����ױ���Ϸ�ˣ���������е㿴�����Ǿ仰��
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
