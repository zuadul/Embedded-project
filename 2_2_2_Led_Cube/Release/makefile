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
2*2*2_Led_Cube.lss \

FLASH_IMAGE += \
2*2*2_Led_Cube.hex \

EEPROM_IMAGE += \
2*2*2_Led_Cube.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 2*2*2_Led_Cube.elf secondary-outputs

# Tool invocations
2*2*2_Led_Cube.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,2*2*2_Led_Cube.map -mmcu=atmega328p -o "2*2*2_Led_Cube.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

2*2*2_Led_Cube.lss: 2*2*2_Led_Cube.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 2*2*2_Led_Cube.elf  >"2*2*2_Led_Cube.lss"
	@echo 'Finished building: $@'
	@echo ' '

2*2*2_Led_Cube.hex: 2*2*2_Led_Cube.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 2*2*2_Led_Cube.elf  "2*2*2_Led_Cube.hex"
	@echo 'Finished building: $@'
	@echo ' '

2*2*2_Led_Cube.eep: 2*2*2_Led_Cube.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 2*2*2_Led_Cube.elf  "2*2*2_Led_Cube.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 2*2*2_Led_Cube.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p 2*2*2_Led_Cube.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 2*2*2_Led_Cube.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
