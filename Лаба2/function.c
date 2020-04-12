#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>
#include<locale.h>
#include<errno.h>


//Эта функция считает колличество строк
int ROW(FILE *I)
{
	int m = 1;
	char tmp;
	while (!feof(I)) {
		if (fscanf_s(I, "%c", &tmp, 1) == 1)
		{
			if (tmp == 10)
			{
				m++;
			}
		}
		else
		{
			break;
		}
	}
	fseek(I, 0, SEEK_SET);
	return m;
}


//Эта функция считает кол-во символов в строке
void CountSymbol(FILE *b, int *count)
{
	int k = 0, i = 0;
	char symbol;
	while (!feof(b))
	{
		fscanf_s(b, "%c", &symbol, 1);
		if (symbol == '\n')
		{
			k = k + 1;
			count[i] = k;
			k = 0;
			i = i + 1;
			continue;
		}
		k++;
	}
	count[i] = k;
	fseek(b, 0, SEEK_SET);
}



//Эта функция считывает строки в массив
void ScanFile(FILE *b, char **text)
{
	int i = 0, j = 0;
	while (!feof(b))
	{
		fscanf_s(b, "%c", &text[i][j], 1);
		if (text[i][j] == '\n')
		{
			text[i][j] = '\0';
			j = 0;
			i = i + 1;
			continue;
		}
		j++;
	}
	text[i][j-1] = '\0';
}




//Эта функция сортирует строки по длине(пузырек)
void Sort(char **text, int *count, int m)
{
	int i = 0, n, j = 0;
	char *p;
	for (i = 0; i < m - 1; i++)
	{
		for (j = m - 1; j > i; j--)
		{
			if (count[j - 1] > count[j])
			{
				n = count[j - 1];
				count[j - 1] = count[j];
				count[j] = n;

				p = text[j - 1];
				text[j - 1] = text[j];
				text[j] = p;
			}
		}
	}
}



//Эта функция сортирует строки по длине(быстрая сортировка)
void quickSort(int *numbers, int left, int right, char **text)
{
	int pivot; // разрешающий элемент
	int l_hold = left; //левая граница
	int r_hold = right; // правая граница
	pivot = numbers[left];
	char *p;
	p = text[left];
	while (left < right) // пока границы не сомкнутся
	{
		while ((numbers[right] >= pivot) && (left < right))
		{
			right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
		}
		if (left != right) // если границы не сомкнулись
		{
			numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
			text[left] = text[right];
			left++; // сдвигаем левую границу вправо 
		}
		while ((numbers[left] <= pivot) && (left < right))
		{
			left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
		}
		if (left != right) // если границы не сомкнулись
		{
			numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
			text[right] = text[left];
			right--; // сдвигаем правую границу вправо 
		}
	}
	numbers[left] = pivot; // ставим разрешающий элемент на место
	text[left] = p;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
	{
		quickSort(numbers, left, pivot - 1, text);
	}
	if (right > pivot)
	{
		quickSort(numbers, pivot + 1, right, text);
	}
}



//Эта функция выполняет работу
void Job(char *filename)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");
	clock_t start, end;
	errno_t err;
	int i = 0, m, *count;
	char **text;
	FILE *b;
	err = fopen_s(&b, filename, "r");
	if (err == NULL)
	{
		m = ROW(b);
		count = (int*)malloc(m * sizeof(int));
		CountSymbol(b, count);
		text = (char**)malloc(m * sizeof(char*));
		for (i = 0; i < m; i++)
		{
			text[i] = (char*)malloc((count[i]) * sizeof(char));
		}
		ScanFile(b, text);
		start = clock();
		quickSort(count, 0, m - 1, text);
		end = clock();
		printf("Восстановленный текст:\n");
		for (i = 0; i < m; i++)
		{
			printf("%s\n", text[i]);
		}
		printf("Время восстановления текста: %f секунд\n", ((float)end - start) / (float)CLOCKS_PER_SEC);
		for (i = 0; i < m; i++)
		{
			free(text[i]);
		}
		free(text);
		free(count);
		fclose(b);
	}
	else if (err != NULL)
	{
		printf("Файл: %s\nКод ошибки: %d\n", filename, err);
		perror("Описание ошибки");
	}
	system("pause");
}