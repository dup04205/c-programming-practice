/*
 * 01강. C 언어의 개요
 *
 * 실습 목표
 *   - C 프로그램의 기본 구조(도입부, main 함수, 사용자 함수)를 확인한다.
 *   - 토큰(예약어, 명칭, 상수, 연산자, 주석)의 종류를 확인한다.
 *   - 에러와 경고가 발생하는 대표 사례를 확인한다.
 *
 * 빌드 과정 (소스 -> 목적 파일 -> 실행 파일)
 *   gcc -c lec01_overview.c -o lec01_overview.o     (컴파일)
 *   gcc lec01_overview.o -o lec01_overview          (링크)
 *   gcc lec01_overview.c -o lec01_overview          (한 번에 수행)
 */

/* 도입부: 선행 처리 지시어와 함수 선언 */
#include <stdio.h>

int add(int x, int y);

/* ---------------------------------------------------------------
 * 실습 1. 프로그램의 기본 구조
 * --------------------------------------------------------------- */
static void practice1_basic_structure(void)
{
    int i = 10, j = 20, sum;

    sum = add(i, j);
    printf("%d+%d=%d\n", i, j, sum);
}

/* ---------------------------------------------------------------
 * 실습 2. 명칭(identifier) 정의 규칙
 *   올바른 명칭과 잘못된 명칭을 주석으로 구분한다.
 * --------------------------------------------------------------- */
static void practice2_identifiers(void)
{
    /* 올바른 명칭 */
    int myname = 1;     /* 영문자로 구성 */
    int myName = 2;     /* myname과 다른 명칭(camel case) */
    int MyName = 3;     /* myname과 다른 명칭(Pascal case) */
    int my_name = 4;    /* 밑줄 사용 가능(snake case) */
    int flag01 = 5;     /* 영문자와 숫자 조합 가능 */
    int For = 6;        /* 예약어 for와 대소문자가 달라 사용 가능 */

    /* 잘못된 명칭 (컴파일 에러가 발생하므로 주석 처리)
     * int my name;     공백 사용 불가
     * int my#name;     특수 문자 사용 불가
     * int my-name;     특수 문자 사용 불가
     * int 4days;       숫자로 시작 불가
     * int auto;        예약어 사용 불가
     */

    printf("myname=%d myName=%d MyName=%d my_name=%d flag01=%d For=%d\n",
           myname, myName, MyName, my_name, flag01, For);
}

/* ---------------------------------------------------------------
 * 실습 3. 설명문(주석)과 변수 선언문
 *   원본 예제는 scanf로 두 수를 입력받는다.
 *   여기서는 실행 결과를 고정하기 위해 값을 직접 대입한다.
 * --------------------------------------------------------------- */
static void practice3_comments(void)
{
    int x, y, sum;      // 변수 선언문

    /* 변수 x, y에 값을 대입한다. (원본: scanf("%d", &x);) */
    x = 15;
    y = 27;

    // 두 수를 더해 변수 sum에 저장
    sum = x + y;

    // 결과를 화면에 출력
    printf("sum = %d\n", sum);
}

/* ---------------------------------------------------------------
 * 실습 4. 에러와 경고
 *   아래 코드는 의도적으로 에러를 일으키므로 주석 처리한다.
 *   주석을 풀고 컴파일하여 메시지를 직접 확인한다.
 *
 *   사례 1) 세미콜론 누락 -> 구문 오류(error)
 *       printf("Hello~\n")
 *
 *   사례 2) 함수 이름 오타 -> 암시적 선언 경고(warning) 후 링크 에러
 *       print("Hello~\n");
 * --------------------------------------------------------------- */
static void practice4_errors(void)
{
    printf("Hello~\n");     /* 올바르게 작성한 코드 */
}

/* main 함수 */
int main(void)
{
    printf("[실습 1] 기본 구조\n");
    practice1_basic_structure();

    printf("\n[실습 2] 명칭 정의 규칙\n");
    practice2_identifiers();

    printf("\n[실습 3] 설명문\n");
    practice3_comments();

    printf("\n[실습 4] 에러와 경고\n");
    practice4_errors();

    return 0;
}

/* 프로그램에 필요한 함수 정의 */
int add(int x, int y)
{
    return x + y;
}
