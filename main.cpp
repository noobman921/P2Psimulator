#include <iostream>
#include <queue>
#include "node.h"
#include "simulator.h"

// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
using namespace std;


int main()
{
    //服务端+1
    SimulatorDataGenerate(INIT_NODE + 1);
    Server server;
    Client client[INIT_NODE + INIT_EMPTY];
    queue<int> free_node;//存放空闲位置
    for (int i = INIT_NODE; i < INIT_NODE + INIT_EMPTY; i++)
    {
        free_node.push(i);
    }
    CreateNodeFromFile(INIT_NODE, server, client);
    //读文件创建节点
    CreateNeibor(INIT_NODE, NEIGHBOR_COUNT, server, client);
    //long long time = 0;
    // while (1)
    // {
        
    //     perFrame(time);

    // }
    return 0;
}
