#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>

int main(void) {
	float input;
	int output1;
	float output2;

	printf("�Ǽ��� �Է����ּ���: ");
	scanf("%f", &input);

	output1 = (int)input;
	output2 = input - output1;

	printf("������: %d, �Ǽ���: %f", output1, output2);

	return 0;
}