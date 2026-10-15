/*
 * 06강. 함수와 기억 클래스 (1)
 *
 * 실습 목표
 *   - 함수를 사용하는 이유(코드 중복 제거)를 확인한다.
 *   - 표준 라이브러리 함수(math.h, ctype.h, string.h, stdlib.h)를 확인한다.
 *   - 사용자 정의 함수의 구성(헤더, 몸체, return)과 함수 원형을 확인한다.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

/* 함수 원형(prototype): main보다 아래에 정의한 함수를 먼저 호출할 수 있게 한다.
 * 매개변수 이름은 정의와 달라도 되고, 생략해도 된다. */
int minimum(int v1, int v2, int v3);
int sum(int, int);
int max(int x, int y);
int min(int x, int y);

/* 실습 1. 함수를 쓰지 않은 경우: 동일한 코드가 중복된다. */
static void practice1_without_function(void)
{
    int a = 15, b = 10, c = 20, m;
    int x = 25, y = 31, z = 17;

    m = a < b ? a : b;
    m = m < c ? m : c;
    printf("%d, %d, %d의 최솟값 = %d\n", a, b, c, m);

    m = x < y ? x : y;          /* 위와 동일한 코드가 반복된다. */
    m = m < z ? m : z;
    printf("%d, %d, %d의 최솟값 = %d\n", x, y, z, m);
}

/* 실습 2. 함수를 쓴 경우: 한 번 정의하고 여러 번 호출한다. */
static void practice2_with_function(void)
{
    int a = 15, b = 10, c = 20;
    int x = 25, y = 31, z = 17;

    printf("%d, %d, %d의 최솟값 = %d\n", a, b, c, minimum(a, b, c));
    printf("%d, %d, %d의 최솟값 = %d\n", x, y, z, minimum(x, y, z));
}

/* 실습 3. 수학 표준 함수 */
static void practice3_math(void)
{
    double x = 12.34;
    int i = -5, j = 2;
    int a, b, c;

    a = (int)ceil(x);           /* 올림 */
    b = (int)floor(x);          /* 내림 */
    c = (int)pow(4, j);         /* 거듭제곱 */

    printf("abs(-5) = %d\n", abs(i));
    printf("ceil(12.34) = %d\n", a);
    printf("floor(12.34) = %d\n", b);
    printf("cos(10) = %f\n", cos(10));
    printf("exp(2) = %f\n", exp(j));
    printf("sqrt(2) = %f\n", sqrt(j));
    printf("pow(4, 2) = %d\n", c);
}

/* 실습 4. 문자 처리 표준 함수: 알파벳, 숫자, 기타 문자의 개수 세기 */
static void practice4_ctype(void)
{
    size_t i;
    int alp = 0, no = 0, et = 0;
    char s[20] = "KNOU1234567890-#*?$";

    printf("문자: %s\n", s);
    for (i = 0; i < strlen(s); i++) {
        if (isalpha((unsigned char)s[i]))
            alp++;
        else if (isdigit((unsigned char)s[i]))
            no++;
        else
            et++;
    }
    printf("알파벳 = %d\n", alp);
    printf("숫자 = %d\n", no);
    printf("기타 = %d\n", et);
}

/* 실습 5. 사용자 정의 함수 */
static void practice5_user_function(void)
{
    int i = 10, j = 20;

    printf("sum(%d, %d) = %d\n", i, j, sum(i, j));
    printf("max(%d, %d) = %d\n", i, j, max(i, j));
    printf("min(%d, %d) = %d\n", i, j, min(i, j));
}

/* 실습 6. 함수 호출의 제어 흐름: 호출 순서를 출력으로 확인 */
static void trace_h(void) { printf("    h() 실행\n"); }
static void trace_g(void) { printf("    g() 실행\n"); }
static void trace_f(void)
{
    printf("  f() 시작\n");
    trace_g();
    trace_h();
    printf("  f() 끝\n");
}

static void practice6_call_flow(void)
{
    printf("main() 시작\n");
    trace_f();
    printf("main() 끝\n");
}

int main(void)
{
    printf("[실습 1] 함수를 쓰지 않은 경우\n");   practice1_without_function();
    printf("\n[실습 2] 함수를 쓴 경우\n");          practice2_with_function();
    printf("\n[실습 3] 수학 표준 함수\n");          practice3_math();
    printf("\n[실습 4] 문자 처리 표준 함수\n");      practice4_ctype();
    printf("\n[실습 5] 사용자 정의 함수\n");        practice5_user_function();
    printf("\n[실습 6] 함수 호출 흐름\n");          practice6_call_flow();

    return 0;
}

/* ---- 함수 정의 ---- */

int minimum(int v1, int v2, int v3)
{
    int m = v1 < v2 ? v1 : v2;
    return m < v3 ? m : v3;
}

int sum(int a, int b)       /* 함수 헤더: 반환형 함수명(매개변수 목록) */
{
    int d;                  /* 몸체 */
    d = a + b;
    return d;
}

int max(int x, int y)
{
    return x > y ? x : y;
}

int min(int x, int y)
{
    if (x > y)
        return y;
    else
        return x;
}
