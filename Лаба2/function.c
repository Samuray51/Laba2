#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include<windows.h>
#include<locale.h>
#include<errno.h>


//��� ������� ������� ����������� �����
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


//��� ������� ������� ���-�� �������� � ������
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



//��� ������� ��������� ������ � ������
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




//��� ������� ��������� ������ �� �����(�������)
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



//��� ������� ��������� ������ �� �����(������� ����������)
void quickSort(int *numbers, int left, int right, char **text)
{
	int pivot; // ����������� �������
	int l_hold = left; //����� �������
	int r_hold = right; // ������ �������
	pivot = numbers[left];
	char *p;
	p = text[left];
	while (left < right) // ���� ������� �� ���������
	{
		while ((numbers[right] >= pivot) && (left < right))
		{
			right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
		}
		if (left != right) // ���� ������� �� ����������
		{
			numbers[left] = numbers[right]; // ���������� ������� [right] �� ����� ������������
			text[left] = text[right];
			left++; // �������� ����� ������� ������ 
		}
		while ((numbers[left] <= pivot) && (left < right))
		{
			left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
		}
		if (left != right) // ���� ������� �� ����������
		{
			numbers[right] = numbers[left]; // ���������� ������� [left] �� ����� [right]
			text[right] = text[left];
			right--; // �������� ������ ������� ������ 
		}
	}
	numbers[left] = pivot; // ������ ����������� ������� �� �����
	text[left] = p;
	pivot = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot) // ���������� �������� ���������� ��� ����� � ������ ����� �������
	{
		quickSort(numbers, left, pivot - 1, text);
	}
	if (right > pivot)
	{
		quickSort(numbers, pivot + 1, right, text);
	}
}



//��� ������� ��������� ������
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
		printf("��������������� �����:\n");
		for (i = 0; i < m; i++)
		{
			printf("%s\n", text[i]);
		}
		printf("����� �������������� ������: %f ������\n", ((float)end - start) / (float)CLOCKS_PER_SEC);
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
		printf("����: %s\n��� ������: %d\n", filename, err);
		perror("�������� ������");
	}
	system("pause");
}