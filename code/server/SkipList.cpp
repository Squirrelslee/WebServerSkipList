#include "SkipList.h"
#include <cstdlib>
#include <ctime>

// SkipNode 构造函数
SkipNode::SkipNode(const string& key, const string& value, int level)
    : key(key), value(value), forward(level, nullptr) {}

// 随机生成跳表节点的层数
int SkipList::randomLevel() {
    int level = 1;
    while (rand() % 2 == 0 && level < maxLevel) {
        level++;
    }
    return level;
}

// SkipList 构造函数
SkipList::SkipList(int maxLevel, float probability)
    : maxLevel(maxLevel), probability(probability), currentLevel(1) {
    srand(time(0));  // 随机种子
    header = new SkipNode("", "", maxLevel);  // 初始化空头节点
}

// 插入数据
void SkipList::skipInsert(const string& key, const string& value) {
    vector<SkipNode*> update(maxLevel, nullptr);  // 更新路径
    SkipNode* current = header;

    // 从最高层开始查找插入位置
    for (int i = currentLevel - 1; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // 检查是否已存在此用户
    current = current->forward[0];
    if (current != nullptr && current->key == key) {
        throw runtime_error("User already exists.");
    }

    // 随机生成新节点的层数
    int newLevel = randomLevel();
    if (newLevel > currentLevel) {
        for (int i = currentLevel; i < newLevel; ++i) {
            update[i] = header;
        }
        currentLevel = newLevel;
    }

    // 创建新节点并插入
    current = new SkipNode(key, value, newLevel);
    for (int i = 0; i < newLevel; ++i) {
        current->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = current;
    }
}

// 查询用户是否存在
bool SkipList::skipFind(const string& key) {
    SkipNode* current = header;
    for (int i = currentLevel - 1; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];  // 到达第一个节点

    return current != nullptr && current->key == key;
    current->value
}


//changePassword
bool SkipList::changePassword(const string& key, const string& newvalue) {
    if(skipFind(key))
    SkipNode* current = header;
    for(int i = currentLevel - 1; i >= 0; --i) {
        while(current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];//find key to change password
    current->value = newvalue;//change password;
    return true;
    else
    return false;
    
}

// 获取用户密码
string SkipList::getPassword(const string& key) {
    SkipNode* current = header;
    for (int i = currentLevel - 1; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];  // 到达第一个节点

    if (current != nullptr && current->key == key) {
        return current->value;  // 返回密码
    } else {
        throw runtime_error("User not found.");
    }
}



// 跳表析构函数
SkipList::~SkipList() {
    SkipNode* current = header;
    while (current != nullptr) {
        SkipNode* next = current->forward[0];
        delete current;
        current = next;
    }
}
