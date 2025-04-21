##!/bin/bash
#
# scripts/build.sh
# (c) Copyright 2013
# Allwinner Technology Co., Ltd. <www.allwinnertech.com>
# James Deng <csjamesdeng@allwinnertech.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.


sudo apt install git bc bison build-essential curl flex libsdl1.2-dev 
sudo apt install g++-multilib gcc-multilib gnupg gperf libncurses5-dev 
sudo apt install imagemagick lib32ncurses5-dev lib32readline-dev squashfs-tools 
sudo apt install lib32z1-dev liblz4-tool xsltproc libssl-dev libwxgtk3.0-dev 
sudo apt install libxml2 libxml2-utils schedtool lzop pngcrush rsync 
sudo apt install yasm zip zlib1g-dev python device-tree-compiler 
sudo apt install python-pip gawk openjdk-8-jdk u-boot-tools patchelf expect
sudo pip install pyelftools

sudo apt-get install g++ make subversion  libxml-parser-perl unzip wget xz-utils vim zlibc zlib1g ccache gettext 