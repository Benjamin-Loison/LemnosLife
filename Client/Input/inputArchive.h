/*

#ifdef _WIN32
    bool CtrlHandler(DWORD type)
    {
        switch(type)
        {
            // Mettre via tabulation auto-completion console linux server c++ game
            // TODO: Ctrl + C or Close windows only close console http://www.mpgh.net/forum/showthread.php?t=986479
            case CTRL_C_EVENT:
                free();
                return false;
            case CTRL_CLOSE_EVENT:
                free();
        }
        return false;
    }
#endif

void inputManager()
{
    #ifdef _WIN32
    //    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, true);
    #endif
    //print("Input is loaded !");
    //if(!inputing)
      //  inputEvent();
}

void inputEvent()
{
    cin >> input;
    if(input == "game")
    {
        launchGame();
        print("Game launched !");
    }
    else if(input == "PotentialFPS")
        potentialFps = !potentialFps;
    else if(input == "exit" || input == "q" || input == "quit" || input == "echap" || input == "logout" || input == "stop" || input == "close")
    {
        #ifdef _WIN32
            closeConsole();
        #endif
        return;
    }
    else if(input == "positionPlayer")
        print(thePlayer->getViewGravity()->toString());
    else
    {
        // TODO: spam if Ctrl + C
        ///print(lg("Unknown command !"));
    }
    inputEvent();
}*/
