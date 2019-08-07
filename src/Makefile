CC = gcc
C_FLAGS = -Wall -m32 -nostdlib -fno-builtin -fno-leading-underscore
AS = as
AS_FLAGS = --32
LD = ld
LD_FLAGS = -melf_i386

objects = loader.o kernel.o stderr.o stdio.o

%.o: %.c
	$(CC) $(C_FLAGS) -o $@ -c $<

%.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<
	
oneiric.bin: $(objects)
	$(LD) $(LD_FLAGS) -n -T link.ld -o $@ $^
	
clean:
	find -name "*~" -delete
	rm -rf $(objects) oneiric.bin
