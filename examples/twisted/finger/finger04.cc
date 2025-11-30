#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"
#include "muduo/base/Logging.h"

using namespace muduo;
using namespace muduo::net;

void onMessage(const TcpConnectionPtr& conn,
               Buffer* buf,
               Timestamp receiveTime)
{
  if (buf->findCRLF())
  {
    LOG_INFO << "Finger - " << conn->peerAddress().toIpPort() << " -> "
           << conn->localAddress().toIpPort() << " is "
           << (conn->connected() ? "UP" : "DOWN");
    conn->shutdown();
  }
}

int main()
{
  EventLoop loop;
  TcpServer server(&loop, InetAddress(1079), "Finger");
  server.setMessageCallback(onMessage);
  server.start();
  loop.loop();
}

//printf "msg\r\n" | nc 127.0.0.1 1079

//telnet 127.0.0.1 1079
