
stack.o : stack.c stack.h
	clang -c stack.c

rpn.o : rpn.c stack.h
	clang -c rpn.c

rpn : rpn.o stack.o
	clang -o rpn rpn.o stack.o

all : rpn