
#include "posix_polyfill.h"


#ifdef _WIN32
#include <errno.h>
#include <string.h>  // for strtok_s()
#include <time.h>    // for timespec, timespec_get()

#include <process.h>  // for _getpid()

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// The rand_r implementation included below is a translation of the musl
// implementation (http://www.musl-libc.org/), which is licensed
// under the MIT license:
//
// ----------------------------------------------------------------------
// Copyright © 2005-2021 Rich Felker, et al.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ----------------------------------------------------------------------
//
// Original location:
// https://git.musl-libc.org/cgit/musl/tree/src/prng/rand_r.c

static unsigned temper(unsigned x)
{
    x ^= x>>11;
    x ^= x<<7 & 0x9D2C5680;
    x ^= x<<15 & 0xEFC60000;
    x ^= x>>18;
    return x;
}
int rand_r(unsigned *seed)
{
    return temper(*seed = *seed * 1103515245 + 12345)/2;
}


char *strtok_r(char *string, char const *delimiter, char **context)
{
    return strtok_s(string, delimiter, context);
}


// Borrowed from https://stackoverflow.com/a/17283549
void usleep(__int64 usec) 
{ 
    HANDLE timer; 
    LARGE_INTEGER ft; 

    ft.QuadPart = -(10*usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL); 
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0); 
    WaitForSingleObject(timer, INFINITE); 
    CloseHandle(timer); 
}


int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    if (tv == NULL)
    {
        errno = EINVAL;
        return -1;
    }
    if (tz != NULL)
    {
        errno = ENOTSUP;  // timezone arguments are not currently supported
        return -1;
    }

    struct timespec ts;
    int base = timespec_get(&ts, TIME_UTC);
    if (base != TIME_UTC)
    {
        errno = EIO;  // no idea what to return here, really
        return -1;
    }
    tv->tv_sec = ts.tv_sec;
    tv->tv_usec = ts.tv_nsec/1000;
    return 0;
}
#endif // _WIN32
