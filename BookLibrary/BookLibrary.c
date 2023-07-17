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
	printf("0. 추가 / 1. 검색 / 2. 대여 / 3. 반납");
	scanf("%d", &todo);
	switch (todo)
	{
	case 0:
		Book* newbook = NULL;
		printf("도서의 이름은?");
		scanf("%s", newbook->name);
		printf("저자의 이름은?");
		scanf("%s", newbook->author);
		printf("출판사의 이름은?");
		scanf("%s", newbook->publisher);
		add(newbook);
		break;
	case 1:
		printf("0. 제목 검색 / 1. 저자 검색 / 2. 출판사 검색");
		scanf("%d", whichone);
		switch (whichone)
		{
		case 0:
			printf("제목을 입력하세요.")
		}
	}
	
}


void add()
{

}