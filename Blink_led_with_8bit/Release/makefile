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
Blink_led_with_8bit.lss \

FLASH_IMAGE += \
Blink_led_with_8bit.hex \

EEPROM_IMAGE += \
Blink_led_with_8bit.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Blink_led_with_8bit.elf secondary-outputs

# Tool invocations
Blink_led_with_8bit.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Blink_led_with_8bit.map -mmcu=atmega328p -o "Blink_led_with_8bit.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Blink_led_with_8bit.lss: Blink_led_with_8bit.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Blink_led_with_8bit.elf  >"Blink_led_with_8bit.lss"
	@echo 'Finished building: $@'
	@echo ' '

Blink_led_with_8bit.hex: Blink_led_with_8bit.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Blink_led_with_8bit.elf  "Blink_led_with_8bit.hex"
	@echo 'Finished building: $@'
	@echo ' '

Blink_led_with_8bit.eep: Blink_led_with_8bit.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Blink_led_with_8bit.elf  "Blink_led_with_8bit.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Blink_led_with_8bit.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Blink_led_with_8bit.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Blink_led_with_8bit.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
