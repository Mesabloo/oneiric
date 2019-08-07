sudo losetup -Pf bin/oneiric.img    \
&& sudo mount /dev/loop0p1 /mnt \
&& sudo cp src/oneiric.bin /mnt \
&& sudo umount /mnt             \
&& sudo losetup -d /dev/loop0   \
&& echo "Done!"
