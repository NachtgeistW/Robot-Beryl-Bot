#pragma once
#include "../../util/util.h"
#include <regex>
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
		return tp == round(res * 100) / 100.00;
	};
	void SetCytusResult(const double tp_int, const double tp_frac, const double perfect, const double miss, const double bad, const double good);
	void Initialize(void) noexcept { perfect_ = 0, black_perfect_ = 0, good_ = 0, bad_ = 0, miss_ = 0, tp_ = 0; };
	std::pair<bool, int> Match(const string msg);
protected:
	double perfect_ = 0, black_perfect_ = 0, good_ = 0, bad_ = 0, miss_ = 0, tp_ = 0;
};

class BlackCalculatePrivate final : public CytusResult
{
private:
	const string kmm_regex_ = "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})";
	const string knm_regex_ = "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})";

public:
	void Main(const int64_t qq, const string msg);
	void ShowResult(const int64_t qq);
};

class BlackCalculateGroup final : public CytusResult
{
private:
	const string kmm_regex_ = util::kat_beryl_regex + "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})";
	const string knm_regex_ = util::kat_beryl_regex + "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})";

public:
	void Main(const int64_t group, const int64_t qq, const string msg);
	void ShowResult(const int64_t group, const int64_t qq);
};