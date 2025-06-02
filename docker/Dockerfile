FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive \
    apt-get install -y build-essential libssl-dev && \
    apt-get clean

COPY ../src/tcp_hash_server.cpp /app/tcp_hash_server.cpp

WORKDIR /app
RUN g++ -std=c++17 -pthread -o tcp_hash_server tcp_hash_server.cpp -lssl -lcrypto

EXPOSE 9000
CMD ["./tcp_hash_server"]