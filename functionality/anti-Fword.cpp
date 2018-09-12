#include "../util.h"
#include "anti-Fword.h"

fWord check;
void select_msg(int count, std::string message, std::string &word,
	const std::regex FHikari, const std::regex FTairitsu, const std::regex HiFTai, const std::regex TaiFHi, const std::regex whitelist)
{
	switch (count)
	{
	case 0:
	{
		if (regex_search(message, FHikari) && !regex_search(message, FTairitsu) && !regex_search(message, whitelist))
			word = "你要干什么？你在说什么可怕的事情？？？";
		else if (regex_search(message, FTairitsu) && !regex_search(message, FHikari) && !regex_search(message, whitelist))
			word = "不……不许欺负対立……";
		else if (regex_search(message, FTairitsu) && regex_search(message, FHikari) && !regex_search(message, whitelist))
			word = "你们……你们……你们到底在想些什么东西啊啊啊！";
		else if (regex_search(message, TaiFHi) && !regex_search(message, whitelist))
			word = "你在说什么啊……対立……対立她不会这么做的吧……";
		else if (regex_search(message, HiFTai) && !regex_search(message, whitelist))
			word = "啊？我才不会做这种事呢……";
		break;
	}
	case 1:
	{
		word = "你冷静……你冷静一点……";
		break;
	}
	case 2:
	{
		word = "连着说了三次，你是……故意的？";
		break;
	}
	case 3:
	{
		word = "又来是吗……你就是故意的……";
		break;
	}
	case 4:
	{
		word = "我生气了。我不理你了。哼。";
		break;
	}
	default:
		break;
	}
}

string anti_Fword_main(int64_t groupid, string message)
{
	string word;
	int length_No = -1;
	std::regex whitelist, FHikari, FTairitsu, HiFTai, TaiFHi;
	std::ifstream fstrm(util::path + "fword.txt");
	try {
		if (fstrm.good())
		{
			check.writeToList(fstrm);
			check.whiteWriteToRegex(whitelist), check.blackWriteToRegex(FHikari, FTairitsu, HiFTai, TaiFHi);
			if (std::regex_search(message, whitelist))
				check.removeWhiteInMsg(message);

			if (check.anti_f.find_subscript(groupid) == -1)
				check.anti_f.store_count_info(groupid);
			length_No = check.anti_f.find_subscript(groupid);

			if (regex_search(message, FHikari) || regex_search(message, FTairitsu)
				|| regex_search(message, TaiFHi) || regex_search(message, HiFTai)
				&& !regex_search(message, whitelist))
			{
				int count = check.anti_f.return_count_num(length_No);
				select_msg(count, message, word, FHikari, FTairitsu, HiFTai, TaiFHi, whitelist);
				check.anti_f.set_repeat_count(length_No);
			}
		}
		else
			throw std::runtime_error("呜……我好像没法回想起敏感词的记忆了……");
	}
	catch (std::runtime_error err) {
		CQ::sendPrivateMsg(util::Master, err.what());
	}
	fstrm.close();
	return word;
}

bool fWord::writeToList(std::istream & is)
{
	string temp;
	getline(is, fWord::BlackList);
	fWord::BlackList = "(?:(" + fWord::BlackList + "))";
	while (std::getline(is, temp))
		fWord::WhiteList += temp;
	return true;
}

bool fWord::whiteWriteToRegex(std::regex &r)
{
	r = fWord::WhiteList;
	return true;
}

bool fWord::blackWriteToRegex(std::regex &FHikari, std::regex &FTairitsu, std::regex &HiFTai, std::regex &TaiFHi)
{
	FHikari = "(.*?)(?:(我|你|他|她)(.*?))" + fWord::BlackList + "(.*?)(?:(光|花嫁白|花白|Hikari))(.*?)";
	FTairitsu = "(.*?)(?:(我|你|他|她)(.*?))" + fWord::BlackList + "(.*?)(?:(伞黑|对立|対立|花黑|Tairitsu))(.*?)";
	HiFTai = "(.*?)(?:(光|花嫁白|花白|Hikari))(.*?)" + fWord::BlackList + "(.*?)(?:(伞黑|对立|対立|花黑|Tairitsu))(.*?)";
	TaiFHi = "(.*?)(?:(伞黑|对立|対立|花黑|Tairitsu))(.*?)" + fWord::BlackList + "(.*?)(?:(光|花嫁白|花白|Hikari))(.*?)";
	return true;
}

void fWord::removeWhiteInMsg(string &message)
{
	string white = "(.*?)(?:" + fWord::WhiteList + ")(.*?)";
	std::regex checkwhite(white);
	string removed = "$1$3";
	if (std::regex_search(message, checkwhite))
	//search for word in whitelist and remove them
		for (std::sregex_iterator it(message.begin(), message.end(), checkwhite), end_it; it != end_it; ++it)
			message = std::regex_replace(message, checkwhite, removed);
}