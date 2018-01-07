// Config - Handle storing and retrieving configuration information.

#include "Config.h"
struct scConfig configRunning;

void configInit(void) {
  EEPROM.get(0, configRunning);
  if(strcmp(configRunning.magic, CFG_MAGIC) != 0) {
    // bad magic, probably no existing config, so create one
    debugMessage("EEPROM has invalid config magic, creating new config.");
    configCreate();
  }
  if(configRunning.cfgVersion != CFG_VERSION) {
    // version of the stored config doesn't match ours, create a new config
    // TODO: we'd have some kind of configuration migration ideally, rather than just wiping the existing config
    debugMessage("Config version mismatch, creating new config.");
    configCreate();
  }
  if(configRunning.maxBoards != MAX_BOARDS) {
    // number of boards we store config info for changed, create a new config
    // this should happen rarely enough there's no need for a migration function here
    debugMessage("MAX_BOARDS config mismatch, creating new config.");
    configCreate();
  }
  // TODO: handle the number of boards changing
}

void configInitMainMenu(SUI::Menu *mainMenu) {
  // config menu
  SUI::Menu *configMenu = mainMenu->subMenu(SUI_STR("config"), SUI_STR("Configuration menu"));
  configMenu->addCommand(SUI_STR("write"), configSave,   SUI_STR("Save running configuraton to EEPROM"));
  configMenu->addCommand(SUI_STR("reset"), configCreate, SUI_STR("Reset running configuration to defaults"));
  configMenu->addCommand(SUI_STR("show"),  configShow,   SUI_STR("Show running configuration"));
}

void configCreate(void) {
  strcpy(configRunning.magic, CFG_MAGIC);
  configRunning.cfgVersion = CFG_VERSION;
  configRunning.maxBoards = MAX_BOARDS;
}

void configShow(void) {
  //char buf[32];
  //sprintf(buf, "Motion timeout: %d", configRunning.motionTimeout);
  //debugUI.println(buf);
}

void configSave(void) {
  EEPROM.put(0, configRunning);
  debugMessage("Configuration saved to EEPROM.");  
}

