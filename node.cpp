#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
#include "node.h"
using namespace std;
/**
 * @brief Node ��Ĺ��캯�������ڳ�ʼ���ڵ����
 *
 * �ù��캯�����սڵ�� ID��x ����� y ������Ϊ�������Խڵ�ĸ������Խ��г�ʼ����
 * �����ڵ��λ����Ϣ��ID���ھӽڵ��������ھӽڵ�������Сֵ�����ֵ���Լ��ھӽڵ������ͷָ���βָ�롣
 *
 * @param id1 �ڵ��Ψһ��ʶ��
 * @param x1 �ڵ�� x ����,ʹ��ll
 * @param y1 �ڵ�� y ����
 */
Node::Node(int id1, ll x1, ll y1)
{
    x = x1;
    y = y1;
    id = id1;
    neibor_count = 0;
    min_dis = 0;
    max_dis = 1e10; // 99999^2?
    neibor_head = NULL;
    neibor_tail = NULL;
}
/**
 * @brief ��ڵ���ھӽڵ����������һ���µ��ھӽڵ�
 *
 * �ú�������һ���µ��ھӽڵ㣬��������뵽�ھӽڵ������У�
 * ����ʱ�ᰴ���ھӽڵ��뵱ǰ�ڵ�ľ�����������Ա�����������
 *
 * @param ptr ָ�����ھӽڵ��ָ��
 * @param id ���ھӽڵ��Ψһ��ʶ��
 * @param dis ���ھӽڵ��뵱ǰ�ڵ�ľ��룬ʹ��double
 */
void Node::AddNeibor(Node *ptr, int id, double dis)
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
/**
 * @brief NeiborNode ��Ĺ��캯�������ڳ�ʼ���ھӽڵ����
 *
 * �ù��캯������һ��ָ��ڵ��ָ�롢�ڵ��Ψһ��ʶ���͸ýڵ��뵱ǰ�ڵ�ľ�����Ϊ������
 * ���ھӽڵ�ĸ������Խ��г�ʼ����ͬʱ��ָ��ǰһ���ͺ�һ���ھӽڵ��ָ���ʼ��Ϊ NULL��
 *
 * @param ptr1 ָ���ھӽڵ��ָ��
 * @param id1 �ھӽڵ��Ψһ��ʶ��
 * @param dis1 �ھӽڵ��뵱ǰ�ڵ�ľ���
 */
NeiborNode::NeiborNode(Node *ptr1, int id1, double dis1)
{
    ptr = ptr1;
    id = id1;
    dis = dis1;
    next = NULL;
    pre = NULL;
}
/**
 * @brief Server ��Ĵ��������캯�������ڳ�ʼ������˽ڵ����
 *
 * �ù��캯�����û��� Node �Ĺ��캯������ʼ���ڵ�Ļ�����Ϣ��
 * ���ڴ˻����϶Է�������е�������ʼλ�úͽ���λ�ý��г�ʼ����
 *
 * @param id1 ����˽ڵ��Ψһ��ʶ��
 * @param x1 ����˽ڵ�� x ����
 * @param y1 ����˽ڵ�� y ����
 */
Server::Server(int id1, ll x1, ll y1) : Node(id1, x1, y1)
{
    data_start = 1;
    data_end = 0;
    next_data_start = 1;
    next_data_end = 0;
}
Server::Server() : Node() {}

void Server::ServerDataUpdate()
{
    data_start = next_data_start;
    data_end = next_data_end;
}
/**
 * @brief Client ��Ĵ��������캯�������ڳ�ʼ���ͻ��˽ڵ����
 *
 * �ù��캯�����û��� Node �Ĺ��캯������ʼ���ڵ�Ļ�����Ϣ��
 * �����ڵ��Ψһ��ʶ����x ����� y ���ꡣ
 *
 * @param id1 �ͻ��˽ڵ��Ψһ��ʶ��
 * @param x1 �ͻ��˽ڵ�� x ���꣬ʹ�� `ll` ����
 * @param y1 �ͻ��˽ڵ�� y ����
 */
Client::Client(int id1, ll x1, ll y1) : Node(id1, x1, y1) {}
Client::Client() : Node() {}

/**
 * @brief �������ݿ�
 */
