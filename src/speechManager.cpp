#include "speechManager.h"
using namespace std;

// 构造函数-实现
SpeechManager::SpeechManager()
{
	// 初始化比赛要用的东西
	init();
}


// 析构函数-实现
SpeechManager::~SpeechManager()
{

}


// 显示菜单-实现 {功能}
void SpeechManager::Show_Menu()
{
	cout << "********************************" << endl;
	cout << "*****   欢迎参加演讲比赛   *****" << endl;
	cout << "******  1. 开始演讲比赛  *******" << endl;
	cout << "******  2. 查看往届记录  *******" << endl;
	cout << "******  3. 清空比赛记录  *******" << endl;
	cout << "******  0. 退出比赛程序  *******" << endl;
	cout << endl;
}


// 退出系统-实现 {功能}
void SpeechManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}


// 初始化容器和属性-实现
void SpeechManager::initSpeech()
{
	// 容器都置空
	this->v1.clear();
	this->v2.clear();
	this->v3.clear();
	this->m1.clear();
	this->record.clear();

	// 初始化比赛的轮数
	this->round = 1;
}


// 创建12个选手-实现
void SpeechManager::createSpeaker()
{
	// 12个选手，分别叫 选手A、选手b、选手c......
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		// 拼接出选手的名字
		string name = "选手";
		name += nameSeed[i];

		// 实例化一个选手
		Speaker s;

		// 初始化选手的名字
		s.m_Name = name;

		// 初始化选手两轮的分数
		for (int i = 0; i < 2; i++)
		{
			s.m_Score[i] = 0;
		}

		// 给该选手定义一个编号，并将该编号放到 v1 容器中
		int id = i + FirstSpeakerID;
		this->v1.push_back(id);

		// 将选手自己，和它的编号，一起存放到 map 容器中（ 即：this->m1 ）
		this->m1.insert(make_pair(id, s));
	}
}


// 抽签-实现
void SpeechManager::speechDraw()
{
	cout << endl << endl;
	cout << "第 << " << this->round << " >> 轮比赛选手正在抽签" << endl << endl;
	cout << "----------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;


	if (this->round == 1)
	{
		// 第一轮比赛（打乱v1容器）
		// 输出打乱后的容器内容
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator iterator = v1.begin(); iterator != v1.end(); iterator++)
		{
			cout << *iterator << " ";
		}
		cout << endl;
	}
	else
	{
		// 第二轮比赛（打乱v2容器）
		random_shuffle(v2.begin(), v2.end());
		// 输出打乱后的容器内容
		for (vector<int>::iterator iterator = v2.begin(); iterator != v2.end(); iterator++)
		{
			cout << *iterator << " ";
		}
		cout << endl;
	}

	cout << "----------------------------------------------" << endl << endl;
	system("pause");
	cout << endl;
}


// 比赛-实现
void SpeechManager::speechContest()
{
	cout << "------------第" << this->round << "轮比赛正式开始------------" << endl << endl;

	// 临时的小组容器，保存分数和选手编号
	multimap<double, int, greater<double>> groupScore;

	// 记录当前是第几个选手
	int num = 0;

	// 装比赛的人员容器
	vector<int> v;
	if (this->round == 1) { v = v1; }
	else { v = v2; }

	// 遍历所有参赛选手
	for (vector<int>::iterator iterator = v.begin(); iterator != v.end(); iterator++)
	{
		// 记录当前是第几个选手
		num++;

		// 评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;		// 600 ~ 1000
			d.push_back(score);
		}

		// 计算平均分
		sort(d.begin(), d.end(), greater<double>());	// 降序排序
		d.pop_front();	// 去除最高分
		d.pop_back();	// 去除最低分
		double sum = accumulate(d.begin(), d.end(), 0.0f);	// 总分
		double avg = sum / (double)d.size();	// 平均分

		// 将平均分存到map容器中
		this->m1[*iterator].m_Score[this->round - 1] = avg;

		// 将打分数据 放入到临时小组容器中
		groupScore.insert(make_pair(avg, *iterator));

		// 每6个人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次:" << endl << endl;

			// 输出小组内所有选手的得分信息
			for (multimap<double, int, greater<double>>::iterator iterator = groupScore.begin(); iterator != groupScore.end(); iterator++)
			{
				cout << "编号：" << iterator->second << " 姓名：" << this->m1[iterator->second].m_Name
					<< " 得分：" << this->m1[iterator->second].m_Score[this->round - 1] << endl;
			}
			cout << endl;

			// 取走每个小组中前三名的选手
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator iterator = groupScore.begin(); iterator != groupScore.end() && count < 3; iterator++)
			{
				if (this->round == 1)
				{
					v2.push_back(iterator->second);
				}
				else
				{
					v3.push_back(iterator->second);
				}
				count++;
			}

			// 清除容器里已经输出过信息的小组选手
			groupScore.clear();
		}
	}

	cout << "------------第" << this->round << "轮比赛结束------------" << endl << endl;
	system("pause");
	cout << endl;
}


