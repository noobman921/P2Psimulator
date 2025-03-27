#include <bits/stdc++.h>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
#include "node.h"
using namespace std;
/**
 * @brief Node 类的构造函数，用于初始化节点对象
 *
 * 该构造函数接收节点的 ID、x 坐标和 y 坐标作为参数，对节点的各项属性进行初始化。
 * 包括节点的位置信息、ID、邻居节点数量、邻居节点距离的最小值和最大值，以及邻居节点链表的头指针和尾指针。
 *
 * @param id1 节点的唯一标识符
 * @param x1 节点的 x 坐标,使用ll
 * @param y1 节点的 y 坐标
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
 * @brief 向节点的邻居节点链表中添加一个新的邻居节点
 *
 * 该函数创建一个新的邻居节点，并将其插入到邻居节点链表中，
 * 插入时会按照邻居节点与当前节点的距离进行排序，以保持链表有序。
 *
 * @param ptr 指向新邻居节点的指针
 * @param id 新邻居节点的唯一标识符
 * @param dis 新邻居节点与当前节点的距离，使用double
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
        // 插入排序保持邻居链表有序
        NeiborNode *ptr = neibor_head;
        // 找到第一个比新邻居距离大的节点 或 末尾节点
        while (ptr->next != NULL && ptr->next->dis < new_neibor->dis)
        {
            ptr = ptr->next;
        }

        if (ptr->next == NULL)
        {
            // 插入到链表尾部
            neibor_tail->next = new_neibor;
            new_neibor->pre = neibor_tail;
            neibor_tail = new_neibor;
        }
        else
        {
            // 插入到中间
            new_neibor->next = ptr->next;
            new_neibor->pre = ptr;
            ptr->next->pre = new_neibor;
            ptr->next = new_neibor;
        }
    }
}
/**
 * @brief NeiborNode 类的构造函数，用于初始化邻居节点对象
 *
 * 该构造函数接收一个指向节点的指针、节点的唯一标识符和该节点与当前节点的距离作为参数，
 * 对邻居节点的各项属性进行初始化，同时将指向前一个和后一个邻居节点的指针初始化为 NULL。
 *
 * @param ptr1 指向邻居节点的指针
 * @param id1 邻居节点的唯一标识符
 * @param dis1 邻居节点与当前节点的距离
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
 * @brief Server 类的带参数构造函数，用于初始化服务端节点对象
 *
 * 该构造函数调用基类 Node 的构造函数来初始化节点的基本信息，
 * 并在此基础上对服务端特有的数据起始位置和结束位置进行初始化。
 *
 * @param id1 服务端节点的唯一标识符
 * @param x1 服务端节点的 x 坐标
 * @param y1 服务端节点的 y 坐标
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
 * @brief Client 类的带参数构造函数，用于初始化客户端节点对象
 *
 * 该构造函数调用基类 Node 的构造函数来初始化节点的基本信息，
 * 包括节点的唯一标识符、x 坐标和 y 坐标。
 *
 * @param id1 客户端节点的唯一标识符
 * @param x1 客户端节点的 x 坐标，使用 `ll` 类型
 * @param y1 客户端节点的 y 坐标
 */
Client::Client(int id1, ll x1, ll y1) : Node(id1, x1, y1) {}
Client::Client() : Node() {}

/**
 * @brief 更新数据块
 */
void Client::ClientDataUpdate()
{
    //处理旧的链表
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
 * @brief 向客户端的缓存中添加数据节点
 *
 * 该函数用于将一个新的数据节点添加到客户端的缓存链表中，
 * 并确保链表按数据 ID 升序排列。同时，会更新缓存链表的头节点、
 * 连续数据的最后一个节点和尾节点。
 *
 * @param data_id 要添加的数据节点的 ID
 */
void Client::AddData(int data_id)
{
    DataNode *ptr = new DataNode(data_id); // 创建数据节点
    // 如果缓存为空
    if (next_cache_head == NULL)
    {
        next_cache_head = ptr;
        next_cache_comptr = ptr;
        next_cache_tail = ptr;
        return;
    }
    DataNode *temp_ptr = next_cache_comptr; // 临时指针 从当前节点开始
    while (temp_ptr->next != NULL && temp_ptr->next->data_id <= ptr->data_id)
    {
        temp_ptr = temp_ptr->next;
    }
    if (temp_ptr->next == NULL)
    {

        // 插入到尾部
        temp_ptr->next = ptr;
        ptr->pre = temp_ptr;
        // 更新next_cache_comptr为连续的最后一个节点
        if (next_cache_comptr == next_cache_tail && ptr->data_id == next_cache_comptr->data_id + 1)
        {
            next_cache_comptr = ptr;
        }
        // 更新next_cache_tail
        next_cache_tail = ptr;
    }
    else
    {
        // 插入到中间
        if (temp_ptr == next_cache_comptr)
        {
            // 插入位置紧挨next_cache_comptr
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
            // 更新next_cache_comptr直到连续的最后一个节点
            while (next_cache_comptr->next != NULL && next_cache_comptr->next->data_id == next_cache_comptr->data_id + 1)
            {
                next_cache_comptr = next_cache_comptr->next;
            }
        }
        else
        {
            // 插入位置保持顺序
            ptr->next = temp_ptr->next;
            ptr->pre = temp_ptr;
            temp_ptr->next->pre = ptr;
            temp_ptr->next = ptr;
        }
    }
}
/**
 * @brief DataNode 类的构造函数，用于初始化数据节点对象
 * 
 * 该构造函数接收一个整数类型的数据 ID 作为参数，对数据节点的各项属性进行初始化。
 * 会将传入的数据 ID 赋值给数据节点的 `data_id` 成员变量，
 * 并将指向前一个和后一个数据节点的指针初始化为 NULL，表示该节点初始时没有前后相邻节点。
 * 
 * @param id 数据节点的唯一标识符
 */
DataNode::DataNode(int id) // 数据节点构造函数
{
    data_id = id;
    next = NULL;
    pre = NULL;
}
/**
 * @brief 计算两个节点之间的欧几里得距离
 * 
 * 该函数接收两个 Node 类型的常量引用作为参数，
 * 通过计算两个节点在二维平面上的 x 坐标差值和 y 坐标差值的平方和的平方根，
 * 得到两个节点之间的欧几里得距离。
 * 
 * @param a 第一个节点的常量引用
 * @param b 第二个节点的常量引用
 * @return double 两个节点之间的欧几里得距离
 */
double distance(const Node &a, const Node &b)
{
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
/**
 * @brief 处理每帧的逻辑，主要功能是增加时间计数
 * 
 * 该函数在每次调用时代表一帧的处理过程，其核心功能是将传入的时间参数递增 1，
 * 模拟时间随帧数的推进。
 * 
 * @param time 当前帧对应的时间，使用ll
 */
void perFrame(ll time)
{
    // 一次调用为一帧 每帧增加时间

    // 时间增加
    time++;
}
