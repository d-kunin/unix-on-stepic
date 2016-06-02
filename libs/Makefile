buildall: hello

hello: main.c hello.h libHello.so
	gcc main.c -fPIC -ldl -o hello


libHello.so: hello.h hello.c
	gcc -o libHello.so -shared -fPIC hello.c

clean:
	-rm hello libHello.so 2>/dev/null #minustoignore
