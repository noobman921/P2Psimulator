#include <iostream>
#include <queue>
#include "node.h"
#include "simulator.h"
#include <thread>
#include <chrono>
#include <cstdio>
// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
using namespace std;

int main()
{
    // �����+1
    SimulatorDataGenerate(INIT_NODE + 1);
    Server server;
    Client client[INIT_NODE + INIT_EMPTY];
    queue<int> free_node; // ��ſ���λ��
    for (int i = INIT_NODE; i < INIT_NODE + INIT_EMPTY; i++)
    {
        free_node.push(i);
    }
    CreateNodeFromFile(INIT_NODE, server, client);
    // ���ļ������ڵ�
    CreateNeibor(INIT_NODE, NEIGHBOR_COUNT, server, client);
    // �������ݿ�
    DataRequest(server, client);
    // ���㴫������
    StreamCalculate(0, 1, client);
    int a = 1;
    // long long time = 0;
    //  while (1)
    //  {

    // perFrame(time);

    // }
    FILE *pipe = _popen("python UI.py", "w");
    if (!pipe)
    {
        fprintf(stderr, "�ܵ���ʧ��\n");
        return 1;
    }
    fprintf(pipe, "POINTS ");
    fprintf(pipe, "%lld %lld ", server.x, server.y);
    for (const auto &p : client)
    {
        fprintf(pipe, "%lld %lld ", p.x, p.y);
    }
    fprintf(pipe, "\n");

    // Ȼ������������ӹ�ϵ��ARROWS��
    fprintf(pipe, "ARROWS ");

    // ��� server �������ھ�����
    for (NeiborNode *curr = server.neibor_head; curr != nullptr; curr = curr->next)
    {
        fprintf(pipe, "%d %d ", server.id, curr->id); // server.id -> neighbor.id
    }

    // ���ÿ�� client �������ھ�����
    for (const auto &p : client)
    {
        for (NeiborNode *curr = p.neibor_head; curr != nullptr; curr = curr->next)
        {
            fprintf(pipe, "%d %d ", p.id, curr->id); // client.id -> neighbor.id
        }
    }

    fprintf(pipe, "\n");
    fprintf(pipe, "END\n");
    fflush(pipe);
    std::this_thread::sleep_for(std::chrono::seconds(1)); // ȷ��Python�������
    _pclose(pipe);
    //system("pause");
    return 0;
}
