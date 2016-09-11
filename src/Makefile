# This is a pretty awful Makefile, please improve it!

test: tests/a.out tests/gtest/libgtest.a
	cd tests
	g++ -I../src -Lgtest Event.c++ -lgtest -lgtest_main -lpthread
	./a.out

gtest/libgtest.a:
	cd gtest
	cmake CMakeLists.txt
	make
