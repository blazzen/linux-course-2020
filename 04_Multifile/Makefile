GENERATES = prog README liboutput_static.a liboutput.so
TRASH = *.o *~ o.*
CFLAGS = -Wall

all: README prog liboutput_static.a liboutput.so

prog: const.o fun.o prog.o

liboutput_static.a: fun.o const.o
		ar -rcs $@ $^

liboutput.so: fun.o const.o
		cc -shared $^ -o $@

README: prog
		./$< 2> $@

fun.o: outlib.h

clean:
		rm -f $(TRASH)

distclean: clean
		rm -rf $(GENERATES)