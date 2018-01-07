// CLI - Handle the serial port communications for configuration and clock setting.

SUI::SerialUI serialCLI = SUI::SerialUI();

void cliInit(void) {
  serialCLI.begin(115200);
  serialCLI.setTimeout(20000);
  serialCLI.setMaxIdleMs(30000);
  
  cliInitMenu();
}

void cliInitMenu(void) {
  serialCLI.setGreeting(SUI_STR("=== Welcome to the StackClock CLI ===\r\nEnter '?' to list available options."));
  // main menu
  SUI::Menu *mainMenu = serialCLI.topLevelMenu();

  configInitMainMenu(mainMenu);
  displaymgrInitMainMenu(mainMenu);
}

void cliPrint(char *msg) {
  serialCLI.println(msg);
}

byte cliGetNumber(char *prompt) {
  serialCLI.print(prompt);
  serialCLI.showEnterNumericDataPrompt();
  return serialCLI.parseInt();
}

// service any waiting CLI requests (called from loop())
void cliServiceLoop(void) {
  if (serialCLI.checkForUser()) {
    while (serialCLI.userPresent()) {
      serialCLI.handleRequests();
    }
  }
}

