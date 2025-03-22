#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
#include "node.h"
using namespace std;
// �ڵ㹹�캯��
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
        // �������򱣳��ھ���������
        NeiborNode *ptr = neibor_head;
        // �ҵ���һ�������ھӾ����Ľڵ� �� ĩβ�ڵ�
        while (ptr->next != NULL && ptr->next->dis < new_neibor->dis)
        {
            ptr = ptr->next;
        }

        if (ptr->next == NULL)
        {
            // ���뵽����β��
            neibor_tail->next = new_neibor;
            new_neibor->pre = neibor_tail;
            neibor_tail = new_neibor;
        }
        else
        {
            // ���뵽�м�
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
    DataNode *ptr = new DataNode(data_id); // �������ݽڵ�
    // �������Ϊ��
    if (cache_head == NULL)
    {
        cache_head = ptr;
        cache_comptr = ptr;
        cache_tail = ptr;
        return;
    }
    DataNode *temp_ptr = cache_comptr; // ��ʱָ�� �ӵ�ǰ�ڵ㿪ʼ
    while (temp_ptr->next != NULL && temp_ptr->next->data_id <= ptr->data_id)
    {
        temp_ptr = temp_ptr->next;
    }
    if (temp_ptr->next == NULL)
    {

        // ���뵽β��
        temp_ptr->next = ptr;
        ptr->pre = temp_ptr;
        // ����cache_comptrΪ���������һ���ڵ�
        if (cache_comptr == cache_tail && ptr->data_id == cache_comptr->data_id + 1)
        {
            cache_comptr = ptr;
        }
        // ����cache_tail
        cache_tail = ptr;
    }
    else
    {
        // ���뵽�м�
        if (temp_ptr == cache_comptr)
        {
            // ����λ�ý���cache_comptr
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
            // ����cache_comptrֱ�����������һ���ڵ�
            while (cache_comptr->next != NULL && cache_comptr->next->data_id == cache_comptr->data_id + 1)
            {
                cache_comptr = cache_comptr->next;
            }
        }
        else
        {
            // ����λ�ñ���˳��
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
        }
    }
}

DataNode::DataNode(int id) // ���ݽڵ㹹�캯��
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
    // һ�ε���Ϊһ֡ ÿ֡����ʱ��

    // ʱ������
    time++;
}
