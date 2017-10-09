/*
 * DS1302mh.h - library for the DS1302 RTC
 *
 * Inspired on:
 *    https://playground.arduino.cc/Main/DS1302
 *    https://github.com/msparks/arduino-ds1302
 *    https://github.com/iot-playground/Arduino/tree/master/external_libraries/DS1302RTC
 */

#ifndef DS1302mh_h
#define DS1302mh_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define FORMAT_SHORT	1
#define FORMAT_LONG	2

#define FORMAT_LITTLEENDIAN	1
#define FORMAT_BIGENDIAN	2
#define FORMAT_MIDDLEENDIAN	3

#define SUNDAY		1
#define MONDAY		2
#define TUESDAY		3
#define WEDNESDAY	4
#define THURSDAY	5
#define FRIDAY		6
#define SATURDAY	7

// Macros to convert the bcd values of the registers to normal
// integer variables.
// The code uses separate variables for the high byte and the low byte
// of the bcd, so these macros handle both bytes separately.
#define bcd2bin(h,l)    (((h)*10) + (l))
#define bin2bcd_h(x)   ((x)/10)
#define bin2bcd_l(x)    ((x)%10)


// Register names.
// Since the highest bit is always '1', 
// the registers start at 0x80
// If the register is read, the lowest bit should be '1'.
#define DS1302_SECONDS           0x80
#define DS1302_MINUTES           0x82
#define DS1302_HOURS             0x84
#define DS1302_DATE              0x86
#define DS1302_MONTH             0x88
#define DS1302_DAY               0x8A
#define DS1302_YEAR              0x8C
#define DS1302_ENABLE            0x8E
#define DS1302_TRICKLE           0x90
#define DS1302_CLOCK_BURST       0xBE
#define DS1302_CLOCK_BURST_WRITE 0xBE
#define DS1302_CLOCK_BURST_READ  0xBF
#define DS1302_RAMSTART          0xC0
#define DS1302_RAMEND            0xFC
#define DS1302_RAM_BURST         0xFE
#define DS1302_RAM_BURST_WRITE   0xFE
#define DS1302_RAM_BURST_READ    0xFF



// Defines for the bits, to be able to change 
// between bit number and binary definition.
// By using the bit number, using the DS1302 
// is like programming an AVR microcontroller.
// But instead of using "(1<<X)", or "_BV(X)", 
// the Arduino "bit(X)" is used.
#define DS1302_D0 0
#define DS1302_D1 1
#define DS1302_D2 2
#define DS1302_D3 3
#define DS1302_D4 4
#define DS1302_D5 5
#define DS1302_D6 6
#define DS1302_D7 7


// Bit for reading (bit in address)
#define DS1302_READBIT DS1302_D0 // READBIT=1: read instruction

// Bit for clock (0) or ram (1) area, 
// called R/C-bit (bit in address)
#define DS1302_RC DS1302_D6

// Seconds Register
#define DS1302_CH DS1302_D7   // 1 = Clock Halt, 0 = start

// Hour Register
#define DS1302_AM_PM DS1302_D5 // 0 = AM, 1 = PM
#define DS1302_12_24 DS1302_D7 // 0 = 24 hour, 1 = 12 hour

// Enable Register
#define DS1302_WP DS1302_D7   // 1 = Write Protect, 0 = enabled

// Trickle Register
#define DS1302_ROUT0 DS1302_D0
#define DS1302_ROUT1 DS1302_D1
#define DS1302_DS0   DS1302_D2
#define DS1302_DS1   DS1302_D2
#define DS1302_TCS0  DS1302_D4
#define DS1302_TCS1  DS1302_D5
#define DS1302_TCS2  DS1302_D6
#define DS1302_TCS3  DS1302_D7

class Time
{
  public:
    uint8_t  hour;
    uint8_t  min;
    uint8_t  sec;
    uint8_t  date;
    uint8_t  mon;
    uint16_t year;
    uint8_t  dow;

  Time();
};

// library interface description
class DS1302mh
{
  // user-accessible "public" interface
  public:
    DS1302mh(uint8_t CE_pin, uint8_t IO_pin, uint8_t SCLK_pin);
    Time  getTime();
    void  setTime(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t dayofweek, uint8_t dayofmonth, uint8_t month, uint16_t year);
    char  *getTimeStr(uint8_t format=FORMAT_LONG);
    char  *getDateStr(uint8_t slformat=FORMAT_LONG, uint8_t eformat=FORMAT_LITTLEENDIAN, char divider='.');
    char  *getDOWStr(uint8_t format=FORMAT_LONG);
    char  *getMonthStr(uint8_t format=FORMAT_LONG);

    void clock_burst_read( uint8_t *p);
    void clock_burst_write( uint8_t *p);
    uint8_t read(int address);
    void write( int address, uint8_t data);

  private:
    static  uint8_t DS1302_CE_PIN;
    static  uint8_t DS1302_IO_PIN;
    static  uint8_t DS1302_SCLK_PIN;
    void _start( void);
    void _stop(void);
    uint8_t _toggleread( void);
    void _togglewrite( uint8_t data, uint8_t release);
    struct ds1302_struct;
};

#endif