#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <queue>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include "node.h"

// 定义 坐标系xy文件范围
#define MAX_X 100000
#define MAX_Y 100000
#define INIT_NODE 10
#define INIT_EMPTY 1
// 定义邻居数量
#define NEIGHBOR_COUNT 3

//定义数据块播放的下限
#define DATA_STREAM 5


void SimulatorDataGenerate(int n);
void CreateNodeFromFile(int n, Server &server, Client client[]);
void CreateNeibor(int n, int neighbor_count, Server &server, Client client[]);
void AddNodeToQueue(queue<int> &node_list, Node &node, bool *awakenedNodes);
void DataRequest(Server &server, Client client[]);
int SpeedGet(int id1, int id2, Server &server, Client Client[]);
int StreamCalculate(int id, int time, Client client[]);

#endif