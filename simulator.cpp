#include "simulator.h"
#include "node.h"
// 此函数用于随机生成n个客户端 1个服务端
// n为初始化的个数
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

// 从文件中读取节点信息
// n 为节点个数
// server 为服务端
// client 为客户端数组
void CreateNodeFromFile(int n, Server& server, Client client[])
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
            if(lineCount==-1)
            server = Server(lineCount, num1, num2);
            else
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

// 生成邻居
// n 为节点个数
// neighbor_count 为邻居个数
// server 为服务端
// client 为客户端数组
void CreateNeibor(int n, int neighbor_count, Server& server, Client client[])
{
    int id = 0;
    random_device rd; // 真随机数生成器
    mt19937 gen(rd()); // 使用 Mersenne Twister 算法
    uniform_int_distribution<> dis(1, n); // 定义范围 [1, n]
    //生成服务端的邻居
    for (int i = 1; i <= neighbor_count; i++)
    {
        //选取随机一个id
        id = dis(gen);
        //判断此节点是否已为邻居
        NeiborNode *temp = server.neibor_head; 
        while (temp != NULL && temp->id != id)
        {
            temp = temp->next;
        }
        if(temp == NULL)
        {
            //为空
        }
        else if (temp->id == id)
        {
            //已为邻居 此次作废
            i--;
            continue;
        }
        server.neibor_count++;
        server.AddNeibor(&client[id], id, distance(server, client[id]));
    }
    //生成客户端的邻居
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= neighbor_count; j++)
        {
            //选取随机一个id
            id = dis(gen);
            //判断此节点是否已为邻居
            NeiborNode *temp = client[i].neibor_head;
            while (temp != NULL && temp->id != id)
            {
                temp = temp->next;
            }
            if(temp == NULL)
            {
                //为空
            }
            else if (temp->id == id)
            {
                //已为邻居 此次作废
                j--;
                continue;
            }
            client[i].neibor_count++;
            client[i].AddNeibor(&client[id], id, distance(client[i], client[id]));
        }
    }
}