#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>
#define PI 3.14

int main(void) {
	//const float pi = 3.14;
	float radius, area, volume;
	
	printf("���� �������� �Է����ּ���(�Ǽ�): ");
	scanf("%f", &radius);

	area = 4. * PI * radius * radius;
	volume = (4. / 3.) * PI * radius * radius * radius;
	//volume = area / 3. * radius;

	printf("ǥ����: %f, ����: %f\n", area, volume);

	return 0;
}
