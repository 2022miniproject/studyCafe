#include <stdio.h>
#include <string.h>

typedef struct{
    char name[255]; //�̸�
    char phone_num[15]; //�޴��� ��ȣ
    int seat_num; // �ڸ����� (1~100)
    int seat_hour; // �ð� ���� (3�ð�, 6�ð�, 9�ð�, 12�ð�, 24�ð�)
    int price; // ���� (�ڵ����� �����)
} Seat;


int loadData(Seat *s); // 0.���� ������ �ҷ�����
void readReserv(Seat s); //1-1. ��ȸ( �������, ����� ����, ���� �ֹ� ����) (��ü ��ϵ� ��ǰ ����Ʈ ��� R-2)
void listReserv(Seat *s, int count); //1-2. ��ȸ(�޴� ����Ʈ ��� R-1)
int addReserv(Seat *s); //2.���� -> �̹� ������̰ų� ���������� ���̹� ���� �Ǿ����ϴ�.�� or ���̹� ������Դϴ�.�� ǥ�� (��ǰ�� �߰��ϴ� �Լ� C)
int deleteReserv(Seat *s); //3.���� ��� (��ǰ�� �����ϴ� �Լ� D)
int updateReserv(Seat *s); //4. ���ຯ�� (��ǰ�� �����ϴ� �Լ� U)
//int plusTime(); //5.�ð� �߰� -> ������� �ƴϸ� ������ ��� ������ ���ֽñ� �ٶ��ϴ�.�� ǥ�� => ����ɵ�?

void saveData(Seat *s, int count); //7.��������
void searchReserv(Seat *s, int count); //8. ������ �˻�(�����ڸ�) (�ֹ��� ���� ���� Ȯ��, �ִٸ� �ֹ� ��Ȳ���� ǥ��)

int selectDataNo(Seat *s, int count);

int selectMenu(){ // �޴���
    int menu;
    printf("\n===========[ STUDY CAFE ]===========\n");
    printf("1. ��ȸ\n");
    printf("2. ����\n");
    printf("3. ���� ���\n");
    printf("4. ���� ����\n");
    printf("5. �ð� �߰�\n");
    printf("6. ���� �ֹ�\n");
    printf("7. ����Ʈ ����\n");
    printf("8. ������ �˻�\n");
    printf("0. ����\n\n");
    printf("=> ���Ͻô� �޴��� ������! ");
    scanf("%d", &menu);
    return menu;
}

int main(void){
    Seat slist[100];
    int index =0;
    int count = 0, menu;
    int result = 0;

    count = loadData(slist);
    index = count;
 
    while (1){
        menu = selectMenu();
        if (menu == 0) break;
        if (menu == 1 || menu == 3 ||menu == 4)
            if(count == 0) continue;
        if (menu == 1){
            if(count>0){
                listReserv(slist, index);
            }
        }
        else if (menu == 2){
            count += addReserv(&slist[index++]);
            }

        else if (menu == 3){
            int no = selectDataNo(slist, index);
            if(no == 0){
                printf("-->��ҵǾ���\n");
                continue;
            }
            int delete_ok;
            printf("������ �����Ͻðڽ��ϱ�?(���� :1)");
            scanf("%d", &delete_ok);
            if(delete_ok == 1){
                if(deleteReserv(&slist[no-1])) count--;
            }
        }
        else if (menu == 4){
            int no = selectDataNo(slist, index);
            if(no == 0){
                printf("-->��ҵǾ���!\n");
                continue;
            }
            updateReserv(&slist[no-1]);

            }
        
        else if(menu == 7){
            saveData(slist, index);
        }
        else if(menu == 8){
            searchReserv(slist, index);
        }
    }
    printf("�����!\n");
    return 0;
}


int addReserv(Seat *s){
    getchar();
    printf("�̸��� �Է����ּ���:");
    fgets(s->name,255,stdin);
    s->name[strlen(s->name)-1] = '\0';
    
    //getchar();
    printf("��ȭ��ȣ�� �Է����ּ���(����: 010-****-****):");
    scanf("%s", s->phone_num);

    printf("�ڸ��� �������ּ���(1~100 �߿� ����):");
    scanf("%d", &s->seat_num);

    printf("�ð��� �������ּ���(�ð��� õ��):");
    scanf("%d", &s->seat_hour);

    //��������
    s->price = 1000*s->seat_hour;
    

    return 1;
}

