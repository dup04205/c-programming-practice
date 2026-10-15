# C 프로그래밍 실습 빌드 스크립트
#
#   make            전체 실습 파일을 build/ 에 빌드한다.
#   make run        전체 실습 파일을 순서대로 실행한다.
#   make run N=05   5강 실습만 실행한다. (필요하면 먼저 빌드한다.)
#   make clean      빌드 결과물을 삭제한다.

CC      ?= gcc
CXX     ?= g++
CFLAGS  ?= -std=c11 -Wall -Wextra -pedantic -O0 -g
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0 -g
LDLIBS  = -lm

SRCS    := $(sort $(wildcard src/lec*.c))
BINS    := $(patsubst src/%.c,build/%,$(SRCS))
CPPBIN  := build/lec15_cpp_overview_cpp

.PHONY: all run clean
all: $(BINS) $(CPPBIN)

build:
	mkdir -p build

build/%: src/%.c | build
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

$(CPPBIN): src/lec15_cpp_overview.cpp | build
	$(CXX) $(CXXFLAGS) -o $@ $<

ifdef N
run: $(filter build/lec$(N)_%,$(BINS))
	@for b in $(filter build/lec$(N)_%,$(BINS)); do \
	  echo "===== $$b ====="; ./$$b; \
	done
else
run: all
	@for b in $(BINS) $(CPPBIN); do \
	  echo ""; echo "===== $$b ====="; ./$$b || exit 1; \
	done
endif

clean:
	rm -rf build
