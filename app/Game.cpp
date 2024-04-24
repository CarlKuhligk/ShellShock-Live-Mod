#include "IncludeHead.h"

// Initialize Static Variabels



//__________Game__________
// Methodes
// PRIVATE:
void Game::findMyPlayer()
{
	// Search for MyPlayer
	for (int i = 0; i < PlayerList.size(); i++)
	{
		// Find MyPlayer
		if (PlayerList[i].MySelf == true)
		{
			MyPlayer = &PlayerList[i];
			MyPlayerIndex = i;
			
		}
	}
}

// Creates all new Player
void  Game::createPlayer()
{
	// Create Player
	// Read all Address from EAX ExtractorArray and compare to existing addresses
	// Update existing Player
	// if Address is new Create Player
	for (int i = 0; i < 8 + 1; i++)
	{
		bool playerAddressExists = false;

		if (rawAddresses[i] != nullptr)
		{

			// Compare existing Players with the EAX Addresses
			for (int j = 0; j < PlayerList.size(); j++)
			{
				if (rawAddresses[i] == PlayerList[j].ObjectAddress)
				{
					playerAddressExists = true;
					break;
				}
			}

			if (playerAddressExists == true)
			{
				// Address exists
				continue; //next address
			}
			else
			{
				// Address dont exist
				// Create Player
				PlayerOBJ newPlayer = PlayerOBJ(rawAddresses[i]);

				// Check if the Player is Connected
				if (newPlayer.IsConnected == true)
				{
					// Find MyPlayer by compareing SteamID
					if (strcmp(newPlayer.SteamId.c_str(), MySteamID.c_str()) == 0)
					{
						// Match
						newPlayer.MySelf = true;
					}

					// Add Player
					PlayerList.push_back(newPlayer);
				}
			}
		}
	}
}

// Deletes all dissconnected Players
void  Game::deletePlayer()
{
	// Remove Player
	for (int i = 0; i < PlayerList.size(); i++)
	{
		if (PlayerList[i].IsConnected == false || PlayerList[i].DeadData == 0)
		{
			// Remove Player from List
			PlayerList.erase(PlayerList.begin() + i);
			changeDetected |= true;

			//  Reset MyPlayer
			if (i == MyPlayerIndex)
			{
				MyPlayerIndex = 0;
				MyPlayer = nullptr;
			}
		}
	}
}

// Update all Players
void Game::updatePlayerData()
{
	// Read Playerdata
	for (int i = 0; i < PlayerList.size(); i++)
	{
		changeDetected |= PlayerList[i].readData();
	}

	// Remove Player
	deletePlayer();

	// Calculate Players Y-Position and Gun-Position
	calculatePlayerPositions();

	// Find MyPlayer (copy Player to MyPlayer Pointer)
	findMyPlayer();
}

// Set all Battlestates
void Game::setBattleStates()
{
	// Set the State of the Battle
	// Clear Playerlist
	if (Aimer.IsActive == true)
	{
		// InBattle change to true -> EnterBattle = true
		if (InBattle == false)
		{
			EnterBattle = true;
		}
		else
		{
			EnterBattle = false;
		}

		// Set in Battle
		InBattle = true;

		// Set NewTurnState
		if (Aimer.NewTurn == true && NewTurn == false)
		{
			// Reset Aimervalue
			Aimer.NewTurn = false;
			// Set Gamevalue
			NewTurn = true;
		}
		else
			NewTurn = false;
	}
	else
	{
		// InBattle change to false -> LeaveBattle = true
		if (InBattle == true)
		{
			// Leaving Battle
			LeaveBattle = true;
		}
		else
		{
			// Battle Left
			LeaveBattle = false;
		}
		// Set not in Battle
		InBattle = false;
	}
}

