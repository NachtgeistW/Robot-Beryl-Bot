#pragma once
#include "../../util/util.h"
#include <regex>
#include <initializer_list>
#include <utility>

constexpr static int IGNORE = -1, SUCCEE = 1, FAILED = 0;

class CytusResult
{
public:
	CytusResult() = default;
	~CytusResult() = default;
	int Calculate(void) noexcept { return static_cast<int>(round(perfect_ / 0.3 + good_ - tp_ * (perfect_ + good_ + bad_ + miss_) / 30)); };
	bool IsLegalValue(const double tp, const int calculated_black_perfect) noexcept {
		const double res = 100 / (perfect_ + good_ + bad_ + miss_) * ((perfect_ - calculated_black_perfect) + 0.7 * calculated_black_perfect + 0.3*good_);
		return (tp == round(res * 100) / 100.00) || (tp == floor(res * 100) / 100.00); //cy1:round; cy2:floor
	};
	void SetCytusResult(const double tp_int, const double tp_frac, const double perfect, 
		const double good, const double bad, const double miss) noexcept;
	void Initialize(void) noexcept { perfect_ = 0, black_perfect_ = 0, good_ = 0, bad_ = 0, miss_ = 0, tp_ = 0; };
protected:
	double perfect_ = 0, black_perfect_ = 0, good_ = 0, bad_ = 0, miss_ = 0, tp_ = 0;
	const string help_info_ = "这是开发者留下的话：\n"
		"显然，该功能用于计算Cytus1/2的黑P。算法没变所以是通用的。\n"
		"格式是\"艾特机绿算黑p tp perfect good bad miss\"，其中good、bad、miss可选，p大小写均可。当然私聊也可以。只要把艾特机绿去掉就可以了。\n"
		"举例：（私聊）算黑P 99.44 1506；（群聊）@机绿算黑p 99.35 1567 0 0 3\n"
		"祝收歌愉快（笑";
};

class BlackCalculatePrivate final : public CytusResult
{
private:
	const string kmm_regex_ = "算黑[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})";
	const string knm_regex_ = "算黑[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})";

public:
	void Main(const int64_t qq, const string msg);
	string ShowResult(const int64_t qq);
	void ShowHelpInfo(const int64_t qq, const string msg);
};

class BlackCalculateGroup final : public CytusResult
{
private:
	const string kmm_regex_ = util::kat_beryl_regex + "算黑[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})";
	const string knm_regex_ = util::kat_beryl_regex + "算黑[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})";

public:
	void Main(const int64_t group, const int64_t qq, const string msg);
	string ShowResult(const int64_t group, const int64_t qq);
};