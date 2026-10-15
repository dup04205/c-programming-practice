/*
 * 07강. 함수와 기억 클래스 (2)
 *
 * 실습 목표
 *   - 값 전달(call by value)과 주소 전달(포인터 매개변수)의 차이를 확인한다.
 *   - 변수의 유효범위(전역, 지역, 블록, 이름 가림)를 확인한다.
 *   - 기억 클래스(auto, static, extern, register)를 확인한다.
 */

#include <stdio.h>

/* 전역 변수: 초기화를 생략하면 0으로 초기화된다. */
int gx;
int gi = 10;
int gj = 20;
int ga = 10;

/* extern 선언의 대상으로 사용할 전역 변수는 main보다 뒤에 정의한다. */
extern int gk;

/* ---- 함수 원형 ---- */
int sum_by_value(int x, int y);
void swap_value(int x, int y);
void swap_pointer(int *x, int *y);
void fcn1(void);
void test(void);

/* 실습 1. 값 전달: 매개변수를 바꾸어도 호출한 쪽의 변수는 바뀌지 않는다. */
static void practice1_call_by_value(void)
{
    int a = 10, b = 20, d;

    d = sum_by_value(a, b);
    printf("%d + %d = %d   (a는 그대로 %d)\n", a, b, d, a);
}

/* 실습 2. swap: 값 전달은 실패하고 주소 전달은 성공한다. */
static void practice2_swap(void)
{
    int a = 3, b = 5;

    printf("[값 전달] 호출 전 a = %d, b = %d\n", a, b);
    swap_value(a, b);
    printf("[값 전달] 호출 후 a = %d, b = %d   (바뀌지 않음)\n", a, b);

    a = 3;
    b = 5;
    printf("[주소 전달] 호출 전 a = %d, b = %d\n", a, b);
    swap_pointer(&a, &b);
    printf("[주소 전달] 호출 후 a = %d, b = %d   (바뀜)\n", a, b);
}

/* 실습 3. 지역 변수: 함수마다 같은 이름의 변수는 서로 다른 변수이다. */
static void practice3_local(void)
{
    int i = 10;

    printf("main i = %d\n", i);
    fcn1();
    printf("main i = %d\n", i);
}

/* 실습 4. 블록 유효범위와 이름 가림 */
static void practice4_block_scope(void)
{
    int x = 2, y = 4;

    printf("A: x = %d, y = %d\n", x, y);
    {
        int x;          /* 바깥 x를 가림 */
        x = 5;
        y++;            /* 바깥 y를 그대로 사용 */
        printf("B: x = %d, y = %d\n", x, y);
    }
    printf("A: x = %d, y = %d\n", x, y);

    {
        int ga = 20;
        {
            int ga = 30;
            printf("가장 안쪽 ga = %d\n", ga);
        }
        printf("중간 ga = %d\n", ga);
    }
    printf("전역 ga = %d\n", ga);
}

/* 실습 5. 전역 변수: 모든 함수에서 접근할 수 있다. */
static void practice5_global(void)
{
    printf("1) gx = %d   (초기화를 생략하면 0)\n", gx);
    gx++;
    printf("2) gx = %d\n", gx);
}

/* 실습 6. 블록별 auto 변수 */
static void practice6_auto(void)
{
    int i = 1;
    int j = 2;      /* 지역 변수는 기본적으로 auto 기억 클래스이다. */
    {
        int i = 3;
        {
            int i = 4;
            printf("블록2의 i = %d\n", i);
            printf("블록2의 j = %d\n", j);
        }
        printf("블록1의 i = %d\n", i);
    }
    printf("함수 내의 i = %d\n", i);
}

/* 실습 7. static 지역 변수: 함수가 끝나도 값이 유지된다. */
static void practice7_static(void)
{
    int i;

    for (i = 0; i < 3; i++)
        test();
}

/* 실습 8. extern: 다른 곳(또는 다른 파일)에 정의된 전역 변수를 참조한다. */
static void practice8_extern(void)
{
    extern int gi;      /* 위에서 정의한 전역 변수 gi를 참조한다. */
    int gj = 100;       /* 전역 변수 gj를 가리는 지역 변수 */

    printf("gi = %d, gj = %d, gk = %d\n", gi, gj, gk);
}

/* 실습 9. register: 레지스터에 저장하도록 컴파일러에 요청한다(강제는 아님). */
static void practice9_register(void)
{
    register int i;
    int sum = 0;

    for (i = 0; i <= 10; ++i)
        sum += i;
    i -= 1;
    printf("i = %d, sum = %d\n", i, sum);
}

int main(void)
{
    printf("[실습 1] 값 전달\n");              practice1_call_by_value();
    printf("\n[실습 2] swap\n");               practice2_swap();
    printf("\n[실습 3] 지역 변수\n");           practice3_local();
    printf("\n[실습 4] 블록 유효범위\n");       practice4_block_scope();
    printf("\n[실습 5] 전역 변수\n");           practice5_global();
    printf("\n[실습 6] auto 변수\n");           practice6_auto();
    printf("\n[실습 7] static 변수\n");         practice7_static();
    printf("\n[실습 8] extern 변수\n");         practice8_extern();
    printf("\n[실습 9] register 변수\n");       practice9_register();

    return 0;
}

/* ---- 함수 정의 ---- */

int gk = 50;    /* extern으로 참조되는 전역 변수 */

int sum_by_value(int x, int y)
{
    x += y;                 /* 복사본 x만 바뀐다. */
    return x;
}

void swap_value(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
    printf("  함수 내 x = %d, y = %d\n", x, y);
}

void swap_pointer(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
    printf("  함수 내 x = %d, y = %d\n", *x, *y);
}

void fcn1(void)
{
    int i;          /* main()의 i와는 별개의 변수 */
    i = 20;
    printf("fcn1 i = %d\n", i);
}

void test(void)
{
    int a = 0;              /* 호출될 때마다 0으로 초기화 */
    static int s = 0;       /* 최초 한 번만 초기화되고 값이 유지됨 */

    printf("auto = %d, static = %d\n", a, s);
    ++a;
    ++s;
}
