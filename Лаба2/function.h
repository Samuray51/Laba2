#ifndef _function_H_
#define  _function_H_
int ROW(FILE *I);
void CountSymbol(FILE *b, int *count);
void ScanFile(FILE *b, char **text);
void Sort(char **text, int *count, int m);
void quickSort(int *numbers, int left, int right, char **text);
void Job(char *filename);
#endif
