

#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>
#include <time.h>

unsigned int sleep(unsigned int seconds)
{
    timespec requested_time, remaining_time;
    requested_time.tv_sec = seconds;
    requested_time.tv_nsec = 0;

    if (nanosleep(&requested_time, &remaining_time) == 0) {
        // Sleep completed as requested
        return 0;
    } else {
        // Sleep was interrupted, return the remaining time in seconds
        return remaining_time.tv_sec;
    }
}
