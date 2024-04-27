.default: ft8900r

SRCS := main.c serial.c packet.c socket.c packet_queue.c command.c keypad.c

ft8900r: $(SRCS)
	$(CC) -o $@ -lpthread $^

install: ft8900r
	cp ft8900r /usr/local/bin/
	cp ft8900r-remote.service /etc/systemd/system/
	systemctl enable ft8900r-remote.service
	systemctl daemon-reload
