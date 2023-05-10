#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Team{
    char name[41];
    int gio;
    int phut;
    struct Team *next;
}Team;
Team * top;
Team *makeTeam(char *name, int gio, int phut){
    Team *team = (Team *)malloc(sizeof(Team));
    strcpy(team->name, name);
    team->gio = gio;
    team->phut = phut;
    team->next = NULL;
    return team;
}
Team *insert(char * name, int gio, int phut){
    Team *p=makeTeam(name,gio,phut);
    p->next = top;
    top=p;
    }
void load(){
    FILE *fin = fopen("log.txt", "r");
    top = NULL;
    while(!feof(fin))
    {   int gio; int phut; char name[30];
        fscanf(fin, "%s%d%d", name, &gio, &phut); 
        top = insert(name,gio,phut);
    }
}
void Timkiem1()
    {
        printf("Dia diem ban muon tim: ");
        fflush(stdin);
        char diadiem[41];
        scanf("%s",diadiem);
        int count=0;
        for ( Team * i = top; i != NULL ; i = i->next)
        {
            if(strcmp(i->name, diadiem) == 0)
            {
                
                if(count!=0) printf(",");
                count++;
                printf("%d:%d",i->gio,i->phut);

            }
        }
        printf("\n");
        if (count==0)
        printf("Ban chua toi dia diem do.\n");
    }
int hople(Team *r, int gio, int phut){
    if(r == NULL) return 0;
    if(gio>=r->gio&&phut>=r->phut) return 1;
    if(gio>r->gio&&phut<r->phut) return 1;
    else return 0;
}

void Timkiem2(){
    printf("Nhap thoi gian muon xem : ");int gio, phut;
    while(1){
        scanf("%d %d", &gio, &phut);
        if(gio >= 0 && gio < 24 && phut >= 0 && phut < 60) break;
        printf("Khong hop le ! Nhap lai : ");
    }
    int exit=0;
    for(Team *i = top; i != NULL; i = i->next){
        if(hople(i,gio, phut)) {
        printf("%s\n ", i->name);
        exit=1;
        }
        if (exit==1) break;
    }
    if(exit==0)
    printf("Khong tim thay lich su di chuyen\n ");
}

void print()
{
    printf("%-50s%-10s%-10s\n","Dia diem","Gio","Phut");
    FILE *fin = fopen("log.txt", "r");
    while(!feof(fin))
    {   int gio; int phut; char name[30];
        fscanf(fin, "%s%d%d", name, &gio, &phut); 
        printf("%-50s%-10d%-10d\n",name,gio,phut);
    }
}
void freeNee(){
    Team * p = top;
    while(p != NULL){
        Team *tmp = p->next;
        free(p);
        p = tmp;
    }
}
int main()
{
    int choice;
	int exit=0;
	while (exit==0)
	{
	printf("CHUONG TRINH TRUY VET COVID19\n");
	printf("1.Nhap file log lich su di chuyen\n");
    printf("2.In ra lich su di chuyen\n");
	printf("3.Tim kiem lich su theo dia diem\n");
	printf("4.Tim kiem lich su theo thoi gian\n");
	printf("5.Thoat\n");
	printf("Chon chuc nang di: ");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			printf("\n");
            load();
			break;
		case 2:
			printf("\n");
            print();
			break;
		case 3:
            printf("\n");
            Timkiem1(); 
			break;
		case 4:
            printf("\n");
            Timkiem2(); 
			break;
		case 5:
			exit=1;
            freeNee();
			break;
		}
	}
	return 0;
}