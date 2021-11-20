#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#pragma comment(linker, "/INCLUDE:_mainCRTStartup")

#define N 20

/* � ������� �[1..20] ����� ������� �������������� ������������� ����� � ���������� ������������� �� ���������� �������� ��������. */

extern "C" {
	int findNegativeCount(int length, int* array);
	int findPositiveArithmeticMean(int length, int* array);
}


int main() {
	srand(time(0));
	int mas[N];
	//fillArray(N, mas);
	for (int i = 0; i < N; i++) {
		mas[i] = rand() % 21 - 10;
	}
	printf("Original array:\n");
	for (int i = 0; i < N; i++) {
		printf("%d ", mas[i]);
	}

	findPositiveArithmeticMean(N, mas);
	//printf("\nAvrage of positive numbers: %d\n", findPositiveArithmeticMean(N, mas));
	printf("\nThe number of negative numbers up to the last zero: %d\n", findNegativeCount(N, mas));
	_getch();
	return 0;
}