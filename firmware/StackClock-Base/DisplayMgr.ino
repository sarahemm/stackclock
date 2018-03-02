// DisplayMgr - Handle storing information about displays and talking to them.

enum boardTypes {
  BOARD_TYPE_BASE,
  BOARD_TYPE_DISPLAY_STANDARD,
  BOARD_TYPE_DISPLAY_UNIXTIME
};

char boardDescs[3][20];
byte displayNbrEditing = 1;

void displaymgrInit(void) {
  // english descriptions for board types
  strcpy(boardDescs[0], "Base");
  strcpy(boardDescs[1], "Standard Display");
  strcpy(boardDescs[2], "Unixtime Display");
  
  // set up the first board, which is us
  configRunning.boards[0].boardType = BOARD_TYPE;
  configRunning.boards[0].boardFWRev = BOARD_FWREV;
  strcpy(configRunning.boards[0].location, "BSE");
  configRunning.boards[0].tzOffset = 0;

  displaymgrRunDiscovery();
}

void displaymgrInitMainMenu(SUI::Menu *mainMenu) {
  // display menu
  
  SUI::Menu *displayMenu = mainMenu->subMenu(SUI_STR("display"), SUI_STR("Display setup menu"));
  displayMenu->addCommand(SUI_STR("show"), displaymgrShowBoardInfo, SUI_STR("Show attached displays"));
  
  // display edit menu
  SUI::Menu *displayEditMenu = displayMenu->subMenu(SUI_STR("edit"), SUI_STR("Edit display configuration"));
  displayEditMenu->addCommand(SUI_STR("select"),    displaymgrEditSelectBoard,    SUI_STR("Select which display to set up"));
  displayEditMenu->addCommand(SUI_STR("location"),  displaymgrEditLocation,       SUI_STR("Change display location"));
  displayEditMenu->addCommand(SUI_STR("tz"),        displaymgrEditTimezone,       SUI_STR("Change display timezone offset"));
  displayEditMenu->addCommand(SUI_STR("secs"),      displaymgrEditToggleSeconds,  SUI_STR("Toggle display of seconds"));
}

void displaymgrEditSelectBoard(void) {
  char buf[64];
  
  while(1) {
    // TODO: handle zero boards
    displayNbrEditing = cliGetNumber("Enter board number to edit ");
    if(displayNbrEditing > 0 && displayNbrEditing < configRunning.nbrBoards)
      break;
    sprintf(buf, "Invalid board, valid boards are 1-%d", configRunning.nbrBoards - 1);
    cliPrint(buf);
  }
}

void displaymgrEditLocation(void) {  
}

void displaymgrEditTimezone(void) {  
}

void displaymgrEditToggleSeconds(void) {  
}

void displaymgrRunDiscovery(void) {
  // TODO: enumerate the displays using the IR stacking rather than just hardcoding it
  configRunning.boards[1].boardType = BOARD_TYPE_DISPLAY_STANDARD;
  configRunning.boards[1].boardFWRev = 0;
  strcpy(configRunning.boards[1].location, "TOR");
  configRunning.boards[1].tzOffset = 0;

  configRunning.nbrBoards = 2;
}

void displaymgrShowBoardInfo(void) {
  signed char boardNbr;
  char buf[64];
  
  cliPrint("");
  cliPrint("Board Info");
  cliPrint("----------");
  byte failsafe = 0;
  for(boardNbr=configRunning.nbrBoards - 1; boardNbr >= 0; boardNbr--) {
    sprintf(buf, "Board %d: %s (FW revision %d)", boardNbr, boardDescs[configRunning.boards[boardNbr].boardType], configRunning.boards[boardNbr].boardFWRev);
    cliPrint(buf);
  }
}

void displaymgrEditConfig(void) {
}

