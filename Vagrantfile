# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/xenial64"

  config.vm.provider "virtualbox" do |vb|
      vb.memory = "4096"
      vb.cpus = 4
  end

  config.vm.provision "shell", inline: <<-SHELL
    set -ev
    cd /vagrant
    sudo apt -y install python g++
    
    cd externals
    wget http://nodejs.org/dist/v9.0.0/node-v9.0.0.tar.gz
    wget http://nodejs.org/dist/v9.0.0/node-v9.0.0-headers.tar.gz

    tar -xzvf node-v9.0.0.tar.gz
    tar -xzvf node-v9.0.0-headers.tar.gz

    cd node-v9.0.0
    ./configure --shared
    make -j4

    cp out/Release/lib.target/libnode.so.59 ../libnode.so.59
    cp out/Release/lib.target/libnode.so.59 ../libnode.59.so

    cd ../..
    g++ src/main.cc -std=c++11 -L ./externals -lnode.59 -I ./externals/node-v9.0.0/include/node -o main
    LD_LIBRARY_PATH=./externals ./main --version
  SHELL
end
