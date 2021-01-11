all: a.out

a.out:
		cc `pkg-config --cflags glib-2.0` glibc-hash.c `pkg-config --libs glib-2.0`

clean:
		rm -f a.out

