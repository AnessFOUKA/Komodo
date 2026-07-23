#include <iostream>
#include "Komodo.hpp"

#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_speech.h"

SoLoud::Soloud gSoloud; // SoLoud engine
SoLoud::Wav gWave;      // One wave file
int main(){

	gSoloud.init(); // Initialize SoLoud
	gWave.load("app0:/assets/music.ogg"); // Load a wave
	gSoloud.play(gWave); // Play the wave
	SoLoud::Speech sp;
	sp.setText("Hello world.  You will be assimilated.");
	gSoloud.play(sp);

	while (1) {
		sceKernelDelayThread(1000 * 1000);
	}

	/*return 0;
    MemoryManager::storeData("app0:/assets/test.png",TEXTURE);
    MemoryManager::removeData("app0:/assets/test.png",TEXTURE);
    Komodo::gameloop();*/
    return 0;
}