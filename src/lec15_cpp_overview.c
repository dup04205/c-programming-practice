/*
 * 15강. C++ 언어의 개요
 *
 * 15강의 원본 예제는 C++(class, 상속, 가상 함수)로 작성되어 있다.
 * 본 파일은 같은 개념을 순수 C로 구현하여 C와 C++의 차이를 비교한다.
 * 원본 C++ 예제는 lec15_cpp_overview.cpp 에 있다.
 *
 * 실습 목표
 *   - struct + 함수 조합으로 "객체"를 흉내 내는 C 방식을 확인한다. (C++ class의 출발점)
 *   - 공개/비공개(캡슐화)를 불투명 포인터로 표현하는 방법을 확인한다.
 *   - 함수 포인터 표(가상 함수 테이블)로 상속과 다형성을 구현하는 방법을 확인한다.
 *
 * C++ 대응 관계
 *   struct Circle + initCircle(&c, ...)  <->  class Circle { void init(...); }
 *   함수 포인터 멤버(vtable)              <->  virtual 함수
 *   구조체의 첫 멤버로 Shape 포함         <->  class Circle : public Shape
 */

#include <stdio.h>
#include <stdlib.h>

/* ===============================================================
 * 실습 1. struct + 함수: 데이터와 처리 함수가 분리되어 있다.
 * =============================================================== */
struct Circle1 {
    float cx, cy;
    float radius;
};

static void initCircle(struct Circle1 *c, float x, float y, float r)
{
    c->cx = x, c->cy = y, c->radius = r;
}

static float areaCircle(const struct Circle1 *c)
{
    return 3.141592f * c->radius * c->radius;
}

static void printCircle(const struct Circle1 *c)
{
    printf("원: 중심 = (%g, %g), ", c->cx, c->cy);
    printf("반경 = %g\n", c->radius);
}

static void practice1_struct_style(void)
{
    struct Circle1 c;

    initCircle(&c, 10.0f, 20.0f, 10.0f);
    printCircle(&c);
    printf("면적 = %g\n", areaCircle(&c));
    /* C에서는 c.radius = -5; 처럼 외부에서 멤버를 마음대로 바꿀 수 있다. */
}

/* ===============================================================
 * 실습 2. 캡슐화: 구조체의 내부를 감추고 함수로만 접근하게 한다.
 *   C++의 private 멤버에 해당한다.
 *   (실제 프로젝트에서는 헤더에 선언만, 소스에 정의를 둔다.)
 * =============================================================== */
typedef struct PrivCircle PrivCircle;   /* 불완전 형식: 외부에서는 내부를 알 수 없다. */

struct PrivCircle {                     /* 정의 (원래는 .c 파일에만 둠) */
    float cx, cy, radius;
};

static PrivCircle *PrivCircle_new(float x, float y, float r)
{
    PrivCircle *c = malloc(sizeof(PrivCircle));

    if (c == NULL)
        return NULL;
    c->cx = x, c->cy = y;
    c->radius = r > 0 ? r : 0;          /* 유효하지 않은 값은 인터페이스에서 걸러낸다. */
    return c;
}

static float PrivCircle_area(const PrivCircle *c)
{
    return 3.141592f * c->radius * c->radius;
}

static void PrivCircle_delete(PrivCircle *c)
{
    free(c);
}

static void practice2_encapsulation(void)
{
    PrivCircle *c = PrivCircle_new(0.0f, 0.0f, -3.0f);

    if (c == NULL) {
        puts("기억 공간 할당 실패!");
        exit(1);
    }
    printf("반지름에 -3을 지정하면 0으로 보정 -> 면적 = %g\n", PrivCircle_area(c));
    PrivCircle_delete(c);
}

/* ===============================================================
 * 실습 3. 상속과 다형성
 *   Shape: 함수 포인터 표(vtable)를 가진 기초 클래스에 해당한다.
 *   Circle, Triangle: Shape를 첫 멤버로 포함하는 파생 클래스에 해당한다.
 *   첫 멤버이므로 (Shape *)로 안전하게 변환할 수 있다.
 * =============================================================== */
typedef struct Shape Shape;

struct ShapeVtbl {
    float (*area)(const Shape *self);       /* virtual float area() const = 0; */
    void  (*print)(const Shape *self);      /* virtual void print() const = 0; */
};

struct Shape {
    const struct ShapeVtbl *vtbl;
};

typedef struct {
    Shape base;                 /* 상속: 기초 클래스 부분 */
    float cx, cy, radius;
} Circle;

typedef struct {
    Shape base;
    float x1, y1, x2, y2, x3, y3;
} Triangle;

/* ---- Circle ---- */
static float Circle_area(const Shape *s)
{
    const Circle *c = (const Circle *)s;
    return 3.141592f * c->radius * c->radius;
}

static void Circle_print(const Shape *s)
{
    const Circle *c = (const Circle *)s;
    printf("원: 중심 = (%g, %g), 반경 = %g\n", c->cx, c->cy, c->radius);
}

static const struct ShapeVtbl circleVtbl = { Circle_area, Circle_print };

static void Circle_init(Circle *c, float x, float y, float r)
{
    c->base.vtbl = &circleVtbl;
    c->cx = x, c->cy = y, c->radius = r;
}

/* ---- Triangle ---- */
static float Triangle_area(const Shape *s)
{
    const Triangle *t = (const Triangle *)s;
    float a = t->x1 * t->y2 + t->x2 * t->y3 + t->x3 * t->y1;
    a -= t->x2 * t->y1 + t->x3 * t->y2 + t->x1 * t->y3;
    return (a >= 0 ? a : -a) / 2.0f;
}

static void Triangle_print(const Shape *s)
{
    const Triangle *t = (const Triangle *)s;
    printf("삼각형: (%g, %g) - (%g, %g) - (%g, %g)\n",
           t->x1, t->y1, t->x2, t->y2, t->x3, t->y3);
}

static const struct ShapeVtbl triangleVtbl = { Triangle_area, Triangle_print };

static void Triangle_init(Triangle *t, float u1, float v1, float u2, float v2,
                          float u3, float v3)
{
    t->base.vtbl = &triangleVtbl;
    t->x1 = u1, t->y1 = v1, t->x2 = u2, t->y2 = v2, t->x3 = u3, t->y3 = v3;
}

/* 도형의 종류를 모르고도 같은 코드로 처리한다. (다형성) */
static void shapeProc(const Shape *s)
{
    s->vtbl->print(s);
    printf("면적 = %g\n", s->vtbl->area(s));
}

static void practice3_polymorphism(void)
{
    Circle c;
    Triangle t;
    const Shape *shapes[2];
    int i;

    Circle_init(&c, 10.0f, 20.0f, 10.0f);
    Triangle_init(&t, 0.0f, 0.0f, 10.0f, 0.0f, 5.0f, 10.0f);

    shapes[0] = &c.base;
    shapes[1] = &t.base;
    for (i = 0; i < 2; i++)
        shapeProc(shapes[i]);
}

int main(void)
{
    printf("[실습 1] struct + 함수 방식\n");     practice1_struct_style();
    printf("\n[실습 2] 캡슐화\n");                practice2_encapsulation();
    printf("\n[실습 3] 상속과 다형성\n");         practice3_polymorphism();

    return 0;
}
