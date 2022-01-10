#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SBookInfo
{
	char name[256]; // å�̸�
	int number; // å��ȣ
	int price; // ����
	int quantity; // ����
}SBookInfo;

void LoadBookInfo(SBookInfo booklist[100], int* index) // ���Ͽ��� å�� �о�´�.
{
	FILE *fp = NULL;
	fopen_s(&fp, "book.txt", "r");

	char name[256];
	char number[256];
	char price[256];
	char quantity[256];

	// ���� ������ �о�´�.
	while(fscanf(fp, "%s %s %s %s", name, sizeof(name), number, sizeof(number), price, sizeof(price), quantity, sizeof(quantity)) != EOF)
	{
		// �о�� ������ ����ü�� ����
		strcpy(booklist[*index].name, name); // �̸� ����
		booklist[*index].number = atoi(number); // ��ȣ �Է�
		booklist[*index].price = atoi(price); //  ���� �Է�
		booklist[*index].quantity = atoi(quantity); // ���� �Է�

		*index = *index + 1;
	}

	fclose(fp);
}

void SaveBookInfo(SBookInfo booklist[100], int size) // å ������ ���Ͽ� �����Ѵ�.
{
	FILE *fp = NULL;
	fopen_s(&fp, "book.txt", "w");

	// å������ ��� ���Ͽ� �����Ѵ�
	// ���Ͽ� ������ �̹� �־ ����� �Ѵ�.
	for(int i = 0; i < size; i++)
	{
		fprintf(fp, "%s %d %d %d\n", booklist[i].name, booklist[i].number, booklist[i].price, booklist[i].quantity);
	}

	fclose(fp);
}

int mainmenu() // ���θ޴�
{
	int input = 0;

	while(1)
	{
		printf("1. å ���� �߰�\n");
		printf("2. å ���� ����\n");
		printf("3. å ���� �˻�\n");
		printf("4. å �Ǹ�\n");
		printf("5. å ��� ǥ��\n");
		printf("6. ���α׷� ����\n");
		printf(" >> ");
		scanf("%d", &input);

		if(input >= 1 && input <= 6) // 1~6���� ���ڸ� �Է°����ϴ�
		{
			break;
		}
		else
		{
			printf("1~6 ���� ���ڸ� �Է��ϼ���\n");
		}
	}

	return input;
}

void AddBook(SBookInfo booklist[100], int* index) // å�� �߰��Ѵ�.
{
	SBookInfo book;

	// �Է�
	printf("å �̸� : ");
	scanf("%s", &book.name);
	printf("å ��ȣ : ");
	scanf("%d", &book.number);
	printf("å ���� : ");
	scanf("%d", &book.price);
	printf("å ���� : ");
	scanf("%d", &book.quantity);

	booklist[*index] = book; // ����

	*index = *index + 1;

	SaveBookInfo(booklist, *index); // ���Ͽ� ����
}

void ModifyBook(SBookInfo booklist[100], int size) // å ���� ����
{
	char name[256];

	// ������ å �̸� ���� �˻�
	printf("������ å �̸� : ");
	scanf("%s", &name);

	// ������ �̸��� �����ϴ��� �˻�
	int modifyIndex = -1;
	for(int i = 0; i < size; i++)
	{
		if(strcmp(name, booklist[i].name) == 0)
		{
			modifyIndex = i;
			break;
		}
	}

	if(modifyIndex == -1) // �������� ������
	{
		printf("�Է��Ͻ� å �̸��� �������� �ʽ��ϴ�.\n");
	}
	else
	{
		SBookInfo book;

		// å ������ �����Ѵ�.
		printf("å �̸�(����:%s) : ", booklist[modifyIndex].name);
		scanf("%s", &book.name);
		printf("å ��ȣ(����:%d) : ", booklist[modifyIndex].number);
		scanf("%d", &book.number);
		printf("å ����(����:%d) : ", booklist[modifyIndex].price);
		scanf("%d", &book.price);
		printf("å ����(����:%d) : ", booklist[modifyIndex].quantity);
		scanf("%d", &book.quantity);

		booklist[modifyIndex] = book;

		SaveBookInfo(booklist, size); // ���Ϸ� ����
	}
}

void SearchBook(SBookInfo booklist[100], int size)
{
	char name[256];

	// å �̸� ���� �˻�
	printf("�˻��� å �̸� : ");
	scanf("%s", &name);

	// �˻��� �̸��� �����ϴ��� �˻�
	int modifyIndex = -1;
	for(int i = 0; i < size; i++)
	{
		if(strcmp(name, booklist[i].name) == 0)
		{
			modifyIndex = i;
			break;
		}
	}

	if(modifyIndex == -1) // �������� ������
	{
		printf("�Է��Ͻ� å �̸��� �������� �ʽ��ϴ�.\n");
	}
	else // ã���� ���
	{
		printf("�̸� : %s, ��ȣ : %d, ���� : %d, ���� : %d\n", booklist[modifyIndex].name, booklist[modifyIndex].number, booklist[modifyIndex].price, booklist[modifyIndex].quantity);
	}
}

void SellBook(SBookInfo booklist[100], int size)
{
	char name[256];

	// å �̸� ���� �˻�
	printf("�Ǹ��� å �̸� : ");
	scanf("%s", &name);

	// �Ǹ��� �̸��� �����ϴ��� �˻�
	int modifyIndex = -1;
	for(int i = 0; i < size; i++)
	{
		if(strcmp(name, booklist[i].name) == 0)
		{
			modifyIndex = i;
			break;
		}
	}

	if(modifyIndex == -1) // �������� ������
	{
		printf("�Է��Ͻ� å �̸��� �������� �ʽ��ϴ�.\n");
	}
	else // ã����
	{
		// � �Ȱ��� �Է�
		int num = 0;
		printf("����� �Ǹ��Ͻ� �ǰ���?(���� ����: %d��) ", booklist[modifyIndex].quantity);
		scanf("%d", &num);

		// �Է��� ������ ���� �������� ���� ���
		if(num < booklist[modifyIndex].quantity)
		{
			booklist[modifyIndex].quantity -= num; // ������ ���ش�.

			printf("�Ǹ��Ͽ����ϴ�.\n");
			printf("���� ������ %d �� �Դϴ�.\n", booklist[modifyIndex].quantity);
		}
		else // �����޽���
		{
			printf("�Է��Ͻ� ������ ���� �������� Ů�ϴ�.\n");
		}
	}
}

void ShowAllInfo(SBookInfo booklist[100], int size) // ��� å ������ ���
{
	for(int i = 0; i < size; i++)
	{
		printf("�̸� : %s, ��ȣ : %d, ���� : %d, ���� : %d\n", booklist[i].name, booklist[i].number, booklist[i].price, booklist[i].quantity);
	}
}
