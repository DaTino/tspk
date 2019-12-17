FROM ubuntu
MAINTAINER apmaiocco@gmail.com
RUN apt-get update -y
RUN apt-get install python3-pip -y
RUN apt-get install git -y
RUN apt-get install vim -y

RUN pip3 install numpy
RUN pip3 install matplotlib
RUN git clone https://github.com/DaTino/tspk.git
RUN chmod 777 -R ./tspk

# Building: docker build -t tspk
# Running:  docker run -it tspk
