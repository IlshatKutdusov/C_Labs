#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
// ��� ������� � ���������� errno
#include <errno.h>
// ������ ������� ������ ����� (INT_MAX, CHAR_MAX � �.�.)
#include <limits.h>


long argtol(char *arg) // ������� ��� �������������� ������ � long
{
	long rez; // ��� ����� ��������� ��������� ��������������
	char *t = NULL; // ��� ����� �� ����� ������, ������� �� ��������������� (�.�. ���� ������������ ������ "123abc", ��� ����� "abc")
	rez = strtol(arg, &t, 10); // ����������� arg � ����� � ���������� 10, ���� ����� �� ����� ������� � long, �� errno = ERANGE
	if (errno == ERANGE || t[0] != '\0') { // ���� ����� �� ������ ��� ���� �� ��������������� �����
		printf("������ �����!\n"); // ������ ������
		exit(-1); // ��������� ���������
	}
	else
		return rez; // ����� ���������� ��������� ��������������
}

void proc(long ch, char* pos)
{
	int rez = -1; //������ ��������� �������� ����������
	int len = strlen(pos); // ����� ������ pos (������� ���������)

	// ������ (������� ������������������) � ������ �����, ������������ ��������
	int *b = (int*)malloc(sizeof(int)*len);
	for (int i = len - 1; i >= 0; i--) 
	{
		if (pos[i] == '0')//��������� ������ ������������ 0, ������������� 1 � ��
			b[len - 1 - i] = 0;
		else if (pos[i] == '1')
			b[len - 1 - i] = 1;
		else {
			printf("������ �����!\n"); // ������ ������
			exit(-1); // ��������� ���������
		}
	}

	// ������ ��� ����� � ���������� ���
	int ch_b;
	char type = 0;
	if (ch >= CHAR_MIN && ch <= CHAR_MAX) // char
		ch_b = sizeof(char) * 8;
	else if (ch >= 0 && ch <= UINT_MAX) // unsigned int
		ch_b = sizeof(int) * 8;
	else if (ch >= INT_MIN && ch <= INT_MAX) // int
		ch_b = sizeof(int) * 8;
	else // long
		ch_b = sizeof(long) * 8;

	// ���� ������ ������������������ ���
	for (int i = 0; i < ch_b - strlen(pos); i++) 
	{
		long temp = ch >> i; // ������ �����
		int br = 0; 
		for (int j = 0; j < strlen(pos); j++) 
		{ // � ����� �������� ��� ������� �� ������������������
			if (b[j] != ((temp >> j) & 1)) 
			{ // ���������� ��� �� ������������������ � �����
				br = 1; break; // ��������, ��� ����� �� ����� � ������� break
			}
		}
		if (!br) 
		{ // ���� ������� ��� �������
			rez = i; break; // ����������� ���������
		}
	}
	if (rez == -1) // ���� �� �� ������ ���������
		printf("���������: �� �������!");
	else // ���� ������
		printf("���������: %d\n", ch_b - rez - strlen(pos) + 1);
}

int main(int argc, char* argv[]) 
{
	setlocale(LC_ALL, "rus");
	long ch;
	if (argc == 3) // ���������, ��� ��������� ���������� ����� 3 (�.�. ������ �������� ��� ���� ��� �������� ��������� � ��� ��� ������ ���, ������� ������ ������������)
	{
		ch = argtol(argv[1]); // ����������� ������ � long
		proc(ch, argv[2]); // ��������� ����������
	} else { // ���� ��������� ���������� �� ����� 3
		printf("������ �����!\n"); // ������ ������
		exit(-1); // ��������� ���������
	}
	return 0;
}

// ����� ���������� ������ ��������� exe ����
// ����� ��� ��������� ����� �������
// ��� �����:
// 1. �������� � �����, cd <����> (������: cd C:\Users\kurba\Documents\Visual/ Studio/ 2015\Projects\lab5)
// 2. ���������, .\file.exe <�����, � ������� ����> <������������������ ���> (������: .\lab5.exe 179 1011)