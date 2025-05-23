FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y g++ make libssl-dev

COPY tcp_hash_server.cpp /app/tcp_hash_server.cpp

WORKDIR /app
RUN g++ -std=c++20 -pthread -o tcp_hash_server tcp_hash_server.cpp -lssl -lcrypto

EXPOSE 9000
CMD ["./tcp_hash_server"]