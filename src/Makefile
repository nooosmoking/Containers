GCC = g++
LDFLAGS = -c 
CFLAGS  = -g -std=c++17
TEST_SOURCE := $(shell find . -iname "*.cc" )
HEADER_SOURCE := $(shell find . -iname "*.h" )

ifeq ($(shell uname -s),Darwin)
	TEST_FLAGS = -lgtest -lpthread --coverage
else
	TEST_FLAGS = -lgtest -lpthread --coverage -lrt -lsubunit  
endif

all: clean test

test: ${TEST_SOURCE} ${HEADER_SOURCE}
	$(GCC) $(CFLAGS) $^ -o $@ $(TEST_FLAGS) 
	./$@


format: ${SOURCE} ${HEADER_SOURCE} ${TEST_SOURCE} 
	cp .././materials/linters/.clang-format .
	clang-format -i -style=google $^;
	rm .clang-format

clean: 
	rm -rf *.o 
	rm -rf *.gcno
	rm -rf *.a
	rm -rf *.gcda
	rm -rf *.info
	rm -rf *.gcov
	rm -rf *gch
	rm -rf ./tests/*gch
	rm -rf test
	rm -rf ./report
	rm -rf valgrind_log.txt
	rm -rf test.dSym
	rm -rf map/test.gcno
