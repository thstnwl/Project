#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "RegTree.h"

// �ֻ��� Ư¡�� �Ӱ谪�� ã�� �Լ�
void find_best_split(Data* data, int num_data, int* best_feature, float* best_threshold, float* best_reduction) {
    float mean_parent = 0; // �θ� ����� ���
    float squared_sum_parent = 0; // �θ� ����� ������

    // �θ� ����� ��հ� ������ ���
    for (int i = 0; i < num_data; i++) {
        mean_parent += data[i].value;
        squared_sum_parent += data[i].value * data[i].value;
    }

    float V_parent = squared_sum_parent / num_data - mean_parent * mean_parent / (num_data * num_data); // �θ� ����� �л� ���

    for (int f = 0; f < FEATURE_DIM; f++) { // ��� Ư¡�� ���ؼ� �ݺ�
        for (int i = 0; i < num_data; i++) {
            float threshold = data[i].feature[f]; // Ư¡�� �Ӱ谪

            int left_count = 0, right_count = 0; // ���ʰ� ������ �ڽ� ����� ������ ����
            float mean_left = 0, mean_right = 0; // ���ʰ� ������ �ڽ� ����� ���
            float squared_sum_left = 0, squared_sum_right = 0; // ���ʰ� ������ �ڽ� ����� ������

            // ���ʰ� ������ �ڽ� ����� ��հ� ������ ���
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

            float V_left = (left_count == 0) ? 0 : (squared_sum_left / left_count) - (mean_left / left_count) * (mean_left / left_count); // ���� �ڽ� ����� �л�
            float V_right = (right_count == 0) ? 0 : (squared_sum_right / right_count) - (mean_right / right_count) * (mean_right / right_count); // ������ �ڽ� ����� �л�
            float V_reduction = V_parent - left_count * V_left / num_data - right_count * V_right / num_data; // ���ҷ� ���� �л� ���ҷ� ���

            if (V_reduction > *best_reduction && left_count >= MIN_SAMPLES && right_count >= MIN_SAMPLES) {
                *best_reduction = V_reduction; // ������ ���� �ĺ��� �л� ���ҷ� ����
                *best_feature = f; // ������ ���� �ĺ��� Ư¡ �ε��� ����
                *best_threshold = threshold; // ������ ���� �ĺ��� �Ӱ谪 ����
            }
        }
    }
}

