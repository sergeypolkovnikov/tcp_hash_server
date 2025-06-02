# tcp_hash_server

## build
~~~
mkdir build && cd build && cmake .. && make
~~~

## start server
~~~
./tcp_hash_server
~~~

## run test
~~~
python3 test.py
~~~

## run unit tests
~~~
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

