#include "BaseConnect.h"
#include "cocos2d.h"


BaseConnect::BaseConnect(CCString* ipaddres,int port,int iptype)
{
	//创建SOCKET管理器
    CREATE_TCPSOCKETMGR();    

    uint64 t_begin = GetCurrentTime();
    //创建并添加SOCKET，参数：服务器IP，端口，自定义的SOCKET_ID标识
	sSocketMgr.createSocket(ipaddres->getCString(), port, iptype);
    uint64 t_end = GetCurrentTime();
    // 注册协议，参数：包头，回调函数
    sSocketMgr.register_process(0x10, SCT_CALLBACK_2(BaseConnect::process_login, this));
    sSocketMgr.register_process(0x2d, SCT_CALLBACK_2(BaseConnect::process_openbackpack, this));
    // 注册消息截获事件，注册此事件后可以截获收到的所有消息，若回调函数返回true则本次事件会继续分发注册过的协议，返回false则不分发
    sSocketMgr.register_connect(SCT_CALLBACK_2(BaseConnect::OnConnect, this));
    sSocketMgr.register_disconnect(SCT_CALLBACK_3(BaseConnect::onDisconnect, this));
	
	CCLOG("add connect player wait [%u]", t_end - t_begin);
	
}


BaseConnect::~BaseConnect(void)
{
	
}

void BaseConnect::process_login(int _tag, WorldPacket & packet)
{
    CCLOG("process_login len:%u", packet.size());
    // 定义协议包
    WorldPacket newP;
    newP.clear();    
    newP.SetOpcode(0x00B6);// 设置协议头
    newP    << uint16(0x00B6) 
            << uint16(0);// 协议长度
    newP.SetLength(newP.size());// 设置协议长度    
    sSocketMgr.SendPacket(1, &newP);// 发送数据
}

void BaseConnect::process_openbackpack(int _tag, WorldPacket & packet)
{
    CCLOG("process_openbackpack len:%u", packet.size());
}

bool BaseConnect::process_all(int _tag, int _cmd, WorldPacket & packet)
{
    CCLOG("process_all _tag:%u, _cmd:%u, len:%u", _tag, _cmd, packet.size());
    return false;
}

void BaseConnect::OnConnect(int _tag, bool isConnect)
{
    // 定义协议包
    WorldPacket packet;
    packet.clear();    
    packet.SetOpcode(0x0010);// 设置协议头
    packet    << uint16(0x0010) 
            << uint16(0)// 协议长度
            << uint8(1) 
            << uint8(0);
    // 加入字符串数据(uint8表示字符串长度所占字节，此处为1字节)
    packet.AppendPacketString<uint8>(std::string("aaa:88889083:d5956683c17d7e284d33ee295b277b52"));    
    packet.SetLength(packet.size());// 设置协议长度    
    sSocketMgr.SendPacket(1, &packet);// 发送数据
    CCLOG("OnConnect:%u, isConnect[%u]", _tag, isConnect);
	
}

void BaseConnect::onDisconnect(int _tag)
{
    CCLOG("desconnect:%u", _tag);
}
