#include <wiringPi.h>
#include <stdio.h>
#include <linux/spi/spidev.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#define SPI_DEVICE_PATH "/dev/spidev0.0"
#define SPI_MODE SPI_MODE_0
#define SPI_BITS_PER_WORD 8
#define SPI_SPEED_HZ 4294967295


#define backlight 4
#define dc 10
#define rst 3

int spi_fd;

void SetBacklight(bool on)
{
    if (on)
    {
        digitalWrite(backlight, HIGH);
    }
    else
    {
        digitalWrite(backlight, LOW);
    }
}

static void Cleanup()
{
    digitalWrite(dc, LOW);
    pinMode(dc, INPUT);
    digitalWrite(rst, LOW);
    pinMode(rst, INPUT);
    SetBacklight(false);
    pinMode(backlight, INPUT);
}

static void Send(uint8_t *tx_buffer, size_t size)
{
    for (size_t i = 0; i < size; i += 4096)
    {
        size_t chunk_size = (size - i < 4096) ? (size - i) : 4096;
        struct spi_ioc_transfer transfer = {
            .tx_buf = (unsigned long)tx_buffer,
            .rx_buf = 0,
            .len = chunk_size,
            .speed_hz = SPI_SPEED_HZ,
            .delay_usecs=0,
            .bits_per_word=8,
        };

        if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &transfer) == -1)
        {
            perror("SPI transfer failed");
        }
    }
}

static void SendCommand(uint8_t *tx_buffer, size_t size)
{
    digitalWrite(dc, LOW);
    Send(tx_buffer, size);
}

static void SendData(uint8_t *tx_buffer, size_t size)
{
    digitalWrite(dc, HIGH);
    Send(tx_buffer, size);
}

static void Init()
{
    uint8_t tx_data_1[] = {0xEF};
    uint8_t tx_data_2[] = {0x03, 0x80, 0x02};
    uint8_t tx_data_3[] = {0xCF};
    uint8_t tx_data_4[] = {0x00, 0xC1, 0x30};
    uint8_t tx_data_5[] = {0xED};
    uint8_t tx_data_6[] = {0x64, 0x03, 0x12, 0x81};
    uint8_t tx_data_7[] = {0xE8};
    uint8_t tx_data_8[] = {0x85, 0x00, 0x78};
    uint8_t tx_data_9[] = {0xCB};
    uint8_t tx_data_10[] = {0x39, 0x2C, 0x00, 0x34, 0x02};
    uint8_t tx_data_11[] = {0xF7};
    uint8_t tx_data_12[] = {0x20};
    uint8_t tx_data_13[] = {0xEA};
    uint8_t tx_data_14[] = {0x00, 0x00};
    uint8_t tx_data_15[] = {0xC0};
    uint8_t tx_data_16[] = {0x23};
    uint8_t tx_data_17[] = {0xC1};
    uint8_t tx_data_18[] = {0x10};
    uint8_t tx_data_19[] = {0xC5};
    uint8_t tx_data_20[] = {0x3E, 0x28};
    uint8_t tx_data_21[] = {0xC7};
    uint8_t tx_data_22[] = {0x86};
    uint8_t tx_data_23[] = {0x36};
    uint8_t tx_data_24[] = {0x48};
    uint8_t tx_data_25[] = {0x3A};
    uint8_t tx_data_26[] = {0x55};
    uint8_t tx_data_27[] = {0xB1};
    uint8_t tx_data_28[] = {0x00, 0x18};
    uint8_t tx_data_29[] = {0xB6};
    uint8_t tx_data_30[] = {0x08, 0x82, 0x27};
    uint8_t tx_data_31[] = {0xF2};
    uint8_t tx_data_32[] = {0x00};
    uint8_t tx_data_33[] = {0x26};
    uint8_t tx_data_34[] = {0x01};
    uint8_t tx_data_35[] = {0xE0};
    uint8_t tx_data_36[] = {0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00};
    uint8_t tx_data_37[] = {0xE1};
    uint8_t tx_data_38[] = {0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F};
    uint8_t tx_data_39[] = {0x11};
    uint8_t tx_data_40[] = {0x29};
    SendCommand(tx_data_1, sizeof(tx_data_1));
    SendData(tx_data_2, sizeof(tx_data_2));
    SendCommand(tx_data_3, sizeof(tx_data_3));
    SendData(tx_data_4, sizeof(tx_data_4));
    SendCommand(tx_data_5, sizeof(tx_data_5));
    SendData(tx_data_6, sizeof(tx_data_6));
    SendCommand(tx_data_7, sizeof(tx_data_7));
    SendData(tx_data_8, sizeof(tx_data_8));
    SendCommand(tx_data_9, sizeof(tx_data_9));
    SendData(tx_data_10, sizeof(tx_data_10));
    SendCommand(tx_data_11, sizeof(tx_data_11));
    SendData(tx_data_12, sizeof(tx_data_12));
    SendCommand(tx_data_13, sizeof(tx_data_13));
    SendData(tx_data_14, sizeof(tx_data_14));
    SendCommand(tx_data_15, sizeof(tx_data_15));
    SendData(tx_data_16, sizeof(tx_data_16));
    SendCommand(tx_data_17, sizeof(tx_data_17));
    SendData(tx_data_18, sizeof(tx_data_18));
    SendCommand(tx_data_19, sizeof(tx_data_19));
    SendData(tx_data_20, sizeof(tx_data_20));
    SendCommand(tx_data_21, sizeof(tx_data_21));
    SendData(tx_data_22, sizeof(tx_data_22));
    SendCommand(tx_data_23, sizeof(tx_data_23));
    SendData(tx_data_24, sizeof(tx_data_24));
    SendCommand(tx_data_25, sizeof(tx_data_25));
    SendData(tx_data_26, sizeof(tx_data_26));
    SendCommand(tx_data_27, sizeof(tx_data_27));
    SendData(tx_data_28, sizeof(tx_data_28));
    SendCommand(tx_data_29, sizeof(tx_data_29));
    SendData(tx_data_30, sizeof(tx_data_30));
    SendCommand(tx_data_31, sizeof(tx_data_31));
    SendData(tx_data_32, sizeof(tx_data_32));
    SendCommand(tx_data_33, sizeof(tx_data_33));
    SendData(tx_data_34, sizeof(tx_data_34));
    SendCommand(tx_data_35, sizeof(tx_data_35));
    SendData(tx_data_36, sizeof(tx_data_36));
    SendCommand(tx_data_37, sizeof(tx_data_37));
    SendData(tx_data_38, sizeof(tx_data_38));
    SendCommand(tx_data_39, sizeof(tx_data_39));
    delay(120);
    SendCommand(tx_data_40, sizeof(tx_data_40));
}

