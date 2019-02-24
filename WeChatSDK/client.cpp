#include "stdafx.h"
#include "client.h"


CallClient::CallClient()
{
    
}


CallClient::~CallClient()
{
}

bool CallClient::OnMessageReceived(IPC::Message * message)
{
    return false;
}

void CallClient::OnChannelConnected(int32 peer_pid)
{
}

void CallClient::OnChannelError()
{
}