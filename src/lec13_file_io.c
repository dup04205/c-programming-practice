/*
 * 13강. 파일 처리 함수
 *
 * 실습 목표
 *   - fopen/fclose와 파일 사용 모드를 확인한다.
 *   - 문자 단위(fputc/fgetc), 형식화(fprintf/fscanf) 순차 파일 처리를 확인한다.
 *   - 이진 파일의 랜덤 접근(fwrite/fread/fseek)을 확인한다.
 *
 * 실습에서 만드는 파일(sample.txt, sample3.txt, sample5.dat)은
 * 현재 디렉터리에 생성되고, 프로그램이 끝나기 전에 remove()로 삭제한다.
 *
 * 원본 예제와 다른 점
 *   - 키보드 입력(fscanf(stdin, ...), gets) 대신 배열에 준비한 값을 사용하였다.
 *   - gets()는 C11 표준에서 삭제되었으므로 사용하지 않았다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REC_SIZE 10         /* 레코드 한 건의 크기(byte) */
#define NREC 5

/* 파일 개방에 실패하면 메시지를 출력하고 종료하는 보조 함수 */
static FILE *open_or_exit(const char *path, const char *mode)
{
    FILE *fp = fopen(path, mode);

    if (fp == NULL) {
        fprintf(stderr, "파일을 개방할 수 없습니다: %s\n", path);
        exit(EXIT_FAILURE);
    }
    return fp;
}

/* 실습 1. 문자 단위 출력: A~Z를 파일에 저장 */
static void practice1_fputc(void)
{
    char ch;
    FILE *fp = open_or_exit("sample.txt", "w");

    for (ch = 'A'; ch <= 'Z'; ch++)
        fputc(ch, fp);
    fclose(fp);
    printf("sample.txt 에 A~Z 를 저장하였다.\n");
}

/* 실습 2. 문자 단위 입력: 저장한 파일을 처음부터 끝까지 읽기 */
static void practice2_fgetc(void)
{
    int ch;
    FILE *fp = open_or_exit("sample.txt", "r");

    printf("읽은 내용: ");
    while ((ch = fgetc(fp)) != EOF)         /* EOF 비교를 위해 int로 받는다. */
        putchar(ch);
    putchar('\n');
    fclose(fp);
}

/* 실습 3. 형식화 출력: 성적 레코드를 텍스트 파일로 저장 */
static void practice3_fprintf(void)
{
    const char *no[NREC]   = { "25001", "25002", "25003", "25004", "25005" };
    const char *name[NREC] = { "KIM_HG", "PARK_SY", "LEE_SY", "CHOI_DS", "KIM_HS" };
    int score[NREC][4] = { {29, 28, 30, 10}, {20, 20, 25, 10}, {25, 20, 20, 10},
                           {23, 25, 26, 10}, {28, 23, 25, 10} };
    int i;
    FILE *fp = open_or_exit("sample3.txt", "w");

    fprintf(stdout, "학번 이름 중간 기말 리포트 출석 (저장 중)\n");
    for (i = 0; i < NREC; ++i)
        fprintf(fp, "%-10s %-8s %3d %3d %3d %3d\n",
                no[i], name[i], score[i][0], score[i][1], score[i][2], score[i][3]);
    fclose(fp);
}

/* 실습 4. 형식화 입력: 텍스트 파일을 읽어 총점 계산 */
static void practice4_fscanf(void)
{
    char no[10], name[10];
    int mid, term, rep, att;
    FILE *fp = open_or_exit("sample3.txt", "r");

    printf("학번       이름       총점\n");
    while (fscanf(fp, "%9s %9s %d %d %d %d", no, name, &mid, &term, &rep, &att) == 6)
        printf("%-10s %-8s %4d\n", no, name, mid + term + rep + att);
    fclose(fp);
}

/* 실습 5. 이진 파일의 랜덤 접근 */
static void practice5_random_access(void)
{
    const char *names[NREC] = { "KIM HG", "PARK SY", "LEE SY", "CHOI DS", "KIM HS" };
    char name[REC_SIZE];
    int i;
    FILE *fp = open_or_exit("sample5.dat", "wb");

    /* 레코드를 10byte 고정 길이로 저장한다. */
    for (i = 0; i < NREC; i++) {
        memset(name, 0, sizeof(name));
        strncpy(name, names[i], REC_SIZE - 1);
        fwrite(name, REC_SIZE, 1, fp);
    }
    fclose(fp);

    fp = open_or_exit("sample5.dat", "rb");

    /* 3번 레코드(0부터 시작)로 이동: 파일 처음에서 3 * REC_SIZE */
    fseek(fp, (long)REC_SIZE * 3, SEEK_SET);
    if (fread(name, REC_SIZE, 1, fp) == 1)
        printf("3번 레코드: %s\n", name);
    else
        printf("Seek error!\n");

    /* 현재 위치(4번 레코드 앞)에서 2레코드 앞으로 이동 -> 2번 레코드 */
    fseek(fp, -2L * REC_SIZE, SEEK_CUR);
    if (fread(name, REC_SIZE, 1, fp) == 1)
        printf("2번 레코드: %s\n", name);
    else
        printf("Seek error!\n");

    /* 파일 끝 기준으로 마지막 레코드 읽기 */
    fseek(fp, -1L * REC_SIZE, SEEK_END);
    if (fread(name, REC_SIZE, 1, fp) == 1)
        printf("마지막 레코드: %s\n", name);

    /* 파일 크기 = 끝으로 이동한 뒤 ftell */
    fseek(fp, 0, SEEK_END);
    printf("파일 크기 = %ld byte, 레코드 수 = %ld\n", ftell(fp), ftell(fp) / REC_SIZE);

    /* 범위를 벗어난 레코드는 읽기에 실패한다. */
    fseek(fp, (long)REC_SIZE * 10, SEEK_SET);
    if (fread(name, REC_SIZE, 1, fp) != 1)
        printf("10번 레코드: 읽기 실패(범위 밖)\n");
    fclose(fp);
}

/* 실습 6. 정수 배열을 이진 파일로 저장하고 다시 읽기 */
static void practice6_fwrite_array(void)
{
    int out[8] = { 1, 1, 2, 3, 5, 8, 13, 21 };
    int in[8] = { 0 };
    size_t n, i;
    FILE *fp = open_or_exit("sample6.dat", "wb");

    fwrite(out, sizeof(int), 8, fp);
    fclose(fp);

    fp = open_or_exit("sample6.dat", "rb");
    n = fread(in, sizeof(int), 8, fp);
    fclose(fp);

    printf("읽은 개수 = %zu, 값 =", n);
    for (i = 0; i < n; i++)
        printf(" %d", in[i]);
    printf("\n");
}

int main(void)
{
    printf("[실습 1] fputc\n");             practice1_fputc();
    printf("\n[실습 2] fgetc\n");           practice2_fgetc();
    printf("\n[실습 3] fprintf\n");         practice3_fprintf();
    printf("\n[실습 4] fscanf\n");          practice4_fscanf();
    printf("\n[실습 5] fseek 랜덤 접근\n"); practice5_random_access();
    printf("\n[실습 6] fwrite/fread 배열\n"); practice6_fwrite_array();

    /* 실습 중 생성한 파일 삭제 */
    remove("sample.txt");
    remove("sample3.txt");
    remove("sample5.dat");
    remove("sample6.dat");

    return 0;
}
