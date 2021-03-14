//
//  Graph.cpp
//  CampusNavigation
//
//  Created by Muxxs🇨🇳 on 2021/3/9.
//
#include <stdlib.h>
#include "Graph.hpp"

typedef struct Edge{ // 边
    int ToId; // 目标节点位置
    int weight; // 权重（距离）
    struct Edge* next;
}Edge;

typedef struct IdLine{ // Edge的链表 是ID的边
    int ID;
    Edge* Start; //边的地址
    struct IdLine * NextLine; // 下一个ID的边
}IdLine;

typedef struct Graph{
    int size;
    IdLine * Start; // 边链表地址
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
    NewEdge->next = NULL;
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

int SearchId(IdLine Line,int id){ // 这个ID能不能直接到 传入的ID 如果可以 返回距离 否则返回0
    Edge* E=Line.Start;
    while (E!=NULL) {
        if (E->ToId==id) {
            return E->weight;
        }else{
            E = E->next;
        }
    }
    return 0;
}
