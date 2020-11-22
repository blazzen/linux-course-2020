GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so *.txt prog-test
CFLAGS = -Wall
LD_LIBRARY_PATH = .

all: README prog prog-a prog-so test

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
		cc -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
		cc -L. $< -loutput -o $@

test: prog prog-a prog-so
		cp -f prog prog-test
		./prog-test 2> prog.txt
		./prog-test p1 >> prog.txt
		./prog-test p1 p2 p3 >> prog.txt

		cp -f prog-a prog-test
		./prog-test 2> prog-a.txt
		./prog-test p1 >> prog-a.txt
		./prog-test p1 p2 p3 >> prog-a.txt
		
		cp -f prog-so prog-test
		./prog-test 2> prog-so.txt
		./prog-test p1 >> prog-so.txt
		./prog-test p1 p2 p3 >> prog-so.txt

		cmp prog.txt prog-a.txt
		cmp prog.txt prog-so.txt
		cmp prog-a.txt prog-so.txt

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