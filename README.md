# Mini-Libc

This is a minimal implementation of the C standard library for Linux on x86_64. It doesn't use glibc or any other library: everything is built directly on top of Linux system calls, which are invoked through the syscall() function in syscall.c. The result is a static library, libc.a, that programs can link against instead of the system libc.

I implemented string and memory functions, file I/O, puts, sleep/nanosleep and a simple memory allocator. The startup code (crt/), the syscall() function, read/write, exit and the mem_list helper list were already there, and I used them as they are.

## String functions (string/string.c)

All of them are written with simple loops and don't use anything besides strlen and strstr, which are also implemented here.

- strcpy, strcat: I copy character by character; for strcat I start from the end of the destination. At the end I add '\0'.
- strncpy, strncat: same thing, but I stop after len characters. For strncpy, if the source is shorter, I fill the rest with '\0'.
- strcmp, strncmp: I go through both strings at the same time and at the first difference I return the difference between the characters. If there is no difference, I return 0.
- strchr: I return the first position where the character appears. strrchr: I go through the whole string and keep the last position.
- strstr: I try every position in haystack and check if needle matches from there.
- strrstr (returns the last occurrence of needle in haystack): I call strstr repeatedly, each time starting right after the last match, and keep the last one. I used the BusyBox implementation as a model.
- memcpy, memset, memcmp: I work byte by byte.
- memmove: if the areas overlap and the destination is after the source, I copy from the end to the beginning. Otherwise I copy normally.

## File I/O (io/, stat/)

open, close, lseek, truncate, ftruncate, stat and fstat are wrappers over the corresponding system calls. They all have the same structure: I call syscall() with the call number (__NR_open, __NR_lseek etc.). On failure, the Linux kernel doesn't set errno itself, it returns -errno instead. So if the result is negative, I set errno = -ret and return -1. Otherwise I return the result (or 0).

The checks for an invalid fd, invalid whence, negative size etc. are done by the kernel; I just pass the error on through errno.

## puts (io/puts.c)

I added the declaration of puts in stdio.h, together with EOF. The function computes the length of the string, writes it with write to stdout (fd 1), then writes a '\n'. If one of the writes fails, I return EOF.

## nanosleep and sleep (process/)

I created the time.h header, where I defined struct timespec (tv_sec and tv_nsec) and declared the two functions.

- nanosleep calls the __NR_nanosleep syscall directly and sets errno on error.
- sleep puts the number of seconds in a timespec and calls nanosleep. If the sleep is interrupted, I return how many seconds were left.

## Memory (mm/)

mmap, mremap and munmap are syscall wrappers, like the I/O ones. The difference is that mmap and mremap return MAP_FAILED on error. I store the result in a long so the address fits.

For malloc I do a separate mmap for each allocation. I allocate a bit more than requested so I can put a mem_list structure at the beginning of the area, where I keep the start address and the size. The user gets the address right after this structure. The block is also added to the list of allocated blocks from mem_list.c. For size 0 I return NULL.

- free: I find the structure before the pointer, remove the block from the list and munmap the whole area.
- calloc: malloc + memset with 0.
- realloc: if size is 0, I call free. If ptr is NULL, I call malloc. Otherwise I allocate a new block, copy the data from the old one and free the old one.
- reallocarray: I compute nmemb * size and call realloc (or malloc if ptr is NULL).
