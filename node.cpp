#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
#include "node.h"
using namespace std;
// �ڵ���
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
    DataNode *ptr = new DataNode(data_num); // ָ���½ڵ�
    // һ�����ݿ鶼��
    if (cache_head == NULL)
    {
        cache_head = ptr;
        return;
    }
    // DataNode *temp_ptr = cache_comptr;//��ʱָ�� ���ڱ���
    // while(temp_ptr->next != NULL && temp_ptr->next->data_num <= ptr->data_num){
    //     temp_ptr = temp_ptr->next;
    // }
    // if(temp_ptr == cache_comptr){
    //     //�ڵ�һ��
    // }
    // ûд��Ķ��� �������ݿ�ȫΪ˳������ �����β���ǲ���˳���
    //            ���ݿ��з�˳�� �������cache_comptr��˳���᲻������
}

DataNode::DataNode(int num)
{
    data_num = num;
    next = NULL;
    pre = NULL;
}
void perFrame(long long time)
{
    // һ����Ϊһ֡ ��һ֡�ڽ������д���
    // �������
    time++;
}
