#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
#include "node.h"
using namespace std;
// �ڵ���
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
        // �����Ƿ����������ã�
        NeiborNode *ptr = neibor_head;
        // �ҵ���һ���������ھӵĽڵ� �� �սڵ�
        while (ptr->next != NULL && ptr->next->dis < new_neibor->dis)
        {
            ptr = ptr->next;
        }

        if (ptr->next == NULL)
        {
            // �յ� ֱ�ӽӵ�����β
            neibor_tail->next = new_neibor;
            new_neibor->pre = neibor_tail;
            neibor_tail = new_neibor;
        }
        else
        {
            // �ǿ� �ӵ��м�
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
    DataNode *ptr = new DataNode(data_id); // ָ���½ڵ�
    // һ�����ݿ鶼��
    if (cache_head == NULL)
    {
        cache_head = ptr;
        cache_comptr = ptr;
        cache_tail = ptr;
        return;
    }
    DataNode *temp_ptr = cache_comptr; // ��ʱָ�� ���ڱ���
    while (temp_ptr->next != NULL && temp_ptr->next->data_id <= ptr->data_id)
    {
        temp_ptr = temp_ptr->next;
    }
    if (temp_ptr->next == NULL)
    {

        // �����β
        temp_ptr->next = ptr;
        ptr->pre = temp_ptr;
        // �ж��Ƿ���˳���
        if (cache_comptr == cache_tail && ptr->data_id == cache_comptr->data_id + 1)
        {
            cache_comptr = ptr;
        }
        // ����cache_tail
        cache_tail = ptr;
    }
    else
    {
        // �����м�
        if (temp_ptr == cache_comptr)
        {
            // ����λ����cache_comptr��һλ
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
            // �ƶ�cache_comptrֱ����β�����һ��˳��ڵ�
            while (cache_comptr->next != NULL && cache_comptr->next->data_id == cache_comptr->data_id + 1)
            {
                cache_comptr = cache_comptr->next;
            }
        }
        else
        {
            // ����λ���ڷ�˳�����
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
        }
    }
}

DataNode::DataNode(int id) // ���ݽڵ�
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
    // һ����Ϊһ֡ ��һ֡�ڽ������д���

    // �������
    time++;
}
