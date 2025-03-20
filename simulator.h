#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <queue>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include "node.h"

// ���� ����ϵxy�ķ�Χ
#define MAX_X 100000
#define MAX_Y 100000

void Simulator_Data_Generate(int n);
void CreateNodeFromFile(int n,Server& server, Client client[]);
void CreateNeibor(int n);

#endif