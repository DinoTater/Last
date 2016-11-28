qemu-system-x86_64 -hda vdisk -m 520m -smp $1 -serial /dev/pts/1 -serial /dev/pts/2 \
-parallel /dev/pts/3 -localtime #-boot d
