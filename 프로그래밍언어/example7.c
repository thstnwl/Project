#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

/* 사용자의 id, password, 잔금(balance)를 저장하는 구조체(user) 선언 */
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
    int num_accounts;   // 최초에 입력 받을 계정 수
    int i;  // for문에 사용할 반복 변수

    int debit;  // 출금 금액을 입력받을 변수
    int index_id;  // 출금할 사용자를 결정하기 위한 변수

    printf("추가할 계정의 개수를 입력하세요: ");
    scanf("%d", &num_accounts);

    USER* accounts = (USER*)malloc(num_accounts * sizeof(USER));

    for (i = 0; i < num_accounts; i++) {
        insert_new_account(&accounts[i]);
        // insert_new_account(accounts + i);  // 같은 표현
    }

    index_id = find_id(accounts, num_accounts);

    // 무한루프
    check_password(&accounts[index_id]);
    // check_password(accounts + index_id);  // 같은 표현

    printf("출금할 금액을 입력하세요: ");
    scanf("%d", &debit);

    /* 해당하는 계정에서 출금 금액을 뺀 잔액을 출력 */
    accounts[index_id].balance -= debit;
    printf("%s의 잔액: %d원", accounts[index_id].id, accounts[index_id].balance);

    free(accounts);

    return 0;
}

void insert_new_account(USER* account) {
    printf("새로 추가할 ID를 입력해주세요: ");
    /* i번째 구조체 배열 요소에 입력 받은 ID를 추가 */
    scanf("%s", account->id);

    // 무한루프
    while (1) {
        /* i번째 구조체 배열 요소에 입력 받은 암호를 추가 */
        printf("%s에 사용할 암호를 입력해주세요: ", account->id);
        scanf("%s", account->password);

        if (strlen(account->password) >= 8)
            break;
        else
            printf("암호는 8글자 이상이어야 합니다.\n");
    }

    /* i번째 구조체 배열 요소에 입력 받은 금액을 입금 */
    printf("%s에 입금할 금액 입력해주세요: ", account->id);
    scanf("%d", &(account->balance));
}

int find_id(USER* accounts, int num_accounts) {
    int i, index_id = -1;
    char input_id[SIZE];    // 사용자에게 ID를 입력 받기 위한 배열

    while (1) { // 구조체 배열에 있는 ID가 입력될 경우 무한루프를 빠져나오면서 해당하는 배열 index를 index_id에 저장
        printf("출금할 계좌의 ID를 입력해주세요: ");
        scanf("%s", input_id);

        // 저장해놨던 ID 중에 입력받은 ID가 있는가?
        for (i = 0; i < num_accounts; i++) {
            if (strcmp(input_id, accounts[i].id) == 0) {
                index_id = i;
                break;
            }
        }

        if (index_id >= 0)
            break;
        else
            printf("존재하지 않는 ID입니다.\n");
    }

    return index_id;
}

void check_password(USER* account) {
    char input_password[SIZE];  // 사용자의 암호를 입력 받기 위한 배열

    while (1) {
        /* 암호를 입력 받고, 입력 받은 ID의 암호가 맞다면 무한루프를 탈출 */
        printf("%s의 암호를 입력해주세요: ", account->id);
        scanf("%s", input_password);

        if (strcmp(input_password, account->password) == 0)
            break;
        else
            printf("올바른 암호를 입력해주세요.\n");
    }
}