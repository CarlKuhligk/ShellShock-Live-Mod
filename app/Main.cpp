// ExShellShockAutpRuler.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#include "IncludeHead.h"


// MemoryLogic
Game vGame = Game();

// Overlay
RulerOverlayOBJ Overlay = RulerOverlayOBJ();

// Windows Messagehandling
LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMesg, WPARAM wParam, LPARAM lParam)
{
    // GDI+
    //HDC hdc;
    //PAINTSTRUCT ps;

    switch (uMesg)
    {
    case WM_PAINT:
        // Draw
        //hdc = BeginPaint(hWnd, &ps);
        //vGame.Draw(&hdc);
        //EndPaint(hWnd, &ps);
        break;
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, uMesg, wParam, lParam);
}


// Simple Timer
std::clock_t timer1;
double duration;


// Collsisontest
//LineCollider2D line1 = LineCollider2D(Point2(500.0f, 40.0f), Point2(200.0f, 100.0f), 0);
//LineCollider2D line2 = LineCollider2D(Point2(30.0f, 20.0f), Point2(500.0f, 200.0f), 1);

int main()
{
    //line1.Collide(line2);


    Overlay.createWindow();

    BOOL running = true;
    while (true)
    {
        // Windowsevents
        while (PeekMessage(&Overlay.msg, 0, 0, 0, PM_REMOVE))
        {
            if (Overlay.msg.message == WM_QUIT) running = false;
            TranslateMessage(&Overlay.msg);
            DispatchMessage(&Overlay.msg);
        }

        
        if (duration >= 0.03f)
        {
            timer1 = std::clock();


            // Set Position and Size
            Overlay.setRectangle(vGame.WindowPosition, vGame.WindowSize);
            Overlay.update();


            vGame.UpdateInput();

            // Draw Overlay 
            HDC hdc = GetDC(Overlay.hMainWindow);
            vGame.Draw(&hdc);
            ReleaseDC(Overlay.hMainWindow, hdc);


            if (vGame.EnterBattle == true)
            {

            }


            if (vGame.InBattle == true)
            {
                system("cls");
                //std::cout << "Gravity: ";
                //std::cin >> vGame.Gravity;
                //system("cls");
                //std::cout << "Window:\n";
                //std::cout << "Position X : " << vGame.WindowPosition.x << " Y : "
                //    << vGame.WindowPosition.y << "\n";
                //std::cout << "Size W : " << vGame.WindowSize.cx
                //    << " H : "
                //    << vGame.WindowSize.cy
                //    << "\n\n";

                //std::cout << "Wind : " << vGame.WindIndicator.Force << "\n";
                std::cout << "WeaponName : " << vGame.WeaponSelector.Name << " Stage : "
                    << vGame.WeaponSelector.Stage << "\n" << (void*)vGame.WeaponSelector.ObjectAddress;
                //std::cout << "Player : " << vGame.PlayerList.size() << "\n\n";
                //std::cout << "A : " << vGame.Aimer.Angle
                //    << " V : " << vGame.Aimer.Velocity << "\n\n";

                //for (int i = 0; i < vGame.PlayerList.size(); i++)
                //{
                //    std::cout << "Addr : " << (void*)vGame.PlayerList[i].ObjectAddress << "\n";
                //    std::cout << "DeadData : " << (void*)vGame.PlayerList[i].DeadData << "\n";
                //    std::cout << "Name : " << vGame.PlayerList[i].Name << "\n";
                //    std::cout << "Steam : " << vGame.PlayerList[i].SteamId << "\n";
                //    std::cout << "Connect : " << vGame.PlayerList[i].IsConnected << "\n";
                //    std::cout << "Level : " << vGame.PlayerList[i].Level << "\n";
                //    std::cout << "Team : " << vGame.PlayerList[i].Team << "\n";
                //    std::cout << "Health : " << vGame.PlayerList[i].Health << "\n";
                //    std::cout << "Amor : " << vGame.PlayerList[i].Amor << "\n";
                //    std::cout << "Fuel : " << vGame.PlayerList[i].Fuel << "\n";
                //    std::cout << "A : " << vGame.PlayerList[i].Angle <<
                //        " V : " << vGame.PlayerList[i].Velocity << "\n";
                //    std::cout << "X : " << vGame.PlayerList[i].TankPosition.X
                //        << " Y : " << vGame.PlayerList[i].TankPosition.Y << "\n\n";
                //}

            }
            else if (vGame.LeaveBattle == true)
            {
                system("cls");
                std::cout << "Battle was left\n";
                
            }


        }
        duration = (std::clock() - timer1) / (double)CLOCKS_PER_SEC;
        
    }

    
    


}
