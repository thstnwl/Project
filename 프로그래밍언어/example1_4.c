#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>


int main(void) {
	int input;

	printf("������ �Է��ϼ���: ");
	scanf("%d", &input);

	printf("%d�� 2�� ����: %d", input, (~input) + 1);

	return 0;
}
