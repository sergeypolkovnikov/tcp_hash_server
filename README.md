# tcp_hash_server

## build
~~~
g++ -std=c++20 -pthread -o tcp_hash_server ./tcp_hash_server.cpp -lssl -lcrypto
~~~

## start server
~~~
./tcp_hash_server
~~~

## test
~~~
python3 test.py
~~~

## docker
go to src dir and run
~~~
docker build -t tcp-hash-server .
docker run -p 9000:9000 --rm tcp-hash-server
~~~

