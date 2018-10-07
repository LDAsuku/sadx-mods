I made some mods for sadx
​
## lightdash
first mod I made. hold B or X after lightdashing and it won't end until sonic reaches a stop
​
## Animation Debugger
second mod. allows locking and manually advancing sonic's animations in-game.
controls:
​
<table>
<tr><th>button combo</th><th>action</th></tr>
<tr><td>C</td><td>toggle animation ID lock</td></tr>
<tr><td>up/down</td><td>advance through animations (hold Y for an increment of 16)</td></tr>
<tr><td>D</td><td>toggle frame lock</td></tr>
<tr><td>left/right</td><td>frame advance through the current active animation (hold Y for continuous)</td></tr>
<tr><td>AZY+down</td><td>toggle outputting the current animation ID and frame to the console every frame (default: off)</td></tr>
</table>
​
a mostly-complete list of animations can be found [on sonic retro](info.sonicretro.org/SCHG:Sonic_Adventure_DX:_PC/Lists#Animation_Lists). beware that letting the animation ID go out-of-bounds will crash the game. the last animations for each character I've tested are as follows:
​
<table>
<tr><td>sonic</td><td>0x0092</td></tr>
<tr><td>tails</td><td>0x0087</td></tr>
<tr><td>knuckles</td><td>0x0073</td></tr>
<tr><td>amy</td><td>0x0065</td></tr>
<tr><td>big the cat</td><td>0x004c</td></tr>
<tr><td>gamma</td><td>0x005a</td></tr>
</table>
​