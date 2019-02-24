

/* this ALWAYS GENERATED file contains the RPC server stubs */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for sdkdef.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#include <string.h>
#include "sdkdef_h.h"

#define TYPE_FORMAT_STRING_SIZE   7                                 
#define PROC_FORMAT_STRING_SIZE   199                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _sdkdef_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } sdkdef_MIDL_TYPE_FORMAT_STRING;

typedef struct _sdkdef_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } sdkdef_MIDL_PROC_FORMAT_STRING;

typedef struct _sdkdef_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } sdkdef_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};

extern const sdkdef_MIDL_TYPE_FORMAT_STRING sdkdef__MIDL_TypeFormatString;
extern const sdkdef_MIDL_PROC_FORMAT_STRING sdkdef__MIDL_ProcFormatString;
extern const sdkdef_MIDL_EXPR_FORMAT_STRING sdkdef__MIDL_ExprFormatString;

/* Standard interface: WechatSDK, ver. 1.0,
   GUID={0xEC3A7CE8,0x8F99,0x47ef,{0x97,0x05,0xDA,0x5D,0xF1,0x4F,0x9A,0x4C}} */


extern const MIDL_SERVER_INFO WechatSDK_ServerInfo;

extern const RPC_DISPATCH_TABLE WechatSDK_v1_0_DispatchTable;

static const RPC_SERVER_INTERFACE WechatSDK___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0xEC3A7CE8,0x8F99,0x47ef,{0x97,0x05,0xDA,0x5D,0xF1,0x4F,0x9A,0x4C}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    (RPC_DISPATCH_TABLE*)&WechatSDK_v1_0_DispatchTable,
    0,
    0,
    0,
    &WechatSDK_ServerInfo,
    0x04000000
    };
RPC_IF_HANDLE WechatSDK_v1_0_s_ifspec = (RPC_IF_HANDLE)& WechatSDK___RpcServerInterface;

extern const MIDL_STUB_DESC WechatSDK_StubDesc;


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif
#if !(TARGET_IS_NT60_OR_LATER)
#error You need Windows Vista or later to run this stub because it uses these features:
#error   compiled for Windows Vista.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const sdkdef_MIDL_PROC_FORMAT_STRING sdkdef__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Initialize */

			0x32,		/* FC_BIND_PRIMITIVE */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 24 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 26 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AntiRevokeMsg */

/* 30 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x48,		/* Old Flags:  */
/* 32 */	NdrFcLong( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x1 ),	/* 1 */
/* 38 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 40 */	NdrFcShort( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 46 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 54 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 56 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 58 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnAntiRevokeMsg */

/* 60 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x48,		/* Old Flags:  */
/* 62 */	NdrFcLong( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x2 ),	/* 2 */
/* 68 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 70 */	NdrFcShort( 0x0 ),	/* 0 */
/* 72 */	NdrFcShort( 0x8 ),	/* 8 */
/* 74 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 76 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 78 */	NdrFcShort( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 84 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 86 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 88 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StartSaveVoiceMsg */

/* 90 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x48,		/* Old Flags:  */
/* 92 */	NdrFcLong( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x3 ),	/* 3 */
/* 98 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 104 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 106 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 108 */	NdrFcShort( 0x0 ),	/* 0 */
/* 110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter path */

/* 114 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 116 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 118 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 120 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 122 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StopSaveVoiceMsg */

/* 126 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x48,		/* Old Flags:  */
/* 128 */	NdrFcLong( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0x4 ),	/* 4 */
/* 134 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 140 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 142 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 146 */	NdrFcShort( 0x0 ),	/* 0 */
/* 148 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 150 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 152 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 154 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SendTextMsg */

/* 156 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x48,		/* Old Flags:  */
/* 158 */	NdrFcLong( 0x0 ),	/* 0 */
/* 162 */	NdrFcShort( 0x5 ),	/* 5 */
/* 164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 170 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 172 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 178 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter wxid */

/* 180 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 182 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 184 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Parameter msg */

/* 186 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 188 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 190 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */

	/* Return value */

/* 192 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 194 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 196 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const sdkdef_MIDL_TYPE_FORMAT_STRING sdkdef__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const unsigned short WechatSDK_FormatStringOffsetTable[] =
    {
    0,
    30,
    60,
    90,
    126,
    156
    };


static const MIDL_STUB_DESC WechatSDK_StubDesc = 
    {
    (void *)& WechatSDK___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    0,
    sdkdef__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x801026e, /* MIDL Version 8.1.622 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

static const RPC_DISPATCH_FUNCTION WechatSDK_table[] =
    {
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    0
    };
static const RPC_DISPATCH_TABLE WechatSDK_v1_0_DispatchTable = 
    {
    6,
    (RPC_DISPATCH_FUNCTION*)WechatSDK_table
    };

static const SERVER_ROUTINE WechatSDK_ServerRoutineTable[] = 
    {
    (SERVER_ROUTINE)Initialize,
    (SERVER_ROUTINE)AntiRevokeMsg,
    (SERVER_ROUTINE)UnAntiRevokeMsg,
    (SERVER_ROUTINE)StartSaveVoiceMsg,
    (SERVER_ROUTINE)StopSaveVoiceMsg,
    (SERVER_ROUTINE)SendTextMsg
    };

static const MIDL_SERVER_INFO WechatSDK_ServerInfo = 
    {
    &WechatSDK_StubDesc,
    WechatSDK_ServerRoutineTable,
    sdkdef__MIDL_ProcFormatString.Format,
    WechatSDK_FormatStringOffsetTable,
    0,
    0,
    0,
    0};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