// Calculate Players Y and Gun-Position
void Game::calculatePlayerPositions()
{
	for (int i = 0; i < PlayerList.size(); i++)
	{
		// Calculate the index of the LinecolliderArray
		int index = ((float)PlayerList[i].TankPosition.X / (1000.0f / 200.0f));
		// Interpolate the Y-Position of the 
		PlayerList[i].TankPosition = Terrain.PolyLineCollider.Lines[index].getYbyX(PlayerList[i].TankPosition);

		// Calculate Gunposition
		// Set right Anglevalue
		int tempAngle;
		if (i != MyPlayerIndex)
		{
			// All other Players
			tempAngle = PlayerList[i].Angle;
		}
		else
		{
			// MyPlayer
			tempAngle = Aimer.Angle;
		}
		// Calculate Gunposition
		float deltaX = cos(((float)tempAngle * M_PI) / 180) * GunOffset;
		float deltaY = sin(((float)tempAngle * M_PI) / 180) * GunOffset;
		PlayerList[i].GunPosition.X = PlayerList[i].TankPosition.X + deltaX;
		PlayerList[i].GunPosition.Y = PlayerList[i].TankPosition.Y + deltaY + 2.0f;

	}
}

// PUBLIC:
Game::Game()
{
	// Set Static Projectile references
	Projectile::Gravity = &this->Gravity;
	Projectile::WindForce = &this->WindIndicator.Force;
	Projectile::Projectiles = &this->Projectiles;
	Projectile::Terrain = &this->Terrain;

	//Projectile::LineCollider = this->

	InBattle = false;
	Initialize();
	
}

Game::~Game()
{
	CloseProcess();
}

