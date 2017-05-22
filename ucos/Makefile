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
# ---------------------------built-in %.a rules variable----------------------------
AR = arm-none-eabi-ar
ARFLAGS = rcs
# export CFLAGS CPPFLAGS

# ------------------------Get .c file's name and dir------------------------------
CSRC := $(shell find -name *.c)
CSRCDIR := $(dir $(CSRC))
CSRCDIR := $(sort $(CSRCDIR))
CSRC := $(notdir $(CSRC))
# ------------------------Get .s file's name and dir-------------------------------
SSRC := $(shell find -name *.s)
SSRCDIR := $(dir $(SSRC))
SSRCDIR := $(sort $(SSRCDIR))
SSRC := $(notdir $(SSRC))
# ------------------------Get .S file's name and dir--------------------------------
SXSRC := $(shell find -name *.S)
SXSRCDIR := $(dir $(SXSRC))
SXSRCDIR := $(sort $(SXSRCDIR))
SXSRC := $(notdir $(SXSRC))
# ------------------------Get .h file's dir-----------------------------------------
INCDIR = $(shell find -name *.h)
INCDIR := $(dir $(INCDIR))
INCDIR := $(sort $(INCDIR))
# ----------------------------------------------------------------------------------
vpath %.c $(CSRCDIR)
vpath %.s $(SSRCDIR)
vpath %.S $(SXSRCDIR)
vpath %.h $(INCDIR)
vpath %.o ./obj
vpath %.a ./obj

CPPFLAGS += $(addprefix -I,$(INCDIR))
OBJ := $(subst .c,.o,$(CSRC))
OBJ += $(subst .s,.o,$(SSRC))
OBJ += $(subst .S,.o,$(SXSRC))
# ------------------------Make Rules-----------------------------------------------

# test:
# 	@echo $(SXSRC)

all:libuc.a
sinclude $(CSRC:%.c=obj/%.d)
libuc.a:$(OBJ)
	$(AR) $(ARFLAGS) ./obj/$@ ./obj/*.o 
%.o: %.s
	$(AS) $(ASFLAGS) $(TARGET_MACH) -o ./obj/$@ $<
%.o: %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $(OUTPUT_OPTION) $<
obj/%.d:%.c 
	@$(CC) -M $(CPPFLAGS) $< >> $@
.PHONY:all clean distclean

clean:
	@-rm -r obj/*.o
	@echo "clean ucos"
distclean:
	@-rm -r obj
	@echo "distclean ucos"