#define _CRT_SECURE_NO_WARNINGS		// scanf
#include <stdio.h>
#define PI 3.14

int main(void) {
	//const float pi = 3.14;
	float radius, area, volume;
	
	printf("구의 반지름을 입력해주세요(실수): ");
	scanf("%f", &radius);

	area = 4. * PI * radius * radius;
	volume = (4. / 3.) * PI * radius * radius * radius;
	//volume = area / 3. * radius;

	printf("표면적: %f, 부피: %f\n", area, volume);

	return 0;
}
