SRC=src
INC=include
BUILD=build
TARGET=app
OBJS=$(SRC)/main.o $(SRC)/Komodo.o $(SRC)/MemoryManager.o $(SRC)/GraphicsManager.o $(SRC)/ErrorHandler.o
LIBS= -lvita2d -lSceGxm_stub -lSceDisplay_stub -lSceSysmodule_stub -lSceCtrl_stub -lScePgf_stub -lScePvf_stub -lSceCommonDialog_stub -lpng -ljpeg -lfreetype -lz -lm -lc -lSceAppMgr_stub -lsoloud -lpthread -lSceAudio_stub

$(BUILD)/$(TARGET).vpk : $(BUILD)/eboot.bin
	vita-mksfoex -s TITLE_ID=APP000001 "app" $(BUILD)/param.sfo
	vita-pack-vpk -s $(BUILD)/param.sfo -a gameFiles=gameFiles -b $^ $@

$(BUILD)/eboot.bin : $(BUILD)/$(TARGET).velf
	vita-make-fself -s $^ $@

$(BUILD)/$(TARGET).velf : $(BUILD)/$(TARGET).elf
	vita-elf-create $^ $@

$(BUILD)/$(TARGET).elf : $(OBJS)
	arm-vita-eabi-g++ -std=c++17 -Wl,-q -fno-lto -DPLATFORM_PSVITA -I$(INC) $^ $(LIBS) -o $@
	mv $(SRC)/*.o $(BUILD)

%.o : %.cpp
	arm-vita-eabi-g++ -std=c++17 -Wl,-q -fno-lto -DPLATFORM_PSVITA -I$(INC) -c $< -o $@