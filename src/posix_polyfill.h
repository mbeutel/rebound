/**
 * @file    posix_polyfill.h
 * @brief   Polyfill implementations for POSIX routines
 * @author  Moritz Beutel <moritz.beutel@ziti.uni-heidelberg.de>
 * 
 * @section LICENSE
 * Copyright (c) 2021 Hanno Rein
 *
 * This file is part of rebound.
 *
 * rebound is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rebound is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rebound.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _POSIX_POLYFILL_H
#define _POSIX_POLYFILL_H


#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif


// We use `defined(_WIN32)` as approximation for "non-POSIX platform".
#ifdef _WIN32

# include <time.h>  // for time_t
# include <process.h>  // for getpid()

# ifdef _MSC_VER
#  define restrict __restrict
# endif

int rand_r(unsigned *seed);

char *strtok_r(char *string, char const *delimiter, char **context);

void usleep(__int64 usec);

typedef __int64 suseconds_t;
struct timeval {
    time_t      tv_sec;     /* seconds */
    suseconds_t tv_usec;    /* microseconds */
};
struct timezone {
    int tz_minuteswest;     /* minutes west of Greenwich */
    int tz_dsttime;         /* type of DST correction */
};
int gettimeofday(struct timeval *tv, struct timezone *tz);

#else // !_WIN32

// assume POSIX
# include <unistd.h>
# include <sys/time.h>

#endif // _WIN32

#endif
