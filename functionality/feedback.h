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
	const string kgroup_regex_ = "(\\[CQ:at,qq=)(" + util::int64_ttos(util::Beryl) + ")(\\])(.*)(����|����������)(.*)";
	const string kprivate_regex_ = "(����|����������)(.*)";
	std::smatch feedback_match_;
};
