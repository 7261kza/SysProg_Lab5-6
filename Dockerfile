FROM Ubuntu:20200122
WORKDIR home
RUN apt update
RUN apt-get install gcc build-essential gcc-multilib
COPY .asm.cpp home
