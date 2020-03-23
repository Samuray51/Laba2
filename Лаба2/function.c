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
	char *str = (char*)malloc(sizeof(char));
	for (i = 0; i < m - 1; i++)
	{
		for (j = m - 1; j > i; j--)
		{
			if (count[j - 1] > count[j])
			{
				n = count[j - 1];
				count[j - 1] = count[j];
				count[j] = n;
				str = (char*)realloc(str, count[j] * sizeof(char));
				strcpy_s(str, count[j], text[j - 1]);
				text[j - 1] = (char*)realloc(text[j - 1], count[j - 1] * sizeof(char));
				strcpy_s(text[j - 1], count[j - 1], text[j]);
				text[j] = (char*)realloc(text[j], count[j] * sizeof(char));
				strcpy_s(text[j], count[j], str);
			}
		}
	}
}