void Client::ClientDataUpdate()
{
    //����ɵ�����
    DataNode* temp = cache_head;
    while(temp!=NULL)
    {
        temp = temp->next;
        delete cache_head;
        cache_head = temp;
    }
    cache_head = next_cache_head;
    cache_comptr = next_cache_comptr;
    cache_tail = next_cache_tail;
}
/**
 * @brief ��ͻ��˵Ļ�����������ݽڵ�
 *
 * �ú������ڽ�һ���µ����ݽڵ���ӵ��ͻ��˵Ļ��������У�
 * ��ȷ���������� ID �������С�ͬʱ������»��������ͷ�ڵ㡢
 * �������ݵ����һ���ڵ��β�ڵ㡣
 *
 * @param data_id Ҫ��ӵ����ݽڵ�� ID
 */
void Client::AddData(int data_id)
{
    DataNode *ptr = new DataNode(data_id); // �������ݽڵ�
    // �������Ϊ��
    if (next_cache_head == NULL)
    {
        next_cache_head = ptr;
        next_cache_comptr = ptr;
        next_cache_tail = ptr;
        return;
    }
    DataNode *temp_ptr = next_cache_comptr; // ��ʱָ�� �ӵ�ǰ�ڵ㿪ʼ
    while (temp_ptr->next != NULL && temp_ptr->next->data_id <= ptr->data_id)
    {
        temp_ptr = temp_ptr->next;
    }
    if (temp_ptr->next == NULL)
    {

        // ���뵽β��
        temp_ptr->next = ptr;
        ptr->pre = temp_ptr;
        // ����next_cache_comptrΪ���������һ���ڵ�
        if (next_cache_comptr == next_cache_tail && ptr->data_id == next_cache_comptr->data_id + 1)
        {
            next_cache_comptr = ptr;
        }
        // ����next_cache_tail
        next_cache_tail = ptr;
    }
    else
    {
        // ���뵽�м�
        if (temp_ptr == next_cache_comptr)
        {
            // ����λ�ý���next_cache_comptr
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
            // ����next_cache_comptrֱ�����������һ���ڵ�
            while (next_cache_comptr->next != NULL && next_cache_comptr->next->data_id == next_cache_comptr->data_id + 1)
            {
                next_cache_comptr = next_cache_comptr->next;
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
/**
 * @brief DataNode ��Ĺ��캯�������ڳ�ʼ�����ݽڵ����
 * 
 * �ù��캯������һ���������͵����� ID ��Ϊ�����������ݽڵ�ĸ������Խ��г�ʼ����
 * �Ὣ��������� ID ��ֵ�����ݽڵ�� `data_id` ��Ա������
 * ����ָ��ǰһ���ͺ�һ�����ݽڵ��ָ���ʼ��Ϊ NULL����ʾ�ýڵ��ʼʱû��ǰ�����ڽڵ㡣
 * 
 * @param id ���ݽڵ��Ψһ��ʶ��
 */
DataNode::DataNode(int id) // ���ݽڵ㹹�캯��
{
    data_id = id;
    next = NULL;
    pre = NULL;
}
/**
 * @brief ���������ڵ�֮���ŷ����þ���
 * 
 * �ú����������� Node ���͵ĳ���������Ϊ������
 * ͨ�����������ڵ��ڶ�άƽ���ϵ� x �����ֵ�� y �����ֵ��ƽ���͵�ƽ������
 * �õ������ڵ�֮���ŷ����þ��롣
 * 
 * @param a ��һ���ڵ�ĳ�������
 * @param b �ڶ����ڵ�ĳ�������
 * @return double �����ڵ�֮���ŷ����þ���
 */
double distance(const Node &a, const Node &b)
{
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
/**
 * @brief ����ÿ֡���߼�����Ҫ����������ʱ�����
 * 
 * �ú�����ÿ�ε���ʱ����һ֡�Ĵ�����̣�����Ĺ����ǽ������ʱ��������� 1��
 * ģ��ʱ����֡�����ƽ���
 * 
 * @param time ��ǰ֡��Ӧ��ʱ�䣬ʹ��ll
 */
void perFrame(ll time)
{
    // һ�ε���Ϊһ֡ ÿ֡����ʱ��

    // ʱ������
    time++;
}
