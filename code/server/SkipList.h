#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// 跳表节点定义
class SkipNode {
public:
    string key;                        // 用户名
    string value;                      // 密码
    vector<SkipNode*> forward;         // 指向下一个节点的指针

    // 构造函数
    SkipNode(const string& key, const string& value, int level);
};

// 跳表类定义
class SkipList {
private:
    SkipNode* header;                  // 跳表头节点
    int maxLevel;                      // 最大层数
    float probability;                 // 层数生成概率
    int currentLevel;                  // 当前跳表实际层数

    // 随机生成跳表节点的层数
    int randomLevel();

public:
    // 构造函数
    SkipList(int maxLevel = 16, float probability = 0.5);

    // 插入数据
    void skipInsert(const string& key, const string& value);

    // 查询用户是否存在
    bool skipFind(const string& key);

    bool changePassword(const string& key, const string& newvalue);





    // 析构函数
    ~SkipList();

private:
    // 获取密码
    string getPassword(const string& key);
};

#endif // SKIPLIST_H
