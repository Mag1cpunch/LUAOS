docker run --rm -it -v "%cd%":/root/env luaos-buildenv make
qemu-system-x86_64 -drive format=raw,file=./kernel/bin/kernel,if=floppy -serial mon:stdio -device virtio-keyboard