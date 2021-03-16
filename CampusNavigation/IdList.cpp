//
//  IDList.c
//  CampusNavigation
//
//  Created by Muxxs🇨🇳 on 2021/3/14.
//

#include <stdlib.h>
#include <stdio.h>

typedef struct ID{ // 记录已经出现的ID
    int num;  // ID
    struct ID* next;
} ID;

typedef struct Ids{ // 已经出现的ID
    int size; // 已经出现的ID数量
    ID * id; // ID地址
}Ids;

Ids *IdsInit(){
    Ids* I = (Ids*)malloc(sizeof(Ids));
    I->size = 0;
    I->id = NULL;
    return I;
}

int IdsPull(Ids* I,int id){ // 已存在返回0 不存在插入后为1
    ID * Pointer = I->id;
    if (Pointer==NULL) {
        ID * NewId = (ID*)malloc(sizeof(ID));
        NewId->num = id;
        NewId->next = NULL;
        I->id = NewId;
        return 1;
    }
    while (Pointer!=NULL) {
        if (Pointer->num==id) {
            return 0;
        }else{
            if(Pointer->next==NULL){
                ID * NewId = (ID*)malloc(sizeof(ID));
                NewId->num = id;
                NewId->next = NULL;
                Pointer->next = NewId;
                return 1;
            }else{
                Pointer = Pointer->next;
                
            }
        }
    }
    return 0;
}


int IdsInsisted(Ids * I, int Id){ // 是否存在 1存在 不存在返回ID
    ID * Pointer = I->id;
    while (Pointer!=NULL) {
        if (Pointer->num==Id) {
            return 1;
        }else{
            Pointer = Pointer->next;
        }
    }
    return 0;
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

int LastIdsId(Ids *I){
    ID * Pointer = I->id;
    int ret=I->id->num;
    if (Pointer==NULL) {
        return I->id->num;
    }
    while(Pointer!=NULL) {
        ret = Pointer->num;
        Pointer = Pointer->next;
    }
    return ret;
}
