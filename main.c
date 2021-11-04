#include<stdio.h>
#include <strings.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define DEV "/dev/ttyS0"
int main(int argc, char *argv[]) {
	int fd, c;
	char buf[1024];
	bzero(buf, sizeof(buf));
	fd = open(DEV, O_RDWR | O_NOCTTY);
	if (fd < 0) {
		perror(DEV);
		exit(-1);
	}
	close(fd);
}
