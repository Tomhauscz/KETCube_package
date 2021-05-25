#ifndef Arduino_h
#define Arduino_h

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef bool boolean;
typedef uint8_t byte;
typedef uint16_t word;

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

// void yield( void ) ;

/* system functions */
// int main( void );
// void init( void );

/* declare sketch */
extern void setup( void ) ;
extern void loop( void ) ;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // Arduino_h
