################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
commandLine.lss \

FLASH_IMAGE += \
commandLine.hex \

EEPROM_IMAGE += \
commandLine.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: commandLine.elf secondary-outputs

# Tool invocations
commandLine.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,commandLine.map -mmcu=atmega328p -o "commandLine.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

commandLine.lss: commandLine.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S commandLine.elf  >"commandLine.lss"
	@echo 'Finished building: $@'
	@echo ' '

commandLine.hex: commandLine.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex commandLine.elf  "commandLine.hex"
	@echo 'Finished building: $@'
	@echo ' '

commandLine.eep: commandLine.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex commandLine.elf  "commandLine.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: commandLine.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p commandLine.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) commandLine.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
