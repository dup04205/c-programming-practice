/*
 * 09강. 배열과 포인터 (2)
 *
 * 실습 목표
 *   - 포인터 변수의 선언, 주소 연산자(&), 간접 참조 연산자(*)를 확인한다.
 *   - 포인터 자료형의 중요성과 void 포인터를 확인한다.
 *   - 포인터 연산(덧셈, 뺄셈, 증감)을 확인한다.
 *
 * 주의
 *   초기화하지 않은 포인터에 값을 저장하는 코드(*p = 10;)는
 *   임의의 주소를 덮어쓰므로 실행하면 안 된다. 주석으로만 설명한다.
 */

#include <stdio.h>

/* 실습 1. 변수와 포인터를 통한 접근 */
static void practice1_basic(void)
{
    int n;
    int *p = &n;        /* p는 n의 주소를 저장한다. */

    n = 200;
    printf("n 직접 접근: n = %d\n", n);

    *p = 300;           /* p가 가리키는 n의 값을 바꾼다. */
    printf("p 간접 접근: n = %d, *p = %d\n", n, *p);
    printf("&n = %p, p = %p  (같은 주소)\n", (void *)&n, (void *)p);
}

/* 실습 2. 선언과 참조 */
static void practice2_declare(void)
{
    int a = 10, b, c;
    int *p;

    p = &a;
    printf("p = &a   -> *p = %d\n", *p);

    *p = 20;
    printf("*p = 20  -> a = %d\n", a);

    a = 5000;
    p = &a;
    b = *p;             /* b = a */
    p = &c;
    *p = 100;           /* c = 100 */
    printf("a = %d, b = %d, c = %d\n", a, b, c);

    /* 잘못된 사용 예 (실행하지 않는다.)
     *   int *q, i = 4;
     *   *q = 10;       q가 초기화되지 않아 임의 주소에 저장하게 된다.
     * 올바른 사용 예
     *   q = &i;  *q = 10;   -> i가 10으로 바뀐다.
     */
}

/* 실습 3. 포인터를 이용한 값 읽기 */
static void practice3_read(void)
{
    int *p, i = 3, j;

    p = &i;
    j = *p;
    j++;
    printf("*p = %d\n", *p);
    printf(" p = %p\n", (void *)p);
    printf(" j = %d\n", j);
}

/* 실습 4. 포인터의 자료형은 접근하는 크기를 결정한다. */
static void practice4_pointer_type(void)
{
    int a = 10;
    float b = 20.0f;
    float c;
    float *p = &c;      /* 자료형이 같은 포인터 */

    *p = (float)a * b;
    printf("float 포인터 사용: c = %f\n", c);

    /* 자료형이 다른 포인터 (경고 발생, 실행하지 않는다.)
     *   int *p = &c;       float 값을 int로 해석한다.
     *   double *p = &c;    float(4byte)보다 큰 8byte 영역을 침범한다.
     */
    printf("sizeof(float*) = %zu, sizeof(int*) = %zu, sizeof(double*) = %zu\n",
           sizeof(float *), sizeof(int *), sizeof(double *));
}

/* 실습 5. void 포인터: 어떤 자료형의 주소든 저장할 수 있으나 사용 전에 형변환이 필요하다. */
static void practice5_void_pointer(void)
{
    int a = 100;
    char b = 'b';
    void *p = NULL;

    p = &a;
    printf("*p = %d\n", *(int *)p);     /* printf("%d", *p); 는 에러 */

    p = &b;
    printf("*p = '%c'\n", *(char *)p);
}

/* 실습 6. 포인터 연산 */
static void practice6_arithmetic(void)
{
    int a[10] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    int *p = a;
    int *q = &a[3];

    printf("*(p + 2) = %d  (a[2])\n", *(p + 2));
    printf("*(p + 5) = %d  (a[5])\n", *(p + 5));
    printf("*(q - 2) = %d  (a[1])\n", *(q - 2));
    printf("*(q + 3) = %d  (a[6])\n", *(q + 3));

    p = &a[6];
    q = &a[2];
    printf("p - q = %td\n", p - q);     /* 주소 차이가 아니라 요소 개수의 차이 */
    printf("q - p = %td\n", q - p);
}

/* 실습 7. *p++ 와 *++p */
static void practice7_incdec(void)
{
    int a[] = { 10, 20, 30, 40, 50 };
    int *p = &a[0];
    int v;

    printf("*p = %d\n", *p);

    v = *p++;           /* 현재 값을 읽은 뒤 p를 다음 칸으로 이동 */
    printf("*p++ = %d, 이동 후 *p = %d\n", v, *p);

    v = *++p;           /* p를 먼저 이동한 뒤 값을 읽음 */
    printf("*++p = %d\n", v);
}

int main(void)
{
    printf("[실습 1] 포인터 기본\n");           practice1_basic();
    printf("\n[실습 2] 선언과 참조\n");          practice2_declare();
    printf("\n[실습 3] 값 읽기\n");              practice3_read();
    printf("\n[실습 4] 포인터 자료형\n");         practice4_pointer_type();
    printf("\n[실습 5] void 포인터\n");          practice5_void_pointer();
    printf("\n[실습 6] 포인터 연산\n");          practice6_arithmetic();
    printf("\n[실습 7] *p++ 와 *++p\n");        practice7_incdec();

    return 0;
}
