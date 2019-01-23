#pragma once
#include "../../util/util.h"
#include <regex>

class CytusResult
{
public:
	CytusResult() = default;
	~CytusResult() = default;
	int Calculate(void) { return round(perfect_ / 0.3 + good_ - tp_ * (perfect_ + good_ + bad_ + miss_) / 30); };
	bool Verify(const double tp, const int calculated_black_perfect);
	void SetCytusResult(double tp_int, double tp_frac, double perfect, double good, double bad, double miss);
	void SetCytusResult(double tp_int, double tp_frac, double perfect);
	void Clear(void) { perfect_ = 0, black_perfect_ = 0, good_ = 0, bad_ = 0, miss_ = 0, tp_ = 0; };
protected:
	double perfect_ = 0, black_perfect_ = 0, good_ = 0, bad_ = 0, miss_ = 0, tp_ = 0;
};

class BlackCalculatePrivate : public CytusResult
{
private:
	const string kmm_regex_ = "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})";
	const string knm_regex_ = "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})";

public:
	void Main(const int64_t qq, const string msg);
	void ShowResult(const int64_t qq);
};

class BlackCalculateGroup : public CytusResult
{
private:
	const string kmm_regex_ = util::kat_beryl_regex + "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})";
	const string knm_regex_ = util::kat_beryl_regex + "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})";

public:
	void Main(const int64_t group, const int64_t qq, const string msg);
	void ShowResult(const int64_t group, const int64_t qq);
};