#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Map{
    char diachi[41];
    int gio;
    int phut;
    struct Map * next;
}Map;

Map * root;

Map *makeNode(char *diachi, int gio, int phut){
    Map *map = (Map *)malloc(sizeof(Map));
    strcpy(map->diachi, diachi);
    map->gio = gio;
    map->phut = phut;
    map->next = NULL;
    return map;
}
Map *inserLast(Map *r, char *diachi, int gio, int phut){
    if(r == NULL) return makeNode(diachi, gio, phut);
    r->next = inserLast(r->next, diachi, gio, phut);
    return r;
}

void loadFile(){
    FILE *fin = fopen("log.txt", "r");
    root = NULL;
    while(!feof(fin)){
        char diachi[41]; int gio, phut;
        fscanf(fin, "%s%d%d", diachi, &gio, &phut);
        root = inserLast(root, diachi, gio, phut);
    }
    printf("\nLoad Succesfully\n");
}

void printLS(){
    printf("Lich su di chuyen : \n");
    printf("%-50s %-10s %-10s\n", "Dia diem", "Gio", "Phut");
    for(Map *i = root; i != NULL; i = i->next){
        printf("%-50s %-10d %-10d\n", i->diachi, i->gio, i->phut);
    }
}

void findDiadiem(){fflush(stdin);int count = 0;
    char diadiem[41]; printf("Nhap dia diem : "); scanf("%s", diadiem);
    for(Map *i = root; i != NULL; i = i->next){
       if(strcmp(i->diachi, diadiem) == 0) count++;
    }
    if(count == 0){ printf("\nBan chua toi dia diem do");
    return;}
    for(Map *i = root; i != NULL; i = i->next){
       if(strcmp(i->diachi, diadiem) == 0) printf("%d:%d,", i->gio, i->phut);
    }
    
}

int hople(Map *r, int gio, int phut){
    if(r == NULL) return 0;
    if(r->next == NULL){
        if(gio - r->gio > 0 && gio - r->gio <= 2) return 1;
        if(gio == r->gio && phut >= r->phut) return 1;
        else return 0;
    }
    if(gio >= r->gio && gio < r->next->gio) return 1;
    if(gio > r->gio && gio == r->next->gio && phut < r->next->phut) return 1;
    if(gio == r->gio && gio == r->next->gio && phut >= r->phut && phut < r->next->phut) return 1;
    return 0;
}

void findTime(){
    printf("Nhap thoi gian muon xem : ");int gio, phut;
    while(1){
        scanf("%d %d", &gio, &phut);
        if(gio >= 0 && gio < 24 && phut >= 0 && phut < 60) break;
        printf("Khong hop le ! Nhap lai : ");
    }
    for(Map *i = root; i != NULL; i = i->next){
        if(hople(i,gio, phut)) {
        printf("%s ", i->diachi);
        return;
        }
    }
    printf("Khong tim thay lich su di chuyen ");
}
int duongtinh(Map * r, char * diadiem, int gio, int phut){
    if(r == NULL) return 0;
    if(strcmp(r->diachi, diadiem) == 0){
        if(gio < r->gio) return 1;
        if(gio == r->gio && phut <= r->phut) return 1;
        if(r->next->gio > gio ) return 1;
        if(r->next->gio == gio && phut <= r->next->phut) return 1;
    }
    return 0;
}

void truyVet(){
    char diadiem[41];int gio, phut;
    printf("Dia diem va thoi gian co F0 : ");
    scanf("%s", diadiem); 
    while(1){
        scanf("%d %d", &gio, &phut);
        if(gio >= 0 && gio <= 24 && phut >= 0 && phut <= 60) break;
        printf("Khong hop le ! Nhap lai : ");
    }
    for(Map *i = root; i != NULL; i = i->next){
        if(duongtinh(i,diadiem,gio, phut)) {
            printf("Ban co kha nang, khai bao y te di ");
            return;
        }
    }
    printf("Chu van oke ");
}
void freeNee(){
    Map * p = root;
    while(p != NULL){
        Map *tmp = p->next;
        free(p);
        p = tmp;
    }
}
int main() {
    int exit = 1; int choice;
    while (exit)
    {
        printf("\n=========================");
        printf("\nCHUONG TRINH TRUY VET COVID 19");
        printf("\n1. Nap file log lich su di chuyen");
        printf("\n2. In ra lich su di chuyen");
        printf("\n3. Tim kiem lich su theo dia diem");
        printf("\n4. Tim kiem lich su theo thoi gian");
        printf("\n5. Kiem tra truy vet moi nhat");
        printf("\n6. Thoat");
        printf("\n=========================");
        printf("\nNhap lua chon : "); scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            loadFile();
            break;
        case 2:
            printLS();
            break;
        case 3:
            findDiadiem();
            break;
        case 4:
            findTime();
            break;
        case 5:
            truyVet();
            break;
        case 6:
            exit = 0;
            freeNee();
            break;
            
        }   

    }



    return 0;
}