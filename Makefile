LD = arm-none-eabi-ld
OBJCP = arm-none-eabi-objcopy
LIBDIR = ucos/obj
LIBDIR += bsp/obj
LIBDIR += bsp/stm32f4_driver/obj
LIBDIR += bsp/stm32f4_driver/stm32f4_lib/obj
LIBDIR := $(addprefix -L,$(LIBDIR))
LDSCRIPT = $(shell ls *.ld)
LDFLAGS = -T $(LDSCRIPT)
LDFLAGS += -L /home/bear/gcc-arm-none-eabi-5_4-2016q2/arm-none-eabi/lib/thumb/
LDFLAGS += -L /home/bear/gcc-arm-none-eabi-5_4-2016q2/lib/gcc/arm-none-eabi/5.4.1/armv7-m
CFLAGS = -g -mtune=cortex-m4 -mthumb -std=c99 -fdata-sections -mfloat-abi=soft \
 -march=armv7-m -mthumb-interwork -mapcs-frame
CPPFLAGS = -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F407xx -D_UCOS
export CFLAGS CPPFLAGS



# test:
# 	echo $(LIBDIR)

all:main.bin

main.bin:main.elf
	$(OBJCP) -Obinary $^ $@
main.elf:ucos bsp app
	$(LD) $(LDFLAGS) app/obj/*.o $(LIBDIR) \
	 -lbsp -luc -ldriver -lst -lm -lc -lgcc -o $@
ucos:
	cd ucos&&make&&cd ..
bsp:
	cd bsp&&make&&cd ..
app:
	cd app&&make&&cd ..

clean:
	@-rm *.elf *.bin 2>/dev/null
	cd ucos&&make clean&&cd ..
	cd bsp&&make clean&&cd ..
	cd app&&make clean&&cd ..
	@echo "remove all .o .a"
distclean:
	@-rm *.elf *.bin 2>/dev/null
	cd ucos&&make distclean&&cd ..
	cd bsp&&make distclean&&cd ..
	cd app&&make distclean&&cd ..
	@echo "remove all"
upload:main.bin
	st-flash --reset write main.bin 0x8000000
.PHONY:all distclean clean ucos bsp app upload