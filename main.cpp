#include "node.h"
#include "simulator.h"
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
using namespace std;

constexpr int Node_Count = 100;//�ڵ�����
int main()
{
    Simulator_Data_Generate(Node_Count);
    
    Server server;
    Client client[Node_Count];
    CreateNodeFromFile(Node_Count, server, client);
    //���ļ������ڵ�
    CreateNeibor(Node_Count);
    //long long time = 0;
    // while (1)
    // {
        
    //     perFrame(time);

    // }
    return 0;
}
