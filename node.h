#ifndef NODE_H
#define NODE_H

using namespace std;

#define ll long long
// �ڽӱ�ڵ�

class Node;
class DataNode;
class NeiborNode;

// �ڵ���
class Node
{
public:
    int id; // ���
    ll x;  // ����λ��X //99999*99999����2e9�������Ϊll
    ll y;  // ����λ��Y
    int neibor_count;//��ǰ�ھ����������ΪNeibor_Count
    ll min_dis; // ��С�ھӾ���
    ll max_dis; // ����ھӾ���
    // �ڽӱ�
    // ��ʼ���ڵ�
    NeiborNode *neibor_head; // ��ͷ
    NeiborNode *neibor_tail;
    Node(int id1, ll x1, ll y1);
    Node():id(0),x(0),y(0){};
    void AddNeibor(Node *ptr, int id, double dis);
};

class NeiborNode
{
public:
    int id;    // ���
    double dis;   // ���Ӧ�ڵ�ľ���
    Node* ptr; // ָ���Ӧ��ŵĽڵ�

    NeiborNode *next; // ָ����һ���ڽӱ�ڵ�
    NeiborNode *pre;
    NeiborNode(Node *ptr1, int id1, double dis1);
};
// �����
class Server : public Node
{
public:
    int data_start; // ���������ݿ���ĵ���
    int data_end;
    int next_data_start;
    int next_data_end;
    Server();
    Server(int id,ll x,ll y);
    void ServerDataUpdate();
};

// �ͻ�����
class Client : public Node
{
public:
    //  ������ʵ�ֻ������ݿ�
    DataNode* cache_head;
    DataNode* cache_comptr; // ָ�����һ��˳��Ľڵ�
    DataNode* cache_tail;
    DataNode* next_cache_head;
    DataNode* next_cache_comptr; // ָ�����һ��˳��Ľڵ�
    DataNode* next_cache_tail;
    int N; // �����С
    int M; // ��������
    // �ڿͻ�����ά��һ������ΪN�Ļ������,�µ�������ݷֿ�Ὣ���ϵ����ݿ���и��ǡ�����������ջһ����
    // ��������ݾͿ���ʵ�� ֻ��Ҫ�ѾɵĽڵ�����Ƴ����ͷž���
    Client();
    Client(int id,ll x,ll y);
    void ClientDataUpdate();
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

void perFrame(ll time);
double distance(const Node &a, const Node &b);

#endif
