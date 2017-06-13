#!/bin/bash
autoreconf -vif || exit 1
chmod +x configure || exit 1
./configure --prefix=/usr || exit 1
make -j5 || exit 1

