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

