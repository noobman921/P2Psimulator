#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
using namespace std;
// �ڵ���
class Node
{   
    int x;
    int y;
    int num; // ���
    //�ڽӱ�
public:
// ��ʼ���ڵ�
    NeiborNode *neibor_head;//��ͷ
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
            //�����Ƿ����������ã�
            NeiborNode *ptr = neibor_head;
            //�ҵ���һ���������ھӵĽڵ� �� �սڵ�
            while(ptr->next != NULL && ptr->next->dis < new_neibor->dis)
            {
                ptr = ptr->next;
            }

            if(ptr->next == NULL)
            {   
                //�յ� ֱ�ӽӵ�����β
                neibor_tail->next = new_neibor;
                new_neibor->pre = neibor_tail;
                neibor_tail = new_neibor;
            }
            else
            {
                //�ǿ� �ӵ��м�
                new_neibor->next = ptr->next;
                new_neibor->pre = ptr;
                ptr->next->pre = new_neibor;
                ptr->next = new_neibor;
            }
        }
    }
};
//�ڽӱ�ڵ�
class NeiborNode
{
public:
    int num;//���
    int dis;//���Ӧ�ڵ�ľ���
    Node *ptr;//ָ���Ӧ��ŵĽڵ�
    NeiborNode *next;//ָ����һ���ڽӱ�ڵ�
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

// �����
class Server : public Node
{
public:
    int data_start; // ���������ݿ���ĵ���
    int data_end;
    Server(int x1, int y1, int num1) : Node(x1, y1, num1)
    {
        data_start = 0;
        data_end = 0;
    }
} ;

// �ͻ�����
class Client : public Node
{
public:
    //  ������ʵ�ֻ������ݿ�
    DataNode *cache_head;
    DataNode *cache_comptr; // ָ�����һ��˳��Ľڵ�
    DataNode *cache_tail;
    int N; // �����С
    int M; // ��������
    // �ڿͻ�����ά��һ������ΪN�Ļ������,�µ�������ݷֿ�Ὣ���ϵ����ݿ���и��ǡ�����������ջһ����
    //��������ݾͿ���ʵ�� ֻ��Ҫ�ѾɵĽڵ�����Ƴ����ͷž���
    Client(int x1, int y1, int num1) : Node(x1, y1, num1){};
    void AddData(int data_num)
    {
        DataNode *ptr = new DataNode(data_num);//ָ���½ڵ�
        //һ�����ݿ鶼��
        if(cache_head == NULL)
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
        //ûд��Ķ��� �������ݿ�ȫΪ˳������ �����β���ǲ���˳���
        //            ���ݿ��з�˳�� �������cache_comptr��˳���᲻������
    }

};
// data N���ݿ�
// ���ݽڵ�
class DataNode // ��������洢���ݿ�
{
public:
    int data_num; // ���ݿ����
    // ���ݿ�����
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
    // һ����Ϊһ֡ ��һ֡�ڽ������д���

    //�������
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