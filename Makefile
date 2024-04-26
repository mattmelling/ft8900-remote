.default: ft8900r

SRCS := main.c serial.c packet.c socket.c packet_queue.c command.c keypad.c

ft8900r: $(SRCS)
	$(CC) -o $@ $^
