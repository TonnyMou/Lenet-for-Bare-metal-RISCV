TARGET_ARCH ?= rv64imac
ifeq ($(TARGET_ARCH),rv64imac)
  RISCV_PREFIX = riscv64-unknown-elf
  ABI          = lp64
else ifeq ($(TARGET_ARCH),rv32imac)
  RISCV_PREFIX = riscv32-unknown-elf
  ABI          = ilp32
else
  $(error Unsupported TARGET_ARCH ($(TARGET_ARCH)))
endif
RISCV_PREFIX = riscv64-unknown-elf
CXX = $(RISCV_PREFIX)-g++
OBJCOPY = $(RISCV_PREFIX)-objcopy
#-nostdlib
CXXFLAGS = -march=$(TARGET_ARCH) -mabi=$(ABI) -Wall -O2  -nostartfiles -static -mcmodel=medany
#LDFLAGS = -lgcc
LDFLAGS = -T /home/ubantu/lenetbuild/lenet0505/link.ld -lc -nostartfiles -static -mcmodel=medany -lgcc
SRC = _start.S main.cpp trace_io.cpp lenet_layer.cpp
OBJ = $(SRC:.cpp=.o)
OBJ := $(OBJ:.S=.o)  # 处理 _start.S

TARGET = main.elf
HEX = main.hex
.PHONY: all clean
all: $(HEX)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) -lgcc 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.S
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(HEX): $(TARGET)
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f *.o *.elf *.hex

