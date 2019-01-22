#pragma once
#include "../../util/util.h"
#include <regex>

class ResultInfo
{
public:
	ResultInfo() = default;
	~ResultInfo() = default;
	int calculation(void);
	void SetResultNum(double tp_int, double tp_frac, double perfect, double good, double bad, double miss);
	void SetResultNum(double tp_int, double tp_frac, double perfect);
	void ShowResult(int64_t group, int64_t qq);
	void ShowResult(int64_t qq);
	void Main(int64_t group, int64_t qq, string msg);
	void Main(int64_t qq, string msg);
	void Clear(void) { perfect = 0, black_perfect = 0, good = 0, bad = 0, miss = 0, tp = 0; };
private:
	double perfect = 0, black_perfect = 0, good = 0, bad = 0, miss = 0, tp = 0;
	string MM = util::kat_beryl + "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})";
	string NM = util::kat_beryl + "ËãºÚ[p|P]\\s+(\\d{1,3})\\.(\\d{1,2})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})\\s+(\\d{1,4})";
};

inline int ResultInfo::calculation(void)
{
	return round(perfect / 0.3 + good - tp * (perfect + good + bad + miss) / 30);
}
