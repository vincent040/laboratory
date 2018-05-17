#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>

#include <dirent.h>

#define MSGSIZE 1024

#define SERIAL1 "/dev/ttySAC1"
#define SERIAL2 "/dev/ttySAC2"

#define AT_RST "AT+RST\r\n"

#define AT_CWMODE1 "AT+CWMODE=1\r\n"
#define AT_CWMODE2 "AT+CWMODE=2\r\n"
#define AT_CWMODE3 "AT+CWMODE=3\r\n"

#define AT_CWSAP(ssid,pw,ecn) "AT+CWSAP=\"#ssid\",\"#pw\",11,ecn\r\n"
#define AT_CIPMUX1 "AT+CIPMUX=1\r\n"
#define AT_CIPSERVER "AT+CIPSERVER=1,8080\r\n"

#define AT_CWLAP "AT+CWLAP\r\n"
#define AT_CWJAP(ssid,pw) "AT+CWJAP=\"#ssid\",\"#pw\"\r\n"

#define AT_CIFSR "AT+CIFSR\r\n"

#define AT_CIPSTART0 "AT+CIPSTART=0,\"TCP\",\"192.168.4.1\",8080\r\n"
#define AT_CIPSTART "AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080\r\n"

#define AT_CIPSEND0(n) "AT+CIPSEND=0,n\r\n"
#define AT_CIPSEND(n) "AT+CIPSEND=n\r\n"

#endif
