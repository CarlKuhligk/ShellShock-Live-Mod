# ShellShock Live Ruler

> [!NOTE]
> The project is inactive, and after numerous game updates, the pattern scan is likely to no longer function and would need to be updated.

![](./doc/img/ingame%202.PNG?raw=true)

The project originated from experimenting with Cheat Engine. The game ShellShock Live served as a learning platform, as it is quite simple and lacks cheat protection. However, it quickly became apparent that reading addresses wasn't as straightforward as expected. ShellShock utilizes the Unity engine, and additionally, a obfuscation technique was applied to obscure the names of variables and functions. Furthermore, I was unable to reliably find a pointer to player data using the usual pointer scan method. Nevertheless, I did discover a function that processes player addresses. With this insight, I then wrote a small assembly code that writes the addresses to a known address space upon each function call. With these addresses, all player data can be intercepted. Originally, it was only about reading the data and not about creating cheats to precisely determine the impact points of projectiles. However, I found it interesting to calculate collisions and trajectories provisionally on my own.

***

## How it works
The function I'm targeting is called every time the game updates the player's object. The address of each player object is handled within it. This function is dynamically generated. If the game is launched, this function is not present. To generate it, it's necessary to start the firing mode or another mode. After this is done, we could find the memory address of this function by searching for the following pattern in memory:

### 1. Patternscan
```c++
pattern = { 0x30, 0x9A8, 0x00, 0x1C, 0x04, 0x188 }
```


### 2. Codeinjection
After the address of the function has been found, the function can be modified so that it initially jumps to a new location in memory, where the code to store the player addresses is executed. Afterwards, the original function is executed.
![](./doc/img/extrating%20TankMC%20addresses.png?raw=true)

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

### 3. Read the extracted addresses

The extracted addresses are just the tip of the iceberg. In exploring the structure of the game in memory, the following connections have become visible. On the right side of the graphic are custom classes created within the 'ruler/mod/cheat,' where most arrows terminate. The light blue objects are those extracted from the game.

![](./doc/img/game%20dependencys.png?raw=true)

### 4. Show results
With this information, the behavior and environment of the game can now be reconstructed and displayed very accurately. The player can now see in advance exactly where their shot will land.

![](./doc/img/02%20-%20Screenshoot.PNG?raw=true)
![](./doc/img/ingame%201.PNG?raw=true)
![](./doc/img/ingame%202.PNG?raw=true)

***
Additional Features:

1. [ ] Create all projectiles for all the different flight behaviors (currently, only the "normal" behavior is implemented; multiple trajectories are possible).
2. [ ] Enable auto-aim to deal maximum damage.
3. [ ] Finish implementing bouncing.
4. [ ] Find obstacles with CheatEngine.
5. [ ] Take obstacles into account (rebounce).
6. [ ] Find black holes with CheatEngine.
7. [ ] Take black holes into account.
8. [ ] Find portals with CheatEngine.
9. [ ] Take portals into account.
10. [ ] Implement speedhack (possible with CheatEngine).
