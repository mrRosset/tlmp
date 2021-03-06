#include "UI.h"

bool TLMP::suppressInGameMouse = false;
bool TLMP::UISetup = false;

void TLMP::ResizeUI()
{
  // Added the main game GUI elements
  CEGUI::Window *pRoot = NULL, *pMainMenuOptions = NULL, *pMainMenuDialogs = NULL;
  CEGUI::Window *pSheet = NULL, *pMainMenuSplash = NULL;
  CEGUI::Window *pMainMenuDialogClientConnecting;
  CEGUI::Window *pMainMenuDialogClientConnectedFailed;
  CEGUI::Window *pMainMenuDialogClientDisconnected;
  CEGUI::Window *pInGameRoot, *pInGameChat;
  CEGUI::Window *pMainMenuButton;
  CEGUI::Window *pMainMenuLobby, *pMainMenuLobbyViewGames, *pMainMenuDialogHost, *pMainMenuDialogJoin;

  CEGUI::SchemeManager* sm = CEGUI::SchemeManager::getSingletonPtr();
  if (!sm) {
    log("Error: No CEGUI SchemeManager found.");
    return;
  } else {
    log("SchemeManager found!");
  }

  //
  log("Loading OgreTray scheme...");
  CEGUI::Scheme *schemeOgreTray;

  try {
    schemeOgreTray = sm->loadScheme("OgreTray.scheme");
  } catch(CEGUI::Exception &ex) {
    log("CEGUI Exception: %s", ex.getMessage().c_str());
  } catch(std::exception &ex) {
    log("exception: %s", ex.what());
  }

  if (!schemeOgreTray) {
    log("Error: Could not load OgreTray.scheme!");
  } else {
    log("Scheme Loaded!");
  }

  // Find the root window for attaching our UI elements
  CEGUI::WindowManager* wm = UserInterface::getManager();
  if (!wm) {
    log("Error: No CEGUI WindowManager found.");
    return;
  }

  if (wm->isWindowPresent(CEGUI::String("25_Root"))) {
    pRoot = wm->getWindow(CEGUI::String("25_Root"));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error finding CEGUI Window \"25_Root\" - cannot add Multiplayer Options window to MainMenu.");
    return;
  }

  log("Loading Layout...");
  // Load the MainMenu Multiplayer Button
  try {
    pMainMenuButton = wm->loadWindowLayout(CEGUI::String("MainMenu_Multiplayer.layout"), CEGUI::String("25_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_Multiplayer.layout");
    return;
  }

  // Hookup button events
  if (pMainMenuButton)
  {
    pMainMenuButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_OpenMultiplayerOptions));
    pRoot->addChildWindow(pMainMenuButton);
  }

  // Load the MainMenu Multiplayer Splash Screen
  try {
    pMainMenuSplash = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerSplash.layout"), CEGUI::String("1001_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerSplash.layout");
    return;
  }
  
  // Hookup button events
  CEGUI::Window *pButtonSplash = pMainMenuSplash->recursiveChildSearch("1001_MultiplayerSplash_OkButton");
  if (pButtonSplash) {
    pButtonSplash->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerSplash_OkButton));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: MultiplayerSplash_OkButton");

    for (size_t i = 0; i < pButtonSplash->getChildCount(); i++) {
      multiplayerLogger.WriteLine(Info, L"  %s", pButtonSplash->getChildAtIdx(i));
    }
  }

  // Load the MainMenu Multiplayer Options Window
  try {
    pMainMenuOptions = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerOptions.layout"), CEGUI::String("1002_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerOptions.layout");
    return;
  }
  
  // Load the MainMenu Multiplayer Dialogs
  try {
    pMainMenuDialogs = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerDialogs.layout"), CEGUI::String("1003_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerDialogs.layout");
    return;
  }

  // Hookup button events
  if (pMainMenuButton)
  {
    pMainMenuButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_OpenMultiplayerOptions));
  }

  CEGUI::Window *pOptionsCancel = pMainMenuOptions->recursiveChildSearch("1002_MultiplayerOptions_CancelButton");
  if (pOptionsCancel) {
    pOptionsCancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_CloseMultiplayerOptions));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1002_MultiplayerOptions_CancelButton");
    return;
  }

  CEGUI::Window *pOptionsHost = pMainMenuOptions->recursiveChildSearch("1002_MultiplayerOptions_HostButton");
  if (pOptionsHost) {
    pOptionsHost->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerDialog_Host));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1002_MultiplayerOptions_HostButton");
    return;
  }
  
  CEGUI::Window *pOptionsJoin = pMainMenuOptions->recursiveChildSearch("1002_MultiplayerOptions_JoinButton");
  if (pOptionsJoin) {
    pOptionsJoin->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerOptions_Join));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1002_MultiplayerOptions_JoinButton");
    return;
  }
    
  CEGUI::Window *pOptionsTestLobby = pMainMenuOptions->recursiveChildSearch("1002_MultiplayerOptions_TestLobbyButton");
  if (pOptionsTestLobby) {
    pOptionsTestLobby->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerOptions_TestLobby));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1002_MultiplayerOptions_TestLobbyButton");
    return;
  }
    

  // Load the MainMenu Multiplayer Join Window
  try {
    pMainMenuDialogJoin = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerDialog_Join.layout"), CEGUI::String("1006_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerDialog_Join.layout");
    return;
  }

  CEGUI::Window *pOptionsJoinCancel = pMainMenuDialogJoin->recursiveChildSearch("1006_MultiplayerOptions_Join_CancelButton");
  if (pOptionsJoinCancel) {
    pOptionsJoinCancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerOptions_Join_Cancel));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1006_MultiplayerOptions_Join_CancelButton");
    return;
  }
   
  CEGUI::Window *pOptionsJoinJoin = pMainMenuDialogJoin->recursiveChildSearch("1006_MultiplayerOptions_Join_JoinButton");
  if (pOptionsJoinJoin) {
    pOptionsJoinJoin->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerOptions_Join_Join));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1006_MultiplayerOptions_Join_JoinButton");
    return;
  }


  // Load the MainMenu Multiplayer Host Window
  try {
    pMainMenuDialogHost = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerDialog_Host.layout"), CEGUI::String("1006_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerOptions.layout");
    return;
  }
    
  CEGUI::Window *pOptionsHostCancel = pMainMenuDialogHost->recursiveChildSearch("1006_MultiplayerDialog_Host_CancelButton");
  if (pOptionsHostCancel) {
    pOptionsHostCancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerDialog_Host_Cancel));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1006_MultiplayerDialog_Host_CancelButton");
    return;
  }
    
  CEGUI::Window *pOptionsHostHost = pMainMenuDialogHost->recursiveChildSearch("1006_MultiplayerDialog_Host_HostButton");
  if (pOptionsHostHost) {
    pOptionsHostHost->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerDialog_Host_Host));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1006_MultiplayerDialog_Host_HostButton");
    return;
  }


  //
      
  CEGUI::Window *pWaitServer = pMainMenuDialogs->recursiveChildSearch("1003_MultiplayerOptions_WaitServerLoad_OkButton");
  if (pWaitServer) {
    pWaitServer->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerOptions_WaitServer_OkButton));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1003_MultiplayerOptions_WaitServerLoad_OkButton");
    return;
  }

  // Load the MainMenu Multiplayer Dialog Client Connecting
  try {
    pMainMenuDialogClientConnecting = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerDialogClientConnecting.layout"), CEGUI::String("1005_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerDialogClientConnecting.layout");
    return;
  }

  // Hookup Button Events   
  CEGUI::Window *pDialogClientConnectingOk = pMainMenuDialogClientConnecting->recursiveChildSearch("1005_MultiplayerOptionsClientConnecting_OkButton");
  if (pDialogClientConnectingOk) {
    pDialogClientConnectingOk->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerClientConnecting_OkButton));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1005_MultiplayerOptionsClientConnecting_OkButton");
    return;
  }
  
  // Hookup Button Events   
  CEGUI::Window *pDialogClientConnectingCancel = pMainMenuDialogClientConnecting->recursiveChildSearch("1005_MultiplayerOptionsClientConnecting_CancelButton");
  if (pDialogClientConnectingCancel) {
    pDialogClientConnectingCancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerClientConnecting_CancelButton));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1005_MultiplayerOptionsClientConnecting_CancelButton");
    return;
  }

  // Load the MainMenu Multiplayer Dialog Client Connected
  try {
    pMainMenuDialogClientConnectedFailed = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerDialogClientConnectedFailed.layout"), CEGUI::String("1006_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerDialogClientConnectedFailed.layout");
    return;
  }
  
  // Hookup Button Events   
  CEGUI::Window *pDialogClientConnectedFailedOk = pMainMenuDialogClientConnectedFailed->recursiveChildSearch("1006_MultiplayerOptionsClientConnectedFailed_OkButton");
  if (pDialogClientConnectedFailedOk) {
    pDialogClientConnectedFailedOk->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerClientConnectedFailed_OkButton));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1006_MultiplayerOptionsClientConnectedFailed_OkButton");
    return;
  }

  // Load the MainMenu Multiplayer Dialog Client Disconnected
  try {
    pMainMenuDialogClientDisconnected = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerDialogClientDisconnected.layout"), CEGUI::String("1007_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerDialogClientConnecting.layout");
    return;
  }
  
  // Hookup Button Events   
  CEGUI::Window *pDialogClientDisconnectedOk = pMainMenuDialogClientDisconnected->recursiveChildSearch("1007_MultiplayerOptionsClientDisconnected_OkButton");
  if (pDialogClientDisconnectedOk) {
    pDialogClientDisconnectedOk->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerClientDisconnected_OkButton));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1007_MultiplayerOptionsClientDisconnected_OkButton");
    return;
  }

  //
  onNetworkStateChange();

  // Find the root window in-game for attaching our UI elements
  if (wm->isWindowPresent(CEGUI::String("1_PlayerHealthRoot"))) {
    pInGameRoot = wm->getWindow(CEGUI::String("1_PlayerHealthRoot"));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error finding CEGUI Window \"1_PlayerHealthRoot\" - cannot add InGame UI functionality");
    return;
  }

  // Load the In-game window
  try {
    pInGameChat = wm->loadWindowLayout(CEGUI::String("InGame_Chat.layout"), CEGUI::String("1010_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_Multiplayer.layout");
    return;
  }

  // Hookup Chat Entry Events -- Testing to stop Inventory from opening when typing 'i' into chat
  CEGUI::Window *pInGameChatEntry = pInGameChat->recursiveChildSearch("1010_ChatEntry");
  if (pInGameChatEntry) {
    pInGameChatEntry->subscribeEvent(CEGUI::Editbox::EventCharacterKey, CEGUI::Event::Subscriber(&EditboxEvent_KeyDownChatEntry));
    pInGameChatEntry->subscribeEvent(CEGUI::Editbox::EventDeactivated, CEGUI::Event::Subscriber(&EditboxEvent_FocusLost));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1010_ChatEntry");
    return;
  }



  // Load the MainMenu Multiplayer Lobby Window
  try {
    pMainMenuLobby = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerLobby.layout"), CEGUI::String("1020_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerLobby.layout");
    return;
  }

  // Hookup Back Button Event
  CEGUI::Window *pLobbyBackButton = pMainMenuLobby->recursiveChildSearch("1020_MultiplayerLobby_BackButton");
  if (pLobbyBackButton) {
    pLobbyBackButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerLobby_Back));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1020_MultiplayerLobby_BackButton");
    return;
  }

  // Hookup Chat Entry Events
  CEGUI::Window *pLobbyChatEntry = pMainMenuLobby->recursiveChildSearch("1020_MultiplayerLobby_ChatEntry");
  if (pLobbyChatEntry) {
    pLobbyChatEntry->subscribeEvent(CEGUI::Editbox::EventCharacterKey, CEGUI::Event::Subscriber(&EditboxEvent_KeyDownLobbyChatEntry));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1020_MultiplayerLobby_ChatEntry");
    return;
  }
  
  // Hookup ViewGames Button Event
  CEGUI::Window *pLobbyViewGamesButton = pMainMenuLobby->recursiveChildSearch("1020_MultiplayerLobby_ViewGamesButton");
  if (pLobbyViewGamesButton) {
    pLobbyViewGamesButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerLobby_ViewGames));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1020_MultiplayerLobby_ViewGamesButton");
    return;
  }


  // Load the MainMenu Multiplayer Lobby View Games Window
  try {
    pMainMenuLobbyViewGames = wm->loadWindowLayout(CEGUI::String("MainMenu_MultiplayerLobbyViewGames.layout"), CEGUI::String("1020_"));
  } catch (exception &e) {
    log(e.what());
    multiplayerLogger.WriteLine(Error, L"Exception occurred when reading MainMenu_MultiplayerLobbyViewGames.layout");
    return;
  }

  // Hookup Back Button Event
  CEGUI::Window *pLobbyViewGamesBackButton = pMainMenuLobbyViewGames->recursiveChildSearch("1020_MultiplayerLobbyViewGames_BackButton");
  if (pLobbyViewGamesBackButton) {
    pLobbyViewGamesBackButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerLobbyViewGames_Back));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1020_MultiplayerLobbyViewGames_BackButton");
    return;
  }

  // Hookup Refresh Button Event
  CEGUI::Window *pLobbyViewGamesRefreshButton = pMainMenuLobbyViewGames->recursiveChildSearch("1020_MultiplayerLobbyViewGames_RefreshButton");
  if (pLobbyViewGamesRefreshButton) {
    pLobbyViewGamesRefreshButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerLobbyViewGames_Refresh));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1020_MultiplayerLobbyViewGames_RefreshButton");
    return;
  }
  
  // Hookup Host Button Event
  CEGUI::Window *pLobbyViewGamesHostButton = pMainMenuLobbyViewGames->recursiveChildSearch("1020_MultiplayerLobbyViewGames_HostButton");
  if (pLobbyViewGamesHostButton) {
    pLobbyViewGamesHostButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerLobbyViewGames_Host));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1020_MultiplayerLobbyViewGames_HostButton");
    return;
  }
  
  // Hookup Join Button Event
  CEGUI::Window *pLobbyViewGamesJoinButton = pMainMenuLobbyViewGames->recursiveChildSearch("1020_MultiplayerLobbyViewGames_JoinButton");
  if (pLobbyViewGamesJoinButton) {
    pLobbyViewGamesJoinButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&ButtonEvent_MultiplayerLobbyViewGames_Join));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1020_MultiplayerLobbyViewGames_JoinButton");
    return;
  }

  // Hookup Games MultiColumnList
  CEGUI::MultiColumnList *pLobbyViewGamesGamesList = (CEGUI::MultiColumnList *)pMainMenuLobbyViewGames->recursiveChildSearch("1020_MultiplayerLobby_GamesListHistory");
  if (pLobbyViewGamesGamesList) {
    CEGUI::ListboxTextItem *newItem0 = new CEGUI::ListboxTextItem("Test Game");
    CEGUI::ListboxTextItem *newItem1 = new CEGUI::ListboxTextItem("1/10");
    CEGUI::ListboxTextItem *newItem2 = new CEGUI::ListboxTextItem("Description");

    pLobbyViewGamesGamesList->addColumn("Game Name", 0, CEGUI::UDim(0.2f, 25));
    pLobbyViewGamesGamesList->addColumn("Players", 1, CEGUI::UDim(0.2f, 25));
    pLobbyViewGamesGamesList->addColumn("Description", 2, CEGUI::UDim(0.25f, 25));

    pLobbyViewGamesGamesList->addRow(newItem0, 0, 0);
    pLobbyViewGamesGamesList->setItem(newItem1, 1, 0);
    pLobbyViewGamesGamesList->setItem(newItem2, 2, 0);

    pLobbyViewGamesGamesList->setShowHorzScrollbar(false);
    pLobbyViewGamesGamesList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
  }


  
  
  
  // Grab the Sheet window
  if (wm->isWindowPresent(CEGUI::String("Sheet"))) {
    pSheet = wm->getWindow(CEGUI::String("Sheet"));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error finding CEGUI Window \"Sheet\" - cannot add Multiplayer Options window to MainMenu.");
    return;
  }

  // Hookup everything to the existing main menu
  pRoot->addChildWindow(pMainMenuButton);
  pInGameRoot->addChildWindow(pInGameChat);
  pSheet->addChildWindow(pMainMenuOptions);
  pSheet->addChildWindow(pMainMenuDialogs);
  pSheet->addChildWindow(pMainMenuDialogClientConnecting);
  pSheet->addChildWindow(pMainMenuDialogClientConnectedFailed);
  pSheet->addChildWindow(pMainMenuDialogClientDisconnected);
  pSheet->addChildWindow(pMainMenuLobby);
  pSheet->addChildWindow(pMainMenuLobbyViewGames);
  pSheet->addChildWindow(pMainMenuDialogHost);
  pSheet->addChildWindow(pMainMenuDialogJoin);

  pMainMenuLobby->setVisible(false);
  pMainMenuDialogHost->setVisible(false);
  pMainMenuDialogJoin->setVisible(false);
  pMainMenuLobbyViewGames->setVisible(false);
  pMainMenuDialogClientConnectedFailed->setVisible(false);
  pMainMenuDialogClientDisconnected->setVisible(false);
  pMainMenuDialogClientConnecting->setVisible(false);
  pMainMenuOptions->setVisible(false);
  pMainMenuDialogs->setVisible(false);

  if (!UISetup) {
    pSheet->addChildWindow(pMainMenuSplash);
    pMainMenuSplash->setVisible(true);
    pMainMenuSplash->moveToFront();
  }
}

