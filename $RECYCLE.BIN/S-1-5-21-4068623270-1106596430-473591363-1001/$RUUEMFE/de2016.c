#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct Phong{
    char maYeuCau[10];
    int nguoi;
    char soPhong[5];
    char maKS[5];
    char day[20];
    int child;
    struct Phong *next;
}Phong;

typedef struct Node {
    char maYeuCau[10];
    int nguoi;
    char soPhong[5];
    char maKS[5];
    char day[20];
    int child;
    struct Node *left;
    struct Node *right;
}Node;

     Phong *root; Node *root2;
Phong * makePhong(char *maYeuCau, int nguoi, char *soPhong, char *maKS, char *day, int child){
    Phong * phong = (Phong *)malloc(sizeof(Phong));
    strcpy(phong->maYeuCau, maYeuCau);
    strcpy(phong->soPhong, soPhong);
    strcpy(phong->maKS, maKS);
    strcpy(phong->day, day);
    phong->nguoi = nguoi;
    phong->child = child;
    phong->next = NULL;
    return phong;
}


Phong *inserPhong(Phong *r, char *maYeuCau, int nguoi, char *soPhong, char *maKS, char *day, int child){
    if(r == NULL) return makePhong(maYeuCau, nguoi, soPhong, maKS, day, child);

    r->next = inserPhong(r->next, maYeuCau, nguoi, soPhong, maKS, day, child);
    return r;
}



void loadFile(){
    int soluong;
    FILE *fin = fopen("booking_orders.txt", "r");
    root = NULL;
    fscanf(fin,"%d",soluong);
    printf("So luong yeu cau doc duoc: %d\n",soluong);
    while(!feof(fin)){

    char maYeuCau[10];
    int nguoi;
    char soPhong[5];
    char maKS[5];
    char day[20];
    int child;
        fscanf(fin, "%s %d %s %s %s %d", maYeuCau, &nguoi, soPhong, maKS, day, &child);
       // printf("%s %s %s %d\n",  bienso, ngay, gio, loai);
        root = inserPhong(root, maYeuCau, nguoi, soPhong, maKS, day, child);
    }

    fclose(fin);
}

void printNe(){
    for (Phong * i = root; i != NULL ; i = i->next)
    {
        printf("%s %d %s %s %s %d\n",  i->maYeuCau, i->nguoi, i->soPhong, i->maKS, i->day, i->child);
    }
    
}

void Khonghople(){
    int count=0;
    for (Phong * i = root; i != NULL ; i = i->next)
    {
        if(i->child >= i->nguoi)
        count++;
    }
    printf("So luong cac yeu cau khong hop le: %d\n",count);
    
}

Node *makeNode(char *maYeuCau, int nguoi, char *soPhong, char *maKS, char *day, int child){
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->maYeuCau, maYeuCau);
    strcpy(node->soPhong, soPhong);
    strcpy(node->maKS, maKS);
    strcpy(node->day, day);
    node->nguoi = nguoi;
    node->child = child;
    node->left = node->right = NULL;
    return node;
}

Node * inserTree(Node * r, char *maYeuCau, int nguoi, char *soPhong, char *maKS, char *day, int child){
    if(r == NULL) return makeNode(maYeuCau, nguoi, soPhong, maKS, day, child);
    int tmp = strcmp(r->maYeuCau, maYeuCau);
    if(tmp == 0) return r;
    if(tmp < 0){
        r->right = inserTree(r->right, maYeuCau, nguoi, soPhong, maKS, day, child);
        return r;
    }else{
        r->left = inserTree(r->left, maYeuCau, nguoi, soPhong, maKS, day, child);
        return r;
    }
}



void addTree(){

    for (Phong * i = root; i != NULL ; i = i->next)
    {   
        root2 = inserTree(root2, i->maYeuCau, i->nguoi, i->soPhong, i->maKS, i->day, i->child);}
    }


Node *findNode(Node * r,char * maYeuCau){
    if(r == NULL) return NULL;
    int tmp = strcmp(r->maYeuCau, maYeuCau);
    if(tmp == 0) return r;
    if(tmp < 0) return findNode(r->right, maYeuCau);
    else return findNode(r->left, maYeuCau);
}
void timkiem()
{
    char maYeuCau[20]; printf("Nhap ma yeu cau can tim : ");fflush(stdin); scanf("%s", maYeuCau);
    Node * tmp = findNode(root2, maYeuCau);
    if(tmp != NULL) {
        printf("Thong tin cua phong: \n");
        printf("%s %d %s %s %s %d\n",  tmp->maYeuCau, tmp->nguoi, tmp->soPhong, tmp->maKS, tmp->day, tmp->child);
        return;
    }
    else printf("Not found");
}

int main()
{
    loadFile();
    printNe();
    Khonghople();
}