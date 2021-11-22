#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <time.h>

#define DEV_NAME "/dev/ttyS0"
// #define DEV_NAME "/dev/tty.usbmodem144101"
#define BAUD_RATE B9600
#define BUFF_SIZE 16 

void serial_init(int fd) {
	struct termios tio;
	memset(&tio, 0, sizeof(tio));
	tio.c_cflag = BAUD_RATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	tio.c_iflag = IGNPAR | ICRNL;
	tio.c_oflag = 0;
	tio.c_lflag = ICANON;
	tio.c_cc[VTIME] = 100;
	tio.c_cc[VEOF] = 4;
	tio.c_cc[VMIN] = 1;
	tcsetattr(fd, TCSANOW, &tio);
}

int main(int argc, char **argv) {
	int fd;
	int i;
	int len;
	unsigned char in[BUFF_SIZE], buffer[BUFF_SIZE], in_data[BUFF_SIZE];
	printf("open serial port..\n");
	fd = open(DEV_NAME, O_RDWR | O_NONBLOCK );
	if (fd < 0) {
		printf("ERROR on device open\n");
		exit(1);
	}
	printf("init serial port\n");
	serial_init(fd);
	for (i = 0; i < BUFF_SIZE; i++) {
		in[i] = 'A';
	}
	printf("start main loop...\n");
	while(1) {
		len = write(fd, in, BUFF_SIZE);
		printf("WRITE:in = [%s], res = %d\n", in, len);
		sleep(1);
		len = read(fd, buffer, BUFF_SIZE);
		printf("READ:buffer = [%s], res = %d\n", buffer, len);
		bzero(buffer, sizeof(buffer));
		// sleep(1);
	}
}
