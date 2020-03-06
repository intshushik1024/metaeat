all: work

work: meat.o  orders.o rtest.o reg.o hand.o
	gcc -lmysqlclient -lpcre -lfcgi -lssl -lcrypto `pkg-config --cflags --libs Magick++`  orders.o meat.o rtest.o reg.o hand.o -o work 

meat.o: meat.c
	gcc -lmysqlclient -lfcgi -lpcre -lssl -lcrypto -c meat.c

orders.o: orders.c
	gcc -lmysqlclient -lfcgi -c orders.c

rtest.o: rtest.c
	gcc -lpcre -c rtest.c

reg.o: reg.c
	gcc -lmysqlclient -lfcgi -lpcre -c -lssl -lcrypto `pkg-config --cflags --libs Magick++` reg.c

hand.o: hand.c
	gcc -lmysqlclient -lfcgi -lpcre -lssl -lcrypto -c hand.c

clean:
	rm -rf *.o work
