PREFIX 	?= out

INCDIRS := 	include \
			.

INCLUDE := 	$(patsubst %, -I%, $(INCDIRS))

.PHONY: all clean poor_udp poor_tcp

all: poor_udp

poor_udp: poor_dgram_cl.o poor_dgram_sv.o
	gcc -Wall -O2 -o $(PREFIX)/client $(PREFIX)/poor_dgram_cl.o
	gcc -Wall -O2 -o $(PREFIX)/server $(PREFIX)/poor_dgram_sv.o 

poor_tcp: poor_stream_sv.o read_line.o
	gcc -Wall -O2 -o $(PREFIX)/server $(PREFIX)/poor_stream_sv.o $(PREFIX)/read_line.o

%.o : %.c
	gcc -Wall -O2 -c $(INCLUDE) -o $(PREFIX)/$@ $^


clean:
	rm -rf out/*