#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
// Khai bao du lieu 
typedef struct Gui{
    char ngay[20];
    char gio[20];
    int loai;
    struct Gui * next;
}Gui;

typedef struct Xe{
    char bienso[13];
    Gui * time;
    struct Xe *next;
}Xe;

typedef struct Ce{
    char bienso[13];
    char ngay[20];
    char gio[20];
    int loai;
    struct Ce *next;
}Ce;
// Khai bao Node cua cay
typedef struct Node {
    char bienso[13];
    char day[20];
    char time[20];
    struct Node *left;
    struct Node *right;
}Node;

    Xe * root1; Ce *root; Node *root2;// tạo gốc

Gui * makeTime(char * ngay, char * gio, int loai){
    Gui *time = (Gui *)malloc(sizeof(Gui));
    strcpy(time->ngay, ngay);
    strcpy(time->gio, gio);
    time->loai = loai;
    time->next = NULL;
    return time;
}

Xe * makeXe(char *bienso, char *ngay, char *gio, int loai){
    Xe * xe = (Xe *)malloc(sizeof(Xe));
    strcpy(xe->bienso, bienso);
    xe->time = makeTime(ngay, gio, loai);
    xe->next = NULL;
    return xe;
}

Ce * makeCe(char *bienso, char *ngay, char *gio, int loai){
    Ce * ce = (Ce *)malloc(sizeof(Ce));
    strcpy(ce->bienso, bienso);
    strcpy(ce->ngay, ngay);
    strcpy(ce->gio, gio);
    ce->loai = loai;
    ce->next = NULL;
    return ce;
}
Gui * inserTime(Gui *r, char *ngay, char *gio, int loai){
    if(r == NULL) return makeTime(ngay, gio, loai);

    r->next = inserTime(r->next, ngay, gio, loai);
    return r;
}

Xe *inserXe(Xe *r, char *bienso, char *ngay, char *gio, int loai){
    if(r == NULL) return makeXe(bienso, ngay, gio, loai);
    int tmp = strcmp(r->bienso, bienso);
    if(tmp == 0) {
        r->time = inserTime(r->time, ngay, gio, loai);
        return r;
    }
    else{
    r->next = inserXe(r->next, bienso, ngay, gio, loai);
    return r;
        }
}

Ce *inserCe(Ce *r, char *bienso, char *ngay, char *gio, int loai){
    if(r == NULL) return makeCe(bienso, ngay, gio, loai);

    r->next = inserCe(r->next, bienso, ngay, gio, loai);
    return r;
}



void loadFile(){
    FILE *fin = fopen("log_input.txt", "r");
    root = NULL;
    root1 = NULL;
    while(!feof(fin)){

        char bienso[13]; char ngay[20]; char gio[20]; int loai;
        fscanf(fin, "%s %s %s %d", ngay, gio, bienso, &loai);
       // printf("%s %s %s %d\n",  bienso, ngay, gio, loai);
        root = inserCe(root, bienso, ngay, gio, loai);

        root1 = inserXe(root1, bienso, ngay, gio, loai);

    }

    fclose(fin);
}

void printNe(){
    for (Ce * i = root; i != NULL ; i = i->next)
    {
        printf("%s %s %s %d\n",  i->bienso, i->ngay, i->gio, i->loai);
    }
    
}

void printKhac(){
    for (Xe * i = root1; i != NULL ; i = i->next)
    {
        printf("%s %s %s %d\n",  i->bienso, i->time->ngay, i->time->gio, i->time->loai);
    }
    
}
Node *makeNode(char *bienso, char *day, char *time){
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->bienso, bienso);
    strcpy(node->day, day);
    strcpy(node->time, time);
    node->left = node->right = NULL;
    return node;
}

Node * inserTree(Node * r, char *bienso, char *day, char *time){
    if(r == NULL) return makeNode(bienso, day,time);
    int tmp = strcmp(r->bienso, bienso);
    if(tmp == 0) return r;
    if(tmp < 0){
        r->right = inserTree(r->right, bienso, day, time);
        return r;
    }else{
        r->left = inserTree(r->left, bienso, day, time);
        return r;
    }
}

Gui * checkin(Xe *r){
  
    Gui * i = r->time;

    //for (i = r->time ; i->next != NULL ; i = i->next);

    while(i->next != NULL){
        i = i->next;
        }

    if(i->loai == 1) {
        return i;
    } else {
        return NULL;}
}

void addTree(){

    for (Xe * i = root1; i != NULL ; i = i->next)
    {   
        Gui *tmp = checkin(i);
        if(tmp != NULL) {root2 = inserTree(root2, i->bienso, tmp->ngay, tmp->gio);}
        
    }
}

Node *findNode(Node * r,char * bienso){
    if(r == NULL) return NULL;
    int tmp = strcmp(r->bienso, bienso);
    if(tmp == 0) return r;
    if(tmp < 0) return findNode(r->right, bienso);
    else return findNode(r->left, bienso);
}
void inOrder(Node * r){
    if(r == NULL) return;
    inOrder(r->left);
    printf("%s %s %s\n", r->bienso, r->day, r->time);
    inOrder(r->right);
} //In tat ca cac node
int main()
{
    loadFile();
    addTree();
    inOrder(root2);
    printf("**********\n");
    
}