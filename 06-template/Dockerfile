FROM debian 

ENV PATH=$PATH:/ipc/build/bin 

RUN apt-get update && apt-get install build-essential cmake -y

COPY . /ipc 
RUN cd ipc && mkdir build && cd build && cmake -DARCH=DOCKER .. && make
WORKDIR /ipc/build/bin 

ENTRYPOINT ["bash", "-c", "launch_processes"]