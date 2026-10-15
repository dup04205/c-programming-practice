# C 프로그래밍 실습

한국방송통신대학교 컴퓨터과학과 「C 프로그래밍」 강의 1~15강의 예제를 직접 실행하며 학습할 수 있도록 회차별 실습 파일로 정리한 저장소이다.
각 파일은 여러 개의 `practiceN_...` 함수로 나뉘어 있고, `main`이 순서대로 호출하여 결과를 출력한다.

## 실습 목록

| 회차 | 주제 | 파일 | 핵심 내용 |
|---|---|---|---|
| 01 | C 언어의 개요 | `src/lec01_overview.c` | 프로그램 구조, 명칭 규칙, 주석, 에러/경고 |
| 02 | 자료형과 선행 처리기 | `src/lec02_datatype_preprocessor.c` | 자료형 범위, enum, 오버플로, 유효범위, 매크로, 조건부 컴파일 |
| 03 | 입출력 함수와 연산자 (1) | `src/lec03_io_operators1.c` | argc/argv, printf/scanf 변환 기호, getchar/putchar, puts |
| 04 | 입출력 함수와 연산자 (2) | `src/lec04_io_operators2.c` | 산술/증감/관계/논리/비트 연산자, 형변환 |
| 05 | 선택 제어문과 반복 제어문 | `src/lec05_control_flow.c` | if, switch, for, while, do-while, break, continue, goto |
| 06 | 함수와 기억 클래스 (1) | `src/lec06_function1.c` | 표준 함수, 사용자 정의 함수, 함수 원형 |
| 07 | 함수와 기억 클래스 (2) | `src/lec07_function2_storage.c` | 값/주소 전달, 유효범위, auto/static/extern/register |
| 08 | 배열과 포인터 (1) | `src/lec08_array_pointer1.c` | 1~3차원 배열, 문자열, 배열 인수 전달 |
| 09 | 배열과 포인터 (2) | `src/lec09_array_pointer2.c` | 포인터 선언/참조, void 포인터, 포인터 연산 |
| 10 | 배열과 포인터 (3) | `src/lec10_array_pointer3.c` | 포인터와 배열, 포인터 배열, 이중 포인터 |
| 11 | 구조체와 공용체 (1) | `src/lec11_struct_union1.c` | 구조체 정의, typedef, 구조체 배열/포인터, 패딩 |
| 12 | 구조체와 공용체 (2) | `src/lec12_struct_union2.c` | 구조체 인수/반환, 비트필드, 공용체 |
| 13 | 파일 처리 함수 | `src/lec13_file_io.c` | fopen/fclose, fputc/fgetc, fprintf/fscanf, fwrite/fread/fseek |
| 14 | 메모리 동적 할당 | `src/lec14_dynamic_memory.c` | malloc/calloc/realloc/free, memcmp/memcpy/memset |
| 15 | C++ 언어의 개요 | `src/lec15_cpp_overview.c` | 클래스/캡슐화/상속/다형성을 C로 구현 |
| 15 | (비교용 원본) | `src/lec15_cpp_overview.cpp` | 위 내용의 C++ 버전 |

## 빌드와 실행

gcc(C11 이상)와 make가 필요하다. 수학 함수(`sqrt`, `pow` 등)를 쓰는 실습이 있어 `-lm`으로 링크한다.

```bash
make                  # 전체 빌드 (결과물: build/)
make run              # 전체 실행
make run N=05         # 5강만 실행
make clean            # 빌드 결과물 삭제
```

make 없이 한 파일만 빌드할 때는 다음과 같이 한다.

```bash
gcc -std=c11 -Wall -Wextra -o lec05 src/lec05_control_flow.c -lm
./lec05
```

3강은 인수에 따라 동작이 달라진다.

```bash
./build/lec03_io_operators1 KNOU     # 명령행 인수 확인
./build/lec03_io_operators1 -i       # 키보드 입력을 받는 대화형 실습
```

## 강의 예제와 다른 점

- 키보드 입력(`scanf`, `gets`)을 쓰는 예제는 실행 결과가 매번 같도록 값을 코드에 고정하거나 `sscanf`로 대체하였다.
- `gets()`는 C11에서 삭제되었으므로 `fgets()`를 사용하였다. `getch()`는 비표준 함수이므로 제거하였다.
- 4강의 `a = ++x * x--;`처럼 한 식에서 같은 변수를 두 번 변경하는 코드는 결과가 정해져 있지 않아, 전위/후위 연산을 문장으로 나누어 확인하도록 바꾸었다.
- 초기화하지 않은 변수나 포인터를 사용하는 잘못된 예제(2강, 9강)는 실행하지 않고 주석으로 설명만 남겼다.
- 비트필드(12강)와 공용체의 값 해석은 컴파일러와 CPU 구조에 따라 달라진다. 출력은 gcc, x86-64(리틀 엔디안) 기준이다.
- 13강의 실습 파일(`sample*.txt`, `sample*.dat`)은 실행 중에 만들어지고 종료 전에 삭제된다.
- 15강은 C++ 강의이지만 `.c` 요청에 맞추어 구조체와 함수 포인터로 클래스·상속·다형성을 구현하였고, 비교용으로 원본 C++ 예제를 함께 두었다.

## 검증

모든 파일은 `-std=c11 -Wall -Wextra -pedantic` 옵션에서 경고 없이 컴파일되며, AddressSanitizer와 UndefinedBehaviorSanitizer를 켠 상태에서도 오류 없이 실행된다.
