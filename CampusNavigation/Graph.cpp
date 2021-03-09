//
//  Graph.cpp
//  CampusNavigation
//
//  Created by Muxxs🇨🇳 on 2021/3/9.
//
#include <stdlib.h>
#include "Graph.hpp"

typedef struct Edge{
    int ToId; // 目标节点位置
    int weight; // 权重（距离）
    struct Edge* next;
}Edge;

typedef struct IdLine{ // Edge的链表 是ID的边
    int ID;
    Edge* Start;
    struct IdLine * NextLine;
}IdLine;

typedef struct Graph{
    int size;
    IdLine * Start;
}Graph;

void graphInit(Graph* g){
    g->size = 0;
    g->Start = NULL;
}

IdLine* FindIdLine(Graph G,int Id){ //在Graph中找到指定的节点
    IdLine* Pointer = G.Start;
    while (Pointer!=NULL) {
        if (Pointer->ID==Id) {
            return Pointer;
        }
        Pointer = Pointer->NextLine;
    }
    return NULL;
}
IdLine* CreateIdLine(Graph *G,int Id){
    IdLine *NewIdLine = (IdLine*)malloc(sizeof(IdLine));
    NewIdLine->ID = Id;
    NewIdLine->NextLine = G->Start;
    G->Start = NewIdLine;
    return NewIdLine;
}

void GraphPush(Graph *G,int IDStart,int IDEnd,int Weight){ // 插入一个边
    IdLine* Line = FindIdLine(*G, IDStart);
    if(!Line){
        Line = CreateIdLine(G, IDStart);
    }
    Edge *NewEdge = (Edge*)malloc(sizeof(Edge));
    NewEdge->ToId = IDEnd;
    NewEdge->weight = Weight;
    NewEdge->next = Line->Start;
    Line->Start = NewEdge;
}

void GraphPutIn(Graph *g){
    int times = 0,IDStart,IDEnd,Weight;
    printf("Please input number of edges:");
    scanf("%d",&times);
    for (int i = 0; i<times; i++) {
        scanf("%d %d %d",&IDStart,&IDEnd,&Weight);
        GraphPush(g, IDStart, IDEnd, Weight);
        GraphPush(g, IDEnd, IDStart, Weight);
    }
}
