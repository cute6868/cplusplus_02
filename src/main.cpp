#include "speechManager.h"
using namespace std;


int main()
{
	// 添加随机数种子
	srand((unsigned int)time(NULL));

	// 创建一个管理对象，管理整个演讲比赛的事务
	SpeechManager sm;

	//// 测试12名选手的创建
	//for (map<int, Speaker>::iterator it = sm.m1.begin(); it != sm.m1.end(); it++)
	//{
	//	cout << "编号：" << it->first << "姓名：" << it->second.m_Name << "分数：" << it->second.m_Score[0] << endl;
	//}

	// 存储用户的选项
	int choice = 0;

	while (true)
	{
		// 显示菜单
		sm.Show_Menu();

		// 获取用户选择
		cout << "请输入您的选择：";
		cin >> choice;

		// 根据用户的选择，执行对应的功能
		switch (choice)
		{
		case 1:	// 开始比赛
			sm.StartSpeech();
			break;
		case 2:	// 查看记录
			sm.ShowRecord();
			break;
		case 3:	// 清空记录
			sm.ClearRecord();
			break;
		case 0:	// 退出系统
			sm.ExitSystem();
			break;
		default:
			break;
		}

		system("pause");	// 暂停让用户查看执行信息
		system("cls");		// 执行清屏操作
	}

	return 0;
}