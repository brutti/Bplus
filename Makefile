FLAGS=-Wall
BINEXEC=a.out

All: ${BINEXEC}

${BINEXEC}: b_plus.o main.c
		gcc main.c b_plus.o ${FLAGS}

arv.o: arv.c
	gcc -c b_plus.c ${FLAGS}

clean:
	rm -f *.o rank.txt ${BINEXEC}
