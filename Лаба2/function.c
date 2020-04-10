#include<stdio.h>
#include<stdlib.h>
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


//��� ������� ��������� ������ � ������ � ������� ���-�� �������� � ���
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


//��� ������� ��������� ������ �� �����
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