#pragma once


// Abstract Coodinatesystem is 0 to 1000 in X
// Aimer-Velocity 0 to 100
// Wind-Velocity -100 to +100	| rightforce force > 0	| leftforce  force < 0
// Terrain 0 to +1000
// Playerposition X 0 to +1000	|Y 0 to +1000


class Game : public MemorySSL
{
	// Variabels
private:
	// Windowinformations
	RECT Window;
	bool changeDetected = false; // Calculate Trace
	bool changeOverlay = false; // Update Overla on change

public:
	// Colors
	Gdiplus::Color translucentKey = Gdiplus::Color(255, 255, 0, 255);
	Gdiplus::Color white = Gdiplus::Color(255, 255, 255, 255);
	Gdiplus::Color red = Gdiplus::Color(255, 255, 0, 0);
	Gdiplus::Color green = Gdiplus::Color(255, 0, 255, 0);
	Gdiplus::Color blue = Gdiplus::Color(255, 0, 0, 255);
	Gdiplus::Color yellow = Gdiplus::Color(255, 255, 255, 0);
	Gdiplus::Color cyan = Gdiplus::Color(255, 0, 255, 255);
	Gdiplus::Color magenta = Gdiplus::Color(255, 254, 0, 254); // Magenta 255, 0, 255 is traslucentkey
	Gdiplus::Color orange = Gdiplus::Color(255, 255, 128, 0);
	Gdiplus::Color lightgeen = Gdiplus::Color(255, 153, 255, 153);
	Gdiplus::Color lightblue = Gdiplus::Color(255, 153, 153, 255);
	Gdiplus::Color lightred = Gdiplus::Color(255, 255, 153, 153);

	// Graphics
	SIZE WindowSize;
	POINT WindowPosition;
	float Scale;
	Gdiplus::Graphics* graphic;

	// InBattleSettings
	bool showEnemyHitbox = true;
	bool showTerrain = true;

	// TEMP Friend
	//std::string Friend[2] = { "steam76561198103406161", "steam76561198026692125" };
	//PlayerOBJ* FriendPlayer = nullptr;

	// MyPlayer
	std::string MySteamID;// = "steam76561198026692125";
	PlayerOBJ* MyPlayer = nullptr;
	int MyPlayerIndex = -1;
	// Gamestates
	bool EnterBattle;
	bool InBattle;
	bool NewTurn;
	bool LeaveBattle;
	// Ingameobjects
	AimerOBJ Aimer = AimerOBJ();
	WindOBJ WindIndicator = WindOBJ();
	TerrainOBJ Terrain = TerrainOBJ();
	WeaponSelectorOBJ WeaponSelector = WeaponSelectorOBJ();
	std::vector<PlayerOBJ> PlayerList;
	// Logicdata
	float Hitbox = 0.003f;
	float GunOffset = 10.0f;

	// Calculations
	float Gravity = 7.715f;
	const float calcTimeResolution = 0.1f;
	std::vector<Projectile> Projectiles;


	// Memoryposition
	BYTE* rawAddresses[8];
	BYTE* PositionUpdateFunktionAddress;
	BYTE* CodeInjectionAddress;
	BYTE* EAX_ExtractorArrayAddress;

	// Pointer to PrositionUpdateFunction
	std::vector<DWORD> OffsetsPositionUpdateFunction = { 0x30, 0x9A8, 0x00, 0x1C, 0x04, 0x188 };

private:
	// Methodes
	void findMyPlayer();
	void createPlayer();
	void deletePlayer();
	void updatePlayerData();
	void setBattleStates();
	void calculatePlayerPositions();	// Calculate Players Y-Position and Gun-Position
	
	//std::vector<Segment> getTrace(PlayerOBJ player, );


public:
	// Methodes
	Game();
	~Game();

	void Initialize();
	void UpdateInput();
	// Draw
	void Draw(HDC* pointer);
	void Calculate();
	//void UpdateOutput();




	// _____________GUI_________________
	POINT toScreen(const Point2 &position);
	int getSize(const float &sizeToScale);
	void drawLine(const Gdiplus::Color &color, const Point2 &point1, const Point2 &point2);
	void drawCross(const Gdiplus::Color &color,const  Point2 &position, const float &size);
	void drawCircle(const Gdiplus::Color &color,const Point2 &position, const float &size);
	void drawSegment(const Gdiplus::Color &color, const Segment &segment);

	

};


