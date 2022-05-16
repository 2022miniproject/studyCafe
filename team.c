#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[255]; //이름
    char phone_num[15]; //휴대폰 번호
    int seat_num; // 자리선택 (1~100)
    int seat_hour; // 시간 선택 (3시간, 6시간, 9시간, 12시간, 24시간)
    int price; // 가격 (자동으로 저장됨)
} Seat;

struct food_struct
{
	int count;
	int price;
	int number;
	char menu[100];
	char list[20];
};


int loadData(Seat *s); // 0.기존 데이터 불러오기
void readReserv(Seat s); //1-1. 조회( 예약상태, 사용중 유뮤, 음식 주문 유무) (전체 등록된 제품 리스트 출력 R-2)
void listReserv(Seat *s, int count); //1-2. 조회(메뉴 리스트 출력 R-1)
int addReserv(Seat *s); //2.예약 -> 이미 사용중이거나 예약했으면 “이미 예약 되었습니다.” or “이미 사용중입니다.” 표시 (제품을 추가하는 함수 C)
int deleteReserv(Seat *s); //3.예약 취소 (제품을 삭제하는 함수 D)
int updateReserv(Seat *s); //4. 예약변경 (제품을 수정하는 함수 U)
//int plusTime(); //5.시간 추가 -> 사용중이 아니면 “먼저 사용 예약을 해주시길 바랍니다.” 표시 => 없어도될듯?

void saveData(Seat *s, int count); //6.파일저장
void searchReserv(Seat *s, int count); //7. 예약자 검색(예약자명) (주문한 음식 유뮤 확인, 있다면 주문 현황까지 표시)

int selectDataNo(Seat *s, int count);

void Clear(void);
void menu();
void showlist(struct food_struct *p[], int count); // 5-1. 주문한 음식 보여주기
int plusfood(struct food_struct *p[], int count); // 5-2. 음식 주문하기
int deletefood(struct food_struct *p[], int count); // 5-3. 주문한 음식 삭제하기
void order(struct food_struct *p[], int count); // 5-4. 음식 주문 넣기 (음식 주문 확정하기)

int selectMenu(){ // 메뉴판
    int menu;
    printf("\n===========[ STUDY CAFE ]===========\n");
    printf("1. 조회\n");
    printf("2. 예약\n");
    printf("3. 예약 취소\n");
    printf("4. 예약 변경\n");
    printf("5. 음식 주문\n");
    printf("6. 리스트 저장\n");
    printf("7. 예약자 검색\n");
    printf("0. 종료\n\n");
    printf("=> 원하시는 메뉴를 고르세요! ");
    scanf("%d", &menu);
    return menu;
}

int main(void){
    int select = 0;
    struct food_struct *Order[20];
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
                printf("-->취소되었음\n");
                continue;
            }
            int delete_ok;
            printf("정말로 삭제하시겠습니까?(삭제 :1)");
            scanf("%d", &delete_ok);
            if(delete_ok == 1){
                if(deleteReserv(&slist[no-1])) count--;
            }
        }
        else if (menu == 4){
            int no = selectDataNo(slist, index);
            if(no == 0){
                printf("-->취소되었음!\n");
                continue;
            }
            updateReserv(&slist[no-1]);

        }
        
        else if (menu == 5){
            int num = 0;
            while(1){
                printf("메뉴를 선택하세요 : ");
                scanf("%d", &select);
                Clear();
                if(select == 1) {
                    showlist(Order, select);
                }
                else if(select == 2) {
                    num = plusfood(Order, select);
                }
                else if(select == 3) {
                    num = deletefood(Order, select);
                }
                else if(select == 4) {
                    order(Order, select);
                }
                else if(select == 0) menu = selectMenu();
            }
            
            free(*Order);
        }
        
        else if(menu == 6){
            saveData(slist, index);
        }
        else if(menu == 7){
            searchReserv(slist, index);
        }
    }
    printf("종료됨!\n");
    return 0;
}


int addReserv(Seat *s){
    getchar();
    printf("이름을 입력해주세요:");
    fgets(s->name,255,stdin);
    s->name[strlen(s->name)-1] = '\0';
    
    //getchar();
    printf("전화번호를 입력해주세요(형식: 010-****-****):");
    scanf("%s", s->phone_num);

    printf("자리를 선택해주세요(1~100 중에 선택):");
    scanf("%d", &s->seat_num);

    printf("시간을 선택해주세요(시간당 천원):");
    scanf("%d", &s->seat_hour);

    //가격저장
    s->price = 1000*s->seat_hour;
    

    return 1;
}

