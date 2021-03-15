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

void ShowIdList(Places P,Ids *I){ // 展示路径
    ID * Pointer = I->id->next;
    printf("From %s",Search(P,I->id->num));
    while (Pointer!=NULL) {
        printf("->%s",Search(P,Pointer->num));
        Pointer=Pointer->next;
    }
    printf("\n");
}




int NextPointerInIdList(Ids *I,Ids *Black,IdLine* LinePointer){
    Edge *Pointer = LinePointer->Start;
    while (Pointer) {
        if (!IdsInsisted(I,Pointer->ToId)&&!IdsInsisted(Black,Pointer->ToId)) {
            return 1;
        }else{
            Pointer=Pointer->next;
        }
    }
    return 0; // 没有往前走的必要
}

int IdsBack(Places P,Ids* I){
    ID * Pointer = I->id;
    int ret=0;
    if (Pointer->next==NULL) {
        ret = Pointer->num;
        printf("Back From %s\n",Search(P,Pointer->num));
        free(Pointer);
        I->id=NULL;
        return ret;
    }
    while (Pointer!=NULL) {
        if (Pointer->next->next==NULL) {
            ret = Pointer->next->num;
            free(Pointer->next);
            Pointer->next=NULL;
            printf("Back From %s\n",Search(P,Pointer->num));
            return ret;
        }else{
            Pointer = Pointer->next;
        }
    }
    return 0;// 无路可退
}

int RoadWeight(Ids *I,Graph *G){ // 此路径的权重（距离）
    IdLine* Line=NULL;
    ID* IdPointer = I->id;
    Edge * e;
    int WeightSum=0;
    while (IdPointer->next!=NULL) {
        Line = FindIdLine(*G, IdPointer->num);
        e=Line->Start;
        while(e){
            if (e->ToId!=IdPointer->next->num) {
                e=e->next;
            }else{
                break;
            }
        }
        WeightSum+=e->weight;
        IdPointer=IdPointer->next;
    }
    return WeightSum;
}

void SearchRoad(Places P,Graph g){
    int IdA,IdB;
    printf("请输入初始点 最终点:");
    scanf("%d %d",&IdA,&IdB);
    int Now = IdA,weight,Tag=1;
    IdLine* LineNow;
    Ids* IdList=IdsInit(); // 走过的ID
    Ids* IdBlack = IdsInit(); // 不能走的ID
    printf("From %s\n",Search(P, IdA));
    while (Now!=IdB) {
        LineNow = FindIdLine(g, Now);
        Edge* IdPointer = LineNow->Start;
        weight=IdsInsisted(IdList, IdB); // 可以直接到B的情况
        IdsPull(IdList, IdA);
        if (weight!=0) { // 直接到B 结束循环
            break;
        }
        if(!NextPointerInIdList(IdList, IdBlack, LineNow)){ // 这个点没必要去遍历 都不行
            IdsPull(IdBlack,IdsBack(P,IdList)); // 后退一步 并将此节点放入黑名单
            Now = LastIdsId(IdList); // 返回到上一个ID
            continue;
        }
        while (Tag) { // 从这个ID的边中找到可能的
            if (IdPointer==NULL) { // 若为空 此时所有边都已遍历
                IdsPull(IdBlack,IdsBack(P,IdList)); // 后退一步 并将此节点放入黑名单
                Now = LastIdsId(IdList); // 返回到上一个ID
            }
            if (!IdsInsisted(IdBlack, IdPointer->ToId)&&!IdsInsisted(IdList, IdPointer->ToId)) { // 不再黑名单中
                IdsPull(IdList, IdPointer->ToId); // 向下一位移动
                printf("move to %s",Search(P,IdPointer->ToId));
                Now = IdPointer->ToId;
                break;
            }else{ // 下一个
                IdPointer=IdPointer->next;
            }
        }
        printf("\n");
    }
    printf("Road:");
    ShowIdList(P,IdList);
    printf("Weight:%d\n",RoadWeight(IdList, &g));
}


void InforInit(){
    Places P;
    PlacesInit(&P);
    PlacesPutIn(&P);
    Graph *G=(Graph*)malloc(sizeof(Graph));
    graphInit(G);
    GraphPutIn(G);
    SearchRoad(P, *G);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    InforInit();
    printf("Goodbye!\n");
    return 0;
}
