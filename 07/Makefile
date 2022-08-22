
decode.o : decode.c decode.h
	clang -c decode.c

loader.o : loader.c loader.h
	clang -c loader.c

parser.o : parser.c decode.h loader.h
	clang -c parser.c

parser : parser.o decode.o loader.o
	clang -o parser parser.o decode.o loader.o

all : parser