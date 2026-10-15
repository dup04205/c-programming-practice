/*
 * 03강. 입출력 함수와 연산자 (1)
 *
 * 실습 목표
 *   - main 함수의 명령행 인수(argc, argv)를 확인한다.
 *   - printf의 출력 변환 기호와 출력 양식 편집을 확인한다.
 *   - scanf의 입력 변환 기호를 확인한다.
 *   - getchar/putchar, fgets/puts 등 기타 입출력 함수를 확인한다.
 *
 * 실행 방법
 *   ./lec03_io_operators1              고정된 값으로 모든 실습을 실행한다.
 *   ./lec03_io_operators1 KNOU         명령행 인수를 이용해 인사말을 출력한다.
 *   ./lec03_io_operators1 -i           키보드 입력을 받는 대화형 실습을 실행한다.
 *
 * 원본 예제와 다른 점
 *   - 키보드 입력 대신 sscanf로 문자열에서 값을 읽어 실행 결과를 고정하였다.
 *   - gets()는 C11 표준에서 삭제되었으므로 fgets()로 대체하였다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 실습 1. 명령행 인수 */
static void practice1_args(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "-i") != 0)
        printf("Hello, %s!\n", argv[1]);
    else
        printf("Hello, KNOU!   (명령행 인수가 없으면 기본값을 사용한다)\n");
}

/* 실습 2. printf 기본 출력과 변환 기호 */
static void practice2_printf_basic(void)
{
    char c = 'A';
    int i = 10, j = 20, k = 30;

    printf("간단한 출력 프로그램\n");
    printf("'%c'의 ASCII 코드값은 %d\n", c, c);
    printf("i=%d, j=%d, k=%d\n", i, j, k);

    printf("\n[정수: 10진수, 16진수, 8진수]\n");
    printf("%d\n", 0x10);
    printf("%x\n", 125);
    printf("%X\n", 125);
    printf("%o\n", 125);

    printf("\n[문자와 문자열]\n");
    printf("%c\n", 'A');
    printf("%c\n", 0x42);
    printf("%s\n", "KNOU");
    printf("%s\n", "ab\0cd");     /* 널 문자(\0)에서 출력이 멈춘다. */

    printf("\n[실수]\n");
    printf("%f\n", 12.34f);
    printf("%f\n", 31.4e-1);
    printf("%e\n", 123.45678);
    printf("%E\n", 12.345678e-6);
    printf("%g\n", 123.45678);
    printf("%g\n", 12.345678e-6);
}

/* 실습 3. 출력 양식의 편집 (부호, 폭, 정렬, 정밀도) */
static void practice3_printf_format(void)
{
    printf("|%d|\n", -123);
    printf("|% d|\n", 123);
    printf("|%+2d|\n", 123);
    printf("|%5d|\n", 123);
    printf("|%-5d|\n", 123);
    printf("|%+5d|\n", 123);
    printf("|%+05d|\n", 123);

    printf("\n");
    printf("|%10f|\n", 123.456);
    printf("|%10.1f|\n", 123.456);
    printf("|% 10.4e|\n", 123.456);
    printf("|%+10.4e|\n", -123.456);
    printf("|%10.4g|\n", 123.456);
}

/* 실습 4. scanf의 입력 변환 기호 (sscanf로 대신 확인) */
static void practice4_scanf_basic(void)
{
    int a;
    short b;
    unsigned long long c;
    float f;
    double d;
    char ch;
    char str[100];

    /* %d: 10진 정수, %hi: 접두어(0x)에 따라 진법을 판단하는 short, %llx: 16진 long long */
    sscanf("10", "%d", &a);
    sscanf("0x20", "%hi", &b);
    sscanf("30", "%llx", &c);
    printf("%d %d %llu\n", a, b, c);

    sscanf("1.23 45.9e-4", "%f %lf", &f, &d);
    printf("%f %e\n", f, d);

    /* 입력 양식에 쉼표를 넣으면 입력에서도 쉼표를 맞추어야 한다. */
    sscanf("1.23, 45.9e-4", "%f, %lf", &f, &d);
    printf("%f %e\n", f, d);

    /* %c는 한 문자, %s는 공백 전까지의 문자열을 읽는다. */
    sscanf("A Computer Science", "%c%s", &ch, str);
    printf("%c %s\n", ch, str);
}

/* 실습 5. 기타 입출력 함수 (고정 값 버전) */
static void practice5_char_string_io(void)
{
    char c = 'A';
    char str[100] = "Computer Science";

    printf("입력한 문자 = ");
    putchar(c);
    putchar('\n');

    printf("입력한 문자열 = ");
    puts(str);      /* puts는 출력 후 줄바꿈을 자동으로 넣는다. */
    puts("KNOU");
}

/* 대화형 실습: 키보드로 직접 입력한다. */
static void practice_interactive(void)
{
    int a;
    char c;
    char str[100];
    int ch;

    printf("정수 하나를 입력하세요: ");
    if (scanf("%d", &a) == 1)
        printf("입력한 정수 = %d\n", a);

    /* 입력 버퍼에 남은 줄바꿈까지 비운다. */
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    printf("문자 하나를 입력하세요: ");
    c = (char)getchar();
    printf("입력한 문자 = ");
    putchar(c);
    putchar('\n');

    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    printf("문자열을 입력하세요: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        printf("입력한 문자열 = ");
        puts(str);
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "-i") == 0) {
        practice_interactive();
        return EXIT_SUCCESS;
    }

    printf("[실습 1] 명령행 인수\n");
    practice1_args(argc, argv);

    printf("\n[실습 2] printf 기본 출력\n");
    practice2_printf_basic();

    printf("\n[실습 3] 출력 양식의 편집\n");
    practice3_printf_format();

    printf("\n[실습 4] scanf 입력 변환 기호\n");
    practice4_scanf_basic();

    printf("\n[실습 5] 문자/문자열 입출력\n");
    practice5_char_string_io();

    return EXIT_SUCCESS;
}
