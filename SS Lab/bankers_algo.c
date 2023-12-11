#include <stdio.h>
#define MAX 20

struct bankers {
    int al[MAX][MAX], m[MAX][MAX], n[MAX][MAX], avail[MAX];
    int nop, nor, k, result[MAX], pnum, work[MAX], finish[MAX];
};

void bankers_init(struct bankers *b);
void bankers_input(struct bankers *b);
void bankers_method(struct bankers *b);
int bankers_search(struct bankers *b, int i);
void bankers_display(struct bankers *b);

void bankers_init(struct bankers *b) {
    b->k = 0;
    int i, j;
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            b->al[i][j] = 0;
            b->m[i][j] = 0;
            b->n[i][j] = 0;
        }
        b->avail[i] = 0;
        b->result[i] = 0;
        b->finish[i] = 0;
    }
}

void bankers_input(struct bankers *b) {
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &b->nop);
    printf("Enter the number of resources: ");
    scanf("%d", &b->nor);
    printf("Enter the allocated resources for each process:\n");
    for (i = 0; i < b->nop; i++) {
        printf("\nProcess %d\n", i);
        for (j = 0; j < b->nor; j++) {
            printf("Resource %d: ", j);
            scanf("%d", &b->al[i][j]);
        }
    }
    printf("Enter the maximum resources that are needed for each process:\n");
    for (i = 0; i < b->nop; i++) {
        printf("\nProcess %d\n", i);
        for (j = 0; j < b->nor; j++) {
            printf("Resource %d: ", j);
            scanf("%d", &b->m[i][j]);
            b->n[i][j] = b->m[i][j] - b->al[i][j];
        }
    }
    printf("Enter the currently available resources in the system:\n");
    for (j = 0; j < b->nor; j++) {
        printf("Resource %d: ", j);
        scanf("%d", &b->avail[j]);
        b->work[j] = -1;
    }
    for (i = 0; i < b->nop; i++)
        b->finish[i] = 0;
}

void bankers_method(struct bankers *b) {
    int i = 0, j, flag;
    while (1) {
        if (b->finish[i] == 0) {
            b->pnum = bankers_search(b, i);
            if (b->pnum != -1) {
                b->result[b->k++] = i;
                b->finish[i] = 1;
                for (j = 0; j < b->nor; j++) {
                    b->avail[j] = b->avail[j] + b->al[i][j];
                }
            }
        }
        i++;
        if (i == b->nop) {
            flag = 0;
            for (j = 0; j < b->nor; j++)
                if (b->avail[j] != b->work[j])
                    flag = 1;
            for (j = 0; j < b->nor; j++)
                b->work[j] = b->avail[j];
            if (flag == 0)
                break;
            else
                i = 0;
        }
    }
}

int bankers_search(struct bankers *b, int i) {
    int j;
    for (j = 0; j < b->nor; j++)
        if (b->n[i][j] > b->avail[j])
            return -1;
    return 0;
}

void bankers_display(struct bankers *b) {
    int i, j;
    printf("\nOUTPUT:");
    printf("\n========");
    printf("\nPROCESS\t     ALLOCATED\t     MAXIMUM\t     NEED");
    for (i = 0; i < b->nop; i++) {
        printf("\nP%d\t     ", i + 1);
        for (j = 0; j < b->nor; j++) {
            printf("%d  ", b->al[i][j]);
        }
        printf("\t     ");
        for (j = 0; j < b->nor; j++) {
            printf("%d  ", b->m[i][j]);
        }
        printf("\t     ");
        for (j = 0; j < b->nor; j++) {
            printf("%d  ", b->n[i][j]);
        }
    }
    printf("\nThe sequence of the safe processes are: \n");
    for (i = 0; i < b->k; i++) {
        int temp = b->result[i] + 1;
        printf("P%d ", temp);
    }
    printf("\nThe sequence of unsafe processes are: \n");
    int flg = 0;
    for (i = 0; i < b->nop; i++) {
        if (b->finish[i] == 0) {
            flg = 1;
        }
        printf("P%d ", i);
    }
    printf("\nRESULT:");
    printf("\n=======");
    if (flg == 1)
        printf("\nThe system is not in a safe state, and deadlock may occur!");
    else
        printf("\nThe system is in a safe state, and deadlock will not occur!");
}

int main() {
    printf("DEADLOCK BANKER’S ALGORITHM\n");
    struct bankers B;
    bankers_init(&B);
    bankers_input(&B);
    bankers_method(&B);
    bankers_display(&B);
    return 0;
}














