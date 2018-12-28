#ifndef VERSION_H
#define VERSION_H

#define COPYRIGHT "Copyright (C) 2018-2020 anhkgg."
#define AHTHOR_NAME "anhkgg"
#define AUTHOR_WECHAT "anhkgg"
#define VERSION_MAJOR 1
#define VERSION_MINOR 1
#define VERSION_RELEASE 2
#define VERSION_BUILD 0

#define _Stringizing(v)         #v
#define _VerJoin(a, b, c, d)    _Stringizing(a.b.c.d)
#define VERSION_FILE			_VerJoin(VERSION_MAJOR, VERSION_MINOR, VERSION_RELEASE, VERSION_BUILD)


#endif//VERSION_H
