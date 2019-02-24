#include <Windows.h>
#pragma comment(lib, "Rpcrt4.lib")

RPC_WSTR ProtocolSequence = (RPC_WSTR)L"ncacn_np";

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return (malloc(len));
}
void __RPC_USER midl_user_free(void __RPC_FAR *ptr)
{
    free(ptr);
}

//pszEndPoint 命名管道
long RpcStartService(RPC_WSTR EndPoint, RPC_IF_HANDLE ifHandle)
{
    void __RPC_FAR * pszSecurity = NULL;

    RPC_STATUS rpcStats = RpcServerUseProtseqEp(
        ProtocolSequence,
        RPC_C_LISTEN_MAX_CALLS_DEFAULT,
        EndPoint,
        pszSecurity);
    if (rpcStats) {
        return(rpcStats);
    }

    rpcStats = RpcServerRegisterIf(ifHandle, NULL, NULL);
    if (rpcStats) {
        return rpcStats;
    }

    unsigned int fDontWait = false;
    rpcStats = RpcServerListen(1, RPC_C_LISTEN_MAX_CALLS_DEFAULT, fDontWait);
    if (rpcStats) {
        return rpcStats;
    }

    return 0;
}

void RpcStopService()
{
    RPC_STATUS rpcStatus;
    rpcStatus = RpcMgmtStopServerListening(NULL);
    rpcStatus = RpcServerUnregisterIf(NULL, NULL, FALSE);
}

//handle_t IfHandle acf定义的句柄
//如果没有acf，每个接口都要传一个IfHandle
long RpcConnectServer(RPC_WSTR EndPoint, handle_t *IfHandle, RPC_WSTR *StringBinding)
{
    RPC_WSTR Uuid = NULL;
    RPC_WSTR NetworkAddress = NULL;
    RPC_WSTR Options = NULL;
    //RPC_WSTR StringBinding = NULL;

    RPC_STATUS rpcStatus = RpcStringBindingCompose(
        Uuid,
        ProtocolSequence,
        NetworkAddress,
        EndPoint,
        Options,
        StringBinding);
    if (rpcStatus) {
        return(rpcStatus);
    }

    rpcStatus = RpcBindingFromStringBinding(*StringBinding,
        IfHandle);
    if (rpcStatus) {
        return(rpcStatus);
    }

    return rpcStatus;
}

long RpcDisconnectServer(handle_t *IfHandle, RPC_WSTR *StringBinding)
{
    RPC_STATUS rpcStatus = RpcStringFree(StringBinding);
    if (rpcStatus) {
        return(rpcStatus);
    }

    rpcStatus = RpcBindingFree(IfHandle);
    if (rpcStatus) {
        return(rpcStatus);
    }

    return rpcStatus;
}

long RcpCall()
{
    RpcTryExcept
    {
        //CallServerFuntions();
    }
    RpcExcept(1)
    {
        unsigned long ulCode = RpcExceptionCode();
        //printf("抛出异常0x%lx = %ld。\n", ulCode, ulCode);
    }
    RpcEndExcept
    return 0;
}