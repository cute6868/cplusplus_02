#pragma once
#include<iostream>
#include<string>

#define FirstSpeakerID 10001	// 第一个选手的编号，注意：编号只能是int类型，其他选手的编号会自动+1

// 创建演讲选手类
class Speaker
{
public:
	std::string m_Name;		// 姓名
	double m_Score[2];		// 分数，最多有两轮得分
};