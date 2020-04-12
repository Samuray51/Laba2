#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<windows.h>
#include<locale.h>
#include"function.h"
#include<errno.h>
int main(int argc, char *argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");
	errno_t err;
	int m, i = 0, j, n;
	char *filename, tmp;
	filename = (char*)malloc(sizeof(char));
	printf("������� 1, ����� ������ ��� � ����������.\n");
	printf("������� 2, ����� ����� ��� ����� �� �����.\n");
	printf("������� 3, ����� ����� ��� ����� ������ �� �����.\n");
	printf("������� 4, ����� ����� �������� �������� � cmd.\n");
	scanf_s("%d", &m);
	scanf_s("%c", &tmp, 1);
	if (m == 1)
	{
		printf("������� �������� �����:\n");
		while (1)
		{
			scanf_s("%c", &filename[i], 1);
			if (filename[i] == '\n')
			{
				break;
			}
			i++;
			filename = (char*)realloc(filename, (i + 1) * sizeof(char));
		}
		filename[i] = '\0';
		
		Job(filename);
		free(filename);
		
	}
	else if (m == 2)
	{
		FILE *NameFile;
		err = fopen_s(&NameFile, "Namefile.txt", "r");
		if (err == NULL)
		{
			while (!feof(NameFile))
			{
				fscanf_s(NameFile, "%c", &filename[i], 1);
				i++;
				filename = (char*)realloc(filename, (i + 1) * sizeof(char));
			}
			filename[i-1] = '\0';
			
			Job(filename);
			free(filename);
		}
		
		fclose(NameFile);
	}
	else if (m == 3)
	{
		FILE *NameFiles;
		err = fopen_s(&NameFiles, "Namefiles.txt", "r");
		if (err == NULL)
		{
			n = ROW(NameFiles);
			for (j = 0; j < n; j++)
			{
				i = 0;
				filename = (char*)realloc(filename, 1 * sizeof(char));
				while (!feof(NameFiles))
				{
					fscanf_s(NameFiles, "%c", &filename[i], 1);
					if (filename[i] == '\n')
					{
						i = i + 1;
						break;
					}
					i++;
					filename = (char*)realloc(filename, (i + 1) * sizeof(char));
				}
				filename[i - 1] = '\0';

				Job(filename);
				system("cls");
			}
			free(filename);
		}
		else if (err != NULL)
		{
			printf("����: Namefiles.txt\n��� ������: %d\n", err);
			perror("�������� ������");
			system("pause");
			exit(1);
		}
		fclose(NameFiles);
	}
	if (m == 4)
	{
		if (argc != 2)
		{
			printf("������. ������������ ���� ����������!\n");
			system("pause");
			exit(1);
		}
		Job(argv[1]);
	}
	else
	{
		printf("������������ ����.\n");
	}
	return 0;
}