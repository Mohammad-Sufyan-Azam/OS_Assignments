all: socket fifo msgque

msgque: msgque.o
	gcc msgque_P1.o -o msgque_P1
	gcc msgque_P2.o -o msgque_P2

msgque.o: MsgQue_P1.c MsgQue_P2.c
	gcc -c MsgQue_P1.c -o msgque_P1.o
	gcc -c MsgQue_P2.c -o msgque_P2.o

fifo: fifo.o
	gcc fifo_P1.o -o fifo_P1
	gcc fifo_P2.o -o fifo_P2

fifo.o: FIFO_P1.c FIFO_P2.c
	gcc -c FIFO_P1.c -o fifo_P1.o
	gcc -c FIFO_P2.c -o fifo_P2.o

socket: socket.o
	gcc socket_P1.o -o socket_P1
	gcc socket_P2.o -o socket_P2

socket.o: P1.c P2.c
	gcc -c P1.c -o socket_P1.o
	gcc -c P2.c -o socket_P2.o

clean:
	rm *.o
	rm socket_P1 socket_P2
	rm fifo_P1 fifo_P2
	rm msgque_P1 msgque_P2