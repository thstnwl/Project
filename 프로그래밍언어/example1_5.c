#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>
#define WON 50000

int main(void) {
	int value, change, change5000, change1000, change500, change100;

	printf("���ǰ��� �Է��ϼ���(�������): ");
	scanf("%d", &value);

	change = WON - value;	// �� �Ž��� ��
	
	change5000 = change / 5000;
	change %= 5000;

	change1000 = change / 1000;
	change %= 1000;

	change500 = change / 500;
	change %= 500;

	change100 = change / 100;
	change %= 100;

	printf("5000����: %d��\n", change5000);
	printf("1000����: %d��\n", change1000);
	printf("500����: %d��\n", change500);
	printf("100����: %d��\n", change100);
}
