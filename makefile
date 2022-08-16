# compile everything with some good flags
CXXFLAGS := -std=c++17 -g -O2 -Wall -Wshadow -Wextra \
		-Wformat=2 -fsanitize=address -fsanitize=undefined \
		-fno-sanitize-recover -Wfatal-errors \
		-Wno-unused-variable
all: $(patsubst %.cpp, %, $(wildcard *))
%: %.cpp
	g++ $(CXXFLAGS) $*.cpp -o $*