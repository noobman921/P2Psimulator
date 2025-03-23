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
    // Node(0, server_x, server_y);

    // ���� n ���ͻ���
    for (int i = 1; i <= n; i++)
    {
        int client_x = dis_x(gen);
        int client_y = dis_y(gen);
        file << "Client " << i + 1 << ": " << client_x << " " << client_y << endl;
        // Node(i, client_x, client_y);
    }
    // ������ѿͻ��˺ͷ�������ɽڵ㣿
    file.close();
    return;
}

// ���ļ��ж�ȡ�ڵ���Ϣ
// n Ϊ�ڵ����
// server Ϊ�����
// client Ϊ�ͻ�������
void CreateNodeFromFile(int n, Server& server, Client client[])
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "�޷����ļ�" << std::endl;
        return;
    }

    std::string line;
    int lineCount = -1;
    while (std::getline(file, line))
    {
        
        size_t colonPos = line.find(':');

        // �����飺ȷ������ð��
        if (colonPos == std::string::npos)
        {
            std::cerr << "�� " << lineCount << " �и�ʽ����ȱ��ð�ţ�: "
                      << line << std::endl;
            continue;
        }

        // �����ַ�������ȡð�ź������
        std::istringstream iss(line.substr(colonPos + 1));
        int num1, num2;

        // ��ȡ��������
        if (iss >> num1 >> num2)
        {
            if(lineCount==-1)
            server = Server(lineCount, num1, num2);
            else
            client[lineCount] = Client(lineCount, num1, num2);
        }
        else
        {
            std::cerr << "�� " << lineCount << " ����ֵ����ʧ��: "
                      << line << std::endl;
        }
        lineCount++;
    }

    file.close();
}

// �����ھ�
// n Ϊ�ڵ����
// neighbor_count Ϊ�ھӸ���
// server Ϊ�����
// client Ϊ�ͻ�������
void CreateNeibor(int n, int neighbor_count, Server& server, Client client[])
{
    int id = 0;
    random_device rd; // �������������
    mt19937 gen(rd()); // ʹ�� Mersenne Twister �㷨
    uniform_int_distribution<> dis(1, n); // ���巶Χ [1, n]
    //���ɷ���˵��ھ�
    for (int i = 1; i <= neighbor_count; i++)
    {
        //ѡȡ���һ��id
        id = dis(gen);
        //�жϴ˽ڵ��Ƿ���Ϊ�ھ�
        NeiborNode *temp = server.neibor_head; 
        while (temp != NULL && temp->id != id)
        {
            temp = temp->next;
        }
        if(temp == NULL)
        {
            //Ϊ��
        }
        else if (temp->id == id)
        {
            //��Ϊ�ھ� �˴�����
            i--;
            continue;
        }
        server.neibor_count++;
        server.AddNeibor(&client[id], id, distance(server, client[id]));
    }
    //���ɿͻ��˵��ھ�
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= neighbor_count; j++)
        {
            //ѡȡ���һ��id
            id = dis(gen);
            //�жϴ˽ڵ��Ƿ���Ϊ�ھ�
            NeiborNode *temp = client[i].neibor_head;
            while (temp != NULL && temp->id != id)
            {
                temp = temp->next;
            }
            if(temp == NULL)
            {
                //Ϊ��
            }
            else if (temp->id == id)
            {
                //��Ϊ�ھ� �˴�����
                j--;
                continue;
            }
            client[i].neibor_count++;
            client[i].AddNeibor(&client[id], id, distance(client[i], client[id]));
        }
    }
}