#include "main.h"

int main()
{
	SBookInfo booklist[100];
	int index = 0;

	LoadBookInfo(booklist, &index); // 파일에서 읽어온다.

	while(1)
	{
		int input = mainmenu(); // 메뉴출력

		if(input == 1) // 책 추가
		{
			AddBook(booklist, &index);
		}
		else if(input == 2) // 책 수정
		{
			ModifyBook(booklist, index);
		}
		else if(input == 3) // 책 검색
		{
			SearchBook(booklist, index);
		}
		else if(input == 4) // 책 판매
		{
			SellBook(booklist, index);
		}
		else if(input == 5) // 책 모두 표시
		{
			ShowAllInfo(booklist, index);
		}
		else if(input == 6) // 프로그램 종료
		{
			break;
		}
	}

	return 0;
}
