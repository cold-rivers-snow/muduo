#!/bin/sh

killall pingpong_server 2>/dev/null
timeout=${timeout:-100}
bufsize=16384

# POSIX compliant way to get script directory
SCRIPT_DIR=$(cd "$(dirname "$0")"; pwd)
# Path to build/bin relative to this script (assuming script is in examples/pingpong)
BIN_DIR="$SCRIPT_DIR/../../build/bin"

if [ ! -x "$BIN_DIR/pingpong_server" ]; then
    echo "Error: pingpong_server not found at $BIN_DIR/pingpong_server"
    exit 1
fi
if [ ! -x "$BIN_DIR/pingpong_client" ]; then
    echo "Error: pingpong_client not found at $BIN_DIR/pingpong_client"
    exit 1
fi

for nosessions in 100 1000; do
  for nothreads in 1 2 3 4; do
    sleep 5
    echo "Bufsize: $bufsize Threads: $nothreads Sessions: $nosessions"
    $BIN_DIR/pingpong_server 0.0.0.0 55555 $nothreads $bufsize & srvpid=$!
    $BIN_DIR/pingpong_client 127.0.0.1 55555 $nothreads $bufsize $nosessions $timeout
    kill -9 $srvpid
  done
done