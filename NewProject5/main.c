#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
// для доступа к переменной errno
#include <errno.h>
// хранит границы разных типов (INT_MAX, CHAR_MAX и т.д.)
#include <limits.h>

int i, j;

long argtol(char *arg) // функция для преобразования строки в long
{
	long rez; // тут будет храниться результат преобразований
	char *t = NULL; // тут будет та часть строки, которая не преобразовалась (т.е. если пользователь введет "123abc", тут будет "abc")
	rez = strtol(arg, &t, 10); // преобразуем arg в число с основанием 10, если число не будет влезать в long, то errno = ERANGE
	if (errno == ERANGE || t[0] != '\0') { // если число не влезло или есть не преобразованная часть
		printf("Ошибка ввода!\n"); // выдаем ошибку
		exit(-1); // закрываем программу
	}
	else
		return rez; // иначе возвращаем результат преобразований
}

void proc(long ch, int nbytes)
{
	int rez = -1; //задаем начальное значение результату

	// узнаем тип числа и количество бит
	int ch_b;
	char type = 0;
	if (ch >= CHAR_MIN && ch <= CHAR_MAX) // char
		ch_b = sizeof(char) * 8;
	else if (ch >= SHRT_MIN && ch <= SHRT_MAX) // short
		ch_b = sizeof(int) * 8;
	else if (ch >= INT_MIN && ch <= INT_MAX) // int
		ch_b = sizeof(int) * 8;
	else // long
		ch_b = sizeof(long) * 8;

	// ищем нужную последовательность бит
	for (i = 0; i < nbytes; i++)
	{
		long temp = ch >> i; // делаем сдвиг
		int br = 0;
		for (j = 0; j < nbytes; j++)
		{ // в цикле проверям все символы из последовательности
			if (b[j] != ((temp >> j) & 1))
			{ // сравниваем бит из последовательности и числа
				br = 1; break; // помечаем, что вышли из цикла с помощью break
			}
		}
		if (!br)
		{ // если найдены все символы
			rez = i; break; // присваиваем результат
		}
	}
	if (rez == -1) // если мы не меняли результат
		printf("результат: не найдено!");
	else // если меняли
		printf("результат: %d\n", ch_b - rez - strlen(pos) + 1);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	long ch;
	if (argc == 3) // проверяем, что количесто аргументов равно 3 (т.к. первый аргумент это путь где запущена программа и еще два нужные нам, которые вводит пользователь)
	{
		ch = argtol(argv[1]); // преобразуем строку в long
		proc(ch, argv[2]); // выполняем вычисления
	} else { // если количесто аргументов не равно 3
		printf("Ошибка ввода!\n"); // выдаем ошибку
		exit(-1); // завершаем программу
	}
	return 0;
}

// после компиляции должен появиться exe файл
// нужно его запустить через консоль
// для этого:
// 1. проходим в папку, cd <путь> (пример: cd C:\Users\kurba\Documents\Visual/ Studio/ 2015\Projects\lab5)
// 2. запускаем, .\file.exe <число, в котором ищем> <последовательность бит> (пример: .\lab5.exe 179 1011)
