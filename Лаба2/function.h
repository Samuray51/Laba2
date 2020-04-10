#ifndef _function_H_
#define  _function_H_
int ROW(FILE *I);
void ScanFile(FILE *b, char **text, int *count);
void Sort(char **text, int *count, int m);
void quickSort(int *numbers, int left, int right, char **text);
#endif
