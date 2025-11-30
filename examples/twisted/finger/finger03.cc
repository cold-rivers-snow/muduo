#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"
#include "muduo/base/Logging.h"

using namespace muduo;
using namespace muduo::net;

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->connected())
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
  server.setConnectionCallback(onConnection);
  server.start();
  loop.loop();
}

//printf "msg\r\n" | nc 127.0.0.1 1079

//telnet 127.0.0.1 1079
