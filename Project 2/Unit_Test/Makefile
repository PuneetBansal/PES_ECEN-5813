#-*-Makefile-*-


TARGET=cross_compile
PLATFORM=HOST
SOURCE= main.c circular_buffer.c 
SOURCE_KL25Z= $(SOURCE) system_MKL25Z4.c
LINKER_FILE = MKL25Z128xxx4_flash.ld
INCLUDES = circular_buffer.h 
CPU = cortex-m0plus
ARCHITECTURE = armv6-m		
FPU = fpv4-sp-d16
SPECS = nosys.specs



ifeq ($(PLATFORM),HOST)
	CC=gcc
	CFFLAGS=-Wall -Werror -g -O0 -std=c99
	LDFLAGS =-Wl,-Map=$(TARGET).map
	OBJFILES = main.o circular_buffer.o
	CFILES = main.c circular_buffer.c
endif
	

ifeq ($(PLATFORM),KL25Z)
	CC = arm-none-eabi-gcc
	CFFLAGS = -Wall -Werror -g -O0 -std=c99 -mcpu=$(CPU) \
		 -mthumb -march=$(ARCHITECTURE) -mfloat-abi=soft \
		 -mfpu=$(FPU) --specs=$(SPECS)
	LDFLAGS = -Wl,-Map=$(TARGET).map -T $(LINKER_FILE)
	OBJFILES = main.o circular_buffer.o startup_MKL25Z4.o
	CFILES= main.c circular_buffer.c system_MKL25Z4.c
	INCLUDES=-I includes/CMSIS \
			-I includes/kl25z

endif

ifeq ($(PLATFORM),BBB)
	CC = arm-linux-gnueabihf-gcc
	CFFLAGS = -Wall -Werror -g -O0 -std=c99
	LDFLAGS = -Wl,-Map=$(TARGET).map
	OBJFILES = main.o circular_buffer.o
	CFILES = main.c circular_buffer.c
endif
	

cross_compile: $(OBJFILES)
	$(CC) $(CFFLAGS) $(LDFLAGS) $(CFILES) $(INCLUDES) -o $(TARGET).elf

proj2: main.o circular_buffer.o
	gcc main.c circular_buffer.c -o proj2 -lm
main.o: main.c circular_buffer.h
	gcc -c main.c
circular_buffer.o: circular_buffer.c circular_buffer.h
	gcc -c circular_buffer.c
test1: test.c circular_buffer.c circular_buffer.h
	gcc test.c circular_buffer.c -lm -lcunit -o test1 
startup_MKL25Z4.o:  startup_MKL25Z4.S
	$(CC) $(CFFLAGS) $(LDFLAGS) $(INCLUDES) -c startup_MKL25Z4.S
clean:
	rm *.o *.elf *.map test1 proj2



