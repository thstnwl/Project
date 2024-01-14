#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "RegTree.h"

// 최상의 특징과 임계값을 찾는 함수
void find_best_split(Data* data, int num_data, int* best_feature, float* best_threshold, float* best_reduction) {
    float mean_parent = 0; // 부모 노드의 평균
    float squared_sum_parent = 0; // 부모 노드의 제곱합

    // 부모 노드의 평균과 제곱합 계산
    for (int i = 0; i < num_data; i++) {
        mean_parent += data[i].value;
        squared_sum_parent += data[i].value * data[i].value;
    }

    float V_parent = squared_sum_parent / num_data - mean_parent * mean_parent / (num_data * num_data); // 부모 노드의 분산 계산

    for (int f = 0; f < FEATURE_DIM; f++) { // 모든 특징에 대해서 반복
        for (int i = 0; i < num_data; i++) {
            float threshold = data[i].feature[f]; // 특징의 임계값

            int left_count = 0, right_count = 0; // 왼쪽과 오른쪽 자식 노드의 데이터 개수
            float mean_left = 0, mean_right = 0; // 왼쪽과 오른쪽 자식 노드의 평균
            float squared_sum_left = 0, squared_sum_right = 0; // 왼쪽과 오른쪽 자식 노드의 제곱합

            // 왼쪽과 오른쪽 자식 노드의 평균과 제곱합 계산
            for (int j = 0; j < num_data; j++) {
                if (data[j].feature[f] < threshold) {
                    mean_left += data[j].value;
                    squared_sum_left += data[j].value * data[j].value;
                    left_count++;
                }
                else {
                    mean_right += data[j].value;
                    squared_sum_right += data[j].value * data[j].value;
                    right_count++;
                }
            }

            float V_left = (left_count == 0) ? 0 : (squared_sum_left / left_count) - (mean_left / left_count) * (mean_left / left_count); // 왼쪽 자식 노드의 분산
            float V_right = (right_count == 0) ? 0 : (squared_sum_right / right_count) - (mean_right / right_count) * (mean_right / right_count); // 오른쪽 자식 노드의 분산
            float V_reduction = V_parent - left_count * V_left / num_data - right_count * V_right / num_data; // 분할로 인한 분산 감소량 계산

            if (V_reduction > *best_reduction && left_count >= MIN_SAMPLES && right_count >= MIN_SAMPLES) {
                *best_reduction = V_reduction; // 최적의 분할 후보의 분산 감소량 갱신
                *best_feature = f; // 최적의 분할 후보의 특징 인덱스 갱신
                *best_threshold = threshold; // 최적의 분할 후보의 임계값 갱신
            }
        }
    }
}

