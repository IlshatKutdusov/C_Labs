#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <Windows.h>
#include <limits.h>

int i;

typedef struct
{
	char name[99];
	char work[99];
	char adress[99];
	struct ring *next;
} ring;

ring *first = NULL;

int get_int()
{
	long long temp = (unsigned)INT_MIN - 1;
	scanf("%lli", &temp);
	while (temp < INT_MIN || temp > INT_MAX) {
		printf("Error! Again: ");
		scanf("%*[^\r^\n]");
		scanf("%lli", &temp);
	}
	return (int)temp;
}

void add()
{
	if (first == NULL)
        {
            first = newring;
            ring *newring;
            newring = (ring*)malloc(sizeof(ring));
            scanf("%*[^\r^\n]");
            printf("UserName: ");
            scanf("%*[\n]%[^\r^\n]", (*newring).name, 98);
            printf("Work: ");
            scanf("%*[\n]%[^\r^\n]", (*newring).work, 98);
            printf("Adrees: ");
            scanf("%*[\n]%[^\r^\n]", (*newring).adress, 98);
            (*newring).next = newring;
            return(newring);
        }
	else
        {
            ring *temp, *p;
            temp = (ring*)malloc(sizeof(ring));
            p = (*newring).next;
            (*newring).next = temp;
            scanf("%*[^\r^\n]");
            printf("UserName: ");
            scanf("%*[\n]%[^\r^\n]", (*temp).name, 98);
            printf("Work: ");
            scanf("%*[\n]%[^\r^\n]", (*temp).work, 98);
            printf("Adrees: ");
            scanf("%*[\n]%[^\r^\n]", (*temp).adress, 98);
            (*temp).next = p;
            return(temp);
        }
}

void print()
{
	ring *p;
	p = newring;
	do {
        printf("# %s # %s # %s #\n", (*p).name, (*p).work, (*p).adress);
        p = (*p).next;
	} while (p != newring);
	system("pause");
}

void _del(ring *member)
{
    ring *temp;
    temp = member;
    while ((*temp).next != member)
    {
        temp = (*temp).next;
    }
    (*temp).next = (*member).next;
    free(member);
    return(temp);
	system("pause");
}

void find()
{
	if (first != NULL)
	{
		ring *t = first, *new_ring;
		new_ring = (ring*)malloc(sizeof(ring));
		char *fields[] = { "UserName", "Work", "Adress" };
		printf("Write field: \n");
		for (i = 0; i < 3; i++)
			printf("%d. %s\n", i + 1, fields[i]);
		printf("Write number: ");
		int point = get_int();

		system("cls");
		switch (point) {
		case 1:
			printf("Write UserName: ");
			scanf("%*[\n]%[^\r^\n]", (*new_ring).name, 98);
			break;
		case 2:
			printf("Write Work: ");
			scanf("%*[\n]%[^\r^\n]", (*new_ring).work, 98);
			break;
		case 3:
			printf("Write Adress: ");
            scanf("%*[\n]%[^\r^\n]", (*new_ring).adress, 98);
			break;
		default:
			printf("\nError!\n"); system("pause"); return;
		}

		int deleted = 0;
		do {
			if ((point == 1 && (stricmp((*t).name, (*new_ring).name) == 0)) ||
				(point == 2 && (stricmp((*t).work, (*new_ring).work) == 0)) ||
				(point == 3 && (stricmp((*t).adress, (*new_ring).adress) == 0))) {
				_del(t);
				deleted = 1;
				break;
			}
			t = (*t).next;
		} while (t);
		free(new_ring);
		if (deleted)
			printf("Result: deleted!\n");
		else
			printf("Result: not deleted!\n");
	}
	else {
		printf("List is empty!\n");
	}
	system("pause");
}


void del_all()
{
	if (first)
	{
		ring *t = first;
		ring *next;
		do {
			next = (*t).next;
			free(t);
			t = next;
		} while (t);
		first = NULL;
	}
}

void save()
{
	if (first)
	{
		FILE *out;
		out = fopen("file.txt", "w");
		ring *t = first;
		do
		{
			fprintf(out, "%s # %s # %s\n", (*t).name, (*t).work, (*t).adress);
			t = (*t).next;
		} while (t);
		fclose(out);
	}
	else
		system("rm file.txt");
}

void load()
{
	del_all();
	FILE *inp;
	inp = fopen("file.txt", "r");
	if (inp == NULL)
	{
		printf("File not founded!\n");
		system("pause");
		return;
	}
	ring *new_ring;
	while (1)
	{
		new_ring = (ring*)malloc(sizeof(ring));
		if (fscanf(inp, "%[^\r^\n]\r # %[^\r^\n]\r # %[^\r^\n]\r\n", &(*new_ring).name, &(*new_ring).work, (*new_ring).adress) == -1) {
			free(new_ring);
			break;
		}
		(*new_ring).next = NULL;
		_add(new_ring);
	}
	fclose(inp);
}

int main()
{

	int point = 1;
	while (point != 0)
	{
		system("cls");
		char* items = {
			"1. Add\n"
			"2. Print\n"
			"3. Delete one\n"
			"4. Delete all\n"
			"5. Save\n"
			"6. Load\n"
			"0. Close\n"
		};
		printf("%s", items);
		printf("Number: ");
		point = get_int();
		system("cls");
		switch (point) {
		case 1:
			add(); break;
		case 2:
			print(); break;
		case 3:
			find(); break;
		case 4:
			del_all(); break;
		case 5:
			save(); break;
		case 6:
			load(); break;
		case 0:
			break;
		default:
			printf("\nError!\n"); system("pause");
		}
	}

	return 0;
}
