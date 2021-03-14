//
//  IDList.c
//  CampusNavigation
//
//  Created by Muxxs🇨🇳 on 2021/3/14.
//

#include <stdlib.h>
#include <stdio.h>

typedef struct ID{
    int num;  // ID
    struct ID* next;
} ID;

typedef struct Ids{
    int size;
    ID * id;
}Ids;

Ids *IdsInit(){
    Ids* I = (Ids*)malloc(sizeof(Ids));
    I->size = 0;
    I->id = NULL;
    return I;
}

int IdsPull(Ids* I,int id){ // 已存在返回0 不存在插入后为1
    ID * Pointer = I->id;
    while (Pointer!=NULL) {
        if (Pointer->num==id) {
            return 0;
        }else{
            Pointer = Pointer->next;
        }
    }
    ID * NewId = (ID*)malloc(sizeof(ID));
    NewId->num = id;
    NewId->next = NULL;
    Pointer->num++;
    Pointer->next = NewId;
    return 1;
}

void IdsDestroy(Ids *I){
    ID * Pointer = I->id,*Next;
    while (Pointer!=NULL) {
        Next = Pointer->next;
        free(Pointer);
        Pointer = Next;
    }
    free(I);
}
