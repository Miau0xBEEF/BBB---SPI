/* Simple SPI configuration */


#ifndef SPI_H
#define SPI_H
#include <stdint.h>
#include <stdio.h> 

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_DEVICE "/dev/spidev0.0"
#define SPI_SPEED 500000  // 50 kHz
#define SPI_MODE SPI_MODE_3 //SPI_MODE_0 // SPI Mode 0 (CPOL = 0, CPHA = 0)
#define SPI_BITS_PER_WORD 8 // 8 bits per word
#define SPI_DELAY 0 // 5 microseconds delay


uint8_t spi_config(int fd);

uint8_t spi_transfer(int fd, uint8_t *tx, uint8_t *rx, int len); 
#endif