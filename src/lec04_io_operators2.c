/*
 * 04강. 입출력 함수와 연산자 (2)
 *
 * 실습 목표
 *   - 산술, 증감, 관계, 논리, 조건, 대입, 비트 연산자를 확인한다.
 *   - sizeof, 콤마 연산자, 형변환을 확인한다.
 *
 * 참고
 *   강의의 "a = ++x * x--;" 는 같은 변수를 한 식에서 두 번 변경하므로
 *   결과가 정해져 있지 않다(컴파일러마다 다를 수 있다).
 *   따라서 여기서는 전위/후위 연산을 문장을 나누어 확인한다.
 */

#include <stdio.h>

/* 값을 8비트 2진수 문자열로 출력하는 보조 함수 */
static void print_bits(const char *label, unsigned char v)
{
    int i;

    printf("%-10s: ", label);
    for (i = 7; i >= 0; i--) {
        putchar((v >> i) & 1 ? '1' : '0');
        if (i == 4)
            putchar(' ');
    }
    putchar('\n');
}

/* 실습 1. 산술 연산자 */
static void practice1_arithmetic(void)
{
    int x = 10, y = 3;

    printf("x = %d, y = %d\n", x, y);
    printf("x + y = %d\n", x + y);
    printf("x - y = %d\n", x - y);
    printf("x * y = %d\n", x * y);
    printf("x / y = %d\n", x / y);          /* 정수끼리의 나눗셈은 몫만 구한다. */
    printf("x %% y = %d\n", x % y);
    printf("y %% x = %d\n", y % x);
    printf("x / (double)y = %f\n", x / (double)y);
}

/* 실습 2. 증감 연산자: 전위와 후위의 차이 */
static void practice2_incdec(void)
{
    int x = 5, a, b;

    a = ++x;        /* x를 먼저 증가시킨 뒤 대입: a = 6, x = 6 */
    printf("a = ++x -> a = %d, x = %d\n", a, x);

    b = x--;        /* 대입한 뒤 x를 감소: b = 6, x = 5 */
    printf("b = x-- -> b = %d, x = %d\n", b, x);
}

/* 실습 3. 관계 연산자와 논리 연산자 */
static void practice3_relational_logical(void)
{
    int a = 4, b, c, d, e;

    b = a > 2;
    c = a < 2;
    d = a == 4;
    printf("b = %d, c = %d, d = %d\n", b, c, d);

    a = 4;
    b = 7;
    c = a > 2 && b <= 7;
    d = a < 2 || b <= 7;
    e = !a;
    printf("c = %d, d = %d, e = %d\n", c, d, e);
}

/* 실습 4. 논리 연산자의 단락 평가 (short-circuit) */
static void practice4_short_circuit(void)
{
    int a = 4, b = 7, c = 10, d;

    /* b++ <= 5 가 거짓이므로 뒤의 --c > 0 은 평가되지 않는다. */
    d = a > 0 && b++ <= 5 && --c > 0;
    printf("d = %d\n", d);
    printf("b = %d\n", b);      /* b++ 는 수행되었으므로 8 */
    printf("c = %d\n", c);      /* --c 는 수행되지 않았으므로 10 */
}

/* 실습 5. 조건 연산자 */
static void practice5_conditional(void)
{
    int a = 25, b = 13;

    printf("최댓값 = %d\n", a >= b ? a : b);
    printf("최솟값 = %d\n", a <= b ? a : b);
}

/* 실습 6. 대입 연산자와 복합 대입 연산자 */
static void practice6_assignment(void)
{
    float f = 1.5f;
    int b;
    float c;
    int p = 10, q = 3, r = 1;

    c = b = (int)f;     /* 실수를 정수에 대입하면 소수부가 버려진다. */
    printf("b = %d, c = %f\n", b, c);

    p *= q - 1;         /* p = p * (q - 1) */
    q /= 2 + 3;         /* q = q / (2 + 3) */
    r += 2;             /* r = r + 2 */
    printf("p = %d, q = %d, r = %d\n", p, q, r);
}

/* 실습 7. 비트 연산자 */
static void practice7_bitwise(void)
{
    unsigned char x = 0xB3;     /* 1011 0011 */
    unsigned char y = 0x49;     /* 0100 1001 */
    unsigned char mask = 0x0F;  /* 0000 1111 */
    int v = 40;

    print_bits("x", x);
    print_bits("y", y);
    print_bits("x & y", (unsigned char)(x & y));
    print_bits("x | y", (unsigned char)(x | y));
    print_bits("x ^ y", (unsigned char)(x ^ y));
    print_bits("~x", (unsigned char)~x);
    print_bits("x << 2", (unsigned char)(x << 2));
    print_bits("x >> 2", (unsigned char)(x >> 2));

    printf("\n[마스크 활용: mask = 0000 1111]\n");
    print_bits("x & mask", (unsigned char)(x & mask));     /* 하위 4비트만 추출 */
    print_bits("x | mask", (unsigned char)(x | mask));     /* 하위 4비트를 1로 설정 */
    print_bits("x ^ mask", (unsigned char)(x ^ mask));     /* 하위 4비트를 반전 */

    printf("\n[시프트 = 2의 거듭제곱 곱셈/나눗셈]\n");
    printf("%d << 3 = %d (= %d * 8)\n", v, v << 3, v);
    printf("%d >> 2 = %d (= %d / 4)\n", v, v >> 2, v);
}

/* 실습 8. sizeof, 콤마 연산자, 형변환 */
static void practice8_misc(void)
{
    int i, j;
    int a = 3, b = 4;
    double c;

    printf("sizeof(int) = %zu, sizeof(double) = %zu\n", sizeof(int), sizeof(double));

    for (i = 0, j = 4; i < 5; i++, j--)
        printf("[%d, %d]\n", i, j);

    c = a / b;                  /* 정수 나눗셈 후 실수로 변환: 0 */
    printf("나눗셈 결과(형변환 없음): %f\n", c);
    c = (double)a / b;          /* a를 실수로 바꾼 뒤 나눗셈: 0.75 */
    printf("나눗셈 결과(형변환 있음): %f\n", c);
}

int main(void)
{
    printf("[실습 1] 산술 연산자\n");
    practice1_arithmetic();

    printf("\n[실습 2] 증감 연산자\n");
    practice2_incdec();

    printf("\n[실습 3] 관계/논리 연산자\n");
    practice3_relational_logical();

    printf("\n[실습 4] 단락 평가\n");
    practice4_short_circuit();

    printf("\n[실습 5] 조건 연산자\n");
    practice5_conditional();

    printf("\n[실습 6] 대입 연산자\n");
    practice6_assignment();

    printf("\n[실습 7] 비트 연산자\n");
    practice7_bitwise();

    printf("\n[실습 8] sizeof, 콤마 연산자, 형변환\n");
    practice8_misc();

    return 0;
}
