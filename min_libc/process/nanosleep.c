#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>
#include <time.h>

int nanosleep(timespec *rqt, timespec *rmt)
{
	int ret = syscall(__NR_nanosleep, rqt, rmt);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return 0;
}
