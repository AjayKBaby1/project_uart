CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

MCU = cortex-m4

# Include paths
INCLUDES = \
	-I../../Core/Inc \
	-I../../Drivers/CMSIS/Include \
	-I../../Drivers/CMSIS/Device/ST/STM32F3xx/Include

# Compiler flags
CFLAGS = -mcpu=$(MCU) -mthumb -O2 -g -Wall \
	$(INCLUDES) \
	-ffunction-sections -fdata-sections

# Linker script
LDSCRIPT = ../Linker/linker_script.ld
LDFLAGS  = -T $(LDSCRIPT) -nostartfiles -Wl,--gc-sections

# Build folder
BUILD = build

# Source files for Dev1 only
SRCS = $(wildcard ../Core/Src/*.c)
SRCS += $(wildcard ../Core/startup/*.c)

# Object files inside build folder
OBJS = $(patsubst ../Core/%, $(BUILD)/%, $(SRCS:.c=.o))

# Targets
TARGET = $(BUILD)/dev1_project.elf
BIN    = $(BUILD)/dev1_project.bin

# Default target
all: $(TARGET) $(BIN) size

# Link
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

# Generate binary
$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

# Show size
size: $(TARGET)
	$(SIZE) $<

# Compile Src files
$(BUILD)/Src/%.o: ../Core/Src/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile startup files
$(BUILD)/startup/%.o: ../Core/startup/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build folder
$(BUILD):
	@mkdir -p $@

# Clean
clean:
	rm -rf $(BUILD)
