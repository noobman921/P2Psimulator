#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
using namespace std;
// 节点类
typedef struct Node
{
    int x;
    int y;
    int num; // 序号
} Node;

// 服务端类
typedef struct Server
{
    Node node;
    int data_start; // 产生的数据库从哪到哪
    int data_end;
} Server;

// 客户端类
typedef struct Client
{
    Node node;

    //  用链表实现缓存数据块
    struct DataNode *cache_head;
    struct DataNode *cache_comptr; // 指向第一个非顺序的节点
    struct DataNode *cache_tail;
    int N; // 缓存大小
    int M; // 播放条件
    // 在客户端上维护一个长度为N的缓存队列,新到达的数据分块会将最老的数据块进行覆盖。看不懂，像栈一样？
    // 要有连续的5个分块
} Client;
// data N数据块
// 数据节点
typedef struct DataNode // 采用链表存储数据块
{
    int data_num; // 数据块序号
    // 数据块放这里？
    struct DataNode *next;
    struct DataNode *pre;
} DataNode;

void perFrame()
{
    // 一秒视为一帧 在一帧内进行所有处理
}
int main()
{
    time_t start_time, current_time;
    time(&start_time);
    while (1)
    {
        time(&current_time);
        if (difftime(current_time, start_time) >= 1)
        {
            perFrame();
            start_time = current_time;
        }
    }
    return 0;
}