//
//  main.c
//  CampusNavigation
//
//  Created by Muxxs🇨🇳 on 2021/3/8.
//

#include "Graph.cpp"
#include "LinkList.cpp"
#include "IdList.cpp"

void GraphShow(Places P,Graph g){
    IdLine * LinePointer = g.Start;
    while (LinePointer!=NULL) {
        Edge* EdgePointer = LinePointer->Start;
        while (EdgePointer!=NULL) {
            printf("节点:%5s 经过%2d后 到达%s\n",Search(P,LinePointer->ID),EdgePointer->weight,Search(P,EdgePointer->ToId));
            EdgePointer=EdgePointer->next;
        }
        LinePointer=LinePointer->NextLine;
    }
}

void SearchRoad(Places P,Graph g){
    int IdA,IdB;
    printf("请输入初始点 最终点:");
    scanf("%d %d",&IdA,&IdB);
    int Now = IdA,weight;
    IdLine* LineNow;
    Ids* IdList=IdsInit(); // 走过的ID
    Ids* IdBlack = IdsInit(); // 不能走的ID
    while (Now!=IdB) {
        LineNow = FindIdLine(g, Now);
        Edge* IdPointer = LineNow->Start;
        weight=IdsInsisted(IdList, IdB); // 可以直接到B的情况
        if (weight!=0) {
            break;
        }
        while (1) {
            if (!IdsInsisted(IdBlack, IdPointer->ToId)) { // 不再黑名单中
                if(IdsPull(IdList, IdPointer->ToId)){ // 尝试移动到下一个节点
                    printf("move to %d",IdPointer->ToId);
                    Now = IdPointer->ToId;
                    break;
                }
                if (IdPointer->next==NULL) { // 无路可走
                    IdsPull(IdBlack,IdsBack(IdList)); // 后退一步 并将此节点放入黑名单
                    break;
                }else{
                    IdPointer = IdPointer->next;
                }
            }
        }
    }
    printf("Road:%d",IdA);
    ShowIdList(IdList);
}


void InforInit(){
    Places P;
    PlacesInit(&P);
    PlacesPutIn(&P);
    Graph *G=(Graph*)malloc(sizeof(Graph));
    graphInit(G);
    GraphPutIn(G);
    GraphShow(P,*G);
    SearchRoad(P, *G);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    InforInit();
    printf("Goodbye!\n");
    return 0;
}
