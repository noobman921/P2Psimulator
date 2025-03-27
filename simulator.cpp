#include "simulator.h"
#include "node.h"
/**
 * @brief ����ģ��ڵ����ݲ�д���ļ�
 *
 * �ú�����������ָ�������Ľڵ����ݣ����� 1 ������˽ڵ�� n ���ͻ��˽ڵ㣬
 * ������Щ�ڵ����Ϣд����Ϊ "data.txt" ���ļ��С�ÿ���ڵ���Ϣ�������͡���š�x ����� y ���ꡣ
 *
 * @param n Ҫ���ɵĿͻ��˽ڵ������
 */
void SimulatorDataGenerate(int n)
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

/**
 * @brief ���ļ�data.txt�ж�ȡ�ڵ���Ϣ�������ڵ�
 *
 * �ú�������Ϊ "data.txt" ���ļ��ж�ȡ�ڵ���Ϣ�������ļ����ݴ���һ������˽ڵ�Ͷ���ͻ��˽ڵ㡣
 * �ļ���ÿһ�д���һ���ڵ㣬��ʽΪ "���� ���: x���� y����"��
 *
 * @param n �ͻ��˽ڵ������
 * @param server �������ͣ����ڴ洢�����ķ���˽ڵ�
 * @param client �ͻ��˽ڵ����飬���ڴ洢�����Ŀͻ��˽ڵ�
 */
void CreateNodeFromFile(int n, Server &server, Client client[])
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
            if (lineCount == -1)
                // ��Ϊ��һ�У���������˽ڵ�
                server = Server(lineCount, num1, num2);
            else
                // �����ǵ�һ�У������ͻ��˽ڵ�
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

/**
 * @brief Ϊ����˺Ϳͻ��˽ڵ������ھӽڵ�
 *
 * �ú���Ϊ����˺�ÿ���ͻ��˽ڵ��������ָ���������ھӽڵ㡣
 * �ڷ�������У�����ڵ��Ƿ��Ѿ����ھӣ������ظ���ӡ�
 * ͬʱ������ÿ���ڵ���ھ���������С����������롣
 *
 * @param n �ڵ������
 * @param neighbor_count ÿ���ڵ���Ҫ���ɵ��ھӽڵ�����
 * @param server ����˽ڵ������
 * @param client �ͻ��˽ڵ�����
 */
