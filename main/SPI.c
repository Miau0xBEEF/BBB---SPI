
#include "SPI.h"


static uint8_t mode = 0;

uint8_t spi_config(int fd) {
    // Set SPI mode
    mode |= SPI_MODE; 
    static uint32_t speed = SPI_SPEED;
    static uint8_t bits = SPI_BITS_PER_WORD;

    if (ioctl(fd, SPI_IOC_RD_MODE, &mode) == -1) {
        perror("can't set spi mode");
        return -1;
    }

    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) {
        perror("can't set spi mode");
        return -1;
    }


    // Set bits per word
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1) {
        perror("can't set bits per word");
        return -1;
    }

    // Set max speed
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
        perror("can't set max speed HZ");
        return -1;
    }

    return 0;
}


uint8_t spi_transfer(int fd, uint8_t *tx, uint8_t *rx, int len) {
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = len,
        .delay_usecs = SPI_DELAY,
        .bits_per_word = SPI_BITS_PER_WORD,
        .speed_hz = SPI_SPEED,  // Set speed here
    };

    // Execute the SPI transfer
    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1) {
        perror("can't send spi message");
    }

    return ret;
}