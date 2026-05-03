FROM ubuntu:14.04
MAINTAINER mcuriel
RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get -y install gcc
RUN apt-get -y install nano
RUN apt-get -y install libzmq3-dev
COPY ./zhelpers.h /home/
COPY ./psenvpub.c /home/
WORKDIR /home/
EXPOSE 5563
RUN gcc -o psenvpub psenvpub.c -lzmq
CMD ["./psenvpub"]


