#pragma once
#include<iostream>
#include<string>

#define FirstSpeakerID 10001	// ��һ��ѡ�ֵı�ţ�ע�⣺���ֻ����int���ͣ�����ѡ�ֵı�Ż��Զ�+1

// �����ݽ�ѡ����
class Speaker
{
public:
	std::string m_Name;		// ����
	double m_Score[2];		// ��������������ֵ÷�
};