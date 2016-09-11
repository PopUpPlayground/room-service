# This is a pretty awful Makefile, please improve it!

test: a.out gtest/libgtest.a
	g++ -Lgtest Event.c++ -lgtest -lgtest_main -lpthread
	./a.out

gtest/libgtest.a:
	cd gtest
	cmake CMakeLists.txt
	make
