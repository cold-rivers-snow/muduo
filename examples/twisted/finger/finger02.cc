#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"

using namespace muduo;
using namespace muduo::net;

int main()
{
  EventLoop loop;
  TcpServer server(&loop, InetAddress(1079), "Finger");
  server.start();
  loop.loop();
}

//nc 127.0.0.1 1079

//telnet 127.0.0.1 1079
