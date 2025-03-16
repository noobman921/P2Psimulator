#ifndef NODE_H
#define NODE_H

using namespace std;
// �ڽӱ�ڵ�
class Node;
class DataNode;

class NeiborNode
{
public:
    int num;          // ���
    int dis;          // ���Ӧ�ڵ�ľ���
    Node *ptr;        // ָ���Ӧ��ŵĽڵ�
    NeiborNode *next; // ָ����һ���ڽӱ�ڵ�
    NeiborNode *pre;
    NeiborNode(Node *ptr1, int num1, int dis1);
};
// �ڵ���
class Node
{
public:
    int x;
    int y;
    int num; // ���
    // �ڽӱ�

    // ��ʼ���ڵ�
    NeiborNode *neibor_head; // ��ͷ
    NeiborNode *neibor_tail;
    Node(int num1,int x1, int y1 );
    void AddNeibor(Node *ptr, int num, int dis);
};

// �����
class Server : public Node
{
public:
    int data_start; // ���������ݿ���ĵ���
    int data_end;
    Server(int x1, int y1, int num1);
};

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
    // ��������ݾͿ���ʵ�� ֻ��Ҫ�ѾɵĽڵ�����Ƴ����ͷž���
    Client(int x1, int y1, int num1);
    void AddData(int data_num);
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
    DataNode(int num);
};

void perFrame(long long time);
double distance(const Node &a, const Node &b);

#endif
