PRG=ff2spa
SRC=main.c
PREFIX?=/usr

SOUNDPIPE_INC=-lm -lsndfile -lsoundpipe
#SOUNDPIPE_INC=../Soundpipe/libsoundpipe.a -lm -lsndfile
ALSA_FLAGS=-lasound
JACK_FLAGS=-ljack -DHAVE_JACK
default:
	${CC} ${SRC} -o ${PRG}

watcher:
	${CC} watcher.c -o watcher

reader-alsa:
	${CC} reader.c ${SOUNDPIPE_INC} ${ALSA_FLAGS} -o reader

reader-jack:
	${CC} reader.c ${SOUNDPIPE_INC} ${JACK_FLAGS} -o reader

install:
	install ${PRG} ${PREFIX}/bin

strip:
	strip ${PRG}

clean:
	rm -f ${PRG} watcher reader
