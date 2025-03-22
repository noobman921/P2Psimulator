#ifndef NODE_H
#define NODE_H

using namespace std;
// �ڽӱ�ڵ�

class Node;
class DataNode;
class NeiborNode;

// �ڵ���
class Node
{
public:
    int id; // ���
    int x;  // ����λ��X
    int y;  // ����λ��Y
    int neibor_count;//��ǰ�ھ����������ΪNeibor_Count
    int min_dis; // ��С�ھӾ���
    int max_dis; // ����ھӾ���
    // �ڽӱ�
    // ��ʼ���ڵ�
    NeiborNode *neibor_head; // ��ͷ
    NeiborNode *neibor_tail;
    Node(int id1, int x1, int y1);
    Node():id(0),x(0),y(0){};
    void AddNeibor(Node *ptr, int id, int dis);
};

class NeiborNode
{
public:
    int id;    // ���
    int dis;   // ���Ӧ�ڵ�ľ���
    Node *ptr; // ָ���Ӧ��ŵĽڵ�

    NeiborNode *next; // ָ����һ���ڽӱ�ڵ�
    NeiborNode *pre;
    NeiborNode(Node *ptr1, int id1, int dis1);
};
// �����
class Server : public Node
{
public:
    int data_start; // ���������ݿ���ĵ���
    int data_end;
    //Server(int x1, int y1, int id1);
    Server(); 
    Server(int id,int x,int y):Node(id,x,y){};
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
    //Client(int x1, int y1, int id1);
    Client();
    Client(int id,int x,int y):Node(id,x,y){};
    void AddData(int data_id);
};
// data N���ݿ�
// ���ݽڵ�
class DataNode // ��������洢���ݿ�
{
public:
    int data_id; // ���ݿ����
    // ���ݿ�����
    struct DataNode *next;
    struct DataNode *pre;
    DataNode(int id);
};

void perFrame(long long time);
double distance(const Node &a, const Node &b);

#endif
