########################################
# TOOLCHAIN
########################################
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

########################################
# MCU SETTINGS (STM32F303 - Cortex-M4F)
########################################
MCU = cortex-m4

CPU_FLAGS = -mcpu=$(MCU) -mthumb \
            -mfpu=fpv4-sp-d16 -mfloat-abi=hard

########################################
# INCLUDE PATHS
########################################
INCLUDES = \
	-I../Core/Inc \
	-I../../Drivers/CMSIS/Include \
	-I../../Drivers/CMSIS/Device/ST/STM32F3xx/Include

########################################
# COMPILER FLAGS
########################################
CFLAGS = $(CPU_FLAGS) -O2 -g -Wall \
         -ffunction-sections -fdata-sections \
         -DSTM32F303x8 \
         -DDEV2 \
         $(INCLUDES)

########################################
# LINKER
########################################
LDSCRIPT = ../../Linker/linker_script.ld

LDFLAGS = $(CPU_FLAGS) -T $(LDSCRIPT) \
          -Wl,--gc-sections -nostartfiles

########################################
# BUILD DIRECTORY
########################################
BUILD = build

########################################
# SOURCE FILES
########################################
SRCS = $(wildcard ../Core/Src/*.c)
SRCS += $(wildcard ../Core/startup/*.c)

########################################
# OBJECT FILES
########################################
OBJS = $(patsubst ../Core/%, $(BUILD)/%, $(SRCS:.c=.o))

########################################
# TARGETS
########################################
TARGET = $(BUILD)/dev2_project.elf
BIN    = $(BUILD)/dev2_project.bin

########################################
# DEFAULT TARGET
########################################
all: $(TARGET) $(BIN) size

########################################
# LINK
########################################
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

########################################
# GENERATE BINARY
########################################
$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

########################################
# SHOW SIZE
########################################
size: $(TARGET)
	$(SIZE) $<

########################################
# COMPILE CORE SRC
########################################
$(BUILD)/Src/%.o: ../Core/Src/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

########################################
# COMPILE STARTUP
########################################
$(BUILD)/startup/%.o: ../Core/startup/%.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

########################################
# CREATE BUILD FOLDER
########################################
$(BUILD):
	@mkdir -p $@

########################################
# CLEAN
########################################
clean:
	rm -rf $(BUILD)