TreeNode* makeTree_depth(Data* data, int num_data, int depth) {
    if (depth >= MAX_DEPTH || num_data < MIN_SAMPLES) { // 트리 깊이 제한 또는 데이터 개수 제한에 도달한 경우
        TreeNode* leaf_node = (TreeNode*)calloc(1, sizeof(TreeNode)); // 리프 노드 생성
        leaf_node->left = NULL;
        leaf_node->right = NULL;

        float mean = 0;
        for (int i = 0; i < num_data; i++) {
            mean += data[i].value;
        }
        leaf_node->output_value = mean / num_data; // 리프 노드의 출력 값은 데이터 값들의 평균
        return leaf_node;
    }

    int best_feature = -1; // 최적의 분할 후보의 특징 인덱스
    float best_threshold = 0; // 최적의 분할 후보의 임계값
    float best_reduction = 0; // 최적의 분할 후보의 분산 감소량

    float mean_parent = 0; // 부모 노드의 평균
    float squared_sum_parent = 0; // 부모 노드의 제곱합

    // 부모 노드의 평균과 제곱합 계산
    for (int i = 0; i < num_data; i++) {
        mean_parent += data[i].value;
        squared_sum_parent += data[i].value * data[i].value;
    }

    float V_parent = squared_sum_parent / num_data - mean_parent * mean_parent / (num_data * num_data); // 부모 노드의 분산 계산

    for (int f = 0; f < FEATURE_DIM; f++) { // 모든 특징에 대해서 반복
        for (int i = 0; i < num_data; i++) {
            float threshold = data[i].feature[f]; // 특징의 임계값

            int left_count = 0, right_count = 0; // 왼쪽과 오른쪽 자식 노드의 데이터 개수
            float mean_left = 0, mean_right = 0; // 왼쪽과 오른쪽 자식 노드의 평균
            float squared_sum_left = 0, squared_sum_right = 0; // 왼쪽과 오른쪽 자식 노드의 제곱합

            // 왼쪽과 오른쪽 자식 노드의 평균과 제곱합 계산
            for (int j = 0; j < num_data; j++) {
                if (data[j].feature[f] < threshold) {
                    mean_left += data[j].value;
                    squared_sum_left += data[j].value * data[j].value;
                    left_count++;
                }
                else {
                    mean_right += data[j].value;
                    squared_sum_right += data[j].value * data[j].value;
                    right_count++;
                }
            }

            float V_left = (left_count == 0) ? 0 : (squared_sum_left / left_count) - (mean_left / left_count) * (mean_left / left_count); // 왼쪽 자식 노드의 분산
            float V_right = (right_count == 0) ? 0 : (squared_sum_right / right_count) - (mean_right / right_count) * (mean_right / right_count); // 오른쪽 자식 노드의 분산
            float V_reduction = V_parent - left_count * V_left / num_data - right_count * V_right / num_data; // 분할로 인한 분산 감소량 계산

            if (V_reduction > best_reduction && left_count >= MIN_SAMPLES && right_count >= MIN_SAMPLES) {
                best_reduction = V_reduction; // 최적의 분할 후보의 분산 감소량 갱신
                best_feature = f; // 최적의 분할 후보의 특징 인덱스 갱신
                best_threshold = threshold; // 최적의 분할 후보의 임계값 갱신
            }
        }
    }

    if (best_reduction <= 0) { // 분산 감소량이 0보다 작거나 같은 경우
        TreeNode* leaf_node = (TreeNode*)calloc(1, sizeof(TreeNode)); // 리프 노드 생성
        leaf_node->left = NULL;
        leaf_node->right = NULL;

        float mean = 0;
        for (int i = 0; i < num_data; i++) {
            mean += data[i].value;
        }
        leaf_node->output_value = mean / num_data; // 리프 노드의 출력 값은 데이터 값들의 평균
        return leaf_node;
    }
    else {
        int left_count = 0, right_count = 0;
        for (int i = 0; i < num_data; i++) {
            if (data[i].feature[best_feature] < best_threshold) {
                left_count++;
            }
            else {
                right_count++;
            }
        }

        Data* left_data = (Data*)calloc(left_count, sizeof(Data)); // 왼쪽 자식 노드의 데이터 배열 생성
        Data* right_data = (Data*)calloc(right_count, sizeof(Data)); // 오른쪽 자식 노드의 데이터 배열 생성

        left_count = right_count = 0;
        for (int i = 0; i < num_data; i++) {
            if (data[i].feature[best_feature] < best_threshold) {
                left_data[left_count++] = data[i];
            }
            else {
                right_data[right_count++] = data[i];
            }
        }

        TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode)); // 분할 노드 생성
        node->feature_index = best_feature; // 분할 노드의 특징 인덱스 설정
        node->threshold = best_threshold; // 분할 노드의 임계값 설정
        node->left = makeTree_depth(left_data, left_count, depth + 1); // 왼쪽 자식 노드 생성
        node->right = makeTree_depth(right_data, right_count, depth + 1); // 오른쪽 자식 노드 생성

        free(left_data); // 왼쪽 자식 노드의 데이터 배열 메모리 해제
        free(right_data); // 오른쪽 자식 노드의 데이터 배열 메모리 해제

        return node;
    }
}


TreeNode* makeTree(Data* data, int num_data) {
    return makeTree_depth(data, num_data, 0);
}

/////////////////////////////////////////////////////////////
// 트리 해제
/////////////////////////////////////////////////////////////
void terminateTree(TreeNode* node) {
    // 현재 node가 NULL (더 이상 방문할 노드가 없는 경우)
    if (node == NULL) {
        return; // 함수 종료
    }
    // 현재 node가 NULL이 아닌 경우
    else {
        terminateTree(node->left);  // 왼쪽 서브트리 해제 (재귀)
        terminateTree(node->right); // 오른쪽 서브트리 해제 (재귀)
        free(node);                 // 현재 노드 메모리 해제
    }
}


/////////////////////////////////////////////////////////////
// 입력 데이터의 출력 값을 예측
/////////////////////////////////////////////////////////////
float predict(TreeNode* tree, Data* data) {
    // 리프 노드가 될때까지 실행 (왼쪽 자식과 오른쪽 자식이 모두 있는지 확인)
    while (tree->left != NULL && tree->right != NULL) {

        // 특성 값이 임계값 이하라면 왼쪽 자식 노드로 이동
        if (data->feature[tree->feature_index] <= tree->threshold) {
            tree = tree->left;  // 왼쪽 자식 노드로 이동
        }
        // 특성 값이 임계값보다 크다면 오른쪽 자식 노드로 이동
        else {
            tree = tree->right; // 오른쪽 자식 노드로 이동
        }
    }

    return tree->output_value;  // 리프 노드의 출력값 반환
}