#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>
#define WON 50000

int main(void) {
	int value, change, change5000, change1000, change500, change100;

	printf("물건값을 입력하세요(백원단위): ");
	scanf("%d", &value);

	change = WON - value;	// 총 거스름 돈
	
	change5000 = change / 5000;
	change %= 5000;

	change1000 = change / 1000;
	change %= 1000;

	change500 = change / 500;
	change %= 500;

	change100 = change / 100;
	change %= 100;

	printf("5000원권: %d개\n", change5000);
	printf("1000원권: %d개\n", change1000);
	printf("500원권: %d개\n", change500);
	printf("100원권: %d개\n", change100);
}
