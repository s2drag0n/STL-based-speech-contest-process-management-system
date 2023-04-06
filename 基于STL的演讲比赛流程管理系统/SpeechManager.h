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
* 提供交互菜单界面
* 对流程进行控制
* 文件读写交互
*/

//设计演讲比赛管理类
class SpeechManager {
public:

    //构造函数
    SpeechManager();
    //析构函数
    ~SpeechManager();

    //比赛选手
    vector<int> v1;
    //参加第二轮选手
    vector<int> v2;
    //前三名
    vector<int> vWinner;
    //编号和选手的映射
    map<int, Speaker> speakers;
    //比赛轮次数
    int index;
    //判断文件是否为空
    bool fileIsEmpty;
    //往届比赛结果map
    map <int, vector<string>> record;

    //展示菜单
    void showMeun();
    //初始化比赛函数
    void initSpeech();
    //创建选手
    void creatSpeaker();
    //开始比赛
    void startSpeech();
    //抽签
    void speechBallot();
    //比赛
    void speechContest();
    //显示晋级成员分数
    void showScore();
    //保存记录
    void saveRecord();
    //读取文件
    void loadRecord();
    //打印记录
    void showRecord();
    //清空记录
    void clearRecord();
    //退出系统
    void exitSystem();
    
};