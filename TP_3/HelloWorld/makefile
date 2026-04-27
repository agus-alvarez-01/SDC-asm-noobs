.PHONY: all build run clean

# Default target
all: build

# Option 1: Only build the image
build: main.img

# Option 2: Build the image if needed and run QEMU
run: main.img
	qemu-system-x86_64 -hda main.img

# Option 3: Burn to physical USB drive (Requires sudo password)
burn: main.img
	@echo "WARNING: Writing to /dev/sdc. Make sure this is your pendrive!"
	sudo dd if=main.img of=/dev/sdc
	@echo "Done! The drive is ready to boot."

# Rule to link the object file into the final binary image
main.img: main.o link.ld
	ld --oformat binary -o main.img -T link.ld main.o

# Rule to assemble the source code into an object file
main.o: main.S
	as -g -o main.o main.S

# Utility to clean up generated files
clean:
	rm -f main.o main.img