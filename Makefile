INC = include
SRC = src
OBJS = src/main.o src/vita/Script.o src/vita/modulesHandler.o src/vita/MemoryManager.o src/vita/GameObject.o src/vita/ItemHandler.o src/vita/Game.o src/vita/InputManager.o src/vita/Engine.o src/vita/AnimatedImage.o src/vita/Camera.o src/vita/Collider.o src/sampleClasses/Commander.o src/sampleClasses/Map.o src/sampleClasses/Node.o
LIBS = -lvita2d -lSceDisplay_stub -lSceGxm_stub -lSceSysmodule_stub -lSceCtrl_stub -lScePgf_stub -lScePvf_stub -lSceCommonDialog_stub -lpng -ljpeg -lfreetype -lz -lm -lc -lSceAppMgr_stub 
TARGET = myApp
TITLE_ID=MYAPP0001
ASSETS=assets

$(TARGET).vpk : eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLE_ID) "$(TARGET)" param.sfo
	vita-pack-vpk -s param.sfo -a $(ASSETS)=$(ASSETS) -b $^ $@
	rm -r *.velf *.elf *.bin *.sfo $(SRC)/vita/*.o $(SRC)/*.o $(SRC)/sampleClasses/*.o

eboot.bin : $(TARGET).velf
	vita-make-fself -s $^ $@

$(TARGET).velf : $(TARGET).elf
	vita-elf-create $^ $@

$(TARGET).elf : $(OBJS)
	arm-vita-eabi-g++ -std=c++17 -Wl,-q -fno-lto -I$(INC)/vita -I$(INC)/sampleClasses $^ $(LIBS) -o $@ 

%.o : %.cpp
	arm-vita-eabi-g++ -std=c++17 -Wl,-q -fno-lto -I$(INC)/vita -I$(INC)/sampleClasses -c $< -o $@