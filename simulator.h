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
#define INIT_NODE 100
#define INIT_EMPTY 10
// 定义邻居数量
#define NEIGHBOR_COUNT 5

void SimulatorDataGenerate(int n);
void CreateNodeFromFile(int n, Server &server, Client client[]);
void CreateNeibor(int n, int neighbor_count, Server &server, Client client[]);
void AddNodeToQueue(queue<int> &node_list, Node &node, bool *awakenedNodes);
void DataRequest(Server &server, Client client[]);
int SpeedGet();

#endif