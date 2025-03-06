#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
using namespace std;
// 节点类
class Node
{   
    int x;
    int y;
    int num; // 序号
    //邻接表
public:
// 初始化节点
    NeiborNode *neibor_head;//表头
    NeiborNode *neibor_tail;
    Node(int x1, int y1, int num1)
    {
        x = x1;
        y = y1;
        num = num1;
        neibor_head = NULL;
        neibor_tail = NULL;
    }
    void AddNeibor(Node *ptr, int num, int dis)
    {
        NeiborNode *new_neibor = new NeiborNode(ptr, num ,dis);
        
        if (neibor_head == NULL)
        {
            neibor_head = new_neibor;
            neibor_tail = new_neibor;
        }
        else
        {
            //排序是否在这里做好？
            NeiborNode *ptr = neibor_head;
            //找到第一个大于新邻居的节点 或 空节点
            while(ptr->next != NULL && ptr->next->dis < new_neibor->dis)
            {
                ptr = ptr->next;
            }

            if(ptr->next == NULL)
            {   
                //空的 直接接到链表尾
                neibor_tail->next = new_neibor;
                new_neibor->pre = neibor_tail;
                neibor_tail = new_neibor;
            }
            else
            {
                //非空 接到中间
                new_neibor->next = ptr->next;
                new_neibor->pre = ptr;
                ptr->next->pre = new_neibor;
                ptr->next = new_neibor;
            }
        }
    }
};
//邻接表节点
class NeiborNode
{
public:
    int num;//序号
    int dis;//与对应节点的距离
    Node *ptr;//指向对应序号的节点
    NeiborNode *next;//指向下一个邻接表节点
    NeiborNode *pre;
    NeiborNode(Node *ptr1, int num1, int dis1)
    {
        ptr = ptr;
        num = num;
        dis = dis;
        next = NULL;
        pre = NULL;
    }
};

// 服务端
class Server : public Node
{
public:
    int data_start; // 产生的数据库从哪到哪
    int data_end;
    Server(int x1, int y1, int num1) : Node(x1, y1, num1)
    {
        data_start = 0;
        data_end = 0;
    }
} ;

// 客户端类
class Client : public Node
{
public:
    //  用链表实现缓存数据块
    DataNode *cache_head;
    DataNode *cache_comptr; // 指向最后一个顺序的节点
    DataNode *cache_tail;
    int N; // 缓存大小
    int M; // 播放条件
    // 在客户端上维护一个长度为N的缓存队列,新到达的数据分块会将最老的数据块进行覆盖。看不懂，像栈一样？
    //上面的内容就可以实现 只需要把旧的节点从中移除并释放就行
    Client(int x1, int y1, int num1) : Node(x1, y1, num1){};
    void AddData(int data_num)
    {
        DataNode *ptr = new DataNode(data_num);//指向新节点
        //一个数据块都无
        if(cache_head == NULL)
        {
            cache_head = ptr;
            return;
        }
        // DataNode *temp_ptr = cache_comptr;//临时指针 用于遍历
        // while(temp_ptr->next != NULL && temp_ptr->next->data_num <= ptr->data_num){
        //     temp_ptr = temp_ptr->next;
        // }
        // if(temp_ptr == cache_comptr){
        //     //在第一个
        // }
        //没写完的东西 包括数据块全为顺序的情况 插入表尾还是不是顺序表
        //            数据块有非顺序 如果插入cache_comptr后顺序表会不会扩大
    }

};
// data N数据块
// 数据节点
class DataNode // 采用链表存储数据块
{
public:
    int data_num; // 数据块序号
    // 数据块放这里？
    struct DataNode *next;
    struct DataNode *pre;
    DataNode(int num){
        data_num = num;
        next = NULL;
        pre = NULL;
    }
};

void perFrame(long long time)
{   
    // 一秒视为一帧 在一帧内进行所有处理

    //处理完毕
    time++;
}   
int main()
{
    long long time = 0;
    while (1)
    {
        
        perFrame(time);

    }
    return 0;
}