TreeNode* makeTree_depth(Data* data, int num_data, int depth) {
    if (depth >= MAX_DEPTH || num_data < MIN_SAMPLES) { // Ʈ�� ���� ���� �Ǵ� ������ ���� ���ѿ� ������ ���
        TreeNode* leaf_node = (TreeNode*)calloc(1, sizeof(TreeNode)); // ���� ��� ����
        leaf_node->left = NULL;
        leaf_node->right = NULL;

        float mean = 0;
        for (int i = 0; i < num_data; i++) {
            mean += data[i].value;
        }
        leaf_node->output_value = mean / num_data; // ���� ����� ��� ���� ������ ������ ���
        return leaf_node;
    }

    int best_feature = -1; // ������ ���� �ĺ��� Ư¡ �ε���
    float best_threshold = 0; // ������ ���� �ĺ��� �Ӱ谪
    float best_reduction = 0; // ������ ���� �ĺ��� �л� ���ҷ�

    float mean_parent = 0; // �θ� ����� ���
    float squared_sum_parent = 0; // �θ� ����� ������

    // �θ� ����� ��հ� ������ ���
    for (int i = 0; i < num_data; i++) {
        mean_parent += data[i].value;
        squared_sum_parent += data[i].value * data[i].value;
    }

    float V_parent = squared_sum_parent / num_data - mean_parent * mean_parent / (num_data * num_data); // �θ� ����� �л� ���

    for (int f = 0; f < FEATURE_DIM; f++) { // ��� Ư¡�� ���ؼ� �ݺ�
        for (int i = 0; i < num_data; i++) {
            float threshold = data[i].feature[f]; // Ư¡�� �Ӱ谪

            int left_count = 0, right_count = 0; // ���ʰ� ������ �ڽ� ����� ������ ����
            float mean_left = 0, mean_right = 0; // ���ʰ� ������ �ڽ� ����� ���
            float squared_sum_left = 0, squared_sum_right = 0; // ���ʰ� ������ �ڽ� ����� ������

            // ���ʰ� ������ �ڽ� ����� ��հ� ������ ���
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

            float V_left = (left_count == 0) ? 0 : (squared_sum_left / left_count) - (mean_left / left_count) * (mean_left / left_count); // ���� �ڽ� ����� �л�
            float V_right = (right_count == 0) ? 0 : (squared_sum_right / right_count) - (mean_right / right_count) * (mean_right / right_count); // ������ �ڽ� ����� �л�
            float V_reduction = V_parent - left_count * V_left / num_data - right_count * V_right / num_data; // ���ҷ� ���� �л� ���ҷ� ���

            if (V_reduction > best_reduction && left_count >= MIN_SAMPLES && right_count >= MIN_SAMPLES) {
                best_reduction = V_reduction; // ������ ���� �ĺ��� �л� ���ҷ� ����
                best_feature = f; // ������ ���� �ĺ��� Ư¡ �ε��� ����
                best_threshold = threshold; // ������ ���� �ĺ��� �Ӱ谪 ����
            }
        }
    }

    if (best_reduction <= 0) { // �л� ���ҷ��� 0���� �۰ų� ���� ���
        TreeNode* leaf_node = (TreeNode*)calloc(1, sizeof(TreeNode)); // ���� ��� ����
        leaf_node->left = NULL;
        leaf_node->right = NULL;

        float mean = 0;
        for (int i = 0; i < num_data; i++) {
            mean += data[i].value;
        }
        leaf_node->output_value = mean / num_data; // ���� ����� ��� ���� ������ ������ ���
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

        Data* left_data = (Data*)calloc(left_count, sizeof(Data)); // ���� �ڽ� ����� ������ �迭 ����
        Data* right_data = (Data*)calloc(right_count, sizeof(Data)); // ������ �ڽ� ����� ������ �迭 ����

        left_count = right_count = 0;
        for (int i = 0; i < num_data; i++) {
            if (data[i].feature[best_feature] < best_threshold) {
                left_data[left_count++] = data[i];
            }
            else {
                right_data[right_count++] = data[i];
            }
        }

        TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode)); // ���� ��� ����
        node->feature_index = best_feature; // ���� ����� Ư¡ �ε��� ����
        node->threshold = best_threshold; // ���� ����� �Ӱ谪 ����
        node->left = makeTree_depth(left_data, left_count, depth + 1); // ���� �ڽ� ��� ����
        node->right = makeTree_depth(right_data, right_count, depth + 1); // ������ �ڽ� ��� ����

        free(left_data); // ���� �ڽ� ����� ������ �迭 �޸� ����
        free(right_data); // ������ �ڽ� ����� ������ �迭 �޸� ����

        return node;
    }
}


TreeNode* makeTree(Data* data, int num_data) {
    return makeTree_depth(data, num_data, 0);
}

/////////////////////////////////////////////////////////////
// Ʈ�� ����
/////////////////////////////////////////////////////////////
void terminateTree(TreeNode* node) {
    // ���� node�� NULL (�� �̻� �湮�� ��尡 ���� ���)
    if (node == NULL) {
        return; // �Լ� ����
    }
    // ���� node�� NULL�� �ƴ� ���
    else {
        terminateTree(node->left);  // ���� ����Ʈ�� ���� (���)
        terminateTree(node->right); // ������ ����Ʈ�� ���� (���)
        free(node);                 // ���� ��� �޸� ����
    }
}


/////////////////////////////////////////////////////////////
// �Է� �������� ��� ���� ����
/////////////////////////////////////////////////////////////
float predict(TreeNode* tree, Data* data) {
    // ���� ��尡 �ɶ����� ���� (���� �ڽİ� ������ �ڽ��� ��� �ִ��� Ȯ��)
    while (tree->left != NULL && tree->right != NULL) {

        // Ư�� ���� �Ӱ谪 ���϶�� ���� �ڽ� ���� �̵�
        if (data->feature[tree->feature_index] <= tree->threshold) {
            tree = tree->left;  // ���� �ڽ� ���� �̵�
        }
        // Ư�� ���� �Ӱ谪���� ũ�ٸ� ������ �ڽ� ���� �̵�
        else {
            tree = tree->right; // ������ �ڽ� ���� �̵�
        }
    }

    return tree->output_value;  // ���� ����� ��°� ��ȯ
}