void SetWindow(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end)
{
    uint8_t x_data[4];
    uint8_t y_data[4];
    x_data[0] = x_start >> 8;
    x_data[1] = x_start;
    x_data[2] = x_end >> 8;
    x_data[3] = x_end;
    y_data[0] = y_start >> 8;
    y_data[1] = y_start;
    y_data[2] = y_end >> 8;
    y_data[3] = y_end;
    uint8_t command_1[] = {0x2B};
    uint8_t command_2[] = {0x2A};
    uint8_t command_3[] = {0x2C};
    SendCommand(command_1, sizeof(command_1));
    SendData(x_data, 4);
    SendCommand(command_2, sizeof(command_2));
    SendData(y_data, 4);
    SendCommand(command_3, sizeof(command_3));

}

static void SingleTestRun(bool test)
{
    uint8_t dataWindow[153600];
    for (int i = 0; i < sizeof(dataWindow); i+=2)
    {
        if (test)
        {
            dataWindow[i] = 0xF8;
        }
        else
        {
            dataWindow[i] = 0x00;
        }
        dataWindow[i+1] = 0xF8;
    }
    SetWindow(0, 319, 0, 239);
    SendData(dataWindow, sizeof(dataWindow));
}

void Test(int amountOfRuns)
{
    bool inverted = true;
    for (int i=0; i<amountOfRuns; i++)
    {
        inverted = !inverted;
        SingleTestRun(inverted);
    }
}

void Reset()
{
    digitalWrite(rst, HIGH);
    delay(500);
    digitalWrite(rst, LOW);
    delay(500);
    digitalWrite(rst, HIGH);
    delay(500);
}

static void SetupSPIDevice()
{
    spi_fd = open(SPI_DEVICE_PATH, O_RDWR);
    if (spi_fd < 0)
    {
        perror("failed to open spi");
        exit(EXIT_FAILURE);
    }
    uint8_t spi_mode = SPI_MODE;
    if (ioctl(spi_fd, SPI_IOC_WR_MODE, &spi_mode) == -1)
    {
        perror("failed to set spi mode");
        close(spi_fd);
        exit(EXIT_FAILURE);
    }

    uint8_t bits_per_word = SPI_BITS_PER_WORD;

    if (ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word) == -1)
    {
        perror("failed to set spi bits per word");
        close(spi_fd);
        exit(EXIT_FAILURE);
    }

    uint32_t speed = SPI_SPEED_HZ;

    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1)
    {
        perror("failed to set spi speed");
        close(spi_fd);
        exit(EXIT_FAILURE);
    }
}

static void SetupGPIOs()
{
    wiringPiSetup();
    pinMode(backlight, OUTPUT);
    pinMode(dc, OUTPUT);
    pinMode(rst, OUTPUT);
    digitalWrite(backlight, HIGH);
}

void Begin()
{
    SetupSPIDevice();
    SetupGPIOs();
    Reset();
    Init();
    atexit(Cleanup);
}


