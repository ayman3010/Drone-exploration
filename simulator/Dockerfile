FROM ubuntu:18.04
LABEL Maintainer="Pierre-Yves Lajoie <pierre-yves.lajoie@polymtl.ca>"
LABEL argos-example.version="0.1"

# Install common dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    dpkg \ 
    git \
    pkg-config \
    python \
    python-dev \
    python-numpy \
    sudo \
    software-properties-common \
    && rm -rf /var/lib/apt/lists/*

# Install ARGoS dependencies
RUN apt-get update && apt-get install -y \
    wget \
    freeglut3-dev \
    qt5-default \
    libxi-dev \
    libxmu-dev \
    libfreeimage-dev \
    libfreeimageplus-dev \
    liblua5.2-dev \
    lua5.2 \
    liblua5.3-dev \
    lua5.3 \
    libboost-filesystem-dev \
    cmake \
    lcov \
    zlib1g-dev \
    nlohmann-json-dev \
    && rm -rf /var/lib/apt/lists/*

# Add dummy argument to force rebuild starting from that point
ARG UPDATE_ARGOS=unknown

# Install Argos from source
RUN cd /root/ &&\
    git clone https://github.com/MISTLab/argos3.git &&\
    cd argos3 &&\
    git checkout inf3995 &&\
    mkdir build_simulator &&\
    cd build_simulator &&\
    cmake ../src -DCMAKE_BUILD_TYPE=Debug \
     -DCMAKE_INSTALL_PREFIX=/usr \
     -DARGOS_BUILD_FOR=simulator \
     -DARGOS_THREADSAFE_LOG=ON \
     -DARGOS_DYNAMIC_LOADING=ON &&\
    make -j $(nproc)

RUN touch /root/argos3/build_simulator/argos3.1.gz &&\
    touch /root/argos3/build_simulator/README.html &&\
    cd /root/argos3/build_simulator &&\
    make install
RUN chmod +x /root/argos3/build_simulator/argos_post_install.sh &&\
    ./root/argos3/build_simulator/argos_post_install.sh &&\
    echo "\nsource /root/argos3/build_simulator/setup_env.sh\n" >> /.bashrc

# Install Argos WebViz plugin
RUN cd /root/ &&\
    git clone https://github.com/willRicard/argos3-webviz &&\
    cd argos3-webviz &&\
    git checkout crazyflie &&\
    mkdir build &&\
    cd build &&\
    cmake ../src -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr &&\
    make && make install


#################################
#          YOUR CODE            #
#################################

# Add dummy argument to force rebuild starting from that point
ARG UPDATE_CODE=unknown

# Clone your repository
# If your repository is private, you will need to use ssh keys, look here: 
# https://stackoverflow.com/a/23411161/8150481
# For now we clone some argos3 examples

EXPOSE 80

COPY ./simulator ./root/simulator

RUN cd /root/simulator &&\ 
    git clone --recurse-submodules https://github.com/socketio/socket.io-client-cpp.git

ADD start.sh /

CMD ./root/simulator/start.sh
