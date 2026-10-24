#ifndef	_TIME_H_
#define	_TIME_H_	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>

typedef struct timespec {
    long tv_sec;  // seconds
    long tv_nsec;   // nanoseconds
} timespec;

int nanosleep(timespec *rqt, timespec *rmt);
unsigned int sleep(unsigned int seconds);

#ifdef __cplusplus
}
#endif

#endif
