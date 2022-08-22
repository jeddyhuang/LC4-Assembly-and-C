
decode.o : decode.c decode.h
	clang -c decode.c

loader.o : loader.c loader.h
	clang -c loader.c

execute.o : execute.c decode.h execute.h
	clang -c execute.c

trace.o : trace.c decode.h loader.h execute.h
	clang -c trace.c

trace : trace.o execute.o decode.o loader.o
	clang -o trace trace.o execute.o decode.o loader.o

clean : 
	rm trace *.o 

all : trace