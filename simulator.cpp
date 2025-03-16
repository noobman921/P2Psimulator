#include "simulator.h"
#include "node.h"
// �˺��������������n���ͻ��� 1�������
// nΪ��ʼ���ĸ���
void Simulator_Data_Generate(int n)
{
    if (n < 1)
    {
        cout << "�ڵ���Ŀ����" << endl;
        return;
    }

    ofstream file("data.txt");
    if (!file.is_open())
    {
        cout << "�ļ���ʧ��" << endl;
        return;
    }

    // ʹ�����������ͷֲ���������� x �� y ����
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis_x(0, MAX_X);
    uniform_int_distribution<> dis_y(0, MAX_Y);

    // ���� 1 ������� �涨����˵����Ϊ0
    int server_x = dis_x(gen);
    int server_y = dis_y(gen);
    file << "Server " << 0 << ": " << server_x << " " << server_y << endl;
    Node(0, server_x, server_y);

    // ���� n ���ͻ���
    for (int i = 1; i <= n; i++)
    {
        int client_x = dis_x(gen);
        int client_y = dis_y(gen);
        file << "Client " << i + 1 << ": " << client_x << " " << client_y << endl;
        Node(i, client_x, client_y);
    }
    // ������ѿͻ��˺ͷ�������ɽڵ㣿
    file.close();
    return;
}