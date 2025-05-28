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

## unit test
~~~
g++ -std=c++20 -I/usr/include -pthread test.cpp -o hasher_test -lgtest -lgtest_main -lcrypto./
./hasher_test
~~~

gtest should be installed. If not you can install it in the following way
~~~
sudo apt update
sudo apt install libgtest-dev
sudo apt install cmake
cd /usr/src/gtest
sudo cmake .
sudo make
cd /lib
sudo cp *.a /usr/lib
~~~

## docker
go to src dir and run
~~~
docker build -t tcp-hash-server .
docker run -p 9000:9000 --rm tcp-hash-server
~~~

