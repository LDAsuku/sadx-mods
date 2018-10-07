
#include <SADXModLoader.h>
#include <Trampoline.h>
#include <math.h>

#define EXPORT __declspec(dllexport)

#define TARGET_DYNAMIC(name) ((decltype(name##_r)*)name##_t->Target())

#define Buttons_AYZ (Buttons_A | Buttons_Y | Buttons_Z)
#define Buttons_BX (Buttons_B | Buttons_X)

static Trampoline* PlayAnimation_t = nullptr;

static bool console_spam = false;
static AnimThing* target_animation = nullptr;
static int16_t animation = 0x0000;
static bool animation_locked = false;
static float frame = 0.0f;
static bool frame_locked = false;

#if 0
static int16_t max_animations() {
	switch (CurrentCharacter) {
	case Characters_Sonic:		return 0x0093;
	case Characters_Eggman:		return 0x1000; //untested
	case Characters_Tails:		return 0x0088;
	case Characters_Knuckles:	return 0x0073;
	case Characters_Tikal:		return 0x1000; //untested
	case Characters_Amy:		return 0x0066;
	case Characters_Gamma:		return 0x005B;
	case Characters_Big:		return 0x004D;
	}
	return 0;
}
#endif

static void __cdecl PlayAnimation_r(AnimThing* anim) {
	const auto original = TARGET_DYNAMIC(PlayAnimation);

	if (anim != target_animation) {
		original(anim);
		return;
	}

	ControllerData* c = ControllerPointers[0];

	// lock animation on C
	if (c->PressedButtons & Buttons_C)
		if (animation_locked ^= true)
			animation = anim->Index;
	// lock frame on D
	if (c->PressedButtons & Buttons_D)
		if (frame_locked ^= true)
			frame = 0.0f;

	if (animation_locked) {
		int inc = c->HeldButtons & Buttons_Y ? 0x10 : 1;
		if (c->PressedButtons & Buttons_Up) animation += inc;
		if (c->PressedButtons & Buttons_Down) animation -= inc;

#if 0
		int16_t max = max_animations();
		if (animation >= max) animation -= max;
		else if (animation < 0) animation += max;
#endif

		anim->Index = animation;
	}
	if (frame_locked) {
		float inc = anim->AnimData->AnimationSpeed;
		uint32_t input = c->HeldButtons & Buttons_Y ? c->HeldButtons : c->PressedButtons;

		if (input & Buttons_Right) frame += inc;
		if (input & Buttons_Left) frame -= inc;
		frame = fmodf((frame + 100.0f), 100.0f);

		anim->Frame = frame;
	}

	// ABXYZ+Down to toggle console spam
	if (((c->HeldButtons & Buttons_AYZ) == Buttons_AYZ) && ((c->HeldButtons & Buttons_BX) == 0) && (c->PressedButtons & Buttons_Down)) {
		if (console_spam ^= true)
			PrintDebug("[animation] console output enabled\n");
		else
			PrintDebug("[animation] console output disabled\n");
	}

	// print everything
	if (console_spam)
		PrintDebug("[animation/%c%c] %04X:%f\n",
			animation_locked ? 'A' : 'a',
			frame_locked ? 'F' : 'f',
			anim->Index, anim->Frame);

	original(anim);
}

extern "C" {
	EXPORT ModInfo SADXModInfo = { ModLoaderVer };

	EXPORT void __cdecl Init(const char *path, const HelperFunctions& helperFunctions) {
		// hijack
		PlayAnimation_t = new Trampoline((intptr_t)PlayAnimation, (intptr_t)PlayAnimation + 8, PlayAnimation_r);
	}

	EXPORT void OnFrame() {
		CharObj2* player = GetCharObj2(0);
		target_animation = &player->AnimationThing;
	}
}