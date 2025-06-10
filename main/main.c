/* C-Code for operating a FM25W256 - FRAM device 
   The Device sould work like a EEPROM, but with a much higher speed and endurance.
   The FRAM is connected to a Beaglebone Blacl via SPI.
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#include "FRAM_FM25W256.h"
#include "SPI.h"


#define FRAM_SIZE 32768 // 32K bytes


int main() {

    /***************************************************************
     * 
     *  Configure SPI 
     * 
    ***************************************************************/  
    int spi_fd;
    uint8_t tx_buffer[4], rx_buffer[4];

    // Open SPI device
    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        perror("Could not open SPI device");
        return 1;
    }
    printf("SPI device opened\n");

    // Configure SPI settings
    if (spi_config(spi_fd) != 0) {
        close(spi_fd);
        return 1;
    }
    printf("SPI device configured\n");


    /***************************************************************
     * 
     *  FRAM Example
     * 
    ***************************************************************/    
    uint8_t fram_status = 0; // Byte for FRAM-status-register

    uint8_t data[3] = {0x01, 0x02, 0x03}; // Example data to write
    uint8_t read_data[3]; // Buffer to read data
    uint16_t address = 0x0030; // Example address to write to     


    // FRAM Write Enable
    if (fram_write_enable(spi_fd))
    {
       printf("FRAM Write Enable command sent\n");
    }
    usleep(1); // 1us delay
    
    // Check Status
    fram_status = fram_read_status(spi_fd);

    // Write data to FRAM	
    fram_write_data(spi_fd, address, data, sizeof(data)); // Write data to FRAM
    printf("Data written to FRAM\n");

    usleep(1); // 1us delay

    // Read cyclically written data from FRAM
    while (1)
    {
        fram_read_data(spi_fd, address, read_data, sizeof(read_data)); // Read data from FRAM
        printf("Data read from FRAM: %02X %02X %02X\n", read_data[0], read_data[1], read_data[2]);
        sleep(1);
    }
    

    // Close SPI device
    close(spi_fd);
    return 0;
}
