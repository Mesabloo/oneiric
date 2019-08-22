#!/bin/sh

./omake.py $@ -c "$PWD/std/build_std.py" -a run && \
./omake.py $@ -c "$PWD/kern/build_kernel.py" -a run && \
./omake.py $@ -c "$PWD/build_bin.py" -a run