FROM ubuntu
MAINTAINER apmaiocco@gmail.com
RUN apt-get update
RUN apt-get install python3-pip
RUN pip3 install numpy
RUN pip3 install matplotlib
