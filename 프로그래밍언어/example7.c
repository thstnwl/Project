#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

/* ������� id, password, �ܱ�(balance)�� �����ϴ� ����ü(user) ���� */
typedef struct user {
    char id[SIZE];
    char password[SIZE];
    int balance;
} USER;

void insert_new_account(USER* account);

int find_id(USER* accounts, int num_accounts);

void check_password(USER* account);

int main(void)
{
    int num_accounts;   // ���ʿ� �Է� ���� ���� ��
    int i;  // for���� ����� �ݺ� ����

    int debit;  // ��� �ݾ��� �Է¹��� ����
    int index_id;  // ����� ����ڸ� �����ϱ� ���� ����

    printf("�߰��� ������ ������ �Է��ϼ���: ");
    scanf("%d", &num_accounts);

    USER* accounts = (USER*)malloc(num_accounts * sizeof(USER));

    for (i = 0; i < num_accounts; i++) {
        insert_new_account(&accounts[i]);
        // insert_new_account(accounts + i);  // ���� ǥ��
    }

    index_id = find_id(accounts, num_accounts);

    // ���ѷ���
    check_password(&accounts[index_id]);
    // check_password(accounts + index_id);  // ���� ǥ��

    printf("����� �ݾ��� �Է��ϼ���: ");
    scanf("%d", &debit);

    /* �ش��ϴ� �������� ��� �ݾ��� �� �ܾ��� ��� */
    accounts[index_id].balance -= debit;
    printf("%s�� �ܾ�: %d��", accounts[index_id].id, accounts[index_id].balance);

    free(accounts);

    return 0;
}

void insert_new_account(USER* account) {
    printf("���� �߰��� ID�� �Է����ּ���: ");
    /* i��° ����ü �迭 ��ҿ� �Է� ���� ID�� �߰� */
    scanf("%s", account->id);

    // ���ѷ���
    while (1) {
        /* i��° ����ü �迭 ��ҿ� �Է� ���� ��ȣ�� �߰� */
        printf("%s�� ����� ��ȣ�� �Է����ּ���: ", account->id);
        scanf("%s", account->password);

        if (strlen(account->password) >= 8)
            break;
        else
            printf("��ȣ�� 8���� �̻��̾�� �մϴ�.\n");
    }

    /* i��° ����ü �迭 ��ҿ� �Է� ���� �ݾ��� �Ա� */
    printf("%s�� �Ա��� �ݾ� �Է����ּ���: ", account->id);
    scanf("%d", &(account->balance));
}

int find_id(USER* accounts, int num_accounts) {
    int i, index_id = -1;
    char input_id[SIZE];    // ����ڿ��� ID�� �Է� �ޱ� ���� �迭

    while (1) { // ����ü �迭�� �ִ� ID�� �Էµ� ��� ���ѷ����� ���������鼭 �ش��ϴ� �迭 index�� index_id�� ����
        printf("����� ������ ID�� �Է����ּ���: ");
        scanf("%s", input_id);

        // �����س��� ID �߿� �Է¹��� ID�� �ִ°�?
        for (i = 0; i < num_accounts; i++) {
            if (strcmp(input_id, accounts[i].id) == 0) {
                index_id = i;
                break;
            }
        }

        if (index_id >= 0)
            break;
        else
            printf("�������� �ʴ� ID�Դϴ�.\n");
    }

    return index_id;
}

void check_password(USER* account) {
    char input_password[SIZE];  // ������� ��ȣ�� �Է� �ޱ� ���� �迭

    while (1) {
        /* ��ȣ�� �Է� �ް�, �Է� ���� ID�� ��ȣ�� �´ٸ� ���ѷ����� Ż�� */
        printf("%s�� ��ȣ�� �Է����ּ���: ", account->id);
        scanf("%s", input_password);

        if (strcmp(input_password, account->password) == 0)
            break;
        else
            printf("�ùٸ� ��ȣ�� �Է����ּ���.\n");
    }
}