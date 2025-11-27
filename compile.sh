export VITASDK=/usr/local/vitasdk
export PATH=$VITASDK/bin:$PATH
for i in ../main Script modulesHandler MemoryManager GameObject ItemHandler Game InputManager Engine AnimatedImage Camera; do
arm-vita-eabi-g++ -std=c++17 -Wl,-q -fno-lto -Iinclude/vita -c src/vita/$i.cpp -o src/vita/$i.o
echo $i has been compiled !
done
arm-vita-eabi-g++ -std=c++17 -Wl,-q -fno-lto -Iinclude/vita src/main.o src/vita/Script.o src/vita/modulesHandler.o src/vita/MemoryManager.o src/vita/GameObject.o src/vita/ItemHandler.o src/vita/Game.o src/vita/InputManager.o src/vita/Engine.o src/vita/AnimatedImage.o src/vita/Camera.o -lvita2d -lSceDisplay_stub -lSceGxm_stub -lSceSysmodule_stub -lSceCtrl_stub -lScePgf_stub -lScePvf_stub -lSceCommonDialog_stub -lfreetype -lpng -ljpeg -lz -lm -lc -lSceAppMgr_stub -o MyApp.elf
echo elf is created !
vita-elf-create MyApp.elf MyApp.velf
echo velf is created !
vita-make-fself -s MyApp.velf eboot.bin
echo eboot is created !
vita-mksfoex -s TITLE_ID=MYAPP0001 "application" param.sfo
echo param.sfo is created !
vita-pack-vpk -s param.sfo -a assets=assets -b eboot.bin application.vpk
echo vpk is created !
rm src/main.o src/vita/*.o MyApp.elf MyApp.velf param.sfo eboot.bin
echo temp files has been removed, game is ready !