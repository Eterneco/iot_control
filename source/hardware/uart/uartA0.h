#ifndef __UART_A0_H
#define __UART_A0_H

#include "typeDefs.h"

#ifdef NOTERM
#define UART_PRINT(x, ...)
#define DBG_PRINT (x, ...)
#define ERR_PRINT (x)
#else
#define UART_PRINT   UartA0Write
#define DBG_PRINT    UartA0Write
#define ERR_PRINT(x) UartA0Write("Error [%d] at line [%d] in function [%s]  \n\r",x,__LINE__,__FUNCTION__)
#endif

// check the error code and handle it
#define ASSERT_ON_ERROR(error_code)\
            {\
                 if(error_code < 0) \
                   {\
                        ERR_PRINT(error_code);\
                        return error_code;\
                 }\
            }

extern void   UartA0Init();
extern uInt8  UartA0Get();
extern int    UartA0Write(char *format, ...);


#endif
