#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>

int main(void) {
	float input;
	int output1;
	float output2;

	printf("실수를 입력해주세요: ");
	scanf("%f", &input);

	output1 = (int)input;
	output2 = input - output1;

	printf("정수부: %d, 실수부: %f", output1, output2);

	return 0;
}