#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
using namespace std;
// �ڵ���
typedef struct Node
{
    int x;
    int y;
    int num; // ���
} Node;

// �������
typedef struct Server
{
    Node node;
    int data_start; // ���������ݿ���ĵ���
    int data_end;
} Server;

// �ͻ�����
typedef struct Client
{
    Node node;

    //  ������ʵ�ֻ������ݿ�
    struct DataNode *cache_head;
    struct DataNode *cache_comptr; // ָ���һ����˳��Ľڵ�
    struct DataNode *cache_tail;
    int N; // �����С
    int M; // ��������
    // �ڿͻ�����ά��һ������ΪN�Ļ������,�µ�������ݷֿ�Ὣ���ϵ����ݿ���и��ǡ�����������ջһ����
    // Ҫ��������5���ֿ�
} Client;
// data N���ݿ�
// ���ݽڵ�
typedef struct DataNode // ��������洢���ݿ�
{
    int data_num; // ���ݿ����
    // ���ݿ�����
    struct DataNode *next;
    struct DataNode *pre;
} DataNode;

void perFrame()
{
    // һ����Ϊһ֡ ��һ֡�ڽ������д���
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