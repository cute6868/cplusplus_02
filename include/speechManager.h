#pragma once
#include"speaker.h"
#include<vector>
#include<map>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<fstream>
#include<ctime>


// 演讲比赛管理类
class SpeechManager
{
public:
	// 成员属性:
	// 存放 第一轮比赛选手编号 的容器
	std::vector<int> v1;

	// 存放 第一轮晋级选手编号 的容器
	std::vector<int> v2;

	// 存放 胜出前三名选手编号 的容器
	std::vector<int> v3;

	// 存放 编号和对应具体选手 的容器
	std::map<int, Speaker> m1;

	// 存放 比赛的轮数
	int round;

	// 标志文件是否为空
	bool fileIsEmpty;

	// 存放往届记录的容器
	std::map<int, std::vector<std::string>> record;

	// 构造函数-声明
	SpeechManager();

	// 析构函数-声明
	~SpeechManager();

	// 显示菜单-声明 {功能}
	void Show_Menu();

	// 退出系统-声明 {功能}
	void ExitSystem();

	// 初始化容器和属性-声明
	void initSpeech();

	// 创建12个选手-声明
	void createSpeaker();

	// 抽签-声明
	void speechDraw();

	// 比赛-声明
	void speechContest();

	// 显示比赛分数-声明
	void showScore();

	// 保存记录-声明
	void saveRecord();

	// 比赛初始化-声明
	void init();

	// 开始比赛-声明
	void StartSpeech();

	// 加载记录-声明
	void loadRecord();

	// 查看记录-声明 {功能}
	void ShowRecord();

	// 清空记录-声明 {功能}
	void ClearRecord();
};