docker run --rm -it -v "%cd%":/root/env luaos-buildenv make all
qemu-system-x86_64 -M q35 -m 2G -cdrom template-x86_64.iso -boot d -serial mon:stdio -device virtio-keyboard