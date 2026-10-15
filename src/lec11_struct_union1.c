/*
 * 11강. 구조체와 공용체 (1)
 *
 * 실습 목표
 *   - 구조체의 정의, 변수 선언, 초기화, 멤버 접근(.)을 확인한다.
 *   - typedef를 이용한 자료형 이름 정의를 확인한다.
 *   - 구조체 배열과 구조체 포인터(->)를 확인한다.
 *   - 멤버 정렬(패딩)에 따른 구조체 크기를 확인한다.
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>

/* 구조체 정의: 중심 좌표와 반지름을 하나로 묶는다. */
struct Circle {
    float x, y;
    float radius;
};

struct UsedCar {
    char maker[15];
    char modelName[15];
    int pYear, mileage;
};

/* typedef: struct 키워드 없이 사용할 수 있는 자료형 이름 */
typedef struct {
    char name[20];
    int age;
    float height;
} Person;

typedef unsigned int UINT;

/* 패딩 확인용 구조체 */
typedef struct {
    int a;      /* 4 bytes */
    char b;     /* 1 byte  */
    int c;      /* 4 bytes */
} StructEx;

typedef struct {
    int a;
    int c;
    char b;     /* 큰 멤버를 앞에 두고 작은 멤버를 뒤로 보낸 배치 */
} StructEx2;

/* 실습 1. 구조체 정의와 변수 선언 */
static void practice1_basic(void)
{
    struct Circle c = { 10.0f, 20.0f, 5.0f };
    struct Circle *pCircle = &c;
    struct UsedCar car;
    UINT length = 100;

    printf("원: 중심 = (%g, %g), 반지름 = %g\n", c.x, c.y, c.radius);
    printf("pCircle->radius = %g\n", pCircle->radius);

    strcpy(car.maker, "KNOU Motors");       /* 문자열 멤버는 strcpy로 복사한다. */
    strcpy(car.modelName, "Alpha");
    car.pYear = 2020;
    car.mileage = 35000;
    printf("중고차: %s %s, %d년식, %d km\n",
           car.maker, car.modelName, car.pYear, car.mileage);

    printf("UINT length = %u\n", length);
}

/* 실습 2. 구조체 초기화와 멤버 접근 */
static void practice2_init(void)
{
    Person prsn = { "홍길동", 25, 178.5f };

    printf("%s %d %f\n", prsn.name, prsn.age, prsn.height);

    /* 같은 구조체끼리는 대입 연산자로 전체 멤버를 복사할 수 있다. */
    Person copy = prsn;
    copy.age = 30;
    printf("원본 age = %d, 복사본 age = %d\n", prsn.age, copy.age);
}

/* 실습 3. 구조체 배열 */
static void practice3_array(void)
{
    Person prsn[2] = { {"홍길동", 25, 178.5f},
                       {"박문수", 20, 180.0f} };
    int i;

    for (i = 0; i < 2; i++)
        printf("%s, %d, %f\n", prsn[i].name, prsn[i].age, prsn[i].height);
}

/* 실습 4. 구조체 포인터: (*p).멤버 와 p->멤버 는 같다. */
static void practice4_pointer(void)
{
    Person prsn = { "홍길동", 25, 178.5f };
    Person *pPrsn = &prsn;

    printf("(*pPrsn).name : %s, %d, %f\n",
           (*pPrsn).name, (*pPrsn).age, (*pPrsn).height);
    printf("pPrsn->name   : %s, %d, %f\n",
           pPrsn->name, pPrsn->age, pPrsn->height);

    pPrsn->age++;
    printf("pPrsn->age++ 후 prsn.age = %d\n", prsn.age);
}

/* 실습 5. 구조체의 크기와 패딩 */
static void practice5_padding(void)
{
    StructEx x = { 10, 'A', 20 };
    StructEx2 y = { 10, 20, 'A' };

    printf("sizeof(StructEx)  = %zu  (int + char + 패딩 3 + int)\n", sizeof(x));
    printf("  offset a=%zu, b=%zu, c=%zu\n",
           offsetof(StructEx, a), offsetof(StructEx, b), offsetof(StructEx, c));
    printf("sizeof(StructEx2) = %zu  (멤버 순서에 따라 크기가 달라진다.)\n", sizeof(y));
    printf("  offset a=%zu, c=%zu, b=%zu\n",
           offsetof(StructEx2, a), offsetof(StructEx2, c), offsetof(StructEx2, b));
}

int main(void)
{
    printf("[실습 1] 구조체 정의와 선언\n");      practice1_basic();
    printf("\n[실습 2] 초기화와 멤버 접근\n");     practice2_init();
    printf("\n[실습 3] 구조체 배열\n");            practice3_array();
    printf("\n[실습 4] 구조체 포인터\n");          practice4_pointer();
    printf("\n[실습 5] 구조체 크기와 패딩\n");     practice5_padding();

    return 0;
}
