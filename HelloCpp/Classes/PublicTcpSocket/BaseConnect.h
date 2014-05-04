#ifndef __BASECONNECT__
#define __BASECONNECT__
#include "cocos2d.h"
#include "../PublicTcpSocket/TCPSocket.h"
USING_NS_CC;
class BaseConnect
{
public:
	BaseConnect(CCString* ipaddres,int port,int iptype);
	~BaseConnect(void);

	// 注册单个协议回调函数（样例)，参数：SOCKET_ID标识，数据包
    void process_login(int _tag, WorldPacket & packet);
    // 消息包更新
    void process_openbackpack(int _tag, WorldPacket & packet);
    // 注册单个协议回调函数（样例)，参数：SOCKET_ID标识，协议头，数据包
    bool process_all(int _tag, int _cmd, WorldPacket & packet);
    // 连接事件
    void OnConnect(int _tag, bool isConnect);
    // 断线事件
    void onDisconnect(int _tag);
};

#endif __BASECONNECT__