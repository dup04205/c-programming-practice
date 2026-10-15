/*
 * 10강. 배열과 포인터 (3)
 *
 * 실습 목표
 *   - 포인터와 1차원/2차원 배열의 관계를 확인한다.
 *   - 배열 이름(상수)과 포인터 변수의 차이를 확인한다.
 *   - 포인터 배열과 2차원 char 배열의 차이를 확인한다.
 *   - 이중 포인터를 확인한다.
 */

#include <stdio.h>

/* 실습 1. 문자열 포인터로 문자 접근 */
static void practice1_char_pointer(void)
{
    char *cp = "COMPUTER";
    int i = 0;

    while (*(cp + i) != 0) {
        printf("*(cp+%d) : %c\n", i, *(cp + i));
        i++;
    }

    /* 마지막 널 문자까지 출력하는 do ~ while 버전 */
    i = 0;
    do {
        printf("[널 포함] *(cp+%d) : %d\n", i, *(cp + i));
    } while (*(cp + i++) != 0);
}

/* 실습 2. 배열 이름은 첫 요소의 주소이다. */
static void practice2_array_name(void)
{
    static int a[] = { 10, 20, 30, 40, 50 };
    int *pt, b, c, d;

    pt = a;                     /* 배열의 시작 주소 */
    b = *pt + *(pt + 3);        /* 10 + 40 */
    pt++;                       /* 한 칸 이동 */
    c = *pt + *(pt + 3);        /* 20 + 50 */
    d = *pt + 3;                /* 20 + 3 (값에 3을 더함) */
    printf("b = %d, c = %d, d = %d\n", b, c, d);

    printf("a == &a[0] ? %s\n", (void *)a == (void *)&a[0] ? "예" : "아니오");
}

/* 실습 3. 2차원 배열은 메모리에 행 순서로 일렬 저장된다. */
static void practice3_2d_array(void)
{
    static int a[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, -9} };
    static int b[2][3] = { {1, 2, 3}, {4, 5, 6} };
    int *pt, i, j;

    /* -9를 만날 때까지 포인터를 한 칸씩 이동하며 출력 */
    pt = a[0];                  /* &a[0][0] 과 동일 */
    while (*pt != -9) {
        printf("%d ", *pt);
        pt++;
    }
    printf("\n");

    /* *(pt + i*열수 + j) == a[i][j] */
    pt = &b[0][0];
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++)
            printf("%d ", *(pt + i * 3 + j));
        printf("\n");
    }
}

/* 실습 4. 배열 이름과 포인터 변수의 차이 */
static void practice4_array_vs_pointer(void)
{
    char A[] = "ARRAY";
    char *p = "POINTER";
    int arr[5] = { 1, 2, 3, 4, 5 };
    int *q = arr;
    int i;

    for (i = 0; i < 5; i++)
        printf("*(A+%d): %c\n", i, *(A + i));
    for (i = 0; i < 7; i++)
        printf("p[%d]: %c\n", i, p[i]);

    q++;                        /* 포인터 변수는 값을 바꿀 수 있다. */
    printf("q++ 후 *q = %d\n", *q);
    /* arr++;                      배열 이름은 상수이므로 에러가 발생한다. */

    printf("sizeof(A) = %zu (배열 전체), sizeof(p) = %zu (포인터 크기)\n",
           sizeof(A), sizeof(p));
}

/* 실습 5. 2차원 char 배열과 포인터 배열 */
static void practice5_pointer_array(void)
{
    char str2d[3][10] = { "KNOU", "Computer", "123456789" };
    char *strp[3] = { "KNOU", "Computer", "123456789" };
    int i, j;

    printf("[2차원 char 배열]\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; str2d[i][j]; j++)       /* 널 문자('\0')가 아니면 참 */
            printf("%c", str2d[i][j]);
        printf("\n");
    }

    printf("[포인터 배열]\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; strp[i][j]; j++)
            printf("%c", strp[i][j]);
        printf("\n");
    }

    printf("sizeof(str2d) = %zu (3 x 10 byte 고정), sizeof(strp) = %zu (포인터 3개)\n",
           sizeof(str2d), sizeof(strp));
}

/* 실습 6. 이중 포인터 */
static void practice6_double_pointer(void)
{
    char a = 'A', *p, **pp;

    p = &a;
    pp = &p;            /* pp -> p -> a */
    printf("a = %c, *p = %c, **pp = %c\n", a, *p, **pp);

    **pp = 'Z';         /* 이중 포인터로 a의 값을 변경 */
    printf("**pp = 'Z' 후 a = %c\n", a);
}

int main(void)
{
    printf("[실습 1] 문자열 포인터\n");           practice1_char_pointer();
    printf("\n[실습 2] 배열 이름과 포인터\n");     practice2_array_name();
    printf("\n[실습 3] 2차원 배열과 포인터\n");     practice3_2d_array();
    printf("\n[실습 4] 배열 이름 vs 포인터 변수\n"); practice4_array_vs_pointer();
    printf("\n[실습 5] 포인터 배열\n");             practice5_pointer_array();
    printf("\n[실습 6] 이중 포인터\n");             practice6_double_pointer();

    return 0;
}
