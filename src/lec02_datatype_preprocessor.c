/*
 * 02강. 자료형과 선행 처리기
 *
 * 실습 목표
 *   - 기본 자료형의 크기와 값의 범위를 확인한다.
 *   - 열거형, 변수의 유효 위치(전역/지역), 초기화의 중요성을 확인한다.
 *   - #include, #define(매크로), 조건부 컴파일을 확인한다.
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

/* 전역 변수 */
int a = 100;

/* 열거형: 첫 번째 상수는 0부터 시작하고 이후 1씩 증가한다. */
enum day { SUN, MON, TUE, WED, THU, FRI, SAT };
enum fruit { APPLE, PEAR, MANGO = 4, GRAPE };

/* 매크로 정의 */
#define PI 3.141592
#define C_AREA(x) (3.141592 * (x) * (x))        /* 올바른 매크로: 인수를 괄호로 묶음 */
#define C_AREA_BAD(x) (3.141592 * x * x)        /* 잘못된 매크로: 인수에 괄호가 없음 */

/* 조건부 컴파일: 0으로 바꾸면 디버그 출력이 컴파일에서 제외된다. */
#define DEBUG_MODE 1

/* ---------------------------------------------------------------
 * 실습 1. 기본 자료형의 크기와 범위
 * --------------------------------------------------------------- */
static void practice1_type_range(void)
{
    int minInt = INT_MIN;
    int maxInt = INT_MAX;
    double minDouble = DBL_MIN;
    double maxDouble = DBL_MAX;
    char ch1 = 'A';
    char ch2 = 0x42;

    printf("int 자료형 범위: %d ~ %d\n", minInt, maxInt);
    printf("double 자료형 범위: %e ~ %e\n", minDouble, maxDouble);

    printf("ch = '%c'\n", ch1);
    printf("'%c'의 ASCII 코드 = %d\n", ch1, ch1);
    printf("ASCII 코드 %d에 해당되는 문자 = '%c'\n", ch2, ch2);

    printf("\n자료형별 크기(byte)\n");
    printf("char=%zu short=%zu int=%zu long=%zu long long=%zu\n",
           sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(long long));
    printf("float=%zu double=%zu long double=%zu\n",
           sizeof(float), sizeof(double), sizeof(long double));
}

/* ---------------------------------------------------------------
 * 실습 2. 열거형
 * --------------------------------------------------------------- */
static void practice2_enum(void)
{
    printf("TUE의 값 = %d\n", TUE);
    printf("PEAR의 값 = %d\n", PEAR);
    printf("MANGO의 값 = %d\n", MANGO);
    printf("GRAPE의 값 = %d\n", GRAPE);
}

/* ---------------------------------------------------------------
 * 실습 3. 변수에 저장되는 값의 크기에 따른 오버플로
 *   short의 표현 범위(-32768 ~ 32767)를 벗어나면 값이 되돌아간다.
 * --------------------------------------------------------------- */
static void practice3_overflow(void)
{
    short s1 = SHRT_MAX;
    short s2 = SHRT_MIN;
    int i1 = SHRT_MAX;
    int i2 = SHRT_MIN;

    s1 = (short)(s1 + 1);
    s2 = (short)(s2 - 1);
    printf("short: num1 = %d, num2 = %d\n", s1, s2);

    i1 = i1 + 1;
    i2 = i2 - 1;
    printf("int  : num1 = %d, num2 = %d\n", i1, i2);
}

/* ---------------------------------------------------------------
 * 실습 4. 전역 변수와 지역 변수
 *   같은 이름의 지역 변수가 전역 변수를 가린다.
 * --------------------------------------------------------------- */
static void func(void)
{
    int a = 200;    /* 전역 변수 a를 가리는 지역 변수 */
    printf("func()에서 a의 값 ==> %d\n", a);
}

static void practice4_scope(void)
{
    printf("main 쪽에서 a의 값 ==> %d\n", a);
    func();
}

/* ---------------------------------------------------------------
 * 실습 5. 변수의 초기화
 *   초기화하지 않은 지역 변수는 쓰레기 값을 가지므로 합계가 틀어진다.
 *   (미초기화 변수를 읽는 코드는 동작이 정해지지 않아 여기서 실행하지 않는다.)
 *
 *   잘못된 코드:  int i, sum;  for (...) sum = sum + i;
 * --------------------------------------------------------------- */
static void practice5_init(void)
{
    int i, sum = 0;     /* 누적 변수는 반드시 0으로 초기화한다. */

    for (i = 1; i <= 10; i++)
        sum = sum + i;
    printf("1부터 10까지의 합 = %d\n", sum);
}

/* ---------------------------------------------------------------
 * 실습 6. 매크로
 * --------------------------------------------------------------- */
static void practice6_macro(void)
{
    double r = 10.0;

    printf("PI 사용: %lf\n", PI * r * r);
    printf("C_AREA(r) = %lf\n", C_AREA(r));

    r = 5.0;
    /* r + 5 가 10.0으로 계산되도록 괄호가 필요하다. */
    printf("C_AREA(r + 5)     = %lf  (올바른 매크로)\n", C_AREA(r + 5));
    /* 전개 결과: 3.141592 * r + 5 * r + 5 */
    printf("C_AREA_BAD(r + 5) = %lf  (의도와 다른 결과)\n", C_AREA_BAD(r + 5));
}

/* ---------------------------------------------------------------
 * 실습 7. 조건부 컴파일
 * --------------------------------------------------------------- */
static void practice7_conditional(void)
{
    int x = 10, y = 20;

#if DEBUG_MODE
    printf("평균을 구할 값: %d, %d\n", x, y);
#endif
    printf("평균 = %f\n", (x + y) / 2.0);

#if defined(__STDC_VERSION__)
    printf("__STDC_VERSION__ = %ld\n", (long)__STDC_VERSION__);
#else
    printf("표준 C 버전 매크로가 정의되어 있지 않다.\n");
#endif
}

int main(void)
{
    printf("[실습 1] 자료형의 크기와 범위\n");
    practice1_type_range();

    printf("\n[실습 2] 열거형\n");
    practice2_enum();

    printf("\n[실습 3] 오버플로\n");
    practice3_overflow();

    printf("\n[실습 4] 전역 변수와 지역 변수\n");
    practice4_scope();

    printf("\n[실습 5] 변수의 초기화\n");
    practice5_init();

    printf("\n[실습 6] 매크로\n");
    practice6_macro();

    printf("\n[실습 7] 조건부 컴파일\n");
    practice7_conditional();

    return 0;
}
