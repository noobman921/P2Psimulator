#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
#include "node.h"
using namespace std;
// 节点类
Node::Node(int x1, int y1, int num1)
{
    x = x1;
    y = y1;
    num = num1;
    neibor_head = NULL;
    neibor_tail = NULL;
}

void Node::AddNeibor(Node *ptr, int num, int dis)
{
    NeiborNode *new_neibor = new NeiborNode(ptr, num, dis);

    if (neibor_head == NULL)
    {
        neibor_head = new_neibor;
        neibor_tail = new_neibor;
    }
    else
    {
        // 排序是否在这里做好？
        NeiborNode *ptr = neibor_head;
        // 找到第一个大于新邻居的节点 或 空节点
        while (ptr->next != NULL && ptr->next->dis < new_neibor->dis)
        {
            ptr = ptr->next;
        }

        if (ptr->next == NULL)
        {
            // 空的 直接接到链表尾
            neibor_tail->next = new_neibor;
            new_neibor->pre = neibor_tail;
            neibor_tail = new_neibor;
        }
        else
        {
            // 非空 接到中间
            new_neibor->next = ptr->next;
            new_neibor->pre = ptr;
            ptr->next->pre = new_neibor;
            ptr->next = new_neibor;
        }
    }
}

NeiborNode::NeiborNode(Node *ptr1, int num1, int dis1)
{
    ptr = ptr;
    num = num;
    dis = dis;
    next = NULL;
    pre = NULL;
}

Server::Server(int x1, int y1, int num1) : Node(x1, y1, num1)
{
    data_start = 0;
    data_end = 0;
}

Client::Client(int x1, int y1, int num1) : Node(x1, y1, num1) {}

void Client::AddData(int data_num)
{
    DataNode *ptr = new DataNode(data_num); // 指向新节点
    // 一个数据块都无
    if (cache_head == NULL)
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
    // 没写完的东西 包括数据块全为顺序的情况 插入表尾还是不是顺序表
    //            数据块有非顺序 如果插入cache_comptr后顺序表会不会扩大
}

DataNode::DataNode(int num)
{
    data_num = num;
    next = NULL;
    pre = NULL;
}
void perFrame(long long time)
{
    // 一秒视为一帧 在一帧内进行所有处理
    // 处理完毕
    time++;
}
