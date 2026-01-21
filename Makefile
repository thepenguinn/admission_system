run: adm
	./adm

adm: libadm.o
	gcc -o adm libadm.o

adm.o: libadm.h libadm.c
	gcc -c libadm.c

.PHONY: run
