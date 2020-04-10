#include<stdio.h>
#include<stdlib.h>
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


//Эта функция считывает строки в массив и считает кол-во символов в них
void ScanFile(FILE *b, char **text, int *count)
{
	int i = 0, j = 0, k = 0;
	while (!feof(b))
	{
		fscanf_s(b, "%c", &text[i][j], 1);
		if (text[i][j] == '\n')
		{
			text[i][j] = '\0';
			j = j + 1;
			count[i] = j;
			j = 0;
			i = i + 1;
			continue;
		}
		j++;
		text[i] = (char*)realloc(text[i], (j + 1) * sizeof(char));
	}
	count[i] = j;
	text[i][j - 1] = '\0';
}


//Эта функция сортирует строки по длине
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
				text[j - 1]= text[j];
				text[j] = p;
			}
		}
	}
}




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