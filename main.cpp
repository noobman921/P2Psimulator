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
    //�����+1
    SimulatorDataGenerate(INIT_NODE + 1);
    Server server;
    Client client[INIT_NODE + INIT_EMPTY];
    queue<int> free_node;//��ſ���λ��
    for (int i = INIT_NODE; i < INIT_NODE + INIT_EMPTY; i++)
    {
        free_node.push(i);
    }
    CreateNodeFromFile(INIT_NODE, server, client);
    //���ļ������ڵ�
    CreateNeibor(INIT_NODE, NEIGHBOR_COUNT, server, client);
    //long long time = 0;
    // while (1)
    // {
        
    //     perFrame(time);

    // }
    return 0;
}