void TLMP::SetupUI()
{
  UISetup = true;

  CEGUI::Window *pSheet = NULL, *pMainMenuSplash = NULL;

  Client::getSingleton().SetCallback_OnConnected(OnClientConnected);
  Client::getSingleton().SetCallback_OnDisconnected(OnClientDisconnected);
  Client::getSingleton().SetCallback_OnConnectFailed(OnClientConnectFailed);

  // Find the root window for attaching our UI elements
  CEGUI::WindowManager* wm = UserInterface::getManager();
  if (!wm) {
    log("Error: No CEGUI WindowManager found.");
    return;
  }

  // Grab the Sheet window
  if (wm->isWindowPresent(CEGUI::String("Sheet"))) {
    pSheet = wm->getWindow(CEGUI::String("Sheet"));
  } else {
    multiplayerLogger.WriteLine(Error, L"Error finding CEGUI Window \"Sheet\" - cannot add Multiplayer Options window to MainMenu.");
    return;
  }

  pMainMenuSplash = pSheet->recursiveChildSearch("1001_MainMenu_Multiplayer_Splash");
  if (pMainMenuSplash) {
    pMainMenuSplash->moveToFront();
  } else {
    log(L"Error: Could not find 1001_MainMenu_Multiplayer_Splash");
    for (size_t i = 0; i < pSheet->getChildCount(); i++) {
      log("  %s", pSheet->getChildAtIdx(i)->getName().c_str());
    }
  }
}

