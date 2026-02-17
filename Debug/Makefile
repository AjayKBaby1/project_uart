CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

MCU = cortex-m4

CFLAGS = -mcpu=$(MCU) -mthumb -O2 -g -Wall \
	-ICore/Inc \
	-ffunction-sections -fdata-sections

LDSCRIPT = ../Linker/linker_script.ld
LDFLAGS  = -T $(LDSCRIPT) -nostartfiles -Wl,--gc-sections

BUILD = ../build

SRCS = $(wildcard ../Core/Src/*.c)
SRCS += $(wildcard ../Core/startup/*.c)

OBJS = $(patsubst ../Core/%, $(BUILD)/Core/%, $(SRCS:.c=.o))

TARGET = $(BUILD)/project.elf
BIN    = $(BUILD)/project.bin

all: $(TARGET) $(BIN) size

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

size: $(TARGET)
	$(SIZE) $<

$(BUILD)/Core/Src/%.o: ../Core/Src/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/Core/startup/%.o: ../Core/startup/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD):
	@mkdir -p $@

clean:
	rm -rf $(BUILD)

