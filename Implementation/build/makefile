#* Created on: Jul 14, 2015
#* This program is free software; you can redistribute it and/or
#* modify it under the terms of the GNU General Public License
#* as published by the Free Software Foundation; either version 2
#* of the License, or (at your option) any later version.
#* 
#* This program is distributed in the hope that it will be useful,
#* but WITHOUT ANY WARRANTY; without even the implied warranty of
#* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#* GNU General Public License for more details.
#* Autor: Eric Sanchez B. esanchez.briones@gmail.com
include toolchain.mk

PROJECT_NAME=avr_at90firmware

BSP_SRC= ../src
BSP_HEADERS= -I"../include" \
		     
BSP_OBJECTS_DIR= obj

# Default char type is unsigned
AVR_CC_FLAGS= -funsigned-char

#Default bit field is unsigned
AVR_CC_FLAGS+= -funsigned-bitfields

#No optimization, optimize for speed (level 1 - 3), optimize for size
AVR_CC_FLAGS+= -Os

#Prepare functions for garbage collection, if a function is never used, its memory will be scrapped
AVR_CC_FLAGS+= -ffunction-sections

# these flags force the compiler to put every function and variable in its own section
AVR_CC_FLAGS+= -fdata-sections

#Pack structure members together
AVR_CC_FLAGS+= -fpack-struct

#Allocate only as many bytes needed by the enumerated types
AVR_CC_FLAGS+= -fshort-enums

#Relax branches
AVR_CC_FLAGS+= -mrelax

#Debug Level
AVR_CC_FLAGS+= -g0

# All warnings
AVR_CC_FLAGS+= -Wall

# MCU Declaration
AVR_CC_FLAGS+= -mmcu=at90can128 -D F_CPU=16000000UL 

AVR_CC_FLAGS+= -c

AVR_CC_FLAGS+= -std=gnu99


BSP_OBJECTS= \
	$(BSP_OBJECTS_DIR)/usart.o \
	$(BSP_OBJECTS_DIR)/watchdog.o \
	$(BSP_OBJECTS_DIR)/Indicator_Driver.o \
	$(BSP_OBJECTS_DIR)/twi_at90can128.o \
	$(BSP_OBJECTS_DIR)/main.o



$(BSP_OBJECTS_DIR)/%.o:$(BSP_SRC)/%.c
	@echo "Building file: $@"
	@echo Invoking: AVR/GNU Linker : 4.8.1
	@$(AVR_CC) -x c $(AVR_CC_FLAGS) $(BSP_HEADERS) "$<" -o "$@"
	@echo "Finished building: $<"

default: all

all: $(PROJECT_NAME).elf $(PROJECT_NAME).hex
	@$(AVR_SIZE) -C --mcu=at90can128 $(PROJECT_NAME).elf

size:
	@$(AVR_SIZE) -C --mcu=at90can128 $(PROJECT_NAME).elf

$(PROJECT_NAME).elf:$(BSP_OBJECTS)
	@$(AVR_CC) -o $(PROJECT_NAME).elf $(BSP_OBJECTS) -Wl,-Map="$(PROJECT_NAME).map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=at90can128	

$(PROJECT_NAME).hex:
	@$(AVR_OBJ_COPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "$(PROJECT_NAME).elf" "$(PROJECT_NAME).hex"
	@$(AVR_OBJ_DUMP) -h -S "$(PROJECT_NAME).elf" > "$(PROJECT_NAME).lss"
	@$(AVR_OBJ_COPY) -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "$(PROJECT_NAME).elf" "$(PROJECT_NAME).srec"
    

flash:
	@echo "Dragon Flash"
	./atprogram -t jtagice3 -i jtag -d at90can128 chiperase
	./atprogram -t jtagice3 -i jtag -d at90can128 program -f $(PROJECT_NAME).elf

clean:
	-rm -rf $(BSP_OBJECTS) $(PROJECT_NAME).elf $(PROJECT_NAME).map $(PROJECT_NAME).lss  $(PROJECT_NAME).srec $(PROJECT_NAME).hex