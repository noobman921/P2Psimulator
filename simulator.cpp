#include "simulator.h"


//此函数用于随机生成n个客户端 1个服务端
//n为初始化的个数
void Simulator_Data_Generate(int n)
{
    if(n < 1){
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
    file << "Server: " << 0 << server_x << " " << server_y << endl;

    // 生成 n 个客户端
    for (int i = 0; i < n; ++i)
    {
        int client_x = dis_x(gen);
        int client_y = dis_y(gen);
        file << "Client " << i + 1 << ": " << client_x << " " << client_y << endl;
    }

    file.close();
}