void TLMP::GameClient_CreateUI(CGame* game)
{
  SetupUI();
}

void TLMP::DisplayWaitForServerWindow()
{
  CEGUI::WindowManager* wm = UserInterface::getManager();
  CEGUI::Window *pWindow = NULL;
  CEGUI::Window *pWaitServerLoad = NULL;
  CEGUI::Window *pWindowOptions = NULL;

  // Sanity check on the window manager
  if (!wm) {
    multiplayerLogger.WriteLine(Error, L"Error getting WindowManager: NULL");
    return;
  }

  // Grab the Sheet window
  if (wm->isWindowPresent(CEGUI::String("Sheet"))) {
    CEGUI::Window *pSheet = wm->getWindow(CEGUI::String("Sheet"));

    pWaitServerLoad = pSheet->recursiveChildSearch("1003_MultiplayerOptions_WaitServerLoad");

    if (pWaitServerLoad) {
      pWaitServerLoad->setVisible(true);
      pWaitServerLoad->moveToFront();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error finding CEGUI Window \"1003_MultiplayerOptions_WaitServerLoad\"");
      return;
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error finding CEGUI Window \"Sheet\" - cannot add Multiplayer Options window to MainMenu.");
    return;
  }
}

bool TLMP::ButtonEvent_MultiplayerLobby_Back(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowLobby = UserInterface::getWindowFromName("1020_MultiplayerLobby");
  CEGUI::Window *pWindowMPOptions = UserInterface::getWindowFromName("1002_MultiplayerOptions");


  if (pWindowLobby && pWindowMPOptions) {
    pWindowMPOptions->setVisible(true);
    pWindowMPOptions->moveToFront();

    pWindowLobby->setVisible(false);
    pWindowLobby->moveToBack();

    // Disconnect and reset the text in our windows
    LobbyClient::getSingleton().Disconnect();
 
    CEGUI::Listbox* pWindowLobbyChatHistory = (CEGUI::Listbox*)getLobbyChatHistoryWindow();
    if (pWindowLobbyChatHistory) {
      pWindowLobbyChatHistory->setText("");
    }

    CEGUI::Listbox* pWindowLobbyPlayerList = (CEGUI::Listbox*)getLobbyPlayerListWindow();
    if (pWindowLobbyPlayerList) {
      pWindowLobbyPlayerList->setText("");
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Lobby Window");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerLobby_ViewGames(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowLobby = UserInterface::getWindowFromName("1020_MultiplayerLobby");
  CEGUI::Window *pWindowLobbyViewGames = UserInterface::getWindowFromName("1020_MultiplayerLobbyViewGames");

  if (pWindowLobbyViewGames) {
    pWindowLobby->setVisible(false);
    pWindowLobby->moveToBack();

    pWindowLobbyViewGames->setVisible(true);
    pWindowLobbyViewGames->moveToFront();
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Lobby Window");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerLobbyViewGames_Back(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowLobby = UserInterface::getWindowFromName("1020_MultiplayerLobby");
  CEGUI::Window *pWindowLobbyViewGames = UserInterface::getWindowFromName("1020_MultiplayerLobbyViewGames");

  if (pWindowLobby) {
    pWindowLobby->setVisible(true);
    pWindowLobby->moveToFront();

    pWindowLobbyViewGames->setVisible(false);
    pWindowLobbyViewGames->moveToBack();
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Lobby Window");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerLobbyViewGames_Refresh(const CEGUI::EventArgs& args)
{
  //CEGUI::Window *pWindowLobby = UserInterface::getWindowFromName("1020_MultiplayerLobby");
  CEGUI::Window *pWindowLobbyViewGames = UserInterface::getWindowFromName("1020_MultiplayerLobbyViewGames");

  if (pWindowLobbyViewGames) {
    /*
    pWindowLobby->setVisible(true);
    pWindowLobby->moveToFront();

    pWindowLobbyViewGames->setVisible(false);
    pWindowLobbyViewGames->moveToBack();
    */

    log("Refresh");

    LobbyMessages::ViewGames msgDummy;  // Used to appease the API
    LobbyClient::getSingleton().SendMessage<LobbyMessages::ViewGames>(L_C_VIEW_GAMES, &msgDummy);
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Lobby Window");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerLobbyViewGames_Host(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1006_MultiplayerDialog_Host");
  CEGUI::Window *pWindowLobbyViewGames = UserInterface::getWindowFromName("1020_MultiplayerLobbyViewGames");

  if (pWindowLobbyViewGames && pWindow) {
    pWindowLobbyViewGames->setVisible(false);
    pWindowLobbyViewGames->moveToBack();

    pWindow->setVisible(true);
    pWindow->moveToFront();
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1006_MultiplayerDialog_Host");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerLobbyViewGames_Join(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowLobby = UserInterface::getWindowFromName("1020_MultiplayerLobby");
  CEGUI::Window *pWindowLobbyViewGames = UserInterface::getWindowFromName("1020_MultiplayerLobbyViewGames");

  if (pWindowLobby) {
    /*
    pWindowLobby->setVisible(true);
    pWindowLobby->moveToFront();
    */

    pWindowLobbyViewGames->setVisible(false);
    pWindowLobbyViewGames->moveToBack();

    CEGUI::MultiColumnList *pLobbyGamesList = (CEGUI::MultiColumnList *)getLobbyViewGames();
    if (pLobbyGamesList) {
      CEGUI::ListboxItem *item = pLobbyGamesList->getFirstSelectedItem();
      if (item) {
        CEGUI::uint index = pLobbyGamesList->getItemRowIndex(item);
        Game* joinGame = LobbyClient::getSingleton().getGameFromIndex(index);
        log("List selection: %s %i", item->getText().c_str(), joinGame->getID());
        
        LobbyMessages::GameID msgGameID;
        msgGameID.set_id(joinGame->getID());
        LobbyClient::getSingleton().SendMessage<LobbyMessages::GameID>(L_C_REQUEST_JOINGAME, &msgGameID);
      }
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Lobby Window");
  }

  return true;
}

bool TLMP::ButtonEvent_OpenMultiplayerOptions(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1002_MultiplayerOptions");

  if (pWindow) {
    pWindow->setVisible(true);
    pWindow->moveToFront();

  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Options Window");
  }

  return true;
}

bool TLMP::ButtonEvent_CloseMultiplayerOptions(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1002_MultiplayerOptions");

  if (pWindow) {
    pWindow->setVisible(false);
    pWindow->moveToBack();
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Options Window");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerDialog_Host(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1006_MultiplayerDialog_Host");

  if (pWindow) {
    pWindow->setVisible(true);
    pWindow->moveToFront();
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1006_MultiplayerDialog_Host");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerOptions_Join(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1006_MultiplayerOptions_Join");

  if (pWindow) {
    pWindow->setVisible(true);
    pWindow->moveToFront();
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1006_MultiplayerOptions_Join");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerOptions_TestLobby(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1020_MultiplayerLobby");
  CEGUI::Window *pWindowOptions = UserInterface::getWindowFromName("1002_MultiplayerOptions");
  CEGUI::Editbox *pWindowLobbyChatEntry = (CEGUI::Editbox *)UserInterface::getWindowFromName("1020_MultiplayerLobby_ChatEntry");

  if (pWindow) {
    pWindow->setVisible(true);
    pWindow->moveToFront();

    pWindowOptions->setVisible(false);
    pWindowOptions->moveToBack();

    pWindowLobbyChatEntry->activate();
    pWindowLobbyChatEntry->moveToFront();
    pWindowLobbyChatEntry->setMaxTextLength(200);
    
    // Connect to lobby server here
    {
      const char url[256] = "localhost";
      const int port = 5446;

      // Load the configuration file if present and extract the url from it
      FILE *fp = NULL;
      errno_t err = fopen_s(&fp, "./TLAPI/lobby.cfg", "rt");
      if (!err) {
        log(L"Error could not open lobby configuration, defaulting to localhost:5446");
        multiplayerLogger.WriteLine(Error, L"Error could not open lobby configuration, defaulting to localhost:5446");
      } else {
        fscanf(fp, "%s:%i", url, &port);
        fclose(fp);

        log(L"Connecting to lobby server: %s:%i", url, port);
        multiplayerLogger.WriteLine(Error, L"Connecting to lobby server: %s:%i", url, port);
      }

      LobbyClient::getSingleton().Connect(url, port);
    }
  } else {
    log(L"Error could not find Multiplayer Lobby Window");
    multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Lobby Window");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerOptions_Join_Cancel(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1006_MultiplayerOptions_Join");
  CEGUI::Window *pWindowOptions = UserInterface::getWindowFromName("1002_MultiplayerOptions");

  log("DEBUG: Join_Cancel: %p %p", pWindow, pWindowOptions);

  if (pWindowOptions && pWindow) {
    pWindow->setVisible(false);
    pWindow->moveToBack();

    pWindowOptions->setVisible(true);
    pWindowOptions->moveToFront();
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Options Join Window *or* 1002_MultiplayerOptions");
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerDialog_Host_Cancel(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1006_MultiplayerDialog_Host");
  CEGUI::Window *pWindowLobbyViewGames = UserInterface::getWindowFromName("1020_MultiplayerLobbyViewGames");

  // Hide hosting options
  if (pWindow) {
    pWindow->setVisible(false);
    pWindow->moveToBack();
  }

  // If we're connected to the Lobby server send us back to the Lobby menu
  if (LobbyClient::getSingleton().IsConnected()) {
    if (pWindowLobbyViewGames) {
      pWindowLobbyViewGames->setVisible(true);
      pWindowLobbyViewGames->moveToFront();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error could not find Multiplayer Options Host Window *or* 1002_MultiplayerOptions");
    }
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerDialog_Host_Host(const CEGUI::EventArgs& args)
{
  u16 port = 0;
  CEGUI::Window *pWindowOptions = UserInterface::getWindowFromName("1002_MultiplayerOptions");

  if (pWindowOptions) {
    pWindowOptions->setVisible(false);
    pWindowOptions->moveToBack();

    CEGUI::Window *pWindow = UserInterface::getWindowFromName("1006_MultiplayerDialog_Host");

    // Remove the window
    if (pWindow) {
      pWindow->setVisible(false);
      pWindow->moveToBack();

      CEGUI::Editbox *pHostPort = (CEGUI::Editbox *)pWindow->recursiveChildSearch("MultiplayerDialog_Host_HostPortEdit");

      // Grab the text
      if (pHostPort) {
        const char* pPortString = pHostPort->getText().c_str();
        port = (u16)atoi(pPortString);

        // If we're connected to the Lobby server, send the server information
        log("LobbyClient::getSingleton().IsConnected() = %i", LobbyClient::getSingleton().IsConnected());
        if (LobbyClient::getSingleton().IsConnected()) {
          LobbyMessages::HostingNewGame msgHostingNewGame;
          LobbyMessages::Game *msgGame = msgHostingNewGame.mutable_game();
          msgGame->set_current_level("Unknown Level");
          msgGame->set_current_players(1);
          msgGame->set_description("Description of Game");
          msgGame->set_id(-1);
          msgGame->set_max_players(32);
          msgGame->set_name("Game Name Here");
          msgGame->set_port(port);
          LobbyClient::getSingleton().SendMessage<LobbyMessages::HostingNewGame>(L_C_HOSTING_NEW_GAME, &msgHostingNewGame);
        }
      } else {
        multiplayerLogger.WriteLine(Error, L"Error could not find MultiplayerDialog_Host_HostPortEdit");
        return false;
      }
    } else {
      multiplayerLogger.WriteLine(Error, L"Error could not find 1006_MultiplayerDialog_Host");
      return false;
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1002_MultiplayerOptions");
    return false;
  }

  // Finally, host it
  multiplayerLogger.WriteLine(Info, L"Hosting game on port %i...", port);
  Network::HostGame(port);

  onNetworkStateChange();
  multiplayerLogger.WriteLine(Info, L"Server setup completed.");

  return true;
}

bool TLMP::ButtonEvent_MultiplayerOptions_Join_Join(const CEGUI::EventArgs& args)
{
  u16 port = 0;
  wstring hostName;
  const char *hostNameString;

  CEGUI::Window *pWindowOptions = UserInterface::getWindowFromName("1002_MultiplayerOptions");

  if (pWindowOptions) {
    pWindowOptions->setVisible(false);
    pWindowOptions->moveToBack();

    CEGUI::Window *pWindow = UserInterface::getWindowFromName("1006_MultiplayerOptions_Join");

    // Remove the window
    if (pWindow) {
      pWindow->setVisible(false);
      pWindow->moveToBack();

      CEGUI::Editbox *pHostPort = (CEGUI::Editbox *)pWindow->recursiveChildSearch("MultiplayerOptions_Join_HostPortEdit");
      CEGUI::Editbox *pHostName = (CEGUI::Editbox *)pWindow->recursiveChildSearch("MultiplayerOptions_Join_HostNameEdit");

      // Grab the text
      if (pHostPort) {
        const char* pPortString = pHostPort->getText().c_str();
        port = (u16)atoi(pPortString);
      } else {
        multiplayerLogger.WriteLine(Error, L"Error could not find MultiplayerOptions_Join_HostPortEdit");
        return false;
      }

      if (pHostName) {
        hostNameString = pHostName->getText().c_str();

        size_t origsize = strlen(hostNameString) + 1;
        const size_t newsize = 100;
        size_t convertedChars = 0;
        wchar_t wcstring[newsize];
        mbstowcs_s(&convertedChars, wcstring, origsize, hostNameString, _TRUNCATE);

        hostName.append(wcstring);
      } else {
        multiplayerLogger.WriteLine(Error, L"Error could not find MultiplayerOptions_Join_HostNameEdit");
        return false;
      }
    } else {
      multiplayerLogger.WriteLine(Error, L"Error could not find 1006_MultiplayerOptions_Join");
      return false;
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1002_MultiplayerOptions");
    return false;
  }

  // Get the Connecting screen
  CEGUI::Window *pWindowClientConnect = UserInterface::getWindowFromName("1005_MultiplayerOptionsClientConnecting");
  if (pWindowClientConnect) {
    pWindowClientConnect->moveToFront();
    pWindowClientConnect->setVisible(true);
  }

  // Finally, attempt to connect
  multiplayerLogger.WriteLine(Info, L"Joining game at %s on port %i...", hostName.c_str(), port);
  Network::JoinGame(hostNameString, port);
  onNetworkStateChange();

  return true;
}

bool TLMP::ButtonEvent_MultiplayerOptions_WaitServer_OkButton(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowOptions = UserInterface::getWindowFromName("1003_MultiplayerOptions_WaitServerLoad");

  if (pWindowOptions) {
    pWindowOptions->setVisible(false);
    pWindowOptions->moveToBack();
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1003_MultiplayerOptions_WaitServerLoad");
    return false;
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerSplash_OkButton(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowSplash = UserInterface::getWindowFromName("1001_MainMenu_Multiplayer_Splash");

  if (pWindowSplash) {
    pWindowSplash->setVisible(false);
    pWindowSplash->moveToBack();
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1001_MainMenu_Multiplayer_Splash");
    return false;
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerClientConnecting_OkButton(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowClientConnect = UserInterface::getWindowFromName("1005_MultiplayerOptionsClientConnecting");
  if (pWindowClientConnect) {
    if (NetworkState::getSingleton().GetState() == CLIENT) {      
      pWindowClientConnect->setVisible(false);
      pWindowClientConnect->moveToBack();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error: Game is in weird state: Client window connecting shown but not in client state.");
      log(L"Error: Game is in weird state: Client window connecting shown but not in client state.");
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1005_MultiplayerOptionsClientConnecting");
    return false;
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerClientConnecting_CancelButton(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowClientConnect = UserInterface::getWindowFromName("1005_MultiplayerOptionsClientConnecting");
  if (pWindowClientConnect) {
    if (NetworkState::getSingleton().GetState() == CLIENT) {      
      NetworkState::getSingleton().SetState(SINGLEPLAYER);
      Client::getSingleton().Disconnect();

      pWindowClientConnect->setVisible(false);
      pWindowClientConnect->moveToBack();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error: Game is in weird state: Client window connecting shown but not in client state.");
      log(L"Error: Game is in weird state: Client window connecting shown but not in client state.");
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1005_MultiplayerOptionsClientConnecting");
    return false;
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerClientConnectedFailed_OkButton(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowClientConnect = UserInterface::getWindowFromName("1006_MultiplayerOptionsClientConnectedFailed");
  if (pWindowClientConnect) {
    if (NetworkState::getSingleton().GetState() == CLIENT) {      
      pWindowClientConnect->setVisible(false);
      pWindowClientConnect->moveToFront();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error: Game is in weird state: Client window connecting shown but not in client state.");
      log(L"Error: Game is in weird state: Client window connecting shown but not in client state.");
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1006_MultiplayerOptionsClientConnectedFailed");
    return false;
  }

  // Hide the connecting window
  pWindowClientConnect = UserInterface::getWindowFromName("1005_MultiplayerOptionsClientConnecting");
  if (pWindowClientConnect) {
    if (NetworkState::getSingleton().GetState() == CLIENT) {      
      NetworkState::getSingleton().SetState(SINGLEPLAYER);
      Client::getSingleton().Disconnect();

      pWindowClientConnect->setVisible(false);
      pWindowClientConnect->moveToBack();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error: Game is in weird state: Client window connecting shown but not in client state.");
      log(L"Error: Game is in weird state: Client window connecting shown but not in client state.");
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1005_MultiplayerOptionsClientConnecting");
    return false;
  }

  return true;
}

bool TLMP::ButtonEvent_MultiplayerClientDisconnected_OkButton(const CEGUI::EventArgs& args)
{
  CEGUI::Window *pWindowClientConnect = UserInterface::getWindowFromName("1007_MultiplayerOptionsClientDisconnected");
  if (pWindowClientConnect) {
    if (NetworkState::getSingleton().GetState() == CLIENT) {      
      pWindowClientConnect->setVisible(false);
      pWindowClientConnect->moveToFront();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error: Game is in weird state: Client window connecting shown but not in client state.");
      log(L"Error: Game is in weird state: Client window connecting shown but not in client state.");
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1007_MultiplayerOptionsClientDisconnected");
    return false;
  }

  return true;
}

bool TLMP::EditboxEvent_FocusLost(const CEGUI::EventArgs& args)
{
  CEGUI::Window* pInGameChatEntryBackground = getChatEntryBackgroundWindow();
  CEGUI::Window *pChatEntry = getChatEntryWindow();

  if (pInGameChatEntryBackground && pChatEntry) { 
    pInGameChatEntryBackground->setVisible(false);
    pChatEntry->setVisible(false);
    pChatEntry->hide();
  }

  return true;
}

bool TLMP::EditboxEvent_KeyDownChatEntry(const CEGUI::EventArgs& args)
{
  CEGUI::KeyEventArgs keyArgs = (CEGUI::KeyEventArgs&)args;
  size_t selectionEnd;
  static bool burnEnter = false;

  // If the user pressed enter, send the message out
  if (keyArgs.codepoint == 0xD) {
    CEGUI::MultiLineEditbox *pWindow = (CEGUI::MultiLineEditbox *)getChatHistoryWindow();
    CEGUI::Window* pInGameChatEntryBackground = getChatEntryBackgroundWindow();
    CEGUI::Window *pChatEntry = getChatEntryWindow();

    // Get the current network player
    NetworkEntity *netPlayer = searchCharacterByInternalObject(gameClient->pCPlayer);

    if (netPlayer) {
      if (pWindow && pChatEntry) {
        if (pChatEntry->getText().length() > 0) {
          NetworkMessages::ChatPlayerText msgChatPlayerText;
          msgChatPlayerText.set_characterid(netPlayer->getCommonId());
          msgChatPlayerText.set_text(pChatEntry->getText().c_str());
          pChatEntry->setText("");
          burnEnter = true;

          if (NetworkState::getSingleton().GetState() == CLIENT) {
            Client::getSingleton().SendMessage<NetworkMessages::ChatPlayerText>(C_PUSH_CHAT_PLAYER, &msgChatPlayerText);
          } else if (NetworkState::getSingleton().GetState() == SERVER) {
            CCharacter *character = (CCharacter*)gameClient->pCPlayer;
            string characterName(character->characterName.begin(), character->characterName.end());
            characterName.assign(character->characterName.begin(), character->characterName.end());

            // Add the server's message to it's own history
            CEGUI::String message = msgChatPlayerText.text().c_str();
            pWindow->appendText(CEGUI::String(characterName) + CEGUI::String(": ") + message + CEGUI::String("\n"));
            selectionEnd = pWindow->getText().length();
            pWindow->setCaratIndex(selectionEnd);

            Server::getSingleton().BroadcastMessage<NetworkMessages::ChatPlayerText>(S_PUSH_CHAT_PLAYER, &msgChatPlayerText);
          }
        } 
        /*
        else {
          if (pInGameChatEntryBackground->isVisible()) {
            pInGameChatEntryBackground->setVisible(false);
            pChatEntry->setVisible(false);
          }
        }*/
      }
    }

    // Really no nice way to make this:
    // Once we press Enter it automatically activates and calls this function
    // and in-turn hides it, so we have to burn off an Enter key
    if (pInGameChatEntryBackground && pChatEntry) { 
      // Hide the chat entry after we typed our message
      if (burnEnter) {
        pInGameChatEntryBackground->setVisible(false);
        pChatEntry->setVisible(false);

        burnEnter = false;
      }
    } else {
      burnEnter = true;
    }
  }
  
  return true;
}


// Lobby chat entry event
bool TLMP::EditboxEvent_KeyDownLobbyChatEntry(const CEGUI::EventArgs& args)
{
  CEGUI::KeyEventArgs keyArgs = (CEGUI::KeyEventArgs&)args;
  //static bool burnEnter = false;

  // If the user pressed enter, send the message out
  if (keyArgs.codepoint == 0xD) {
    CEGUI::MultiLineEditbox *pWindow = (CEGUI::MultiLineEditbox *)getLobbyChatHistoryWindow();
    CEGUI::Window *pChatEntry = getLobbyChatEntryWindow();

    // Get the current network player name
    string senderName(gameClient->pCPlayer->characterName.begin(), gameClient->pCPlayer->characterName.end());
    senderName.assign(gameClient->pCPlayer->characterName.begin(), gameClient->pCPlayer->characterName.end());

    if (pWindow && pChatEntry) {
      if (pChatEntry->getText().length() > 0) {
        LobbyMessages::ChatMessage msgChatMessage;
        msgChatMessage.set_sender(senderName);
        msgChatMessage.set_message(pChatEntry->getText().c_str());
        pChatEntry->setText("");

        LobbyClient::getSingleton().SendMessage<LobbyMessages::ChatMessage>(L_C_CHAT_MESSAGE, &msgChatMessage);
      }
    }
  }
  
  return true;
}


// In-game chat
CEGUI::Window* TLMP::getChatHistoryWindow()
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1010_ChatHistory");

  if (!pWindow) {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1010_ChatHistory");
  }

  return pWindow;
}

CEGUI::Window* TLMP::getChatEntryWindow()
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1010_ChatEntry");

  if (!pWindow) {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1010_ChatEntry");
  }

  return pWindow;
}

CEGUI::Window* TLMP::getChatEntryBackgroundWindow()
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1010_ChatEntryBackground");

  if (!pWindow) {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1010_ChatEntryBackground");
  }

  return pWindow;
}

// Lobby chat
CEGUI::Window* TLMP::getLobbyChatHistoryWindow()
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1020_MultiplayerLobby_ChatHistory");

  if (!pWindow) {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1020_MultiplayerLobby_ChatHistory");
  }

  return pWindow;
}

CEGUI::Window* TLMP::getLobbyChatEntryWindow()
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1020_MultiplayerLobby_ChatEntry");

  if (!pWindow) {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1020_MultiplayerLobby_ChatEntry");
  }

  return pWindow;
}

CEGUI::Window* TLMP::getLobbyPlayerListWindow()
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1020_MultiplayerLobby_PlayerList");

  if (!pWindow) {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1020_MultiplayerLobby_PlayerList");
  }

  return pWindow;
}

CEGUI::Window* TLMP::getLobbyViewGames()
{
  CEGUI::Window *pWindow = UserInterface::getWindowFromName("1020_MultiplayerLobby_GamesListHistory");

  if (!pWindow) {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1020_MultiplayerLobby_GamesListHistory");
  }

  return pWindow;
}


//
// Client has connected, hide the connecting screen
void TLMP::OnClientConnected(void *args)
{
  log(L"UI::OnClientConnected");

  CEGUI::Window *pWindowClientConnect = UserInterface::getWindowFromName("1005_MultiplayerOptionsClientConnecting");

  if (pWindowClientConnect) {
    if (NetworkState::getSingleton().GetState() == CLIENT) {      
      pWindowClientConnect->setVisible(false);
      pWindowClientConnect->moveToBack();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error: Game is in weird state: Client window connecting shown but not in client state.");
      log(L"Error: Game is in weird state: Client window connecting shown but not in client state.");
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1005_MultiplayerOptionsClientConnecting");
  }
}

void TLMP::OnClientDisconnected(void *args)
{
  log(L"UI::OnClientDisconnected");

  CEGUI::Window *pWindowClientConnect = UserInterface::getWindowFromName("1007_MultiplayerOptionsClientDisconnected");

  if (pWindowClientConnect) {
    if (NetworkState::getSingleton().GetState() == CLIENT) {      
      pWindowClientConnect->setVisible(true);
      pWindowClientConnect->moveToFront();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error: Game is in weird state: Client window connecting shown but not in client state.");
      log(L"Error: Game is in weird state: Client window connecting shown but not in client state.");
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1007_MultiplayerOptionsClientDisconnected");
  }
}

void TLMP::OnClientConnectFailed(void *args)
{
  log(L"UI::OnClientFailed");

  CEGUI::Window *pWindowClientConnect = UserInterface::getWindowFromName("1006_MultiplayerOptionsClientConnectedFailed");

  if (pWindowClientConnect) {
    if (NetworkState::getSingleton().GetState() == CLIENT) {      
      pWindowClientConnect->setVisible(true);
      pWindowClientConnect->moveToFront();
    } else {
      multiplayerLogger.WriteLine(Error, L"Error: Game is in weird state: Client window connecting shown but not in client state.");
      log(L"Error: Game is in weird state: Client window connecting shown but not in client state.");
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find 1006_MultiplayerOptionsClientConnectedFailed");
  }
}

void TLMP::onNetworkStateChange()
{
  CEGUI::Window *pMainMenuOptions = UserInterface::getWindowFromName("1002_MultiplayerOptions");
  CEGUI::Window *pOptionsStatusText = pMainMenuOptions->recursiveChildSearch("1002_MultiplayerOptions_MultiplayerStateText");

  multiplayerLogger.WriteLine(Info, L"Updating network state");

  if (pOptionsStatusText) {
    switch (NetworkState::getSingleton().GetState()) {
    case SINGLEPLAYER:
      pOptionsStatusText->setText("State: Singleplayer.");
      break;
    case SERVER:
      pOptionsStatusText->setText("State: Server");
      break;
    case CLIENT:
      pOptionsStatusText->setText("State: Client");
      break;
    }
  } else {
    multiplayerLogger.WriteLine(Error, L"Error could not find Button: 1002_MultiplayerOptions_MultiplayerStateText");
    return;
  }
}
