GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so
CFLAGS = -Wall
LD_LIBRARY_PATH = .

all: README prog prog-a prog-so

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
		cc -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
		cc -L. $< -loutput -o $@

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