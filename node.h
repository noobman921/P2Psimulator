using namespace std;
// 邻接表节点
class Node;
class DataNode;

class NeiborNode
{
public:
    int num;          // 序号
    int dis;          // 与对应节点的距离
    Node *ptr;        // 指向对应序号的节点
    NeiborNode *next; // 指向下一个邻接表节点
    NeiborNode *pre;
    NeiborNode(Node *ptr1, int num1, int dis1);
};
// 节点类
class Node
{
    int x;
    int y;
    int num; // 序号
    // 邻接表
public:
    // 初始化节点
    NeiborNode *neibor_head; // 表头
    NeiborNode *neibor_tail;
    Node(int x1, int y1, int num1);
    void AddNeibor(Node *ptr, int num, int dis);
};


// 服务端
class Server : public Node
{
public:
    int data_start; // 产生的数据库从哪到哪
    int data_end;
    Server(int x1, int y1, int num1);
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
    Client(int x1, int y1, int num1);
    void AddData(int data_num);
};
// data N数据块
// 数据节点
class DataNode // 采用链表存储数据块
{
public:
    int data_num; // 数据块序号
    // 数据块放这里？
    struct DataNode *next;
    struct DataNode *pre;
    DataNode(int num);
};

void perFrame(long long time);
