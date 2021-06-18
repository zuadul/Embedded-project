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
convey.lss \

FLASH_IMAGE += \
convey.hex \

EEPROM_IMAGE += \
convey.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: convey.elf secondary-outputs

# Tool invocations
convey.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,convey.map -mmcu=atmega328p -o "convey.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

convey.lss: convey.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S convey.elf  >"convey.lss"
	@echo 'Finished building: $@'
	@echo ' '

convey.hex: convey.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex convey.elf  "convey.hex"
	@echo 'Finished building: $@'
	@echo ' '

convey.eep: convey.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex convey.elf  "convey.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: convey.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p convey.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) convey.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
