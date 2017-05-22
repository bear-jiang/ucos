$(shell mkdir ./obj 2>/dev/null )
# ------------------------------------built-in %.o%.c rules variable -----------------
CC = arm-none-eabi-gcc
ifneq "$(origin CFLAGS)" "environment"
CFLAGS = -g -mtune=cortex-m4 -mthumb -std=c99 -fdata-sections -mfloat-abi=soft \
 -march=armv7-m -mthumb-interwork -mapcs-frame
endif
ifneq "$(origin CPPFLAGS)" "environment"
CPPFLAGS = -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F407xx 
endif
CPPFLAGS := $(filter-out -I%, $(CPPFLAGS) )
TARGET_ARCH = 
OUTPUT_OPTION = -o ./obj/$@
# ---------------------------built-in %.s rules variable----------------------------
AS = arm-none-eabi-as
ASFLAGS = -c -g -mcpu=cortex-m4 -mthumb-interwork -mthumb -mfloat-abi=soft
TARGET_MACH = 
# ---------------------------built-in %.a rules variable-------------------------
AR = arm-none-eabi-ar
ARFLAGS = rcs
# ---------------------------Export environment variable to sub-dir Makefiles
export CFLAGS CPPFLAGS

# ------------------------Get .c file's name and dir------------------------------
CSRC := $(shell ls *.c)
CSRCDIR := $(dir $(CSRC))
CSRCDIR := $(sort $(CSRCDIR))
CSRC := $(notdir $(CSRC))
# ------------------------Get .s file's name and dir-----------------------------
SSRC := $(shell ls *.s)
SSRCDIR := $(dir $(SSRC))
SSRCDIR := $(sort $(SSRCDIR))
SSRC := $(notdir $(SSRC))
# ------------------------Get .h file's dir---------------------------------------
INCDIR += $(shell find . | grep '\>.h')
INCDIR += $(shell find ../ucos/ | grep '\>.h')
INCDIR += $(shell find ../app/ | grep '\>.h')
INCDIR := $(dir $(INCDIR))
INCDIR := $(sort $(INCDIR))
# -------------------------------------------------------------------------------
vpath %.c $(CSRCDIR)
vpath %.s $(SSRCDIR)
vpath %.h $(INCDIR)
vpath %.o ./obj
vpath %.a ./obj
vpath %.a ./stm32f4_driver/obj
vpath %.a ./stm32f4_driver/stm32f4_lib/obj

CPPFLAGS += $(addprefix -I,$(INCDIR))
OBJ = $(subst .c,.o,$(CSRC))
OBJ += $(subst .s,.o,$(SSRC))
# ------------------------Make Rules---------------------------------------------

# test:
# 	@echo $(INCDIR)

all:libbsp.a driver
sinclude $(CSRC:%.c=obj/%.d)
libbsp.a:$(OBJ)
	$(AR) $(ARFLAGS) ./obj/$@ ./obj/*.o 
driver:
	cd stm32f4_driver&&make&&cd ..
%.o: %.s
	$(AS) $(ASFLAGS) $(TARGET_MACH) -o ./obj/$@ $<
obj/%.d:%.c 
	@$(CC) -M $(CPPFLAGS) $< >> $@
clean:
	-rm -r obj/*.o
distclean:
	-rm -r obj
.PHONY:all clean distclean driver