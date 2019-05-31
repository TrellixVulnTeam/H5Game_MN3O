#!/bin/bash

rm -rf /usr/local/include/zmq.h
rm -rf /usr/local/include/zmq.hpp
rm -rf /usr/local/include/zmq_utils.h
rm -rf /usr/local/lib/libzmq.so
cp ./zmq.h /usr/local/include/zmq.h
cp ./zmq.hpp /usr/local/include/zmq.hpp
cp ./zmq_utils.h /usr/local/include/zmq_utils.h
cp ./libzmq.so.3.1.0 /usr/local/lib/libzmq.so.3.1.0
ln /usr/local/lib/libzmq.so.3.1.0 /usr/local/lib/libzmq.so.3
ln /usr/local/lib/libzmq.so.3.1.0 /usr/local/lib/libzmq.so
