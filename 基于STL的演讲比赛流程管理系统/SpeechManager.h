#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <numeric>
#include <fstream>
using namespace std;

/*
* �ṩ�����˵�����
* �����̽��п���
* �ļ���д����
*/

//����ݽ�����������
class SpeechManager {
public:

    //���캯��
    SpeechManager();
    //��������
    ~SpeechManager();

    //����ѡ��
    vector<int> v1;
    //�μӵڶ���ѡ��
    vector<int> v2;
    //ǰ����
    vector<int> vWinner;
    //��ź�ѡ�ֵ�ӳ��
    map<int, Speaker> speakers;
    //�����ִ���
    int index;
    //�ж��ļ��Ƿ�Ϊ��
    bool fileIsEmpty;
    //����������map
    map <int, vector<string>> record;

    //չʾ�˵�
    void showMeun();
    //��ʼ����������
    void initSpeech();
    //����ѡ��
    void creatSpeaker();
    //��ʼ����
    void startSpeech();
    //��ǩ
    void speechBallot();
    //����
    void speechContest();
    //��ʾ������Ա����
    void showScore();
    //�����¼
    void saveRecord();
    //��ȡ�ļ�
    void loadRecord();
    //��ӡ��¼
    void showRecord();
    //��ռ�¼
    void clearRecord();
    //�˳�ϵͳ
    void exitSystem();
    
};