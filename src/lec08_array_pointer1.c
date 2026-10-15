/*
 * 08강. 배열과 포인터 (1)
 *
 * 실습 목표
 *   - 1차원/다차원 배열의 선언과 초기화를 확인한다.
 *   - char 배열과 문자열(널 문자)의 관계를 확인한다.
 *   - 함수에 배열을 전달하는 방법을 확인한다.
 */

#include <stdio.h>

/* 함수 원형: 배열 매개변수는 실제로는 포인터로 전달된다. */
double average(int arr[], int n);
void score_sum(int gr[][5], int row, int column);

/* 전역 배열: 초기화하지 않은 요소는 0이 된다. */
int g_a[3] = { 1, 2, 3 };
int g_b[4];

/* 실습 1. 배열을 쓰지 않을 때와 쓸 때의 최댓값 찾기 */
static void practice1_max(void)
{
    int max, i;
    int data[10] = { 10, 23, 5, 9, 22, 48, 12, 10, 55, 31 };

    max = data[0];
    printf("데이터 : %d", data[0]);
    for (i = 1; i < 10; i++) {
        printf(" %d", data[i]);
        if (max < data[i])
            max = data[i];
    }
    printf("\n데이터의 최댓값 : %d\n", max);
}

/* 실습 2. 1차원 배열의 초기화 방법 */
static void practice2_init(void)
{
    int a1[4] = { 10, 20, 30, 40 };
    int a2[] = { 10, 20, 30, 40 };      /* 크기는 초깃값 개수로 결정 */
    int a3[4] = { 10, 20 };             /* 나머지는 0 */
    int a4[4] = { 0 };                  /* 전체가 0 */
    int c[3] = { 1 };                   /* 1, 0, 0 */
    int i;

    for (i = 0; i <= 3; i++) printf("a1[%d] = %d\t", i, a1[i]);
    printf("\n");
    for (i = 0; i <= 3; i++) printf("a2[%d] = %d\t", i, a2[i]);
    printf("\n");
    for (i = 0; i <= 3; i++) printf("a3[%d] = %d\t", i, a3[i]);
    printf("\n");
    for (i = 0; i <= 3; i++) printf("a4[%d] = %d\t", i, a4[i]);
    printf("\n");

    printf("c = %d %d %d\n", c[0], c[1], c[2]);
    printf("전역 g_a = %d %d %d,  전역 g_b = %d %d %d %d\n",
           g_a[0], g_a[1], g_a[2], g_b[0], g_b[1], g_b[2], g_b[3]);
    printf("sizeof(a2) = %zu, 요소 개수 = %zu\n", sizeof(a2), sizeof(a2) / sizeof(a2[0]));
}

/* 실습 3. 2차원 배열: 성적표 */
static void practice3_2d(void)
{
    int score[4][3] = { {90, 90, 90}, {80, 80, 80},
                        {70, 70, 70}, {60, 60, 60} };
    int sum, i, j;

    printf("번호\t국어\t수학\t영어\t합계\n");
    for (i = 0; i < 4; i++) {
        sum = 0;
        printf("%3d", i + 1);
        for (j = 0; j < 3; j++) {
            printf("\t%3d", score[i][j]);
            sum += score[i][j];
        }
        printf("\t%3d\n", sum);
    }
}

/* 실습 4. 3차원 배열: 면, 행, 열 */
static void practice4_3d(void)
{
    int a[2][3][4] = {
        { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} },
        { {13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24} }
    };
    int i, j, k;

    for (i = 0; i < 2; i++) {
        printf("면 %d\n", i);
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 4; k++)
                printf("%3d", a[i][j][k]);
            printf("\n");
        }
    }
}

/* 실습 5. char 배열과 문자열 */
static void practice5_string(void)
{
    char name[] = "HONG GIL DONG";                  /* 13글자 + 널 문자 = 14 */
    char addr1[] = { 'S', 'E', 'O', 'U', 'L' };     /* 널 문자 없음: 문자열이 아님 */
    char addr2[] = { 'S', 'E', 'O', 'U', 'L', '\0' };
    char name16[16] = "HONG GIL DONG";              /* 나머지 칸은 모두 널 문자 */
    int i = 0;

    printf("sizeof(name)   = %zu\n", sizeof(name));
    printf("sizeof(addr1)  = %zu  (널 문자 없음)\n", sizeof(addr1));
    printf("sizeof(addr2)  = %zu  (널 문자 포함)\n", sizeof(addr2));
    printf("sizeof(name16) = %zu\n", sizeof(name16));

    /* addr1은 널 문자가 없으므로 %s 대신 길이를 지정해 출력해야 한다. */
    printf("addr1: %.5s, addr2: %s, name16: %s\n", addr1, addr2, name16);

    /* 널 문자를 만날 때까지 문자 단위로 출력 */
    printf("문자 단위 출력: ");
    while (name[i] != '\0') {
        printf("%c", name[i]);
        i++;
    }
    printf("\n문자열 길이 = %d\n", i);
}

/* 실습 6. 함수와 배열 전달 */
static void practice6_array_param(void)
{
    int score[4] = { 90, 85, 100, 88 };
    int score2[2][5] = { {10, 20, 30, 40, 50}, {10, 10, 10, 10, 10} };

    printf("평균 = %4.1lf\n", average(score, 4));
    score_sum(score2, 2, 5);
}

int main(void)
{
    printf("[실습 1] 최댓값 찾기\n");            practice1_max();
    printf("\n[실습 2] 1차원 배열의 초기화\n");   practice2_init();
    printf("\n[실습 3] 2차원 배열\n");            practice3_2d();
    printf("\n[실습 4] 3차원 배열\n");            practice4_3d();
    printf("\n[실습 5] char 배열과 문자열\n");    practice5_string();
    printf("\n[실습 6] 함수와 배열\n");           practice6_array_param();

    return 0;
}

double average(int arr[], int n)
{
    int sum = 0;
    int i;

    for (i = 0; i < n; i++)
        sum += arr[i];
    return sum / (double)n;
}

void score_sum(int gr[][5], int row, int column)
{
    int sum[2] = { 0 };
    int i, j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++)
            sum[i] += gr[i][j];
        printf("sum[%d] = %d\n", i, sum[i]);
    }
}
