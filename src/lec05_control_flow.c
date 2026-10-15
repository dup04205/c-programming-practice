/*
 * 05강. 선택 제어문과 반복 제어문
 *
 * 실습 목표
 *   - if, if ~ else, 다중 if, else if 사다리, switch를 확인한다.
 *   - for, 다중 for, while, do ~ while을 확인한다.
 *   - break, continue, goto를 확인한다.
 *
 * 원본 예제는 scanf로 값을 입력받는다.
 * 여기서는 실행 결과를 고정하기 위해 배열에 입력값을 미리 준비한다.
 */

#include <stdio.h>
#include <math.h>

/* 실습 1. 단순 if 문: 두 수를 내림차순으로 정렬 */
static void practice1_if(void)
{
    int a = 10, b = 20;

    if (a < b) {            /* 블록({})으로 묶어야 세 문장이 모두 조건에 속한다. */
        int tmp = a;
        a = b;
        b = tmp;
    }
    printf("max = %d, min = %d\n", a, b);
}

/* 실습 2. if ~ else 문 */
static void practice2_if_else(void)
{
    int pairs[2][2] = { {250, 100}, {30, 200} };
    int i, max;

    for (i = 0; i < 2; i++) {
        if (pairs[i][0] >= pairs[i][1])
            max = pairs[i][0];
        else
            max = pairs[i][1];
        printf("%d, %d -> max = %d\n", pairs[i][0], pairs[i][1], max);
    }
}

/* 실습 3. 다중 if 문: else는 가장 가까운 if와 짝을 이룬다. */
static void practice3_nested_if(void)
{
    int values[3] = { 10, 0, -4 };
    int i, a;

    for (i = 0; i < 3; i++) {
        a = values[i];
        if (a >= 0)
            if (a == 0)
                printf("%d: 입력된 값은 0\n", a);
            else
                printf("%d: 입력된 값은 양수\n", a);
        else
            printf("%d: 입력된 값은 음수\n", a);
    }
}

/* 실습 4. if ~ else if ~ else 문: 점수별 학점 */
static void practice4_else_if(void)
{
    int scores[5] = { 95, 85, 72, 60, 41 };
    int i, score;

    for (i = 0; i < 5; i++) {
        score = scores[i];
        if (score >= 90)
            printf("%d점: 학점은 A\n", score);
        else if (score >= 80)
            printf("%d점: 학점은 B\n", score);
        else if (score >= 70)
            printf("%d점: 학점은 C\n", score);
        else if (score >= 60)
            printf("%d점: 학점은 D\n", score);
        else
            printf("%d점: 학점은 F\n", score);
    }
}

/* 실습 5. switch 문: break가 없으면 아래 case로 계속 실행된다(fall-through). */
static void practice5_switch(void)
{
    int score = 85;

    printf("[break 없음] score = %d\n", score);
    switch (score / 10) {
    case 10:
    case 9: printf("학점은 A\n");
        /* fall through */
    case 8: printf("학점은 B\n");
        /* fall through */
    case 7: printf("학점은 C\n");
        /* fall through */
    case 6: printf("학점은 D\n");
        /* fall through */
    default: printf("학점은 F\n");
    }

    printf("[break 있음] score = %d\n", score);
    switch (score / 10) {
    case 10:
    case 9: printf("학점은 A\n");
        break;
    case 8: printf("학점은 B\n");
        break;
    case 7: printf("학점은 C\n");
        break;
    case 6: printf("학점은 D\n");
        break;
    default: printf("학점은 F\n");
    }
}

/* 실습 6. for 문과 다중 for 문 */
static void practice6_for(void)
{
    int i, sum = 0;
    int a, b;

    for (i = 1; i <= 10; ++i)
        sum = sum + i;
    printf("1부터 %d까지의 합 = %d\n", i - 1, sum);

    for (a = 1; a <= 3; ++a) {
        printf("a=%d\n", a);
        for (b = 0; b < 4; b++)
            printf("b=%d ", b);
        putchar('\n');
    }
}

/* 실습 7. while 문과 do ~ while 문 */
static void practice7_while(void)
{
    int i = 1, sum = 0;
    int n = 10;

    while (i <= 10) {
        sum = sum + i;
        i++;
    }
    printf("[while] 1부터 %d까지의 합 = %d\n", i - 1, sum);

    /* do ~ while 은 조건을 나중에 검사하므로 최소 한 번은 실행한다. */
    i = 1;
    sum = 0;
    do {
        sum = sum + i;
        i++;
    } while (i <= n);
    printf("[do-while] i = %d, 1부터 %d까지의 합 = %d\n", i, i - 1, sum);

    /* 조건이 처음부터 거짓이어도 do ~ while 은 한 번 실행된다. */
    i = 100;
    do {
        printf("[do-while] 조건이 거짓이어도 한 번 실행된다. i = %d\n", i);
    } while (i < 10);
}

/* 실습 8. break 문: 0이 입력되면 반복을 종료하고 합계를 출력 */
static void practice8_break(void)
{
    int inputs[] = { 10, 20, 30, 0, 99 };   /* 0 이후의 값은 읽지 않는다. */
    int idx = 0, num, sum = 0;

    while (1) {
        num = inputs[idx++];
        printf("num(끝이면 0을 입력) : %d\n", num);
        if (num == 0)
            break;
        sum += num;
    }
    printf("sum = %d\n", sum);
}

/* 실습 9. continue 문: 음수는 건너뛰고 다음 반복으로 이동 */
static void practice9_continue(void)
{
    int inputs[] = { 2, -3, 0 };
    int idx = 0, num;

    do {
        num = inputs[idx++];
        printf("num = %d\n", num);
        if (num < 0) {
            printf("음수의 제곱근은 계산 불가\n");
            continue;       /* do ~ while 에서는 조건식 검사로 이동한다. */
        }
        printf("%d의 제곱근 = %f\n", num, sqrt(num));
    } while (num != 0);
    printf("The end\n");
}

/* 실습 10. goto 문: 중첩 반복문을 한 번에 탈출 (제한적으로 사용한다.) */
static void practice10_goto(void)
{
    int i, j;

    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            if (i * j == 42) {
                printf("i * j == 42 인 첫 조합: i = %d, j = %d\n", i, j);
                goto found;
            }
        }
    }
found:
    printf("goto로 이중 반복문을 탈출하였다.\n");
}

/* 응용: 구구단 */
static void practice11_gugudan(void)
{
    int dan, i;

    for (dan = 2; dan <= 3; dan++) {
        printf("--- %d단 ---\n", dan);
        for (i = 1; i <= 9; i++)
            printf("%d x %d = %2d\n", dan, i, dan * i);
    }
}

int main(void)
{
    printf("[실습 1] 단순 if 문\n");                 practice1_if();
    printf("\n[실습 2] if ~ else 문\n");              practice2_if_else();
    printf("\n[실습 3] 다중 if 문\n");                practice3_nested_if();
    printf("\n[실습 4] else if 사다리\n");             practice4_else_if();
    printf("\n[실습 5] switch 문\n");                 practice5_switch();
    printf("\n[실습 6] for 문\n");                    practice6_for();
    printf("\n[실습 7] while / do-while 문\n");       practice7_while();
    printf("\n[실습 8] break 문\n");                  practice8_break();
    printf("\n[실습 9] continue 문\n");               practice9_continue();
    printf("\n[실습 10] goto 문\n");                  practice10_goto();
    printf("\n[실습 11] 응용: 구구단\n");              practice11_gugudan();

    return 0;
}
