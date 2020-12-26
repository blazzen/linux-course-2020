GENERATES = *.so temp tempFIXtemp

all: wrapper.so

wrapper.so: wrapper.c
		cc -shared -fPIC wrapper.c -ldl -o wrapper.so

test-real: wrapper.so
		touch temp
		touch tempFIXtemp

		rm -f temp
		rm -f tempFIXtemp

		if [ -e temp ]; then echo "FAILED"; else echo "PASSED"; fi 
		if [ -e tempFIXtemp ]; then echo "FAILED"; else echo "PASSED"; fi

test-wrapped: wrapper.so
		touch temp
		touch tempFIXtemp

		LD_PRELOAD=`pwd`/wrapper.so rm -f temp
		LD_PRELOAD=`pwd`/wrapper.so rm -f tempFIXtemp || true

		if [ -e temp ]; then echo "FAILED"; else echo "PASSED"; fi
		if [ -e tempFIXtemp ]; then echo "PASSED"; else echo "FAILED"; fi

test: test-real test-wrapped

clean:
	rm -f $(GENERATES)
