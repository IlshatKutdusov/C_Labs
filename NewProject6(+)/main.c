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
ring *act;

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

void add(ring *newring)
{
	if (first == NULL)
        {
            ring *new_ring;
            new_ring = (ring*)malloc(sizeof(ring));
            scanf("%*[^\r^\n]");
            printf("UserName: ");
            scanf("%*[\n]%[^\r^\n]", (*new_ring).name, 98);
            printf("Work: ");
            scanf("%*[\n]%[^\r^\n]", (*new_ring).work, 98);
            printf("Adrees: ");
            scanf("%*[\n]%[^\r^\n]", (*new_ring).adress, 98);
            (*new_ring).next = new_ring;
            act = new_ring;
            first = new_ring;
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
            act = temp;
        }
}

void print(ring *new_ring)
{
    if (act != NULL)
        {
            ring *p;
            p = new_ring;
            do {
                printf("# %s # %s # %s #\n", (*p).name, (*p).work, (*p).adress);
                p = (*p).next;
            } while (p != new_ring);
        } else {
            printf("List is empty!\n");
        }
        system("pause");
}

void _del(ring *newring)
{
    if (newring != first)
        {
            ring *temp;
            temp = newring;
            while ((*temp).next != newring)
            {
                temp = (*temp).next;
            }
            (*temp).next = (*newring).next;
            free(newring);
            act = temp;
        } else {
            free(act);
            act = NULL;
            first = NULL;
        }
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
		} while (t != first);
		free(new_ring);
		if (deleted == 1)
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
	if (act != NULL)
	{
		ring *tmp;
        tmp = act;
        while (act != first) {
            (*tmp).next = (*act).next;
            free(act);
            act = tmp;
            printf("next");
        }
        act = NULL;
        first = NULL;
        printf("Result: deleted!\n");
	} else {
        printf("List is empty!\n");
	}
	system("pause");
}

void save()
{
	if (act != NULL)
	{
		FILE *out;
		out = fopen("file.txt", "w");
		ring *p;
        p = act;
        do {
            fprintf(out, "# %s # %s # %s #\n", (*p).name, (*p).adress, (*p).work);
            p = (*p).next;
        } while (p != act);
		fclose(out);
        printf("List saved!\n");
        system("pause");
	}
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
	while (feof(inp) == 0)
	{
        if (first == NULL)
        {
            ring *n_ring;
            n_ring = (ring*)malloc(sizeof(ring));
            fscanf(inp, "# %s # %s # %s #\n", &(*n_ring).name, &(*n_ring).work, (*n_ring).adress);
            (*n_ring).next = n_ring;
            act = n_ring;
            first = n_ring;
        }
        else
        {
            ring *tp, *pt;
            tp = (ring*)malloc(sizeof(ring));
            pt = (*act).next;
            (*act).next = tp;
            fscanf(inp, "# %s # %s # %s #\n", &(*tp).name, &(*tp).work, (*tp).adress);
            (*tp).next = pt;
            act = tp;
        }
	}
	printf("List loaded!\n");
	fclose(inp);
	system("pause");
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
			add(act); break;
		case 2:
			print(act); break;
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
