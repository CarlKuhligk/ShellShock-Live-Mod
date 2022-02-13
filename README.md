## ShellShockLiveRuler
![](https://github.com/CarlKuhligk/ShellShockLiveRuler/blob/main/01%20-%20Screenshoot.PNG?raw=true)

This program creates an overlay showing the map boundaries and the projectile trail. It takes wind in to account and corrects the trace.
It also shows some techniques to access some ingame variabels.
Its not possible to find static pointers to the players object. Therefore other methods are needed to finde the right memory.

The following steps are implemented:

***

# 1. Patternscan
> The function/methode i'm aming at, is called every time the game updates the players object.
> The address of each player object is handled in it.
> This function is dynamicly generated. If the game is lunched, this function/methode is not present.
> To generate it, its nesessary to start the firing mode or an other mode.
> The pattern:
```c++
{ 0x30, 0x9A8, 0x00, 0x1C, 0x04, 0x188 };
```

***

# 2. Codeinjection
> To extract thoes player addresses, a very simple code is injected.
> ![](https://github.com/CarlKuhligk/ShellShockLiveRuler/blob/main/Overview%20of%20injected%20code%20for%20extrating%20TankMC%20addresses.png?raw=true)

```c++
// Code to Inject Size 55 Bytes
	BYTE EAX_ExtractionCode[] = {
		0x53,                                       //1  save ebx on stack
		0x57,                                       //1  save edi on stack
		0x56,                                       //1  save esi on stack
		0xBF, 0x40, 0x00, 0x014, 0x07,              //5  index counter__________________________position to write beginns start address +0x04
		0x83, 0x3f, 0x08,                           //3  compare for jump (counterlimit 7)
		0x72, 0x06,                                 //2  jump short over reset
		0xC7, 0x07, 0x00, 0x00, 0x00, 0x00,         //6  rest counter
		0xBE, 0x44, 0x00, 0x14, 0x07,               //5  load array base________________________position to write beginns start address +0x14
		0x8B, 0xDF,                                 //2  save index counter address
		0x8B, 0x3F,                                 //2  load counter value
		0x89, 0x04, 0xBE,                           //3  copy eax to the array at index ...
		0xFF, 0x03,                                 //2  increment index counter
		0x5E,                                       //1  restore esi from stack
		0x5F,                                       //1  restore edi from stack
		0x5B,                                       //1  restore ebx from stack
		0xD9, 0x58, 0x44,                           //3  original code
		0x0F, 0xB6, 0x85, 0x27, 0xFF, 0xFF, 0xFF,   //7  original code
		0xE9, 0x00, 0x00, 0x00, 0x00,               //5  jump back to original code ___________position to write beginns start address +0x2F
		0x90, 0x90, 0x90, 0x90  //  spacer
		//array index counter = address +0x38
		//array item 0 = start address  +0x3C
		// total amout of bytes needes = 92
	};
```

***

# 3. Read the extracted addresses

Now its possible to read all nesessary values to calculate the projectiles.
![](https://github.com/CarlKuhligk/ShellShockLiveRuler/blob/main/02%20-%20Screenshoot.PNG?raw=true)
![](https://github.com/CarlKuhligk/ShellShockLiveRuler/blob/main/03%20-%20Screenshoot.PNG?raw=true)

***

## Gamememory-Dependencys
![](https://github.com/CarlKuhligk/ShellShockLiveRuler/blob/main/Overview%20of%20game%20dependencys.png?raw=true)

***

Some things that can be implemented:
1. [ ] create all projectiles for all the different flight behaviors (currently i have only the "normal" behavior implemented, multiple traces are possible)
2. [ ] enable auto-aim to deal maximum damage
3. [ ] finish implementing bouncing
4. [ ] find obstacles with CheatEngine
5. [ ] take obstacles in to account (rebounce)
6. [ ] find blackholes with CheatEngine
7. [ ] take blackholes in to account
8. [ ] find portals with CheatEngine
9. [ ] take portals in to account
10. [ ] implement speedhack (possible with cheatengine ;))
