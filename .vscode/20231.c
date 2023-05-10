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
    char maYeuCau[20]; printf("Nhap ma yeu cau can tim : "); fflush(stdin); scanf("%s", maYeuCau);
    Node * tmp = findNode(root2, maYeuCau);
    if(tmp != NULL) {
        printf("Thong tin cua phong: \n");
        printf("%s %d %s %s %s %d\n",  tmp->maYeuCau, tmp->nguoi, tmp->soPhong, tmp->maKS, tmp->day, tmp->child);
        return;
    }
    else printf("Not found");
}

void guiXe(){
    char bienso[20]; printf("Nhap bien so xe can gui : "); scanf("%s", bienso);
    Node * tmp = findNode(root2, bienso);
    if(tmp != NULL) {
        printf("Xe dang dc gui !");
        return;
    }
    time_t t = time(NULL);  char day[39]; char time[29];
    struct tm tm = *localtime(&t);
    sprintf(day,"%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday);
    sprintf(time,"%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
    root2 = inserTree(root2, bienso, day, time);
    root1 = inserXe(root1, bienso, day, time, 1);
    root = inserCe(root, bienso, day, time, 1);
    printf("Gui xe thanh cong \n");
}

Node* deleteNode(Node* r, char* bienso) {
    // Trường hợp cơ bản: cây rỗng
    if (r == NULL) return r;

    // Tìm nút cần xóa trong cây
    int cmp = strcmp(bienso, r->bienso);
    if (cmp < 0)
        r->left = deleteNode(r->left, bienso);
    else if (cmp > 0)
        r->right = deleteNode(r->right, bienso);
    else {
        // Nếu nút có tối đa một con hoặc không có con
        if (r->left == NULL) {
            Node* temp = r->right;
            free(r);
            return temp;
        }
        else if (r->right == NULL) {
            Node* temp = r->left;
            free(r);
            return temp;
        }

        // Nếu nút có hai con: tìm nút lớn nhất ở cây con bên trái
        Node* temp = r->left;
        while (temp->right != NULL)
            temp = temp->right;

        // Thay thế nút cần xóa bằng nút lớn nhất bên trái

        strcpy(r->day, temp->day);
        strcpy(r->time, temp->time);
        strcpy(r->bienso, temp->bienso);

        // Xóa nút lớn nhất bên trái
        r->left = deleteNode(r->left, temp->bienso);
    }
    return r;
}
void freeTree(Node *r)
{
    if(r==NULL)
    return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

void traXe(){
    char bienso[29]; printf("Nhap bien so lay ra ");
    scanf("%s", bienso);
    Node *tmp = findNode(root2, bienso);

    if(tmp == NULL) {
        printf("Xe khong gui trong bai ");
        return;
    }

    printf("%s %s %s ", tmp->bienso , tmp->day, tmp->time);
    root2 = deleteNode(root2, bienso);
    printf("Lay xe thanh cong !");

    time_t t = time(NULL);  char day[39]; char time[29];
    struct tm tm = *localtime(&t);
    sprintf(day,"%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1,tm.tm_mday);
    sprintf(time,"%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);

    root = inserCe(root, bienso, day, time, 0);
    root1 = inserXe(root1, bienso, day, time, 0);
    

}

void inOrder(Node * r){
    if(r == NULL) return;
    inOrder(r->left);
    printf("%s %s %s\n", r->bienso, r->day, r->time);
    inOrder(r->right);
}

void updateFile(){
    FILE *fout = fopen("change_log.txt", "w");
    for (Ce *i = root; i != NULL ; i = i->next )
    {
        fprintf(fout,"%s %s %s %d\n", i->ngay, i->gio, i->bienso, i->loai);
    }
    fclose(fout);
}

void newFile(Node * r, FILE *fout){

    if(r == NULL) return;
    newFile(r->left, fout);
    fprintf(fout, "%s %s %s\n", r->bienso, r->day, r->time);
    newFile(r->right, fout);
}

Xe *findXe(char *bienso){
    for (Xe* i = root1; i != NULL ;i = i->next )
    {
        if(strcmp(i->bienso, bienso) == 0) return i;
    }
    return NULL;
}



void lichsu(){
    char bienso[20]; printf("Nhap bien so muon ra ls : "); scanf("%s", bienso);

    int count = 0;

    for (Ce * i = root; i != NULL ;i = i->next )
    {   
        if(strcmp(i->bienso, bienso) == 0) {
            count++; break;
        }
    }
    if(count == 0) {
        printf("khong co lich sui gui xe nay ");
        return;
    }
    printf("Lich su gui cua xe la : \n");
    for (Ce * i = root; i != NULL ;i = i->next )
    {
        printf("%s %s %d\n", i->ngay, i->gio, i->loai);
    }
    
}
int main() {

    int exit = 1;
    while(exit){
        printf("\n===============Menu==================\n");
        printf("Chuong trinh quan li dat phong\n");
        printf("Vui long chon mot trong cac chuc nang sau\n\n");
        printf("1. Doc du lieu tu file log \n");
        printf("2. Kiem tra so luong yeu cau khong hop le \n");
        printf("3. Tra cuu theo ma yeu cau \n");
        printf("4. Thay doi yeu cau\n");
        printf("5. Huy yeu cau\n");
        printf("6. Luu danh sach yeu cau ra file \n");
        printf("7. \n");
        printf("8.  \n");
        printf("9. Exit\n");
        printf("=====================================\n");

        printf("lua chon cua ban la : "); int choice;
        scanf("%d", &choice);printf("\n");

        switch(choice){
            case 1:
                loadFile();
                addTree();
                break;
            case 2:
                xetrongNgay();
                break;
            case 3: 
                inOrder(root2);
                break;
            case 4:
                guiXe();
                break;
            case 5:
            traXe();
                break;
            case 6:
            updateFile();
                break;
            case 7: 
            FILE *fout = fopen("Xein.txt", "w");
            newFile(root2, fout);
            fclose(fout);

                break;
            case 8:
            lichsu();
            
                break;
            case 9:
                printf("Exiting..................");

                exit = 0;
                break;
        }
    }
    return 0;
}