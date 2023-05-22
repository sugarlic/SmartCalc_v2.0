NAME = Project
CC = gcc -lstdc++
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SOURSES = Model/Model.cc Model/Parser.cc Controler/Controler.cc
OBJECT = $(patsubst %*.cc, %*.o,  ${SOURSES})
TEST_FLAGS =-lgtest -pthread

ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 ADD_LIB =
 TEST_FLAGS =-lgtest
endif
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
 ADD_LIB = -lgtest -lm -lrt -lpthread
 TEST_FLAGS =-lpthread -lgtest -pthread -lrt -lm
endif

all: install

install: uninstall
	@mkdir build
	cd View && qmake && make && make clean && rm Makefile && mv SmartCalc.app ../build
	cd build/SmartCalc.app/Contents/MacOS && ./SmartCalc

open:
	cd build/SmartCalc.app/Contents/MacOS && ./SmartCalc

uninstall:
	@rm -rf build

test: clean
	$(CC) Model/Model.cc Model/Parser.cc Model/GraphModel.cc Controler/Controler.cc Tests/NotationTests.cc -o unit-test -lgtest -Wall -Werror -Wextra
	./unit-test

test_linux: clean
	$(CC) Model/Model.cc Model/Parser.cc Model/GraphModel.cc Controler/Controler.cc Tests/NotationTests.cc -o unit-test $(TEST_FLAGS) -ggdb  -Wall -Werror -Wextra
	./unit-test

leaks:
	$(CC) Model/Model.cc Model/Parser.cc Model/GraphModel.cc Controler/Controler.cc Tests/NotationTests.cc -o unit-test -lgtest -Wall -Werror -Wextra
	CK_FORK=no leaks --atExit -- ./unit-test

gcov_report: clean 
	@gcc -lstdc++ --coverage -Wall -Werror -Wextra Model/Model.cc Model/Parser.cc Model/GraphModel.cc Controler/Controler.cc Tests/NotationTests.cc -o GcovReport -lm -lgtest
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d ./ --no-external
	@genhtml -o report GcovReport.info
	@open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./GcovReport.*

dvi:
	open readme.html

dist:
	rm -rf ../Archive_SmartCalc_v2.0/
	mkdir ../Archive_SmartCalc_v2.0/
	mkdir ../Archive_SmartCalc_v2.0/src
	cp build/SmartCalc.app/Contents/MacOS/SmartCalc ../Archive_SmartCalc_v2.0/src/
	cd .. && tar cvzf Archive_SmartCalc_v2.0.tgz ./Archive_SmartCalc_v2.0

cl:
	rm -rf ../Archive_SmartCalc_v2.0 2
	rm -rf ../Archive_SmartCalc_v2.0.tgz

clean:
	@rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda  ./*.info ./*.dSYM ./unit-test ./CPPLINT* report GcovReport
