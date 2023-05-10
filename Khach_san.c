#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct Node {
    char name[8];
    int sl;
    int sophong;
    char maks[5];
    char day[20];
    int tre;

    struct Node *right;
    struct Node *left;
}Node;

Node *root;

Node *root1;


Node *makeNode(char *name, int sl, int sophong, char *maks, char *day, int tre){
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->sl = sl;
    node->sophong = sophong;
    strcpy(node->maks, maks);
    strcpy(node->day, day);
    node->tre = tre;

    node->right = node->left = NULL;
    return node;
}


Node *insertNode(Node *r,  char *name, int sl, int sophong, char *maks, char *day, int tre)
{
    if (r == NULL) return makeNode(name, sl,sophong, maks, day, tre);

    int tmp = strcmp(r->name, name);

    if (tmp == 0) {
        strcpy(r->name, name);
        r->sl = sl;
        r->sophong = sophong;
        strcpy(r->maks, maks);
        strcpy(r->day, day);
        r->tre = tre;
        return r;
        }

    if (tmp < 0)
    {
        r->right = insertNode(r->right, name, sl,sophong, maks, day, tre);
        return r;
    }
    else
    {
        r->left = insertNode(r->left, name, sl,sophong, maks, day, tre);
        return r;
    }
}

Node *inserLast(Node * r, char *name, int sl, int sophong, char *maks, char *day, int tre){
    if(r == NULL) return makeNode(name, sl, sophong, maks, day, tre);
    
    r->left = inserLast(r->left, name, sl, sophong, maks, day, tre );
    return r;
}

void loadLKD(){
    FILE *fin = fopen("booking_orders.txt", "r");
    if(fin == NULL) {
        printf("Load file khong thanh cong , vui long kiem tra lai \n");
        return;
    }

    printf("Load file thanh cong \n");
    root = NULL;
    int sl; fscanf(fin,"%d", &sl);
    for (int i = 0; i < sl; i++)
    {   
        char name[50];
    int sl;
    int sophong;
    char maks[5];
    char day[20];
    int tre;
        fscanf(fin,"%s %d %d %s %s %d", name, &sl, &sophong, maks, day, &tre);
        //printf("%s %d %d %s %s %d\n", name, sl, sophong, maks, day, tre);
        root1 = inserLast(root1, name, sl, sophong, maks, day, tre);
        root = insertNode(root, name, sl, sophong, maks, day, tre);
    }
    printf("So luong yeu cau la : %d ", sl);
    printf("\n");
}

void checkHople(){

    int cout = 0;
    for (Node * i = root1; i != NULL ;i = i->left )
    {
        if(i->sl <= i->tre) cout++;
    }
    printf("Co %d yeu cau khong hop le !", cout);
}
Node *findNode(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int tmp = strcmp(r->name, name);
    if (tmp == 0) return r;
    if (tmp < 0)
        return findNode(r->right, name);
    else
        return findNode(r->left, name);
}


Node *deleteNode(Node *r, char *name)
{
    // Trường hợp cơ bản: cây rỗng
    if (r == NULL)
        return r;

    // Tìm nút cần xóa trong cây
    int cmp = strcmp(name, r->name);
    if (cmp < 0)
        r->left = deleteNode(r->left, name);
    else if (cmp > 0)
        r->right = deleteNode(r->right, name);
    else
    {
        // Nếu nút có tối đa một con hoặc không có con
        if (r->left == NULL)
        {
            Node *temp = r->right;
            free(r);
            return temp;
        }
        else if (r->right == NULL)
        {
            Node *temp = r->left;
            free(r);
            return temp;
        }

        // Nếu nút có hai con: tìm nút lớn nhất ở cây con bên trái
        Node *temp = r->left;
        while (temp->right != NULL)
            temp = temp->right;

        // Thay thế nút cần xóa bằng nút lớn nhất bên trái
        r->sl = temp->sl;
        r->sophong = temp->sophong;
        r->tre = temp->tre;
        strcpy(r->day, temp->day);
        strcpy(r->maks, temp->maks);
        strcpy(r->name, temp->name);

        // Xóa nút lớn nhất bên trái
        r->left = deleteNode(r->left, temp->name);
    }
    return r;
}


void newFile(Node * r, FILE *fout){

    if(r == NULL) return;
    newFile(r->left, fout);
    fprintf(fout, "%s %d %d %s %s %d\n", r->name, r->sl, r->sophong, r->maks, r->day, r->tre);
    newFile(r->right, fout);
}
void freeTree(Node *r)
{
    if (r == NULL)
        return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}
void findTT(){
    char name[9]; printf("Nhap ma yeu cau : ");fflush(stdin); scanf("%s", name);

    Node *tmp = findNode(root, name);

    if(tmp == NULL ) {printf("Not found ");  return; }

     else {printf("%s %d %d %s %s %d ", tmp->name, tmp->sl,tmp->sophong, tmp->maks, tmp->day, tmp->tre);
     return;
     }


}





void update(){
    char name[8]; printf("Nhap ma phong ");
    scanf("%s", name); 
    Node *tmp = findNode(root, name);
    if(tmp == NULL) {
        printf("Not found "); return;
    }
    int sl; printf("Nhap so nguoi : "); scanf("%d", &sl);
    int tre; printf("Nhap so luong tre em : "); scanf("%d", &tre);
    if(sl <= tre) {
        printf("Invalid"); return;
    }
    char day[30]; printf("Nhap ngay : "); scanf("%s", day);
    root = insertNode(root, tmp->name, sl, tmp->sophong, tmp->maks, day, tre);
    printf("Update thanh cong ");
}

void huyYeucau(){
    char name[20]; printf("Nhap ma yeu cau : "); scanf("%s", name);
    Node *tmp = findNode(root, name);
    if(tmp == NULL){
        printf("Not Fonud ");
        return;
    }
    root = deleteNode(root, name);
    printf("Delete thanh cong ");
}
void freeNee(){
    Node * p = root1;
    while(p != NULL){
        Node *tmp = p->left;
        free(p);
        p = tmp;
    }
}


int main() {

    int exit = 1;
    while(exit){
        printf("\n===============Menu==================\n");
        printf("1. Doc du lieu tu file log. \n");
        printf("2. Kiem tra so luong yeu cau khong hop le. \n");
        printf("3. Tra cuu theo ma yeu cau\n");
        printf("4. Thay doi yeu cau\n");
        printf("5. Huy yeu cau\n");
        printf("6. Luu danh sach yeu cau ra file\n");
        printf("7.Thong ke khach san duoc ua thich nhat\n");
        printf("8. Ngay khong hop le\n");
        printf("9. Ngay khong hop le\n");
        printf("10. Exit\n");
        printf("=====================================\n");

        printf("lua chon cua ban la : "); int choice; fflush(stdin);
        scanf("%d", &choice);printf("\n");

        switch(choice){
            case 1:
                loadLKD();
                
                break;
            case 2:
                checkHople();
                break;
            case 3: 
                findTT();
                break;
            case 4:
                update();
                break;
            case 5:
                huyYeucau();
                break;
            case 6:
                FILE *fout = fopen("booking_output.txt", "w");
                newFile(root, fout);
                fclose(fout);
                break;
            case 7: 
            
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                printf("Exit ! ");
                freeTree(root);
                freeNee();
                exit = 0;
                break;
        }
    }
    return 0;
}

