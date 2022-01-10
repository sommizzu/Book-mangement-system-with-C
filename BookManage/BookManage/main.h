#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SBookInfo
{
	char name[256]; // 책이름
	int number; // 책번호
	int price; // 가격
	int quantity; // 수량
}SBookInfo;

void LoadBookInfo(SBookInfo booklist[100], int* index) // 파일에서 책을 읽어온다.
{
	FILE *fp = NULL;
	fopen_s(&fp, "book.txt", "r");

	char name[256];
	char number[256];
	char price[256];
	char quantity[256];

	// 파일 끝까지 읽어온다.
	while(fscanf(fp, "%s %s %s %s", name, sizeof(name), number, sizeof(number), price, sizeof(price), quantity, sizeof(quantity)) != EOF)
	{
		// 읽어온 정보를 구조체에 복사
		strcpy(booklist[*index].name, name); // 이름 복사
		booklist[*index].number = atoi(number); // 번호 입력
		booklist[*index].price = atoi(price); //  가격 입력
		booklist[*index].quantity = atoi(quantity); // 수량 입력

		*index = *index + 1;
	}

	fclose(fp);
}

void SaveBookInfo(SBookInfo booklist[100], int size) // 책 정보를 파일에 저장한다.
{
	FILE *fp = NULL;
	fopen_s(&fp, "book.txt", "w");

	// 책정보를 모두 파일에 저장한다
	// 파일에 내용이 이미 있어도 덮어쓰기 한다.
	for(int i = 0; i < size; i++)
	{
		fprintf(fp, "%s %d %d %d\n", booklist[i].name, booklist[i].number, booklist[i].price, booklist[i].quantity);
	}

	fclose(fp);
}

int mainmenu() // 메인메뉴
{
	int input = 0;

	while(1)
	{
		printf("1. 책 정보 추가\n");
		printf("2. 책 정보 수정\n");
		printf("3. 책 정보 검색\n");
		printf("4. 책 판매\n");
		printf("5. 책 모두 표시\n");
		printf("6. 프로그램 종료\n");
		printf(" >> ");
		scanf("%d", &input);

		if(input >= 1 && input <= 6) // 1~6사이 숫자만 입력가능하다
		{
			break;
		}
		else
		{
			printf("1~6 사이 숫자만 입력하세요\n");
		}
	}

	return input;
}

void AddBook(SBookInfo booklist[100], int* index) // 책을 추가한다.
{
	SBookInfo book;

	// 입력
	printf("책 이름 : ");
	scanf("%s", &book.name);
	printf("책 번호 : ");
	scanf("%d", &book.number);
	printf("책 가격 : ");
	scanf("%d", &book.price);
	printf("책 수량 : ");
	scanf("%d", &book.quantity);

	booklist[*index] = book; // 저장

	*index = *index + 1;

	SaveBookInfo(booklist, *index); // 파일에 저장
}

void ModifyBook(SBookInfo booklist[100], int size) // 책 정보 수정
{
	char name[256];

	// 수정할 책 이름 으로 검색
	printf("수정할 책 이름 : ");
	scanf("%s", &name);

	// 수정할 이름이 존재하는지 검사
	int modifyIndex = -1;
	for(int i = 0; i < size; i++)
	{
		if(strcmp(name, booklist[i].name) == 0)
		{
			modifyIndex = i;
			break;
		}
	}

	if(modifyIndex == -1) // 존재하지 않을때
	{
		printf("입력하신 책 이름은 존재하지 않습니다.\n");
	}
	else
	{
		SBookInfo book;

		// 책 정보를 수정한다.
		printf("책 이름(현재:%s) : ", booklist[modifyIndex].name);
		scanf("%s", &book.name);
		printf("책 번호(현재:%d) : ", booklist[modifyIndex].number);
		scanf("%d", &book.number);
		printf("책 가격(현재:%d) : ", booklist[modifyIndex].price);
		scanf("%d", &book.price);
		printf("책 수량(현재:%d) : ", booklist[modifyIndex].quantity);
		scanf("%d", &book.quantity);

		booklist[modifyIndex] = book;

		SaveBookInfo(booklist, size); // 파일로 저장
	}
}

void SearchBook(SBookInfo booklist[100], int size)
{
	char name[256];

	// 책 이름 으로 검색
	printf("검색할 책 이름 : ");
	scanf("%s", &name);

	// 검색할 이름이 존재하는지 검사
	int modifyIndex = -1;
	for(int i = 0; i < size; i++)
	{
		if(strcmp(name, booklist[i].name) == 0)
		{
			modifyIndex = i;
			break;
		}
	}

	if(modifyIndex == -1) // 존재하지 않을때
	{
		printf("입력하신 책 이름은 존재하지 않습니다.\n");
	}
	else // 찾으면 출력
	{
		printf("이름 : %s, 번호 : %d, 가격 : %d, 수량 : %d\n", booklist[modifyIndex].name, booklist[modifyIndex].number, booklist[modifyIndex].price, booklist[modifyIndex].quantity);
	}
}

void SellBook(SBookInfo booklist[100], int size)
{
	char name[256];

	// 책 이름 으로 검색
	printf("판매할 책 이름 : ");
	scanf("%s", &name);

	// 판매할 이름이 존재하는지 검사
	int modifyIndex = -1;
	for(int i = 0; i < size; i++)
	{
		if(strcmp(name, booklist[i].name) == 0)
		{
			modifyIndex = i;
			break;
		}
	}

	if(modifyIndex == -1) // 존재하지 않을때
	{
		printf("입력하신 책 이름은 존재하지 않습니다.\n");
	}
	else // 찾으면
	{
		// 몇개 팔건지 입력
		int num = 0;
		printf("몇권을 판매하실 건가요?(현재 수량: %d권) ", booklist[modifyIndex].quantity);
		scanf("%d", &num);

		// 입력한 수량이 기존 수량보다 작을 경우
		if(num < booklist[modifyIndex].quantity)
		{
			booklist[modifyIndex].quantity -= num; // 수량을 빼준다.

			printf("판매하였습니다.\n");
			printf("남은 수량은 %d 권 입니다.\n", booklist[modifyIndex].quantity);
		}
		else // 에러메시지
		{
			printf("입력하신 수량이 현재 수량보다 큽니다.\n");
		}
	}
}

void ShowAllInfo(SBookInfo booklist[100], int size) // 모든 책 정보를 출력
{
	for(int i = 0; i < size; i++)
	{
		printf("이름 : %s, 번호 : %d, 가격 : %d, 수량 : %d\n", booklist[i].name, booklist[i].number, booklist[i].price, booklist[i].quantity);
	}
}
