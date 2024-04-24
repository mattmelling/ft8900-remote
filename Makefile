.default: ft8900r

SRCS := main.c serial.c packet.c

ft8900r: $(SRCS)
	$(CC) -o $@ $^
