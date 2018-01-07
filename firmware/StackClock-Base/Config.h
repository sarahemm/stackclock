// Config.h - Definitions related to configuration that other modules need to be able to access.

#define CFG_VERSION 0

#define CFG_MAGIC   "SCc"
#define MAX_BOARDS  16

struct boardEntry {
  byte boardType;
  byte boardFWRev;
  char location[3];
  signed short tzOffset;
  byte flags; // bit 0 = Seconds on/off
};

struct scConfig {
  char magic[3];
  byte cfgVersion;
  byte maxBoards;
  byte nbrBoards;
  
  struct boardEntry boards[MAX_BOARDS];
};

extern struct scConfig configRunning;

