FROM randomdude/gcc-cross-x86_64-elf

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y nasm
RUN apt-get install -y xorriso
RUN apt-get install -y curl
RUN apt-get install -y git
RUN apt-get install -y clang
RUN apt-get install -y llvm lld

VOLUME /root/env
WORKDIR /root/env