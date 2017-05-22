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

# ------------------------Get .c file's name and dir------------------------------
CSRC := $(shell find . | grep '\>.c')
CSRCDIR := $(dir $(CSRC))
CSRCDIR := $(sort $(CSRCDIR))
CSRC := $(notdir $(CSRC))
# ------------------------Get .h file's dir---------------------------------------
INCDIR += $(shell find . | grep '\>.h')
INCDIR += $(shell find ../ucos/ | grep '\>.h')
INCDIR += $(shell find ../bsp/ | grep '\>.h')
INCDIR := $(dir $(INCDIR))
INCDIR := $(sort $(INCDIR))
# -------------------------------------------------------------------------------
vpath %.c $(CSRCDIR)
vpath %.h $(INCDIR)
vpath %.o ./obj
vpath %.a ./obj

CPPFLAGS += $(addprefix -I,$(INCDIR))
OBJ = $(subst .c,.o,$(CSRC))
# ------------------------Make Rules---------------------------------------------

# test:
# 	@echo $(INCDIR)
all:$(OBJ)
sinclude $(CSRC:%.c=obj/%.d)
obj/%.d:%.c 
	@$(CC) -M $(CPPFLAGS) $< >> $@
clean:
	-rm -r obj/*.o
distclean:
	-rm -r obj
.PHONY:all clean distclean