#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>


int main(void) {
	int input;

	printf("정수를 입력하세요: ");
	scanf("%d", &input);

	printf("%d의 2의 보수: %d", input, (~input) + 1);

	return 0;
}