void listReserv(Seat *s, int count){
    printf("======================\n");
    for(int i=0; i<count; i++){
        if(s[i].price == -1){continue;} 
        printf("      <%2d번>\n", i+1);
        readReserv(s[i]);

    }
}
void readReserv(Seat s){
    //int count = 1;
    printf("이름:%s\n휴대폰번호:%s\n자리번호:%d\n시간:%d\n가격:%d\n"
    ,s.name, s.phone_num, s.seat_num, s.seat_hour, s.price);
}
int selectDataNo(Seat *s, int count){
    int no;
    listReserv(s, count);
    printf("\n번호는 (취소 :0)?");
    scanf("%d", &no);
    return no;
}
int updateReserv(Seat *s){
    getchar();
    printf("새 이름을 입력해주세요:");
    fgets(s->name,255,stdin);
    s->name[strlen(s->name)-1] = '\0';
    
    printf("새 전화번호를 입력해주세요(형식: 010-****-****):");
    scanf("%s", s->phone_num);

    printf("새 자리를 선택해주세요(1~100 중에 선택):");
    scanf("%d", &s->seat_num);

    printf("새 시간을 선택해주세요(3,6,9,12,24 중 선택):");
    scanf("%d", &s->seat_hour);

    //가격저장
    s->price = 1000*s->seat_hour;

    return 1;
}
int deleteReserv(Seat *s){
    s->price = -1;
    printf("--> 삭제됨!\n");
    return 1;
}
void saveData(Seat *s, int count)
{
    FILE *fp;
    fp = fopen("Reserv.txt", "wt");

    for(int i =0; i < count; i++){
        if(s[i].price == -1) continue;


        fprintf(fp, "%s %d %d %d %s\n", s[i].phone_num, s[i].seat_num, s[i].seat_hour, s[i].price, s[i].name);
    
    }
    fclose(fp);
    printf("=> 저장됨!\n");
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
        printf("\n=> 로딩 성공!\n");
    }else{
        printf("\n=> 파일 없음...\n");
    }

    return i;
}
void searchReserv(Seat *s, int count){
    int scnt = 0;
    char search[20];
    
    getchar();
    printf("검색할 이름?:");
    fgets(search,255,stdin);
    search[strlen(search)-1] = '\0';

    printf("\n*****************\n");
    for(int i=0; i < count; i++){
        if(s[i].price == -1) continue;
        if(strstr(s[i].name, search)){
            printf("      <%2d번>\n", i+1);
            readReserv(s[i]);
            scnt++;
        }
    }
    if(scnt == 0) printf("=> 검색된 데이터 없음!");
    printf("\n");
}

void Clear(void)
{
	while (getchar() != '\n')
		;
}

void menu()
{
	printf("** 메뉴 **\n");
	printf("라면 2500원\n");
	printf("컵밥 3500원\n");
	printf("아이스 아메리카노 2000원\n");
	printf("자몽에이드 2500원\n");
	printf("콜라 1500원\n");
}

void showlist(struct food_struct *p[], int count)
{ // 5-1
	printf("==========================\n");
	printf("메뉴            가격  수량\n");
	printf("==========================\n");
	for (int i = 0; i < count; i++)
	{
		printf("%s                %d    %d\n", p[i]->menu, p[i]->price, p[i]->number);
	}
}

int plusfood(struct food_struct *p[], int count)
{ // 5-2
	menu();
	p[count] = (struct food_struct *)malloc(sizeof(struct food_struct));
	printf("메뉴명 : ");
	scanf("%[^\n]", p[count]->menu);
	Clear();
	printf("가격 : ");
	scanf("%d", &p[count]->price);
	printf("수량 : ");
	scanf("%d", &p[count]->number);
	printf("=> 음식이 주문되었습니다.\n");

	return count + 1;
}

int deletefood(struct food_struct *p[], int count)
{ // 5-3
	int index;
	printf("취소할 번호 (0 : 취소) : ");
	scanf("%d", &index);
	if (index == 0)
		return count - 1;
	else
	{
		for (int i = index - 1; i < count; i++)
		{
			p[i] = p[i + 1];
		}
		printf("=> 취소되었습니다\n");
	}

	return count - 1;
}

void order(struct food_struct *p[], int count)
{ // 5-4
	for (int i = 0; i < count; i++)
	{
		p[i]->menu[0] = '\0';
		p[i]->price = -1;
		p[i]->number = -1;
	}

	FILE *fp = fopen("studyCafe.txt", "w");

	for (int i = 0; i < count; i++)
	{
		fprintf(fp, "%s\n%d\n%d\n", p[i]->menu, p[i]->price, p[i]->number);
	}
	fclose(fp);
	printf("=> 주문이 저장 되었습니다.\n");
}

