// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
    /* TODO: Implement strcpy(). */
    size_t i;

    for (i = 0; i < strlen(source); i++) {
        destination[i] = source[i];
    }

    destination[i] = '\0';

    return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
    /* TODO: Implement strncpy(). */
    size_t i;

    for (i = 0; i < len; i++) {
        destination[i] = source[i];

        if (i >= strlen(source)) {
            break;
        }
    }

    // Ensure null-termination
    while (i < len) {
        destination[i++] = '\0';
    }

    return destination;
}

char *strcat(char *destination, const char *source)
{
    /* TODO: Implement strcat(). */
    size_t dest_length = strlen(destination);
    size_t i;

    for (i = 0; i < strlen(source); i++) {
        destination[dest_length + i] = source[i];
    }

    destination[dest_length + i] = '\0';

    return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
    /* TODO: Implement strncat(). */
    size_t dest_length = strlen(destination);
    size_t i;

    for (i = 0; i < len && source[i] != '\0'; i++) {
        destination[dest_length + i] = source[i];
    }

    destination[dest_length + i] = '\0';

    return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */

    while (*str1 != '\0' || *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return 0;

	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
    /* TODO: Implement strncmp(). */
    size_t i;

    for (i = 0; i < len; i++) {
        if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
            return (int)(str1[i] - str2[i]);
        }
    }

    return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}


char *strchr(const char *str, int c)
{
    /* TODO: Implement strchr(). */
    size_t i;

    for (i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            return (char *)(str + i);
        }
    }

    return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */

	const char *pos = NULL;

	while (*str) {
		if(*str == c)
			pos = str;
		str++;
	}

	return (char *)pos;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */

    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);

    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        size_t j;
        for (j = 0; j < needle_len; j++) {
            if (haystack[i + j] != needle[j]) {
                break;
            }
        }
        if (j == needle_len) {
            return (char *)(haystack + i);
        }
    }

    return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */

    // source: https://github.com/brgl/busybox/blob/master/libbb/strrstr.c

	char *r = NULL;

	if (!needle[0])
		return (char*)haystack + strlen(haystack);
	while (1) {
		char *p = strstr(haystack, needle);
		if (!p)
			return r;
		r = p;
		haystack = p + 1;
	}

	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
    // source: https://www.tutorialspoint.com/write-your-own-memcpy-in-c

    char *dest = (char *)destination;
    const char *src = (const char *)source;

    for (int i = 0; i < (int)num; i++) {
        dest[i] = src[i];
    }

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */

    char *pDest = (char *)destination;
    const char *pSrc = (const char *)source;

    if (pDest > pSrc && pDest < pSrc + num) {
        for (size_t i = num; i > 0; i--) {
            pDest[i - 1] = pSrc[i - 1];
        }
    } else {
        for (size_t i = 0; i < num; i++) {
            pDest[i] = pSrc[i];
        }
    }
    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */

	char *p1 = (char *)ptr1;
	char *p2 = (char *)ptr2;

    for (int i = 0; i < (int)num; i++) {
        if (p1[i] != p2[i]) {
            if (p1[i] < p2[i]) {
                return -1;
            } else {
                return 1;
            }
        }
    }

    return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */

	unsigned char *p = (unsigned char *)source;
    unsigned char val = (unsigned char)value;

    for (size_t i = 0; i < num; i++) {
        p[i] = val;
    }

	return source;
}
