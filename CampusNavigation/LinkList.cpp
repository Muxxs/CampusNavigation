//
//  LinkList.cpp
//  CampusNavigation
//
//  Created by Muxxs🇨🇳 on 2021/3/9.
//
#include <stdlib.h>
#include <stdio.h>
// 地名 - ID 的表 仅插入 删除 查询使用 用于程序中查询对应地点的名称
typedef struct Place{
    char name[10];  // 地名
    int num;  // ID
    int type; // 地点类型
    struct Place* next;
} Place;

typedef struct{
    int size;
    Place * Start; // 头指针
    Place * End; // 尾指针
} Places;

void PlacesInit(Places *P){  // 初始化链表的属性
    P->size=0;
    P->Start=NULL;
    P->End = NULL;
}

void NameToName(char *a,char *b){ // Name到Name的赋值
    for (int i=0; i<10; i++) {
        a[i] = b[i];
    }
}

void Push(Places *P,char PlaceName[] , int PlaceNum){ // 插入信息
    Place *NewPlace=(Place*)malloc(sizeof(Place));
    NameToName(NewPlace->name, PlaceName);
    NewPlace->num = PlaceNum;
    NewPlace->next = NULL;
    if(P->End==NULL){
        P->Start = NewPlace;
        P->End = NewPlace;
    }else{
        P->End->next = NewPlace;
        P->End = NewPlace;
    }
}

void PlacesPutIn(Places *P){ // 第一次输入信息
    int times = 0,num = 0;
    char name[10];
    printf("Please input size of the Place:");
    scanf("%d",&times);
    for (int x = 0; x<times; x++) {
        scanf("%d %s",&num,name);
        Push(P,name,num);
    }
}

void Show(Places P){  // 展示所有的表中的数据
    Place* Pointer=P.Start;
    while (Pointer!=NULL) {
        printf("ID:%2d Name:%s\n",Pointer->num,Pointer->name);
        Pointer = Pointer->next;
    }
}

char* Search(Places P,int ID){ // 在P中查找ID 返回名称
    Place* Pointer=P.Start;
    while (Pointer!=NULL) {
        if (Pointer->num == ID) {
            return Pointer->name;
        }
        Pointer=Pointer->next;
    }
    return (char*)"MISSING";
}

void PlacesCheck(){
    Places P;
    PlacesInit(&P);
    PlacesPutIn(&P);
    Show(P);
    printf("请输入要查找的ID:");
    int i=0;
    scanf("%d",&i);
    printf("查找结果:%s\n", Search(P, i));
}