// Read ProcessID
// Read mono.dll Base
// Find Function for Injection
// Prepare Code
// Inject Code
// Set Jump to Injected Code
void Game::Initialize()
{
	InitializeMemory();

	// Find Position Update Function Beginn
	PositionUpdateFunktionAddress = readPointer(MonoDLL + 0x1F795C, OffsetsPositionUpdateFunction) + 0x77C;
	std::cout << "HookAddress: " << (void*)PositionUpdateFunktionAddress << "\n";
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
	// Allocate Memory for the Code
	//!!!!
	CodeInjectionAddress = virtualAlloc(100);
	//!!!!

	// Prepare Code
	// Set Counteraddress
	BYTE* indexCounterAddr = CodeInjectionAddress + 0x38;
	memcpy(&EAX_ExtractionCode[4], &indexCounterAddr, 4);

	// Set Array-Baseaddress
	EAX_ExtractorArrayAddress = CodeInjectionAddress + 0x3C;
	memcpy(&EAX_ExtractionCode[20], &EAX_ExtractorArrayAddress, 4);

	// Set Jumpaddress (back to Original Code)
	BYTE* jumpBackAddr = PositionUpdateFunktionAddress + 0x0A;

	// Calculate the dictance to the destination
	jumpBackAddr = (BYTE*)(jumpBackAddr - CodeInjectionAddress - 0x33);
	memcpy(&EAX_ExtractionCode[47], &jumpBackAddr, 4);

	// Inject EAX_ExtractionCode
	writeBytes(CodeInjectionAddress, EAX_ExtractionCode, sizeof(EAX_ExtractionCode));

	// Set Jumpaddress (to Injected Code)
	BYTE JumpToExtractionCode[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
	BYTE* jumpForwardAddr = CodeInjectionAddress;

	// Calculate the dictance to the destination
	jumpForwardAddr = (BYTE*)(jumpForwardAddr - PositionUpdateFunktionAddress - 0x05);
	memcpy(&JumpToExtractionCode[1], &jumpForwardAddr, 4);

	// Inject Code
	writeBytes(PositionUpdateFunktionAddress, JumpToExtractionCode, sizeof(JumpToExtractionCode));

	// Replace the Originalcode fragmets with nops
	BYTE ReplaceCode[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
	// Inject Code
	writeBytes(PositionUpdateFunktionAddress + 0x05, ReplaceCode, sizeof(JumpToExtractionCode));

	// Read MySteamID
	std::vector<DWORD> offsetMySteamID = { 0xA8, 0x24, 0x1DC, 0x160, 0x34, 0x38 };
	MySteamID = readString(readPointer(MonoDLL + 0x1F9C54, offsetMySteamID));
}

// Updates all Values
void Game::UpdateInput()
{
	// Read all Extracted Addresses
	readBytes(EAX_ExtractorArrayAddress, (BYTE*)&rawAddresses[0], 8 * 4);
	// Reset ArrayCounter
	writeBytes(EAX_ExtractorArrayAddress - 0x04, { 0 }, 4);


	// Crash if own tank dies?
	// Update AimerBaseAddress only if the Playerlist is empty
	if (PlayerList.size() == 0)
	{
		// Set AimerAddress
		Aimer.ObjectAddress = readPointer(rawAddresses[0] + 0x28, { 0x08, 0x1C, 0x0C, 0x18, 0x18 });
	}

	if (Aimer.ObjectAddress != nullptr) {
		// Read AimerData
		changeDetected |= Aimer.readData();
	}

	// Set all Battlestates
	setBattleStates();

	// EnterBattle Inizialiation
	if (EnterBattle == true)
	{
		createPlayer();

		// Find MyPlayer
		findMyPlayer();

		// Set Enemystate
		for (int i = 0; i < PlayerList.size(); i++)
		{
			if (PlayerList[i].Team == 0 || PlayerList[i].Team != MyPlayer->Team)
			{
				// Enemy found!
				PlayerList[i].IsEnemy = true;
			}
		}

		// Initialize Adresses Terrain, Wind and Weaponselector
		Terrain.ObjectAddress = readPointer(UnityPlayerDLL + 0xFF4A74, { 0x58, 0xC0, 0x0C }) + 0x10;
		WindIndicator.ObjectAddress = readPointer(MonoDLL + 0x1F50AC, { 0x15C, 0x77C, 0x00, 0xA8, 0x80 }) + 0x14;
		WeaponSelector.ObjectAddress = readPointer(UnityPlayerDLL + 0x1001D00, { 0x00, 0x2C, 0x3C }) + 0x70;

		// Update Overlay
		changeDetected = true;
	}

	// Update BattleData
	if (InBattle == true)
	{
		// In Battle
		// Read only Turnupdated Data
		if (true)///////////////////////////////////////////////////////////////////////////////
		{
			Terrain.readData();
			WindIndicator.readData();
			WeaponSelector.readData();
		}

		// Update Data and Remove Players
		updatePlayerData();

	}


	// Battle Leav
	if (LeaveBattle == true)
	{
		// Clear Playerlist
		PlayerList.clear();

		// Clear Overlay
		changeOverlay == true;
	}


	// Update Windowinformation
	readGameWindowRect(&Window);
	
	// Calculate new GameWindowData
	// Position and Size
	WindowPosition.x = Window.left + 8;
	WindowPosition.y = Window.top + 30;
	WindowSize.cx = Window.right - Window.left - 16;
	Scale =  (float)WindowSize.cx / (12.5f );
	WindowSize.cy = Window.bottom - Window.top - 30 - 8;
	

	if (changeDetected == true)
	{
		changeDetected = false;
		Calculate();
		changeOverlay = true;
	}

}

// Calculate Trace
void Game::Calculate()
{
	// Add StandartProjectile
	if (MyPlayer != nullptr)
	{
		Projectiles.clear();
		Projectiles.push_back(Projectile(MyPlayer->GunPosition, Aimer.VelocityVector, 0));

		// Calculate Trace for each Projectile
		for (int i = 0; i < Projectiles.size(); i++)
		{
			if (Projectiles[i].IsFlying == true)
			{
				Projectiles[i].Calculate(calcTimeResolution);
			}
		}
		
	}
}


// _____________GUI_________________
POINT Game::toScreen(const Point2 &position)
{
	POINT result;
	result.x = (position.X / 1000.0f) * WindowSize.cx;
	result.y = (WindowSize.cy - WindowSize.cx) + (WindowSize.cx - (position.Y / 1000.0f) * WindowSize.cx);
	return result;
}

int  Game::getSize(const float &sizeToScale)
{
	return sizeToScale * WindowSize.cx;
}

void Game::drawLine(const Gdiplus::Color &color, const Point2 &p1, const  Point2 &p2)
{
	Gdiplus::Pen pen(color, 0);
	POINT point1 = toScreen(p1);
	POINT point2 = toScreen(p2);
	graphic->DrawLine(&pen, (INT)point1.x, (INT)point1.y, (INT)point2.x, (INT)point2.y);
}

void Game::drawCross(const Gdiplus::Color &color, const Point2 &position, const float &size)
{
	Gdiplus::Pen pen(color, 0);
	POINT point = toScreen(position);
	int lenght = getSize(size);
	graphic->DrawLine(&pen, (INT)(point.x - lenght), (INT)(point.y + lenght), (INT)(point.x + lenght), (INT)(point.y - lenght));
	graphic->DrawLine(&pen, (INT)(point.x - lenght), (INT)(point.y - lenght), (INT)(point.x + lenght), (INT)(point.y + lenght));
}

void Game::drawCircle(const Gdiplus::Color &color, const Point2 &position, const float &radius)
{
	Gdiplus::Pen pen(color, 0);
	POINT point = toScreen(position);
	int r = getSize(radius);
	graphic->DrawEllipse(&pen, (INT)point.x - r, (INT)point.y - r, (INT)r * 2, (INT)r * 2);
}

void Game::drawSegment(const Gdiplus::Color &color, const Segment &segment)
{
	Point2 point2 = Point2(segment.Origin.X + segment.Vector.X, segment.Origin.Y + segment.Vector.Y);
	drawLine(color, segment.Origin, point2);
}

// Draw 
void Game::Draw(HDC* pointer)
{
	// Initialisize graphic
	Gdiplus::Graphics temp(*pointer);
	graphic = &temp;

	if (changeOverlay == true && InBattle == true && LeaveBattle == false)
	{
		// Reset detectState
		changeOverlay = false;

		// Clear
		graphic->Clear(translucentKey);

		// Draw InBattle Values
		if (InBattle == true)
		{
			// Enemy Hitbox
			if (showEnemyHitbox == true)
			{
				// Playerposition
				if (PlayerList.size() > 0)
				{
					for (int i = 0; i < PlayerList.size(); i++)
					{
						if (PlayerList[i].MySelf == true || PlayerList[i].IsEnemy == true)
							continue;
						drawCircle(magenta, PlayerList[i].TankPosition, 0.010f);

					}
				}
			}

			// Terrain
			if (showTerrain == true)
			{
				for (int i = 0; i < Terrain.Size - 1; i++)
				{
					// Terrainvalues
					drawLine(yellow, Terrain.Points[i], Terrain.Points[i + 1]);
				}

			}

			// Draw Traces
			for (int i = 0; i < Projectiles.size(); i++)
			{
				if (Projectiles[i].TracePoints.size() > 0)
				{
					for (int e = 0; e < Projectiles[i].TracePoints.size() - 1; e++)
					{
						drawLine(white, Projectiles[i].TracePoints[e], Projectiles[i].TracePoints[e + 1]);
					}
				}
				// Events
				if (Projectiles[i].Events.size() > 0)
				{
					for (int e = 0; e < Projectiles[i].Events.size(); e++)
					{
						switch (Projectiles[i].Events[e].Type)
						{
						case 1:
							drawCross(red, Projectiles[i].Events[e].Location, Hitbox);
							drawCircle(red, Projectiles[i].Events[e].Location, 0.031f);
							break;
						default:
							break;
						}
						
					}
					
				}
			}

			drawLine(red, MyPlayer->GunPosition, MyPlayer->GunPosition + Aimer.VelocityVector);
			drawCross(blue, MyPlayer->GunPosition, Hitbox);
			drawCross(magenta, MyPlayer->TankPosition, Hitbox);
			
		}


	}
	else if (LeaveBattle == true)
	{
		// Clear
		graphic->Clear(translucentKey);
	}

}
