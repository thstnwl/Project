#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int c;
    int x1;
    int y1;
    int x2;
    int y2;
    float confidence;
    int result; //1이면 출력, 0이면 미출력
} BBox;

void swap(BBox* a, BBox* b) {
    BBox tmp = *a;
    *a = *b;
    *b = tmp;
}

// 1. pivot을 기준으로 배열을 두개로
int partition(BBox arr[], int low, int high, float conf_threshold, int* num_boxes) {
    float pivot = arr[high].confidence;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // 2. 신뢰도가 0.7 미만이면 num_boxes 숫자 1씩 감소시키는 부분 (제외하기위해)
        if (arr[j].confidence < conf_threshold) {
            (*num_boxes)--;
            arr[j].result = 0;
        }
        if (arr[j].confidence >= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// 1. 퀵정렬
void quick_sort(BBox arr[], int low, int high, float conf_threshold, int* num_boxes) {
    if (low < high) {
        int temp = partition(arr, low, high, conf_threshold, num_boxes);

        quick_sort(arr, low, temp - 1, conf_threshold, num_boxes);
        quick_sort(arr, temp + 1, high, conf_threshold, num_boxes);
    }
}

// 3~8. IoU 계산 및 최종 출력
int IoU(BBox arr[], int num, float iou_threshold) {
    for (int head = 0; head < num - 1; head++) {

        int box1 = (arr[head].x2 - arr[head].x1) * (arr[head].y2 - arr[head].y1);
        for (int n = head + 1; n <= num - 1; n++) {
            int box2 = (arr[n].x2 - arr[n].x1) * (arr[n].y2 - arr[n].y1);

            int x_min = fmax(arr[head].x1, arr[n].x1);
            int x_max = fmin(arr[head].x2, arr[n].x2);
            int y_min = fmax(arr[head].y1, arr[n].y1);
            int y_max = fmin(arr[head].y2, arr[n].y2);

            int width = fmax(0, x_max - x_min);
            int height = fmax(0, y_max - y_min);

            int box_in = abs(width * height);
            float iou = (float)(box_in) / (box1 + box2 - box_in);

            if ((iou >= iou_threshold)) { arr[n].result = 0; }

        }
    }

    for (int last = 0; last < num; last++) {
        if (arr[last].result == 1) {
            printf("%d %d %d %d %d %.2f\n", arr[last].c, arr[last].x1, arr[last].y1, arr[last].x2, arr[last].y2, arr[last].confidence);
        }
    }
    return 0;
}

int main(void) {
    // 검출 결과의 입력 개수와 정보를 저장할 배열
    int num_boxes = 0;

    // 테스트 샘플을 실행하기 위한 파일 입출력 코드 //
    const char* file_path = "D:/samples.txt";
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Opening file fails\n");
        return 1;
    }
    fscanf(file, "%d", &num_boxes);
    BBox* bboxes = (BBox*)malloc(sizeof(BBox) * num_boxes);

    for (int i = 0; i < num_boxes; i++) {
        int c, x1, y1, x2, y2;
        float confidence;
        fscanf(file, "%d %d %d %d %d %f", &c, &x1, &y1, &x2, &y2, &confidence);
        bboxes[i].c = c;
        bboxes[i].x1 = x1;
        bboxes[i].y1 = y1;
        bboxes[i].x2 = x2;
        bboxes[i].y2 = y2;
        bboxes[i].confidence = confidence;
        bboxes[i].result = 1;
    }
    fclose(file);

    // 데이터 처리를 위한 기준 값 //
    float conf_threshold = 0.7;
    float iou_threshold = 0.5;

    // 알고리즘 작성 및 결과 출력
    quick_sort(bboxes, 0, num_boxes - 1, conf_threshold, &num_boxes);
    IoU(bboxes, num_boxes - 1, iou_threshold);

    free(bboxes);

    return 0;
}