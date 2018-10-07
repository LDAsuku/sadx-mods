
#include <SADXModLoader.h>

#define EXPORT __declspec(dllexport)

extern "C" {
	EXPORT ModInfo SADXModInfo = { ModLoaderVer };

	EXPORT void OnFrame() {
		ControllerData* c = ControllerPointers[0];
		if (c->HeldButtons & (Buttons_B | Buttons_X)) {
			CharObj2* player = GetCharObj2(0);
			player->LightdashTime = 10;
		}
	}
}