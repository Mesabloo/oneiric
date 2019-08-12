#!/bin/sh

# Sometimes Bochs leaves .lock files that prevent access to the image the next
# launch. We do this in order to ensure that this will never happen.
if [ -f "bin/oneiric.img.lock" ]; then
    rm "bin/oneiric.img.lock"
fi

bochs -f bochs.cfg -q $@
