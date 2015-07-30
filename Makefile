#libdata.dylib:	include/utils.h include/data.h src/utils.c src/data.c
#	gcc -dynamiclib -o libdata.dylib -fPIC -I./include/ -dy src/utils.c src/data.c
all: client server stream

stream:	include/utils.h include/data.h include/hyper-socket.h libdata.so src/stream.c
	gcc -o stream -I./include/ -L. -ldata src/stream.c
server:	include/utils.h include/data.h include/hyper-socket.h libdata.so src/server.c
	gcc -o server -I./include/ -L. -ldata src/server.c
client:	include/utils.h include/hyper-socket.h libdata.so src/client.c
	gcc -o client -I./include -L. -ldata src/client.c
libdata.so:	include/utils.h include/data.h include/hyper-socket.h src/utils.c src/data.c src/hyper-socket.c
	gcc -shared -o libdata.so -fPIC -I./include/ src/utils.c src/hyper-socket.c src/data.c
clean:
	rm -f libdata.so client server stream
