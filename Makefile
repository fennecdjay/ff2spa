PRG=ff2spa
SRC=main.c
PREFIX?=/usr

default:
	${CC} ${SRC} -o ${PRG}

install:
	install ${PRG} ${PREFIX}/bin

strip:
	strip ${PRG}

clean:
	rm -f ${PRG}