// 显示比赛分数-实现
void SpeechManager::showScore()
{
	cout << "-----------第" << this->round << "轮晋级选手信息-----------" << endl << endl;
	vector<int> v;
	if (this->round == 1)
	{
		v = v2;
	}
	else
	{
		v = v3;
	}

	for (vector<int>::iterator iterator = v.begin(); iterator != v.end(); iterator++)
	{
		cout << "选手编号：" << *iterator << " 姓名：" << this->m1[*iterator].m_Name
			<< " 得分：" << this->m1[*iterator].m_Score[this->round - 1] << endl;
	}
	cout << endl;
	system("pause");
	cout << endl;
}


// 保存记录-实现
void SpeechManager::saveRecord()
{
	ofstream file;
	file.open("speech.csv", ios::out | ios::app);	// 用输出的方式打开文件

	// 将每个人数据写入到文件中
	for (vector<int>::iterator iterator = v3.begin(); iterator != v3.end(); iterator++)
	{
		file << *iterator << "," << this->m1[*iterator].m_Score[1] << ",";
	}
	file << endl;

	// 关闭文件
	file.close();

	cout << "\n记录已自动保存" << endl << endl;
}


// 比赛初始化-实现
void SpeechManager::init()
{
	// 初始化容器和属性
	initSpeech();

	// 创建12个选手
	createSpeaker();

	// 获取往届记录
	this->loadRecord();
}


// 开始比赛-实现 {功能}
void SpeechManager::StartSpeech()
{	
	// 第一轮比赛
	// 1.抽签
	speechDraw();

	// 2.比赛
	speechContest();

	// 3.显示结果
	showScore();

	// 第二轮比赛
	this->round++;

	// 1.抽签
	speechDraw();

	// 2.比赛
	speechContest();

	// 3.显示结果
	showScore();

	// 4.保存分数
	saveRecord();

	// 重置，实现数据的更新
	init();
}


// 加载记录-实现
void SpeechManager::loadRecord()
{
	ifstream file("speech.csv", ios::in);
	
	// 文件不存在的情况
	if (!file.is_open())
	{
		this->fileIsEmpty = true;
		file.close();
		return;
	}

	// 文件内容为空的情况
	char ch;
	file >> ch;
	if (file.eof())		// EOF: End Of File
	{
		this->fileIsEmpty = true;
		file.close();
		return;
	}

	// 文件不为空
	this->fileIsEmpty = false;

	file.putback(ch);	// 将上面读取的单个字符 放回来
	string data;
	int index = 0;		// 用来标志是第几届

	while (file >> data)
	{
		//cout << data << endl;		// 测试输出：10002,86.675,10009,81.3,10007,78.55,

		vector<string> v;	// 存放6个string字符串
		
		int pos = -1;	// 逗号的位置
		int start = 0;	// 查找的起始位置

		while (true)
		{
			// 查找逗号，如果查找不到默认返回-1，如果查找得到，返回其对应的位置
			pos = data.find(",", start);

			// 没有找到逗号的情况
			if (pos == -1)
			{
				break;
			}

			// 找到逗号的情况，获取子串
			string temp = data.substr(start, pos - start);

			// 放到专门存放这一届数据的容器中
			v.push_back(temp);

			// 更新开始的位置
			start = pos + 1;
		}

		// 往大容器中放入，装满了这一届数据的小容器
		this->record.insert(make_pair(index, v));

		// 继续下一届的数据
		index++;
	}
	file.close();
}


// 查看记录-实现 {功能}
void SpeechManager::ShowRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
		return;
	}

	// 获取每一届的冠军、亚军、季军数据
	for (int i = 0; i < this->record.size(); i++)
	{
		cout << "第" << i + 1 << "届\t"
			<< "  | 冠军编号：" << this->record[i][0] << "  得分：" << this->record[i][1]
			<< "  | 亚军编号：" << this->record[i][0] << "  得分：" << this->record[i][1]
			<< "  | 季军编号：" << this->record[i][0] << "  得分：" << this->record[i][1] << endl;
	}
}


// 清空记录-声明 {功能}
void SpeechManager::ClearRecord()
{
	int select;
	cout << endl;
	cout << "确认清空？" << endl;
	cout << "1. 确认" << endl;
	cout << "2. 取消" << endl;
	cout << ">>> ";
	cin >> select;

	if (select == 1)
	{
		// 打开模式 ios::trunc ~~~ 如果文件存在，则删除文件并重新创建
		ofstream file("speech.csv", ios::trunc);
		file.close();

		// 刷新数据，初始化操作
		init();

		// 输出提示信息
		cout << "清除成功！" << endl;
	}
}
