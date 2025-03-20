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
            server=Server(lineCount, num1, num2);
            else
            client[lineCount - 1] = Client(lineCount, num1, num2);
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

void CreateNeibor(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            // 计算距离
        }
    }
}