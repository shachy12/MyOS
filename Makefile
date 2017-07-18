CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
PLATFORM = qemu-arm

CFLAGS = -O0 \
	 -nostartfiles -T platform/$(PLATFORM)/memory_layout.ld \
	 -fno-builtin -Iplatform/$(PLATFORM) -I. \
	 -ansi -pedantic -Wall -Wextra -march=armv6 -msoft-float -fPIC -mapcs-frame -marm


OUTPUT_DIR = build

FILES = $(shell find . -type f -iname "*.[cs]")

TARGET = $(OUTPUT_DIR)/os.bin
all: $(TARGET)

$(TARGET): $(FILES)
	mkdir -p $(OUTPUT_DIR)
	$(CROSS_COMPILE)gcc $(CFLAGS) $^ -o $(OUTPUT_DIR)/os.elf
	$(CROSS_COMPILE)objcopy -O binary $(OUTPUT_DIR)/os.elf $(TARGET)
qemu: $(TARGET)
	echo "Press Ctrl-A and then X to exit QEMU"
	echo
	QEMU_AUDIO_DRV=none qemu-system-arm -s -M versatilepb -cpu arm1176 -serial mon:stdio -append 'console=ttyS0' -nographic -kernel $(TARGET)

clean:
	rm -rf $(OUTPUT_DIR)
