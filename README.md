# This is a high-performance server based on a web server and a skip list database.

# WebServer
The high-performance WEB server implemented in C++ can achieve tens of thousands of QPS after webbenchh stress testing

## function
* Using the IO multiplexing technology Epoll and thread pool to achieve the multi-threaded Reactor high concurrency model;
* Use regular and state machines to parse HTTP request packets to process requests for static resources;
* Use the standard library container to encapsulate the char to achieve automatic growth of the buffer;
* Timer based on the implementation of the small root heap to close the inactive connection that timed out;
* Implement an asynchronous log system with singleton mode and blocking queue to record the running status of the server;
* The RAII mechanism is used to realize the database connection pool, reduce the overhead of database connection establishment and closing, and realize the user registration and login function.

* Add logsys, threadpool test units (todo: timer, sqlconnpool, httprequest, httpresponse)

## Environmental requirements
* Linux
* C++14
* MySql

## Directory tree
```
.
├── code           
│   ├── buffer
│   ├── config
│   ├── http
│   ├── log
│   ├── timer
│   ├── pool
│   ├── server
│   └── main.cpp
├── test           unit test
│   ├── Makefile
│   └── test.cpp
├── resources      static
│   ├── index.html
│   ├── image
│   ├── video
│   ├── js
│   └── css
├── bin            
│   └── server
├── log            log file
├── webbench-1.5   stress test
├── build          
│   └── Makefile
├── Makefile
├── LICENSE
└── readme.md
```


## Project initiation
You need to configure the corresponding database first
```bash

create database yourdb;

// create a user table
USE yourdb;
CREATE TABLE user(
    username char(50) NULL,
    password char(50) NULL
)ENGINE=InnoDB;

// add data
INSERT INTO user(username, password) VALUES('name', 'password');
```

```bash
make
./bin/server
```

## unit test
```bash
cd test
make
./test
```

## stress test
![image-webbench](https://github.com/markparticle/WebServer/blob/master/readme.assest/%E5%8E%8B%E5%8A%9B%E6%B5%8B%E8%AF%95.png)
```bash
./webbench-1.5/webbench -c 100 -t 10 http://ip:port/
./webbench-1.5/webbench -c 1000 -t 10 http://ip:port/
./webbench-1.5/webbench -c 5000 -t 10 http://ip:port/
./webbench-1.5/webbench -c 10000 -t 10 http://ip:port/
```
* test enviroment: Ubuntu:19.10 cpu:i5-8400 内存:8G 
* QPS 10000+

## TODO
* config configuration
* Improve unit tests
* Implement a circular buffer
