#pragma once
#include "../util/util.h"
class Feedback
{
public:
	Feedback() = default;
	string FeedbackGroup(const int64_t groupID, const int64_t qq, const string msg);
	string FeedbackPrivate(const int64_t qq, const string msg);
	~Feedback() = default;

private:
	const string kgroup_regex_ = "(\\[CQ:at,qq=)(" + util::int64_ttos(util::Beryl) + ")(\\])(.*)(反馈|告诉你主人)(.*)";
	const string kprivate_regex_ = "(反馈|告诉你主人)(.*)";
	std::smatch feedback_match_;
};
