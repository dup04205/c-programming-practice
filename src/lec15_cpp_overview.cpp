/*
 * 15강. C++ 언어의 개요 (원본 C++ 예제)
 *
 * lec15_cpp_overview.c 의 C 구현과 비교하기 위한 C++ 버전이다.
 * 클래스, 캡슐화(private/public), 상속, 가상 함수를 이용한 다형성을 확인한다.
 *
 * 빌드: g++ -std=c++17 -Wall -Wextra -o lec15_cpp_overview lec15_cpp_overview.cpp
 */

#include <iostream>
using namespace std;

/* 실습 1. 클래스와 객체: 데이터와 처리 함수를 하나로 묶고 내부를 감춘다. */
class CircleBasic {
    float cx, cy, radius;               // 비공개: 내부 구현
public:                                 // 공개: 외부 인터페이스
    void init(float x, float y, float r) {
        cx = x, cy = y, radius = r;
    }
    float area() const {
        return 3.141592f * radius * radius;
    }
    void print() const {
        cout << "원: 중심 = (" << cx << ", " << cy << ")";
        cout << ", 반경 = " << radius << endl;
    }
};

/* 실습 2. 상속과 다형성 */
class Shape {
public:
    virtual float area() const = 0;
    virtual void print() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    float cx, cy, radius;
public:
    void init(float x, float y, float r) {
        cx = x, cy = y, radius = r;
    }
    float area() const override {
        return 3.141592f * radius * radius;
    }
    void print() const override {
        cout << "원: 중심 = (" << cx << ", " << cy << ")";
        cout << ", 반경 = " << radius << endl;
    }
};

class Triangle : public Shape {
    float x1, y1, x2, y2, x3, y3;
public:
    void init(float u1, float v1, float u2, float v2,
              float u3, float v3) {
        x1 = u1, y1 = v1, x2 = u2, y2 = v2, x3 = u3, y3 = v3;
    }
    float area() const override {
        float a = x1 * y2 + x2 * y3 + x3 * y1;
        a -= x2 * y1 + x3 * y2 + x1 * y3;
        return (a >= 0 ? a : -a) / 2.0f;
    }
    void print() const override {
        cout << "삼각형: (" << x1 << ", " << y1 << ") - ("
             << x2 << ", " << y2 << ") - (" << x3 << ", " << y3 << ")" << endl;
    }
};

void shapeProc(Shape& s) {
    s.print();
    cout << "면적 = " << s.area() << endl;
}

int main() {
    cout << "[실습 1] 클래스와 객체" << endl;
    CircleBasic cb;
    cb.init(10.0f, 20.0f, 10.0f);
    cb.print();
    cout << "면적 = " << cb.area() << endl;

    cout << "\n[실습 2] 상속과 다형성" << endl;
    Circle c;
    Triangle t;
    c.init(10.0f, 20.0f, 10.0f);
    t.init(0.0f, 0.0f, 10.0f, 0.0f, 5.0f, 10.0f);
    shapeProc(c);
    shapeProc(t);
    return 0;
}
