/*
 * 12강. 구조체와 공용체 (2)
 *
 * 실습 목표
 *   - 구조체를 함수의 인수(값 전달)와 반환값으로 사용하는 방법을 확인한다.
 *   - 구조체 포인터를 함수의 인수로 전달하는 방법을 확인한다.
 *   - 비트필드를 확인한다.
 *   - 공용체(union)를 확인한다.
 *
 * 참고
 *   비트필드의 배치와 공용체 멤버 간의 값 해석은 컴파일러와 CPU 구조에 따라 다르다.
 *   아래 출력은 gcc(x86-64, 리틀 엔디안) 기준이다.
 */

#include <stdio.h>

struct num {
    int x;
    int y;
    int sum;
    int mul;
};

/* 구조체 값을 받아 계산한 뒤 복사본을 반환한다. */
struct num calc_value(struct num number2);
/* 구조체 주소를 받아 원본을 직접 수정한다. */
struct num *calc_pointer(struct num *number2);

/* 비트필드 */
struct nibble {
    unsigned int a : 1;
    unsigned int b : 2;
    unsigned int c : 1;
};

struct test_int {
    unsigned a : 5;
    unsigned b : 6;
    unsigned c : 6;
    unsigned d : 4;
};

struct test_short {
    unsigned short a : 5;
    unsigned short b : 6;
    unsigned short c : 6;
    unsigned short d : 4;
};

struct test_pad {
    unsigned short a : 5;
    unsigned short   : 3;      /* 이름 없는 필드: 3비트를 건너뜀 */
    unsigned short b : 6;
    unsigned short c : 6;
    unsigned short d : 4;
};

struct test_zero {
    unsigned short a : 5;
    unsigned short   : 0;      /* 크기 0: 다음 필드를 새 저장 단위에서 시작 */
    unsigned short b : 6;
    unsigned short c : 6;
    unsigned short d : 4;
};

/* 공용체: 모든 멤버가 같은 메모리를 공유하고 크기는 가장 큰 멤버와 같다. */
union Var {
    char a;
    int b;
    double c;
};

union test {
    short i;
    float f;
    double d;
};

/* 실습 1. 구조체의 값 전달과 반환 */
static void practice1_struct_value(void)
{
    struct num number1 = { 10, 20, 0, 0 };

    number1 = calc_value(number1);      /* 반환된 복사본을 다시 대입해야 반영된다. */
    printf("x:%d, y:%d, sum:%d, mul:%d\n",
           number1.x, number1.y, number1.sum, number1.mul);
}

/* 실습 2. 구조체 포인터 전달 */
static void practice2_struct_pointer(void)
{
    struct num number1 = { 10, 20, 0, 0 };

    calc_pointer(&number1);             /* 원본이 직접 수정된다. */
    printf("x:%d, y:%d, sum:%d, mul:%d\n",
           number1.x, number1.y, number1.sum, number1.mul);
    printf("sizeof(struct num) = %zu  (값 전달은 전체 복사, 주소 전달은 포인터 크기 %zu)\n",
           sizeof(struct num), sizeof(struct num *));
}

/* 실습 3. 비트필드의 사용과 크기 */
static void practice3_bitfield(void)
{
    struct nibble n = { 1, 3, 0 };
    struct test_int v = { 1, 2, 3, 4 };

    printf("nibble: a=%u b=%u c=%u, sizeof = %zu\n", n.a, n.b, n.c, sizeof(n));

    /* 비트 수를 넘는 값은 하위 비트만 저장된다. (b는 2비트이므로 0~3) */
    n.b = 3;
    n.a = 0;
    printf("n.b = 3, n.a = 0 -> a=%u b=%u\n", n.a, n.b);

    printf("v.a=%u v.b=%u v.c=%u v.d=%u\n", v.a, v.b, v.c, v.d);
    printf("struct test_int 크기  = %zu byte\n", sizeof(struct test_int));
    printf("struct test_short 크기 = %zu byte\n", sizeof(struct test_short));
    printf("struct test_pad 크기   = %zu byte  (이름 없는 필드 포함)\n", sizeof(struct test_pad));
    printf("struct test_zero 크기  = %zu byte  (크기 0 필드 포함)\n", sizeof(struct test_zero));
}

/* 실습 4. 비트필드로 플래그 표현하기 (응용) */
static void practice4_flags(void)
{
    struct {
        unsigned read  : 1;
        unsigned write : 1;
        unsigned exec  : 1;
    } perm = { 1, 1, 0 };

    printf("권한: r=%u w=%u x=%u  -> %c%c%c\n", perm.read, perm.write, perm.exec,
           perm.read ? 'r' : '-', perm.write ? 'w' : '-', perm.exec ? 'x' : '-');
}

/* 실습 5. 공용체 */
static void practice5_union(void)
{
    union Var abc;
    union Var *p = &abc;

    printf("sizeof(union Var) = %zu  (가장 큰 멤버 double의 크기)\n", sizeof(abc));

    abc.a = 'A';
    printf("abc.a = '%c'\n", abc.a);

    abc.b = 66;                         /* 0x42 = 'B' */
    printf("abc.b = %d, abc.a = '%c'  (같은 메모리의 첫 바이트)\n", abc.b, abc.a);

    abc.c = 1234.5678;
    printf("abc.c = %f 저장 후 abc.b = %d  (double의 하위 4바이트 해석)\n", abc.c, abc.b);

    p->a = 'A';                         /* 포인터로도 접근 가능 */
    printf("p->a = '%c'\n", p->a);
}

/* 실습 6. 공용체의 멤버 값 해석 */
static void practice6_union_test(void)
{
    union test u;

    u.i = u.f = u.d = 0;
    printf("%zu bytes\n", sizeof(u));

    u.i = 100;
    printf("u.i = 100  -> i=%d\n", u.i);        /* f, d는 같은 메모리를 다른 방식으로 해석하므로 의미가 없다. */

    u.f = 0.5;
    printf("u.f = 0.5  -> f=%f\n", u.f);

    u.d = 0.016667;
    printf("u.d = 0.016667 -> d=%f\n", u.d);
}

int main(void)
{
    printf("[실습 1] 구조체 값 전달\n");           practice1_struct_value();
    printf("\n[실습 2] 구조체 포인터 전달\n");     practice2_struct_pointer();
    printf("\n[실습 3] 비트필드\n");               practice3_bitfield();
    printf("\n[실습 4] 비트필드 응용\n");          practice4_flags();
    printf("\n[실습 5] 공용체\n");                 practice5_union();
    printf("\n[실습 6] 공용체 멤버 해석\n");       practice6_union_test();

    return 0;
}

struct num calc_value(struct num number2)
{
    number2.sum = number2.x + number2.y;
    number2.mul = number2.x * number2.y;
    return number2;
}

struct num *calc_pointer(struct num *number2)
{
    number2->sum = number2->x + number2->y;
    number2->mul = number2->x * number2->y;
    return number2;
}
