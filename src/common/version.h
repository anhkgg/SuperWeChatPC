#ifndef WECHARSDK_VERSION
#define WECHARSDK_VERSION

#include <windows.h>

#define VER_Major           1
#define VER_Minor           3
#define VER_Revision        0
#define VER_Build           0

#define _Stringizing(v)         #v
#define _VerJoin(a, b, c, d)    _Stringizing(a.b.c.d)
#define VER_FileVersion         TEXT(_VerJoin(VER_Major, VER_Minor, VER_Revision, VER_Build))

#define VER_CompanyName         TEXT("Author: anhkgg")
#define VER_CopyRight           TEXT("Copyright (C) 2019-2030 anhkgg.com")
#define VER_Trademarks          TEXT("anhkgg")
#define VER_ProductName         TEXT("³¬¼¶Î¢ÐÅSuperWeChatPC")
#endif // !WECHARSDK_VERSION
