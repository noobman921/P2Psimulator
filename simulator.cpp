#include "simulator.h"
#include "node.h"
/**
 * @brief 生成模拟节点数据并写入文件
 *
 * 该函数用于生成指定数量的节点数据，包括 1 个服务端节点和 n 个客户端节点，
 * 并将这些节点的信息写入名为 "data.txt" 的文件中。每个节点信息包含类型、序号、x 坐标和 y 坐标。
 *
 * @param n 要生成的客户端节点的数量
 */
void Simulator_Data_Generate(int n)
{
    if (n < 1)
    {
        cout << "节点数目过少" << endl;
        return;
    }

    ofstream file("data.txt");
    if (!file.is_open())
    {
        cout << "文件打开失败" << endl;
        return;
    }

    // 使用随机数引擎和分布生成随机的 x 和 y 坐标
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis_x(0, MAX_X);
    uniform_int_distribution<> dis_y(0, MAX_Y);

    // 生成 1 个服务端 规定服务端的序号为0
    int server_x = dis_x(gen);
    int server_y = dis_y(gen);
    file << "Server " << 0 << ": " << server_x << " " << server_y << endl;
    // Node(0, server_x, server_y);

    // 生成 n 个客户端
    for (int i = 1; i <= n; i++)
    {
        int client_x = dis_x(gen);
        int client_y = dis_y(gen);
        file << "Client " << i + 1 << ": " << client_x << " " << client_y << endl;
        // Node(i, client_x, client_y);
    }
    // 在这里把客户端和服务端做成节点？
    file.close();
    return;
}

/**
 * @brief 从文件data.txt中读取节点信息并创建节点
 *
 * 该函数从名为 "data.txt" 的文件中读取节点信息，根据文件内容创建一个服务端节点和多个客户端节点。
 * 文件中每一行代表一个节点，格式为 "类型 序号: x坐标 y坐标"。
 *
 * @param n 客户端节点的数量
 * @param server 引用类型，用于存储创建的服务端节点
 * @param client 客户端节点数组，用于存储创建的客户端节点
 */
void CreateNodeFromFile(int n, Server &server, Client client[])
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "无法打开文件" << std::endl;
        return;
    }

    std::string line;
    int lineCount = -1;
    while (std::getline(file, line))
    {

        size_t colonPos = line.find(':');

        // 错误检查：确保存在冒号
        if (colonPos == std::string::npos)
        {
            std::cerr << "第 " << lineCount << " 行格式错误（缺少冒号）: "
                      << line << std::endl;
            continue;
        }

        // 创建字符串流读取冒号后的内容
        std::istringstream iss(line.substr(colonPos + 1));
        int num1, num2;

        // 提取两个整数
        if (iss >> num1 >> num2)
        {
            if (lineCount == -1)
                // 若为第一行，创建服务端节点
                server = Server(lineCount, num1, num2);
            else
                // 若不是第一行，创建客户端节点
                client[lineCount] = Client(lineCount, num1, num2);
        }
        else
        {
            std::cerr << "第 " << lineCount << " 行数值解析失败: "
                      << line << std::endl;
        }
        lineCount++;
    }

    file.close();
}

/**
 * @brief 为服务端和客户端节点生成邻居节点
 *
 * 该函数为服务端和每个客户端节点随机分配指定数量的邻居节点。
 * 在分配过程中，会检查节点是否已经是邻居，避免重复添加。
 * 同时，更新每个节点的邻居数量、最小距离和最大距离。
 *
 * @param n 节点的数量
 * @param neighbor_count 每个节点需要生成的邻居节点数量
 * @param server 服务端节点的引用
 * @param client 客户端节点数组
 */
void CreateNeibor(int n, int neighbor_count, Server &server, Client client[])
{
    int id = 0;
    random_device rd;                     // 真随机数生成器
    mt19937 gen(rd());                    // 使用 Mersenne Twister 算法
    uniform_int_distribution<> dis(1, n); // 定义范围 [1, n]
    // 生成服务端的邻居
    for (int i = 1; i <= neighbor_count; i++)
    {
        // 选取随机一个id
        id = dis(gen);
        // 判断此节点是否已为邻居
        NeiborNode *temp = server.neibor_head;
        while (temp != NULL && temp->id != id)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            // 为空
        }
        else if (temp->id == id)
        {
            // 已为邻居 此次作废
            i--;
            continue;
        }
        server.neibor_count++;
        // 将该客户端节点添加为服务端的邻居，并计算它们之间的距离
        server.AddNeibor(&client[id], id, distance(server, client[id]));
        // 更新服务端邻居的最小距离和最大距离
        server.min_dis = server.neibor_head->dis;
        server.max_dis = server.neibor_tail->dis;
    }
    // 生成客户端的邻居
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= neighbor_count; j++)
        {
            // 选取随机一个id
            id = dis(gen);
            // 判断此节点是否已为邻居
            NeiborNode *temp = client[i].neibor_head;
            while (temp != NULL && temp->id != id)
            {
                temp = temp->next;
            }
            if (temp == NULL)
            {
                // 为空
            }
            else if (temp->id == id)
            {
                // 已为邻居 此次作废
                j--;
                continue;
            }
            client[i].neibor_count++;
            // 将该客户端节点添加为当前客户端节点的邻居，并计算它们之间的距离
            client[i].AddNeibor(&client[id], id, distance(client[i], client[id]));
        }
        // 更新当前客户端节点邻居的最小距离和最大距离
        client[i].min_dis = client[i].neibor_head->dis;
        client[i].max_dis = client[i].neibor_tail->dis;
    }
}
/**
 * @brief 将指定节点的所有未被唤醒的邻居节点的 ID 添加到队列中
 * 
 * 该函数会遍历指定节点的邻居节点链表，把其中尚未被唤醒的邻居节点的 ID 依次添加到给定的队列里，
 * 并将这些节点标记为已唤醒。
 * 
 * @param node_list 引用类型，用于存储邻居节点 ID 的队列
 * @param node 引用类型，需要遍历其邻居节点的节点
 * @param awakenedNodes 布尔数组，用于记录节点是否已经被唤醒，数组下标对应节点 ID
 */
void AddNodeToQueue(queue<int> &node_list, Node &node, bool *awakenedNodes)
{
    NeiborNode *temp = node.neibor_head;
    while (temp->next != NULL)
    {
        //没唤醒就唤醒
        if (!awakenedNodes[temp->id]) {
            node_list.push(temp->id);
            awakenedNodes[temp->id] = 1;
        }
        temp = temp->next;
    }
}
/**
 * @brief 处理数据请求，服务端产生数据块并唤醒邻居节点
 *
 * 此函数模拟服务端产生数据块的过程，每调用一次服务端产生 30K 的数据块。
 * 同时，当节点产生或得到数据块时，会唤醒其邻居节点，将邻居节点 ID 存入队列。
 *
 * @param server 服务端节点的引用，用于产生数据块
 * @param client 客户端节点数组，用于处理相关节点的唤醒操作
 */
void DataRequest(Server &server, Client client[])
{
    // 服务端产生数据块 每帧30K
    server.data_end += 30;
    // 每个节点产生或得到数据块时 唤醒其邻居节点
    queue<int> node_call_list;
    // 重复访问？ 怎么解决?//用一个bool数组来判断是否唤醒过
    bool *awakenedNodes = new bool[INIT_EMPTY+INIT_NODE + 1]();//这里要改
    // 唤醒服务端的邻居节点
    AddNodeToQueue(node_call_list, server, awakenedNodes);

    // 唤醒客户端的邻居节点
    
    // 释放内存
    delete[] awakenedNodes;
}
