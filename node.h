#ifndef NODE_H
#define NODE_H

using namespace std;
// 邻接表节点

constexpr int Neibor_Count = 5;//邻居数量
class Node;
class DataNode;

class NeiborNode
{
public:
    int id;    // 序号
    int dis;   // 与对应节点的距离
    Node *ptr; // 指向对应序号的节点

    NeiborNode *next; // 指向下一个邻接表节点
    NeiborNode *pre;
    NeiborNode(Node *ptr1, int id1, int dis1);
};
// 节点类
class Node
{
public:
    int id; // 序号
    int x;  // 地理位置X
    int y;  // 地理位置Y
    int neibor_count;//当前邻居数量，最大为Neibor_Count
    // 邻接表
    vector<int> neibors; // 邻居节点列表
    queue<int> buffer;     // 数据块缓存队列
    // 初始化节点
    NeiborNode *neibor_head; // 表头
    NeiborNode *neibor_tail;
    Node(int id1, int x1, int y1);
    Node():id(0),x(0),y(0){};
    void AddNeibor(Node *ptr, int id, int dis);
};

// 服务端
class Server : public Node
{
public:
    int data_start; // 产生的数据库从哪到哪
    int data_end;
    //Server(int x1, int y1, int id1);
    Server(); 
    Server(int id,int x,int y):Node(id,x,y){};
};

// 客户端类
class Client : public Node
{
public:
    //  用链表实现缓存数据块
    DataNode *cache_head;
    DataNode *cache_comptr; // 指向最后一个顺序的节点
    DataNode *cache_tail;
    int N; // 缓存大小
    int M; // 播放条件
    // 在客户端上维护一个长度为N的缓存队列,新到达的数据分块会将最老的数据块进行覆盖。看不懂，像栈一样？
    // 上面的内容就可以实现 只需要把旧的节点从中移除并释放就行
    //Client(int x1, int y1, int id1);
    Client();
    Client(int id,int x,int y):Node(id,x,y){};
    void AddData(int data_id);
};
// data N数据块
// 数据节点
class DataNode // 采用链表存储数据块
{
public:
    int data_id; // 数据块序号
    // 数据块放这里？
    struct DataNode *next;
    struct DataNode *pre;
    DataNode(int id);
};

void perFrame(long long time);
double distance(const Node &a, const Node &b);

#endif
