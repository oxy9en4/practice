#include <stdio.h>
#include <stdlib.h>

typedef struct book {
	int index;
	char name[30];
	char author[30];
	char publisher[20];
	int enab;
	struct book* pNext;
	struct book* pPrev;

}Book;

struct book gHead = {-1, ,,,, NULL, NULL};
void add(Book* newbook);
void search(Book* target);
void borrow();
void return();

void main()
{
	int todo;
	int whichone = 0;
	printf("0. �߰� / 1. �˻� / 2. �뿩 / 3. �ݳ�");
	scanf("%d", &todo);
	switch (todo)
	{
	case 0:
		Book* newbook = NULL;
		printf("������ �̸���?");
		scanf("%s", newbook->name);
		printf("������ �̸���?");
		scanf("%s", newbook->author);
		printf("���ǻ��� �̸���?");
		scanf("%s", newbook->publisher);
		add(newbook);
		break;
	case 1:
		printf("0. ���� �˻� / 1. ���� �˻� / 2. ���ǻ� �˻�");
		scanf("%d", whichone);
		switch (whichone)
		{
		case 0:
			printf("������ �Է��ϼ���.")
		}
	}
	
}


void add()
{

}