#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
#include "node.h"
using namespace std;
// 节点类
Node::Node(int id1, int x1, int y1)
{
    x = x1;
    y = y1;
    id = id1;
    neibor_head = NULL;
    neibor_tail = NULL;
}

void Node::AddNeibor(Node *ptr, int id, int dis)
{
    NeiborNode *new_neibor = new NeiborNode(ptr, id, dis);

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

NeiborNode::NeiborNode(Node *ptr1, int id1, int dis1)
{
    ptr = ptr;
    id = id;
    dis = dis;
    next = NULL;
    pre = NULL;
}

Server::Server(int x1, int y1, int id1) : Node(x1, y1, id1)
{
    data_start = 0;
    data_end = 0;
}
Server::Server() : Node() {}
Client::Client(int x1, int y1, int id1) : Node(x1, y1, id1) {}
Client::Client() : Node() {}

void Client::AddData(int data_id)
{
    DataNode *ptr = new DataNode(data_id); // 指向新节点
    // 一个数据块都无
    if (cache_head == NULL)
    {
        cache_head = ptr;
        cache_comptr = ptr;
        cache_tail = ptr;
        return;
    }
    DataNode *temp_ptr = cache_comptr; // 临时指针 用于遍历
    while (temp_ptr->next != NULL && temp_ptr->next->data_id <= ptr->data_id)
    {
        temp_ptr = temp_ptr->next;
    }
    if (temp_ptr->next == NULL)
    {

        // 插入表尾
        temp_ptr->next = ptr;
        ptr->pre = temp_ptr;
        // 判断是否是顺序表
        if (cache_comptr == cache_tail && ptr->data_id == cache_comptr->data_id + 1)
        {
            cache_comptr = ptr;
        }
        // 更新cache_tail
        cache_tail = ptr;
    }
    else
    {
        // 插入中间
        if (temp_ptr == cache_comptr)
        {
            // 插入位置在cache_comptr后一位
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
            // 移动cache_comptr直至表尾或到最后一个顺序节点
            while (cache_comptr->next != NULL && cache_comptr->next->data_id == cache_comptr->data_id + 1)
            {
                cache_comptr = cache_comptr->next;
            }
        }
        else
        {
            // 插入位置在非顺序表中
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
        }
    }
}

DataNode::DataNode(int id) // 数据节点
{
    data_id = id;
    next = NULL;
    pre = NULL;
}

double distance(const Node &a, const Node &b)
{
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
void perFrame(long long time)
{
    // 一秒视为一帧 在一帧内进行所有处理

    // 处理完毕
    time++;
}
