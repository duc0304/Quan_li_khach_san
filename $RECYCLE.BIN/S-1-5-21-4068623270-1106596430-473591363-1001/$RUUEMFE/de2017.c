#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Team{
    int id;
    char name[30];
    struct Team *next;
}Team;
Team * root;
Team *makeTeam(int id, char *name){
    Team *team = (Team *)malloc(sizeof(Team));
    team->id = id;
    strcpy(team->name, name);
    team->next = NULL;
    return team;
}
Team *inserLast(Team *f,int id, char * name){
    if(f == NULL) return makeTeam(id, name);
     else f->next = inserLast(f->next,id, name);
     return f;
}
void load(FILE *fin){
    root = NULL;
    while (!feof(fin))
    {   int id; char name[30];
        fscanf(fin, "%d\t", &id); 
        fgets(name,30,fin); 
        if (name[strlen(name) - 1] == '\n') name[strlen(name) - 1] = '\0';
        root = inserLast(root, id, name);
    }
}
void printList()
{
    printf("%-10s%-20s\n","ID","Name");
    for ( Team * i = root; i != NULL ; i = i->next)
    {
        printf("%-10d%-20s\n",i->id,i->name);
    }
}
void search(){
    int id;
    printf("Nhap id ban muon tim: ");
    scanf("%d",&id);
    printf("%-10s%-20s\n","ID","Name");
    for ( Team * i = root; i != NULL ; i = i->next)
    {
        if(i->id==id) printf("%-10d%-20s\n",i->id,i->name);
    }}
int main()
{
    char filename[20] = "bongda.txt";
    FILE *fin = fopen(filename, "r");
    load(fin);
    //printList();
    search();
}