void CreateNeibor(int n, int neighbor_count, Server &server, Client client[])
{
    int id = 0;
    random_device rd;                     // �������������
    mt19937 gen(rd());                    // ʹ�� Mersenne Twister �㷨
    uniform_int_distribution<> dis(1, n); // ���巶Χ [1, n]
    // ���ɷ���˵��ھ�
    for (int i = 1; i <= neighbor_count; i++)
    {
        if (server.neibor_count == NEIGHBOR_COUNT)
            break; // ������ھ��������� ����ѭ��
        // ѡȡ���һ��id
        id = dis(gen);
        // �жϴ˽ڵ��Ƿ���Ϊ�ھ�
        NeiborNode *temp = server.neibor_head;
        while (temp != NULL && temp->id != id)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            // Ϊ��
        }
        else if (temp->id == id)
        {
            // ��Ϊ�ھ� �˴�����
            i--;
            continue;
        }
        if (client[id].neibor_count != NEIGHBOR_COUNT)
        {
            server.neibor_count++;
            client[id].neibor_count++;
            // ���ÿͻ��˽ڵ����Ϊ����˵��ھӣ�����������֮��ľ���
            server.AddNeibor(&client[id], id, distance(server, client[id]));
            client[id].AddNeibor(&server, -1, distance(server, client[id]));
            // ���·�����ھӵ���С�����������
            server.min_dis = server.neibor_head->dis;
            server.max_dis = server.neibor_tail->dis;
            // ���¿ͻ����ھӵ���С�����������
            client[id].min_dis = client[id].neibor_head->dis;
            client[id].max_dis = client[id].neibor_tail->dis;
        }
        else
        {
            i--; // �ھ��������� �˴�����
        }
    }
    // ���ɿͻ��˵��ھ�
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= neighbor_count; j++)
        {
            if (client[i].neibor_count == NEIGHBOR_COUNT)
                break; // �ͻ����ھ��������� ����ѭ��
            // ѡȡ���һ��id
            id = dis(gen);
            // �жϴ˽ڵ��Ƿ���Ϊ�ھ�
            NeiborNode *temp = client[i].neibor_head;
            while (temp != NULL && temp->id != id)
            {
                temp = temp->next;
            }
            if (temp == NULL)
            {
                // Ϊ��
            }
            else if (temp->id == id)
            {
                // ��Ϊ�ھ� �˴�����
                j--;
                continue;
            }
            if (client[id].neibor_count != NEIGHBOR_COUNT)
            {
                client[i].neibor_count++;
                client[id].neibor_count++;
                // ���ÿͻ��˽ڵ����Ϊ��ǰ�ͻ��˽ڵ���ھӣ�����������֮��ľ���
                client[i].AddNeibor(&client[id], id, distance(client[i], client[id]));
                client[id].AddNeibor(&client[i], i, distance(client[i], client[id]));
                // ���µ�ǰ�ͻ��˽ڵ��ھӵ���С�����������
                client[i].min_dis = client[i].neibor_head->dis;
                client[i].max_dis = client[i].neibor_tail->dis;
                // ���±���ӵĿͻ��˽ڵ��ھӵ���С�����������
                client[id].min_dis = client[id].neibor_head->dis;
                client[id].max_dis = client[id].neibor_tail->dis;
            }
            else
            {
                j--; // �ھ��������� �˴�����
            }
        }
    }
}
/**
 * @brief ��ָ���ڵ������δ�����ѵ��ھӽڵ�� ID ��ӵ�������
 *
 * �ú��������ָ���ڵ���ھӽڵ�������������δ�����ѵ��ھӽڵ�� ID ������ӵ������Ķ����
 * ������Щ�ڵ���Ϊ�ѻ��ѡ�
 *
 * @param node_list �������ͣ����ڴ洢�ھӽڵ� ID �Ķ���
 * @param node �������ͣ���Ҫ�������ھӽڵ�Ľڵ�
 * @param awakenedNodes �������飬���ڼ�¼�ڵ��Ƿ��Ѿ������ѣ������±��Ӧ�ڵ� ID
 */
void AddNodeToQueue(queue<int> &node_list, Node &node, bool *awakenedNodes)
{
    NeiborNode *temp = node.neibor_head;
    while (temp->next != NULL)
    {
        // û���Ѿͻ���
        if (!awakenedNodes[temp->id])
        {
            node_list.push(temp->id);
            awakenedNodes[temp->id] = 1;
        }
        temp = temp->next;
    }
}
/**
 * @brief �����������󣬷���˲������ݿ鲢�����ھӽڵ�
 *
 * �˺���ģ�����˲������ݿ�Ĺ��̣�ÿ����һ�η���˲��� 30K �����ݿ顣
 * ͬʱ�����ڵ������õ����ݿ�ʱ���ỽ�����ھӽڵ㣬���ھӽڵ� ID ������С�
 *
 * @param server ����˽ڵ�����ã����ڲ������ݿ�
 * @param client �ͻ��˽ڵ����飬���ڴ�����ؽڵ�Ļ��Ѳ���
 */
