#include "IncludeHead.h"

// Initialize Static Variabels
HANDLE MemorySSL::ShellShock = nullptr;
HWND MemorySSL::MainWindow = nullptr;
const char* MemorySSL::ProcessName = "ShellShockLive.exe";
int MemorySSL::ProcessID = 0;
BYTE* MemorySSL::MonoDLL = nullptr;
BYTE* MemorySSL::UnityPlayerDLL = nullptr;


	// Methodes
	MemorySSL::MemorySSL()
	{
		//std::cout << "Memory is Created" << "\n";
	}

	MemorySSL::~MemorySSL()
	{
	}

	void MemorySSL::CloseProcess()
	{
		CloseHandle(ShellShock);
	}


	void MemorySSL::InitializeMemory()
	{
		// Find Gameprocess
		ShellShock = openProcessByProcessName(ProcessName);
		// Find Windowhandle
		MainWindow = getWindowHandleByWindowName("ShellShock Live");

		// Finde ProcessID
		ProcessID = findProcessIdByProcessName(ProcessName);
		std::cout << "ProcessID: " << ProcessID << "\n";

		// Find Baseaddress from Mono-Modul 
		MonoDLL = getModuleBase("mono.dll", ProcessID);
		std::cout << "mono.dll: " << (void*)MonoDLL << "\n";

		// Find Baseaddress from UnityPlayer-Modul 
		UnityPlayerDLL = getModuleBase("UnityPlayer.dll", ProcessID);
		std::cout << "UnityPlayer.dll: " << (void*)UnityPlayerDLL << "\n";
	}


	BYTE* MemorySSL::virtualAlloc(int size)
	{
		return (BYTE*)VirtualAllocEx(ShellShock, NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	}



	//============PROCESSHANDLE============
	//finds the process id by the processname
	int MemorySSL::findProcessIdByProcessName(const char* processName)
	{

		HANDLE hProcessSnap;
		PROCESSENTRY32 pe32;
		int processID = NULL;
		DWORD _err;

		//Set all menbers of the struct to zero
		ZeroMemory(&pe32, sizeof(PROCESSENTRY32));

		//Set size of the struct
		pe32.dwSize = sizeof(PROCESSENTRY32);

		//Take a snapshot of all processes in the operating system.
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			_err = GetLastError();
			printf("Error: CreateToolhelp32Snapshot faild! | Code: %d [%x]\n", _err, _err);
			return NULL;
		}

		if (Process32First(hProcessSnap, &pe32) == FALSE)
		{
			_err = GetLastError();
			printf("Error: Process32First faild! | Code: %d [%x]\n", _err, _err);
			CloseHandle(hProcessSnap); // clean the snapshot object
			return NULL;
		}

		do
		{
			//Get a handle to the process
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);

			if (hProcess != NULL)
			{
				//compare process names
				if (strcmp(pe32.szExeFile, processName) == 0)
				{
					processID = pe32.th32ProcessID;
					CloseHandle(hProcessSnap);
					CloseHandle(hProcess);
					return processID;
				}
				CloseHandle(hProcess);
			}

		} while (Process32Next(hProcessSnap, &pe32) != FALSE);

		CloseHandle(hProcessSnap); // clean the snapshot object

		return processID;
	}

	//opens the target process and returns the handle
	HANDLE MemorySSL::openProcessByProcessName(const char* processName)
	{
		int processID = findProcessIdByProcessName(processName);
		if (processID != NULL)
		{
			return OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, processID);
		}
		else
		{
			printf("Error: Unable to find process!\n");
			return NULL;
		}
	}

	//close the handle
	void MemorySSL::closeProcess(HANDLE process)
	{
		CloseHandle(process);
	}



	//============MODULEINFO============
	//finde module by name
	MODULEENTRY32 MemorySSL::getModule(const char* modulName, int processId)
	{
		HANDLE hProcessSnap;
		MODULEENTRY32 modulEnty;
		modulEnty.dwSize = sizeof(MODULEENTRY32);
		DWORD _err;

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			_err = GetLastError();
			printf("Error: CreateToolhelp32Snapshot faild! | Code: %d [%x]\n", _err, _err);
			MODULEENTRY32 notFound = { -1 };
			return notFound;
		}

		if (Module32First(hProcessSnap, &modulEnty) == FALSE)
		{
			_err = GetLastError();
			printf("Error: Modul32First faild! | Code: %d [%x]\n", _err, _err);
			CloseHandle(hProcessSnap); // clean the snapshot object
			MODULEENTRY32 notFound = { -1 };
			return notFound;
		}
		//search all moduls an compare name
		do
		{
			if (strcmp(modulEnty.szModule, modulName) == 0)
			{
				CloseHandle(hProcessSnap);
				return modulEnty;
			}
		} while (Module32Next(hProcessSnap, &modulEnty) != FALSE);

		CloseHandle(hProcessSnap);
		MODULEENTRY32 notFound = { -1 };
		return notFound;
	}

	BYTE* MemorySSL::getModuleBase(const char* modulName, int processId)
	{
		HANDLE hProcessSnap;
		MODULEENTRY32 modulEnty;
		modulEnty.dwSize = sizeof(MODULEENTRY32);
		DWORD _err;

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			_err = GetLastError();
			return nullptr;
		}

		if (Module32First(hProcessSnap, &modulEnty) == FALSE)
		{
			_err = GetLastError();
			printf("Error: Modul32First faild! | Code: %d [%x]\n", _err, _err);
			CloseHandle(hProcessSnap); // clean the snapshot object
			return nullptr;
		}
		//search all moduls an compare name
		do
		{
			if (strcmp(modulEnty.szModule, modulName) == 0)
			{
				CloseHandle(hProcessSnap);
				return (BYTE*)modulEnty.modBaseAddr;
			}
		} while (Module32Next(hProcessSnap, &modulEnty) != FALSE);

		CloseHandle(hProcessSnap);
		return nullptr;
	}

	//get entire modullist of the process
	std::vector<MODULEENTRY32>* MemorySSL::get_moduleList(const char* modulName, int processId)
	{
		HANDLE hProcessSnap;
		std::vector<MODULEENTRY32>* modulList = new std::vector<MODULEENTRY32>;
		MODULEENTRY32 currentModul;
		currentModul.dwSize = sizeof(MODULEENTRY32);
		int count = 0;
		DWORD _err;

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			_err = GetLastError();
			printf("Error: CreateToolhelp32Snapshot faild! | Code: %d [%x]\n", _err, _err);
			return nullptr;
		}

		if (Module32First(hProcessSnap, &currentModul) == FALSE)
		{
			_err = GetLastError();
			printf("Error: Modul32First faild! | Code: %d [%x]\n", _err, _err);
			CloseHandle(hProcessSnap); // clean the snapshot object
			return nullptr;
		}

		//copy eatch modul into the list
		do
		{
			modulList->push_back(currentModul);
		} while (Module32Next(hProcessSnap, &currentModul) != FALSE);
		CloseHandle(hProcessSnap); // clean the snapshot object
		return modulList;
	}


	//============PROCESSMEMORY============
	//read pointer without module
	BYTE* MemorySSL::readPointer(void* baseAddr, std::vector<DWORD> offsets)
	{
		BYTE* address;
		DWORD _err;

		if (ReadProcessMemory(ShellShock, baseAddr, &address, sizeof(address), NULL) != NULL)
		{
			for (int i = 0; i < offsets.size(); i++)
			{
				address = readPointer((void*)(address + offsets[i]), {});
			}
			return address;
		}
		else
		{
			
			_err = GetLastError();
			return NULL;
		}
	}


	//read Value
	void MemorySSL::readBytes(void* startAddr, BYTE* targetBuffer, int size)
	{
		ReadProcessMemory(ShellShock, startAddr, targetBuffer, size, NULL);
	}

	void MemorySSL::writeBytes(BYTE* address, BYTE bytes[], int size)
	{
		WriteProcessMemory(ShellShock, address, bytes, (SIZE_T)size, NULL);
	}

	std::string MemorySSL::readString(BYTE* stringAddress)
	{
		int lenght = readValue<int>(stringAddress + 0x08);
		if (lenght > 0 && lenght < 50)
		{
			BYTE buffer[256];
			readBytes(stringAddress + 0x0C, buffer, lenght * 2);

			std::string result = "";

			for (int i = 0; i < lenght * 2; i += 2)
			{
				result.append((char*)&buffer[i]);
			}
			return result;
		}
		
		return "?";
	}


	//============WINDOWINFO============
	HWND MemorySSL::getWindowHandleByWindowName(LPCSTR windowName)
	{
		HWND ApplicationWindowHandle = FindWindowA(0, windowName);
		DWORD _err;
		if (ApplicationWindowHandle != NULL)
		{
			return ApplicationWindowHandle;
		}
		else
		{
			_err = GetLastError();
			printf("Error: Getting windowhandle by windowname faild! | Code: %d [%x]\n", _err, _err);
			return NULL;
		}
	}
	void MemorySSL::readGameWindowRect(RECT* rectAddr)
	{
		GetWindowRect(MainWindow, rectAddr);
	}