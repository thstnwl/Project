#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>

int main(void) {
	// ������ �ۼ�.
	int dollor, won, currency;

	printf("��ȯ�ϰ��� �ϴ� �޷��� �׼��� �Է����ּ���:");
	scanf("%d", &dollor);

	printf("���� ȯ���� �Է����ּ���:");
	scanf("%d", &currency);

	// won = dollor * currency
	printf("�޾ƾ��� ��ȭ�� %d���Դϴ�.\n", dollor * currency);

	return 0;
}
