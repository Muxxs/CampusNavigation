//
//  main.c
//  CampusNavigation
//
//  Created by Muxxs🇨🇳 on 2021/3/8.
//

#include "Graph.cpp"
#include "LinkList.cpp"


void GraphShow(Places P,Graph g){
    IdLine * LinePointer = g.Start;
    while (LinePointer!=NULL) {
        Edge* EdgePointer = LinePointer->Start;
        while (EdgePointer!=NULL) {
            printf("节点:%s 经过%d后 到达%s\n",Search(P,LinePointer->ID),EdgePointer->weight,Search(P,EdgePointer->ToId));
            EdgePointer=EdgePointer->next;
        }
        LinePointer=LinePointer->NextLine;
    }
}



void InforInit(){
    Places P;
    PlacesInit(&P);
    PlacesPutIn(&P);
    Graph *G=(Graph*)malloc(sizeof(Graph));
    graphInit(G);
    GraphPutIn(G);
    GraphShow(P,*G);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    InforInit();
    printf("Hello, World!\n");
    return 0;
}
