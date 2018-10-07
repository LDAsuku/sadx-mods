I made some mods for sadx
​
## lightdash
first mod I made. hold B or X after lightdashing and it won't end until sonic reaches a stop
​
## Animation Debugger
second mod. allows locking and manually advancing sonic's animations in-game.
controls:
​

button combo | action
--- | ---
C | toggle animation ID lock
up/down | advance through animations (hold Y for an increment of 16)
D | toggle frame lock
left/right | frame advance through the current active animation (hold Y for continuous)
AZY+down | toggle outputting the current animation ID and frame to the console every frame (default: off)

a mostly-complete list of animations can be found [on sonic retro](http://info.sonicretro.org/SCHG:Sonic_Adventure_DX:_PC/Lists#Sonic.27s_Animations). beware that letting the animation ID go out-of-bounds will crash the game. the last animations for each character I've tested are as follows:
​

char | max
--- | ---
sonic | 0x0092
tails | 0x0087
knuckles | 0x0073
amy | 0x0065
big the cat | 0x004C
gamma | 0x005A
