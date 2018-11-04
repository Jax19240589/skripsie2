#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "c-periphery/src/gpio.h"
#include "c-periphery/src/spi.h"
int main(void) {

    	gpio_t gpio_in, gpio_out;
	bool value;

    	if (gpio_open(&gpio_out, 60, GPIO_DIR_OUT) < 0) {
        	fprintf(stderr, "gpio_open(): %s\n", gpio_errmsg(&gpio_out));
        	exit(1);
    	}
	
	value = 1;
	if (gpio_write(&gpio_out, !value) < 0) {
        	fprintf(stderr, "gpio_write(): %s\n", gpio_errmsg(&gpio_out));
        	exit(1);
    	}
	value = 0;
    	usleep(100);
	if (gpio_write(&gpio_out, !value) < 0) {
        	fprintf(stderr, "gpio_write(): %s\n", gpio_errmsg(&gpio_out));
        	exit(1);
    	}

    	usleep(100);

	spi_t spi;
	unsigned char buf[2];
	buf[0] = 0x42 & 0x7F;
	buf[1] = 0x00;

	if (spi_open(&spi, "/dev/spidev1.0", 0, 500000) < 0) {
        	fprintf(stderr, "spi_open(): %s\n", spi_errmsg(&spi));
        	exit(1);
    	}

    	if (spi_transfer(&spi, buf, buf, sizeof(buf)) < 0) {
        	fprintf(stderr, "spi_transfer(): %s\n", spi_errmsg(&spi));
        	exit(1);
    	}
    	
    	if (gpio_open(&gpio_in, 58, GPIO_DIR_IN) < 0) {
        fprintf(stderr, "gpio_open(): %s\n", gpio_errmsg(&gpio_in));
        exit(1);
		}
		if (gpio_read(&gpio_in, &value) < 0) {
			fprintf(stderr, "gpio_read(): %s\n", gpio_errmsg(&gpio_in));
			exit(1);
		}
		printf("%d\n", value);

	printf("Hexadecimal value is (Alphabet in capital letters): %X\n",buf[1]);

        printf("Hello World\n");
        return 0;
}