void DataRequest(Server &server, Client client[])
{
    // ����˲������ݿ� ÿ֡30K
    server.data_end += 30;
    // ÿ���ڵ������õ����ݿ�ʱ �������ھӽڵ�
    queue<int> node_call_list;
    // �ظ����ʣ� ��ô���?//��һ��bool�������ж��Ƿ��ѹ�
    bool *awakenedNodes = new bool[INIT_EMPTY + INIT_NODE]();
    // ���ѷ���˵��ھӽڵ�
    AddNodeToQueue(node_call_list, server, awakenedNodes);
    int temp;
    // ���ѿͻ��˵��ھӽڵ�
    while(!node_call_list.empty())
    {
        //��ڵ㴦��
        temp = node_call_list.front();
        //tempΪ��ǰ�ڵ��id
        node_call_list.pop();
        //����temp�ھӲ���������
        NeiborNode* ptr = client[temp].neibor_head;
        //ptrָ���ھӽڵ�
        for(int i = 0; i < NEIGHBOR_COUNT; i++)
        {
            //�ھ�ΪServer
            int speed = SpeedGet(ptr->id, temp, server, client);
            if(ptr->id == -1)
            {
                if(client[temp].cache_comptr->data_id < server.data_start)
                {
                    //�������� ��������Ϊ�ٶ�
                    for(int i = 0; i < speed; i++)
                    {
                        //Ѱ�ҿ��������ݿ�
                        while(client[temp].cache_comptr != client[temp].cache_tail && client[temp].cache_comptr->data_id + 1 == client[temp].cache_comptr->next->data_id)
                        {
                            client[temp].cache_comptr = client[temp].cache_comptr->next;
                        }
                        if(client[temp].cache_comptr->data_id + 1 <= server.data_end)
                        {
                            //�������ݿ�
                            client[temp].AddData(client[temp].cache_comptr->data_id + 1);
                        }
                        else
                        {
                            //û�����ݿ������
                            break;
                        }
                    }
                }
            }
            else
            {
                //�ھ�Ϊclient
                DataNode* ptr_receiver = client[temp].cache_comptr;
                DataNode* ptr_sender = client[ptr->id].cache_head;
                int i = 0;
                while(i < speed)
                {
                    while(ptr_sender != NULL && ptr_receiver->data_id >= ptr_sender->data_id)
                    {
                        //��������������ݿ�
                        //�ҵ���һ������comptr��id
                        ptr_sender = ptr_sender->next;
                    }
                    //�޿��������ݿ�
                    if(ptr_sender == NULL)break;
                    //�ж�receiver�Ƿ���ӵ�д����ݿ� ���ҵ�һ�����ݿ���ڵ���sender�����ݿ�
                    DataNode* checkptr = ptr_receiver->next;
                    while(checkptr->data_id < ptr_sender->data_id)
                    {
                        //receiver�������ݿ��С��sender ֱ�����sender
                        if(checkptr == client[temp].cache_tail)break;
                        checkptr = checkptr->next;
                    }
                    //�ҵ����ڵ���sender�����ݿ�
                    if(checkptr->data_id == ptr_sender->data_id)
                    {
                        //��ӵ�и����ݿ�
                        continue;
                        //��һ��ѭ��
                    }
                    //�ҵ�����sender�����ݿ� �� receiver�������ݿ��С��sender
                    client[temp].AddData(ptr_sender->data_id);
                    i++;
                }
            }
        }
        AddNodeToQueue(node_call_list, client[temp], awakenedNodes);
    }
    
    // �ͷ��ڴ�
    delete[] awakenedNodes;
}

/**
 * @brief ��ô����ٶ�
 * @param id1 �������ݵĽڵ�id
 * @param id2 �������ݵĽڵ�id
 * @param server ����˽ڵ������
 * @param client �ͻ��˽ڵ�����
 */
int SpeedGet(int id1, int id2, Server &server, Client Client[])
{
    if(id1 == -1)
    {
        return 100 - (int)((distance(server, Client[id2])-server.neibor_head->dis)/(server.neibor_tail->dis - server.neibor_head->dis)*80);
    }
    else
    {
        return 100 - (int)((distance(Client[id1], Client[id2])-Client[id1].neibor_head->dis)/(Client[id1].neibor_tail->dis - Client[id1].neibor_head->dis)*80);
    }
    return 0;
}