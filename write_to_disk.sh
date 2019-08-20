#!/bin/sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 <drive>"
fi

sudo dd if=bin/oneiric.img of=$1 bs=2048 status=progress