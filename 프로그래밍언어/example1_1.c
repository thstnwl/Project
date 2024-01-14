#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>

int main(void) {
	// 내용을 작성.
	int dollor, won, currency;

	printf("교환하고자 하는 달러의 액수를 입력해주세요:");
	scanf("%d", &dollor);

	printf("현재 환율을 입력해주세요:");
	scanf("%d", &currency);

	// won = dollor * currency
	printf("받아야할 원화는 %d원입니다.\n", dollor * currency);

	return 0;
}