void listReserv(Seat *s, int count){
    printf("======================\n");
    for(int i=0; i<count; i++){
        if(s[i].price == -1){continue;} 
        printf("      <%2d��>\n", i+1);
        readReserv(s[i]);

    }
}
void readReserv(Seat s){
    //int count = 1;
    printf("�̸�:%s\n�޴�����ȣ:%s\n�ڸ���ȣ:%d\n�ð�:%d\n����:%d\n"
    ,s.name, s.phone_num, s.seat_num, s.seat_hour, s.price);
}
int selectDataNo(Seat *s, int count){
    int no;
    listReserv(s, count);
    printf("\n��ȣ�� (��� :0)?");
    scanf("%d", &no);
    return no;
}
int updateReserv(Seat *s){
    getchar();
    printf("�� �̸��� �Է����ּ���:");
    fgets(s->name,255,stdin);
    s->name[strlen(s->name)-1] = '\0';
    
    printf("�� ��ȭ��ȣ�� �Է����ּ���(����: 010-****-****):");
    scanf("%s", s->phone_num);

    printf("�� �ڸ��� �������ּ���(1~100 �߿� ����):");
    scanf("%d", &s->seat_num);

    printf("�� �ð��� �������ּ���(3,6,9,12,24 �� ����):");
    scanf("%d", &s->seat_hour);

    //�������� �������� �����

    return 1;
}
int deleteReserv(Seat *s){
    s->price = -1;
    printf("--> ������!\n");
    return 1;
}
void saveData(Seat *s, int count)
{
    FILE *fp;
    fp = fopen("Reserv.txt", "wt");

    for(int i =0; i < count; i++){
        if(s[i].price == -1) continue;

        //fprintf(fp,"%s\n", s[i].name);
        //fprintf(fp,"%d\n",s[i].phone_num);
        //fprintf(fp,"%d\n",s[i].seat_num);
        //fprintf(fp,"%d\n",s[i].seat_hour);
        //fprintf(fp,"%d\n",s[i].price);

        //�̸�:%s\n�޴�����ȣ:%d\n�ڸ���ȣ:%d\n�ð�:%d\n����:%d\n"
        fprintf(fp, "%s %d %d %d %s\n", s[i].phone_num, s[i].seat_num, s[i].seat_hour, s[i].price, s[i].name);
    
    }
    fclose(fp);
    printf("=> �����!\n");
}
int loadData(Seat *s){
    int count = 0, i = 0;
    FILE *fp;
    if (fp = fopen("Reserv.txt", "rt")){
        for(; i<100; i++){ 
            //if(feof(fp)) break;

            //fscanf(fp, "%s", &s[i].name);

            fscanf(fp, "%s", s[i].phone_num);
            //if(feof(fp)) break;

            fscanf(fp, "%d", &s[i].seat_num);
            //if(feof(fp)) break;

            fscanf(fp, "%d", &s[i].seat_hour);
            //if(feof(fp)) break;

            fscanf(fp, "%d", &s[i].price);
            if(feof(fp)) break;
            
            fgets(s[i].name,255, fp);
            s[i].name[strlen(s[i].name)-1] = '\0';
        }
        fclose(fp);
        printf("\n=> �ε� ����!\n");
    }else{
        printf("\n=> ���� ����...\n");
    }

    return i;
}
void searchReserv(Seat *s, int count){
    int scnt = 0;
    char search[20];
    
    getchar();
    printf("�˻��� �̸�?:");
    fgets(search,255,stdin);
    search[strlen(search)-1] = '\0';

    printf("\n*****************\n");
    for(int i=0; i < count; i++){
        if(s[i].price == -1) continue;
        if(strstr(s[i].name, search)){
            printf("      <%2d��>\n", i+1);
            readReserv(s[i]);
            scnt++;
        }
    }
    if(scnt == 0) printf("=> �˻��� ������ ����!");
    printf("\n");
}