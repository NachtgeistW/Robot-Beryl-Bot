#pragma once

#include "cqdefine.h"

#include <string>
#include <map>
#include <vector>

class Unpack;
namespace CQ {
	//增加运行日志
	int addLog(int 优先级, const char* 类型, const char* 内容);

	//发送好友消息
	//Auth=106 失败返回负值,成功返回消息ID
	int sendPrivateMsg(int64_t QQ, const char* msg);
	//发送好友消息
	//Auth=106 失败返回负值,成功返回消息ID
	int sendPrivateMsg(int64_t QQ, std::string&msg);

	//发送群消息
	//Auth=101 失败返回负值,成功返回消息ID
	int sendGroupMsg(int64_t 群号, const char* msg);
	//发送群消息
	//Auth=101 失败返回负值,成功返回消息ID
	int sendGroupMsg(int64_t 群号, std::string&msg);

	//发送讨论组消息
	//Auth=103 失败返回负值,成功返回消息ID
	int sendDiscussMsg(int64_t 讨论组号, const char* msg);
	//发送讨论组消息
	//Auth=103 失败返回负值,成功返回消息ID
	int sendDiscussMsg(int64_t 讨论组号, std::string&msg);

	//发送赞 Auth=110
	int sendLike(int64_t QQID, int times);

	//取Cookies,Auth=20 慎用,此接口需要严格授权
	const char* getCookies();

	//接收语音
	const char* getRecord(
		const char* file, // 收到消息中的语音文件名 (file)
		const char* outformat // 应用所需的格式 mp3,amr,wma,m4a,spx,ogg,wav,flac
	);
	//接收语音
	std::string getRecord(
		std::string&file, // 收到消息中的语音文件名 (file)
		std::string outformat // 应用所需的格式 mp3,amr,wma,m4a,spx,ogg,wav,flac
	);

	//取CsrfToken (慎用，此接口需要严格授权)
	//Auth=20 即QQ网页用到的bkn/g_tk等 慎用,此接口需要严格授权
	int getCsrfToken();

	//取应用目录,返回的路径末尾带"\"
	const char* getAppDirectory();

	//取登录QQ
	int64_t getLoginQQ();

	//取登录昵称
	const char* getLoginNick();

	//置群员移除 Auth=120
	int setGroupKick(
		int64_t 群号, int64_t QQID,
		int 拒绝再加群 = false // 如果为真，则“不再接收此人加群申请”，请慎用
	);

	//置群员禁言 Auth=121
	int setGroupBan(
		int64_t 群号, int64_t QQID,
		int64_t 禁言时间 = 60 // 禁言的时间，单位为秒。如果要解禁，这里填写0
	);

	//置群管理员 Auth=122
	int setGroupAdmin(
		int64_t 群号, int64_t QQID,
		int 成为管理员 = true // 真/设置管理员 假/取消管理员
	);

	//置群成员专属头衔 Auth=128 需群主权限
	int setGroupSpecialTitle(
		int64_t 群号, int64_t QQID,
		const char* 头衔, // 如果要删除，这里填空
		int64_t = -1 // 专属头衔有效期，单位为秒。如果永久有效，这里填写-1
	);
	//置群成员专属头衔 Auth=128 需群主权限
	int setGroupSpecialTitle(
		int64_t 群号, int64_t QQID,
		std::string&头衔, // 如果要删除，这里填空
		int64_t 过期时间 = -1 // 专属头衔有效期，单位为秒。如果永久有效，这里填写-1
	);

	//置全群禁言 Auth=123
	int setGroupWholeBan(
		int64_t 群号,
		int 开启禁言 = true // 真/开启 假/关闭
	);

	//置匿名群员禁言 Auth=124
	int setGroupAnonymousBan(
		int64_t 群号,
		const char* 匿名, // 群消息事件收到的“匿名”参数
		int64_t 禁言时间 = 60 // 禁言的时间，单位为秒。不支持解禁
	);

	//置群匿名设置 Auth=125
	int setGroupAnonymous(int64_t 群号, int 开启匿名 = true);

	//置群成员名片 Auth=126
	int setGroupCard(int64_t 群号, int64_t QQID, const char* 新名片_昵称);

	//置群成员名片 Auth=126
	int setGroupCard(int64_t 群号, int64_t QQID, std::string 新名片_昵称);

	//置群退出 Auth=127 慎用,此接口需要严格授权
	int setGroupLeave(
		int64_t 群号,
		int 是否解散 = false // 真/解散本群 (群主) 假/退出本群 (管理、群成员)
	);

	//置讨论组退出 Auth=140
	int setDiscussLeave(
		int64_t 讨论组号
	);

	//置好友添加请求 Auth=150
	int setFriendAddRequest(
		const char* 请求反馈标识, // 请求事件收到的“反馈标识”参数
		int 反馈类型, // #请求_通过 或 #请求_拒绝
		const char* 备注 // 添加后的好友备注
	);

	//置群添加请求 Auth=151
	int setGroupAddRequest(
		const char* 请求反馈标识, // 请求事件收到的“反馈标识”参数
		int 请求类型, // 根据请求事件的子类型区分 #请求_群添加 或 #请求_群邀请
		int 反馈类型, // #请求_通过 或 #请求_拒绝
		const char* 理由 // 操作理由，仅 #请求_群添加 且 #请求_拒绝 时可用
	);

	//置致命错误提示,暂时不知道干什么用的
	int setFatal(const char* 错误信息);

	class GroupMemberInfo;
	//取群成员信息 (支持缓存) Auth=130
	GroupMemberInfo getGroupMemberInfo(int64_t 群号, int64_t QQID, int 不使用缓存 = false);

	class StrangerInfo;
	//取陌生人信息 (支持缓存) Auth=131
	StrangerInfo getStrangerInfo(int64_t QQID, int 不使用缓存 = false);

	//取群成员列表 Auth=160
	std::vector<GroupMemberInfo> getGroupMemberList(int64_t 群号);

	//取群列表 Auth=161
	std::map<long long, std::string> getGroupList();

	//撤回消息 Auth=180
	int deleteMsg(int64_t MsgId);

	const char * getlasterrmsg();

	// 群成员信息
	class GroupMemberInfo
	{
		void Void();
		void setdata(Unpack&pack);
	public:
		int64_t Group;
		int64_t QQID;
		std::string 昵称;
		std::string 名片;
		int 性别; // 0/男性 1/女性
		int 年龄;
		std::string 地区;
		int 加群时间;
		int 最后发言;
		std::string 等级_名称;
		int permissions; //1/成员 2/管理员 3/群主
		std::string 专属头衔;
		int 专属头衔过期时间; // -1 代表不过期
		int 不良记录成员;
		int 允许修改名片;

		GroupMemberInfo(Unpack& msg);
		GroupMemberInfo(const char* msg);//从API解码
		GroupMemberInfo(std::vector<unsigned char> msg);//从Unpack解码
		GroupMemberInfo() = default;

		std::string tostring() const;
	};

	// 陌生人信息
	class StrangerInfo
	{
	public:
		int64_t QQID;
		std::string nick;//昵称
		int sex;//0/男性 1/女性 255/未知
		int age;//年龄

		StrangerInfo(const char* msg);
		StrangerInfo() = default;

		std::string tostring() const;
	};
}