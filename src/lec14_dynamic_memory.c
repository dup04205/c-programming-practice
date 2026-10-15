/*
 * 14강. 메모리 동적 할당
 *
 * 실습 목표
 *   - 데이터/스택/힙 영역의 차이를 주소 출력으로 확인한다.
 *   - malloc, calloc, realloc, free를 확인한다.
 *   - memcmp, memcpy, memset을 확인한다.
 *
 * 규칙
 *   - 할당 결과는 반드시 NULL 여부를 검사한다.
 *   - 할당한 공간은 사용이 끝나면 free로 반환한다.
 *   - free한 포인터는 NULL로 바꾸어 이중 해제를 방지한다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gVar = 10;      /* 데이터 영역 */

/* 실습 1. 메모리 영역별 주소 비교 */
static void practice1_memory_areas(void)
{
    int local = 5;                      /* 스택 영역 */
    int *heap = malloc(sizeof(int));    /* 힙 영역 */

    if (heap == NULL) {
        puts("기억 공간 할당 실패!");
        exit(1);
    }
    printf("전역 변수 gVar 주소   : %p (데이터 영역)\n", (void *)&gVar);
    printf("지역 변수 local 주소  : %p (스택 영역)\n", (void *)&local);
    printf("malloc 반환 주소      : %p (힙 영역)\n", (void *)heap);
    free(heap);
}

/* 실습 2. malloc: int 하나를 힙에 할당 */
static void practice2_malloc(void)
{
    int *a = malloc(sizeof(int));

    if (a == NULL) {
        puts("기억 공간 할당 실패!");
        exit(1);
    }
    *a = 20;
    printf("힙에 저장된 값: %d\n", *a);
    free(a);
    a = NULL;
}

/* 실습 3. malloc: 실행 시점에 크기가 정해지는 문자열 */
static void practice3_malloc_string(void)
{
    int size = 20;      /* 원본: 키보드로 입력받는 값 */
    char *str = malloc((size_t)size + 1);   /* 널 문자 공간 1byte 추가 */

    if (str == NULL) {
        puts("기억 공간 할당 실패!");
        exit(1);
    }
    strcpy(str, "KNOU");
    printf("동적 할당된 메모리에 저장된 문자열: %s (할당 크기 %d byte)\n", str, size + 1);
    free(str);
}

/* 실습 4. 동적 배열: 입력 개수만큼 할당하여 합계/평균 계산 */
static void practice4_dynamic_array(void)
{
    int n = 6, i;
    int *arr = malloc(sizeof(int) * (size_t)n);
    int sum = 0;

    if (arr == NULL) {
        puts("기억 공간 할당 실패!");
        exit(1);
    }
    for (i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
        sum += arr[i];
    }
    printf("동적 배열 합계 = %d, 평균 = %.2f\n", sum, sum / (double)n);
    free(arr);
}

/* 실습 5. calloc: 0으로 초기화된 공간 할당 */
static void practice5_calloc(void)
{
    int i;
    int *a = calloc(5, sizeof(int));

    if (a == NULL) {
        puts("기억 공간 할당 실패!");
        exit(1);
    }
    printf("calloc 직후:");
    for (i = 0; i < 5; i++)
        printf(" %d", a[i]);
    printf("\n");
    free(a);
}

/* 실습 6. realloc: 이미 할당한 공간의 크기 변경 */
static void practice6_realloc(void)
{
    int i;
    int *p = malloc(sizeof(int) * 3);
    int *tmp;

    if (p == NULL) {
        puts("기억 공간 할당 실패!");
        exit(1);
    }
    for (i = 0; i < 3; i++)
        p[i] = i + 1;

    /* 다른 위치에 할당될 수 있으므로 임시 포인터로 받고 성공했을 때만 p를 바꾼다. */
    tmp = realloc(p, sizeof(int) * 6);
    if (tmp == NULL) {
        puts("공간 확장 실패!");
        free(p);
        exit(1);
    }
    p = tmp;
    for (i = 3; i < 6; i++)
        p[i] = (i + 1) * 100;

    printf("realloc 후:");
    for (i = 0; i < 6; i++)
        printf(" %d", p[i]);
    printf("\n");
    free(p);
}

/* 실습 7. 2차원 동적 배열: 행마다 따로 할당 */
static void practice7_dynamic_2d(void)
{
    int rows = 3, cols = 4, i, j;
    int **m = malloc(sizeof(int *) * (size_t)rows);

    if (m == NULL) {
        puts("기억 공간 할당 실패!");
        exit(1);
    }
    for (i = 0; i < rows; i++) {
        m[i] = calloc((size_t)cols, sizeof(int));
        if (m[i] == NULL) {
            puts("기억 공간 할당 실패!");
            exit(1);
        }
        for (j = 0; j < cols; j++)
            m[i][j] = i * cols + j;
    }
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            printf("%3d", m[i][j]);
        printf("\n");
    }
    for (i = 0; i < rows; i++)
        free(m[i]);         /* 할당한 순서의 반대로 해제한다. */
    free(m);
}

/* 실습 8. 기억공간 관리 함수 */
static void practice8_mem_functions(void)
{
    char *s1 = "aaa";
    char *s2 = "bbb";
    int cmp;
    char src[] = "1234567890";
    char dest[] = "abcdefghijklmnopqrstuvwxyz";
    char fill[] = "1234567890";

    /* memcmp: 두 영역을 바이트 단위로 비교. 반환값은 부호만 의미가 있다. */
    cmp = memcmp(s1, s2, 3);
    printf("memcmp(\"aaa\", \"bbb\", 3) 부호 = %d\n", (cmp > 0) - (cmp < 0));
    cmp = memcmp(s2, s1, 3);
    printf("memcmp(\"bbb\", \"aaa\", 3) 부호 = %d\n", (cmp > 0) - (cmp < 0));
    cmp = memcmp(s1, s1, 3);
    printf("memcmp(\"aaa\", \"aaa\", 3) 부호 = %d\n", (cmp > 0) - (cmp < 0));

    /* memcpy: n byte 복사 (영역이 겹치면 memmove를 사용한다.) */
    printf("src의 데이터: %s\n", src);
    printf("dest의 데이터: %s\n", dest);
    printf("복사 후 dest의 데이터: %s\n", (char *)memcpy(dest, src, strlen(src)));

    /* memset: n byte를 같은 값으로 채움 */
    printf("fill의 데이터 : %s\n", fill);
    memset(fill, '*', strlen(fill));
    printf("memset() 실행 후 fill의 데이터: %s\n", fill);
}

int main(void)
{
    printf("[실습 1] 메모리 영역\n");        practice1_memory_areas();
    printf("\n[실습 2] malloc\n");           practice2_malloc();
    printf("\n[실습 3] malloc 문자열\n");    practice3_malloc_string();
    printf("\n[실습 4] 동적 배열\n");        practice4_dynamic_array();
    printf("\n[실습 5] calloc\n");           practice5_calloc();
    printf("\n[실습 6] realloc\n");          practice6_realloc();
    printf("\n[실습 7] 2차원 동적 배열\n");  practice7_dynamic_2d();
    printf("\n[실습 8] mem 함수\n");         practice8_mem_functions();

    return 0;
}
