#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
#include "node.h"
using namespace std;
// 节点构造函数
Node::Node(int id1, int x1, int y1)
{
    x = x1;
    y = y1;
    id = id1;
    neibor_count = 0;
    min_dis = 0;
    max_dis = 0;
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
        // 插入排序保持邻居链表有序
        NeiborNode *ptr = neibor_head;
        // 找到第一个比新邻居距离大的节点 或 末尾节点
        while (ptr->next != NULL && ptr->next->dis < new_neibor->dis)
        {
            ptr = ptr->next;
        }

        if (ptr->next == NULL)
        {
            // 插入到链表尾部
            neibor_tail->next = new_neibor;
            new_neibor->pre = neibor_tail;
            neibor_tail = new_neibor;
        }
        else
        {
            // 插入到中间
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
    DataNode *ptr = new DataNode(data_id); // 创建数据节点
    // 如果缓存为空
    if (cache_head == NULL)
    {
        cache_head = ptr;
        cache_comptr = ptr;
        cache_tail = ptr;
        return;
    }
    DataNode *temp_ptr = cache_comptr; // 临时指针 从当前节点开始
    while (temp_ptr->next != NULL && temp_ptr->next->data_id <= ptr->data_id)
    {
        temp_ptr = temp_ptr->next;
    }
    if (temp_ptr->next == NULL)
    {

        // 插入到尾部
        temp_ptr->next = ptr;
        ptr->pre = temp_ptr;
        // 更新cache_comptr为连续的最后一个节点
        if (cache_comptr == cache_tail && ptr->data_id == cache_comptr->data_id + 1)
        {
            cache_comptr = ptr;
        }
        // 更新cache_tail
        cache_tail = ptr;
    }
    else
    {
        // 插入到中间
        if (temp_ptr == cache_comptr)
        {
            // 插入位置紧挨cache_comptr
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
            // 更新cache_comptr直到连续的最后一个节点
            while (cache_comptr->next != NULL && cache_comptr->next->data_id == cache_comptr->data_id + 1)
            {
                cache_comptr = cache_comptr->next;
            }
        }
        else
        {
            // 插入位置保持顺序
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
        }
    }
}

DataNode::DataNode(int id) // 数据节点构造函数
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
    // 一次调用为一帧 每帧增加时间

    // 时间增加
    time++;
}
