
stack.o : stack.c stack.h
	clang -c stack.c

token.o : token.c token.h
	clang -c token.c

tokenwriter.o : tokenwriter.c tokenwriter.h stack.h token.h
	clang -c tokenwriter.c

jcompiler.o : jcompiler.c tokenwriter.h token.h
	clang -c jcompiler.c

jc : stack.o token.o tokenwriter.o jcompiler.o
	clang -o jc stack.o token.o tokenwriter.o jcompiler.o

clean : 
	rm jc *.o 

all : jc