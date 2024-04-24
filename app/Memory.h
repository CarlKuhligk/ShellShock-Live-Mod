#pragma once
// Memory



class MemorySSL
{
public:
	// Variabels
	BYTE* ObjectAddress = nullptr;

	// Static Variabels
	static HANDLE ShellShock;
	static HWND MainWindow;
	static const char* ProcessName;
	static int ProcessID;
	static BYTE* MonoDLL;
	static BYTE* UnityPlayerDLL;



	// Methodes
	MemorySSL();
	~MemorySSL();

	void CloseProcess();

	void InitializeMemory();

	BYTE* virtualAlloc(int size);


	//============PROCESSHANDLE============
	//finds the process id by the processname
	int findProcessIdByProcessName(const char* processName);

	//opens the target process and returns the handle
	HANDLE openProcessByProcessName(const char* processName);

	//close the handle
	void closeProcess(HANDLE process);



	//============MODULEINFO============
	//finde module by name
	MODULEENTRY32 getModule(const char* modulName, int processId);

	BYTE* getModuleBase(const char* modulName, int processId);

	//get entire modullist of the process
	std::vector<MODULEENTRY32>* get_moduleList(const char* modulName, int processId);


	//============PROCESSMEMORY============
	//read pointer without module
	BYTE* readPointer(void* baseAddr, std::vector<DWORD> offsets);

	//read Bytearray
	void readBytes(void* startAddr, BYTE* targetBuffer, int size);


	//read Value
	template <typename ValueType>
	ValueType readValue(void* address)
	{
		ValueType value;
		ReadProcessMemory(ShellShock, address, &value, sizeof(ValueType), NULL);
		return value;

	}

	// write bytes
	void writeBytes(BYTE* address, BYTE bytes[], int size);

	std::string readString(BYTE* address);

	//============WINDOWINFO============
	HWND getWindowHandleByWindowName(LPCSTR windowName);
	void readGameWindowRect(RECT* rectAddr);
};

