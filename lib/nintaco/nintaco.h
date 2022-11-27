#ifndef NINTACO_H
#define NINTACO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h> 
  
typedef enum {
  GRAY = 0x00,
  DARK_BLUE = 0x01,
  DARK_INDIGO = 0x02,
  DARK_VIOLET = 0x03,
  DARK_MAGENTA = 0x04,
  DARK_RED = 0x05,
  DARK_ORANGE = 0x06,
  DARK_BROWN = 0x07,
  DARK_OLIVE = 0x08,
  DARK_CHARTREUSE = 0x09,
  DARK_GREEN = 0x0A,
  DARK_MINT = 0x0B,
  DARK_CYAN = 0x0C,
  BLACKER_THAN_BLACK = 0x0D,
  BLACK3 = 0x0E,
  BLACK = 0x0F,

  LIGHT_GRAY = 0x10,
  BLUE = 0x11,
  INDIGO = 0x12,
  VIOLET = 0x13,
  MAGENTA = 0x14,
  RED = 0x15,
  ORANGE = 0x16,
  BROWN = 0x17,
  OLIVE = 0x18,
  CHARTREUSE = 0x19,
  GREEN = 0x1A,
  MINT = 0x1B,
  CYAN = 0x1C,
  BLACK2 = 0x1D,
  BLACK4 = 0x1E,
  BLACK5 = 0x1F,

  WHITE = 0x20,
  LIGHT_BLUE = 0x21,
  LIGHT_INDIGO = 0x22,
  LIGHT_VIOLET = 0x23,
  LIGHT_MAGENTA = 0x24,
  LIGHT_RED = 0x25,
  LIGHT_ORANGE = 0x26,
  LIGHT_BROWN = 0x27,
  LIGHT_OLIVE = 0x28,
  LIGHT_CHARTREUSE = 0x29,
  LIGHT_GREEN = 0x2A,
  LIGHT_MINT = 0x2B,
  LIGHT_CYAN = 0x2C,
  DARK_GRAY = 0x2D,
  BLACK6 = 0x2E,
  BLACK7 = 0x2F,  

  WHITE2 = 0x30,
  PALE_BLUE = 0x31,
  PALE_INDIGO = 0x32,
  PALE_VIOLET = 0x33,
  PALE_MAGENTA = 0x34,
  PALE_RED = 0x35,
  PALE_ORANGE = 0x36,
  CREAM = 0x37,
  YELLOW = 0x38,
  PALE_CHARTREUSE = 0x39,
  PALE_GREEN = 0x3A,
  PALE_MINT = 0x3B,
  PALE_CYAN = 0x3C,  
  PALE_GRAY = 0x3D,
  BLACK8 = 0x3E,
  BLACK9 = 0x3F,
} Colors;  
 
typedef enum {  
  PreRead = 0,
  PostRead = 1,
  PreWrite = 2,
  PostWrite = 3,
  PreExecute = 4,
  PostExecute = 5,
} AccessPointType;

typedef enum { 
  A = 0,
  B = 1,
  Select = 2,
  Start = 3,
  Up = 4,
  Down = 5,
  Left = 6,
  Right = 7, 
} GamepadButtons;

typedef struct _ObjectIntEntry {
  void* key;
  int32_t value;
  struct _ObjectIntEntry* next;
} ObjectIntEntry;

typedef struct _IntObjectEntry {
  int32_t key;
  void* value;
  struct _IntObjectEntry* next;
} IntObjectEntry;

typedef struct {
  unsigned char *buffer;
  uint32_t capacity;
  uint32_t size;
  uint32_t tail;
  int fileDescriptor;
  bool alive;
} DataInputStream;

typedef struct {
  unsigned char *buffer;
  uint32_t size;
  uint32_t head;
  int fileDescriptor;
  bool alive;
} DataOutputStream;

typedef struct {
  char* host;
  int port;
  ObjectIntEntry* listenerIDs;
  IntObjectEntry** listenerObjects;
  int nextID;
  bool running;
  DataInputStream* in;
  DataOutputStream* out;
} NintacoAPI;

typedef int (*AccessPointListener)(NintacoAPI* api, int accessPointType, 
    int address, int value);
typedef void (*ActivateListener)(NintacoAPI* api);
typedef void (*ControllersListener)(NintacoAPI* api);
typedef void (*DeactivateListener)(NintacoAPI* api);
typedef void (*FrameListener)(NintacoAPI* api);
typedef void (*ScanlineCycleListener)(NintacoAPI* api, int scanline, 
    int scanlineCycle, int address, bool rendering);
typedef void (*ScanlineListener)(NintacoAPI* api, int scanline);
typedef void (*SpriteZeroListener)(NintacoAPI* api, int scanline, 
    int scanlineCycle);
typedef void (*StatusListener)(NintacoAPI* api, char* message);
typedef void (*StopListener)(NintacoAPI* api);

NintacoAPI* newNintacoAPI(char*host, int port);
void run(NintacoAPI* api);
void getPixels(NintacoAPI* api, int* pixels);
void addActivateListener(NintacoAPI* api, ActivateListener listener);
void removeActivateListener(NintacoAPI* api, ActivateListener listener);
void addDeactivateListener(NintacoAPI* api, DeactivateListener listener);
void removeDeactivateListener(NintacoAPI* api, DeactivateListener listener);
void addStopListener(NintacoAPI* api, StopListener listener);
void removeStopListener(NintacoAPI* api, StopListener listener);
void addAccessPointListener3(NintacoAPI* api, AccessPointListener listener, 
    int32_t accessPointType, int32_t minAddress, int32_t maxAddress, 
        int32_t bank);
void addAccessPointListener2(NintacoAPI* api, AccessPointListener listener, 
    int32_t accessPointType, int32_t minAddress, int32_t maxAddress);
void addAccessPointListener(NintacoAPI* api, AccessPointListener listener, 
    int32_t accessPointType, int32_t address);
void removeAccessPointListener(NintacoAPI* api, AccessPointListener listener);
void addControllersListener(NintacoAPI* api, ControllersListener listener);
void removeControllersListener(NintacoAPI* api, ControllersListener listener);
void addFrameListener(NintacoAPI* api, FrameListener listener);
void removeFrameListener(NintacoAPI* api, FrameListener listener);
void addScanlineListener(NintacoAPI* api, ScanlineListener listener, 
    int32_t scanline);
void removeScanlineListener(NintacoAPI* api, ScanlineListener listener);
void addScanlineCycleListener(NintacoAPI* api, ScanlineCycleListener listener,
    int32_t scanline, int32_t scanlineCycle);
void removeScanlineCycleListener(NintacoAPI* api, 
    ScanlineCycleListener listener);
void addSpriteZeroListener(NintacoAPI* api, SpriteZeroListener listener);
void removeSpriteZeroListener(NintacoAPI* api, SpriteZeroListener listener);
void addStatusListener(NintacoAPI* api, StatusListener listener);
void removeStatusListener(NintacoAPI* api, StatusListener listener);

/* AUTOGENERATED CONTENT FOLLOWS. DO NOT MODIFY. */
void setPaused(NintacoAPI* api, bool paused);
bool isPaused(NintacoAPI* api);
int getFrameCount(NintacoAPI* api);
int getA(NintacoAPI* api);
void setA(NintacoAPI* api, int A);
int getS(NintacoAPI* api);
void setS(NintacoAPI* api, int S);
int getPC(NintacoAPI* api);
void setPC(NintacoAPI* api, int PC);
int getX(NintacoAPI* api);
void setX(NintacoAPI* api, int X);
int getY(NintacoAPI* api);
void setY(NintacoAPI* api, int Y);
int getP(NintacoAPI* api);
void setP(NintacoAPI* api, int P);
bool isN(NintacoAPI* api);
void setN(NintacoAPI* api, bool N);
bool isV(NintacoAPI* api);
void setV(NintacoAPI* api, bool V);
bool isD(NintacoAPI* api);
void setD(NintacoAPI* api, bool D);
bool isI(NintacoAPI* api);
void setI(NintacoAPI* api, bool I);
bool isZ(NintacoAPI* api);
void setZ(NintacoAPI* api, bool Z);
bool isC(NintacoAPI* api);
void setC(NintacoAPI* api, bool C);
int getPPUv(NintacoAPI* api);
void setPPUv(NintacoAPI* api, int v);
int getPPUt(NintacoAPI* api);
void setPPUt(NintacoAPI* api, int t);
int getPPUx(NintacoAPI* api);
void setPPUx(NintacoAPI* api, int x);
bool isPPUw(NintacoAPI* api);
void setPPUw(NintacoAPI* api, bool w);
int getCameraX(NintacoAPI* api);
void setCameraX(NintacoAPI* api, int scrollX);
int getCameraY(NintacoAPI* api);
void setCameraY(NintacoAPI* api, int scrollY);
int getScanline(NintacoAPI* api);
int getDot(NintacoAPI* api);
bool isSpriteZeroHit(NintacoAPI* api);
void setSpriteZeroHit(NintacoAPI* api, bool sprite0Hit);
int getScanlineCount(NintacoAPI* api);
void requestInterrupt(NintacoAPI* api);
void acknowledgeInterrupt(NintacoAPI* api);
int peekCPU(NintacoAPI* api, int address);
int readCPU(NintacoAPI* api, int address);
void writeCPU(NintacoAPI* api, int address, int value);
int peekCPU16(NintacoAPI* api, int address);
int readCPU16(NintacoAPI* api, int address);
void writeCPU16(NintacoAPI* api, int address, int value);
int peekCPU32(NintacoAPI* api, int address);
int readCPU32(NintacoAPI* api, int address);
void writeCPU32(NintacoAPI* api, int address, int value);
int readPPU(NintacoAPI* api, int address);
void writePPU(NintacoAPI* api, int address, int value);
int readPaletteRAM(NintacoAPI* api, int address);
void writePaletteRAM(NintacoAPI* api, int address, int value);
int readOAM(NintacoAPI* api, int address);
void writeOAM(NintacoAPI* api, int address, int value);
bool readGamepad(NintacoAPI* api, int gamepad, int button);
void writeGamepad(NintacoAPI* api, int gamepad, int button, bool value);
bool isZapperTrigger(NintacoAPI* api);
void setZapperTrigger(NintacoAPI* api, bool zapperTrigger);
int getZapperX(NintacoAPI* api);
void setZapperX(NintacoAPI* api, int x);
int getZapperY(NintacoAPI* api);
void setZapperY(NintacoAPI* api, int y);
void setColor(NintacoAPI* api, int color);
int getColor(NintacoAPI* api);
void setClip(NintacoAPI* api, int x, int y, int width, int height);
void clipRect(NintacoAPI* api, int x, int y, int width, int height);
void resetClip(NintacoAPI* api);
void copyArea(NintacoAPI* api, int x, int y, int width, int height, int dx, 
      int dy);
void drawLine(NintacoAPI* api, int x1, int y1, int x2, int y2);
void drawOval(NintacoAPI* api, int x, int y, int width, int height);
void drawPolygon(NintacoAPI* api, int* xPoints, int* yPoints, int nPoints);
void drawPolyline(NintacoAPI* api, int* xPoints, int* yPoints, int nPoints);
void drawRect(NintacoAPI* api, int x, int y, int width, int height);
void drawRoundRect(NintacoAPI* api, int x, int y, int width, int height, 
      int arcWidth, int arcHeight);
void draw3DRect(NintacoAPI* api, int x, int y, int width, int height, 
      bool raised);
void drawArc(NintacoAPI* api, int x, int y, int width, int height, 
      int startAngle, int arcAngle);
void fill3DRect(NintacoAPI* api, int x, int y, int width, int height, 
      bool raised);
void fillArc(NintacoAPI* api, int x, int y, int width, int height, 
      int startAngle, int arcAngle);
void fillOval(NintacoAPI* api, int x, int y, int width, int height);
void fillPolygon(NintacoAPI* api, int* xPoints, int* yPoints, int nPoints);
void fillRect(NintacoAPI* api, int x, int y, int width, int height);
void fillRoundRect(NintacoAPI* api, int x, int y, int width, int height, 
      int arcWidth, int arcHeight);
void drawChar(NintacoAPI* api, char c, int x, int y);
void drawChars(NintacoAPI* api, char* data, int offset, int length, int x, 
      int y, bool monospaced);
void drawString(NintacoAPI* api, char* str, int x, int y, bool monospaced);
void createSprite(NintacoAPI* api, int id, int width, int height, int* pixels);
void drawSprite(NintacoAPI* api, int id, int x, int y);
void setPixel(NintacoAPI* api, int x, int y, int color);
int getPixel(NintacoAPI* api, int x, int y);
void powerCycle(NintacoAPI* api);
void reset(NintacoAPI* api);
void deleteSprite(NintacoAPI* api, int id);
void setSpeed(NintacoAPI* api, int percent);
void stepToNextFrame(NintacoAPI* api);
void showMessage(NintacoAPI* api, char* message);
char* getWorkingDirectory(NintacoAPI* api);
char* getContentDirectory(NintacoAPI* api);
void openFile(NintacoAPI* api, char* fileName);
void openArchiveEntry(NintacoAPI* api, char* archiveFileName, 
      char* entryFileName);
char** getArchiveEntries(NintacoAPI* api, char* archiveFileName);
char* getDefaultArchiveEntry(NintacoAPI* api, char* archiveFileName);
void openDefaultArchiveEntry(NintacoAPI* api, char* archiveFileName);
void closeFile(NintacoAPI* api);
void saveState(NintacoAPI* api, char* stateFileName);
void loadState(NintacoAPI* api, char* stateFileName);
void quickSaveState(NintacoAPI* api, int slot);
void quickLoadState(NintacoAPI* api, int slot);
void setTVSystem(NintacoAPI* api, char* tvSystem);
char* getTVSystem(NintacoAPI* api);
int getDiskSides(NintacoAPI* api);
void insertDisk(NintacoAPI* api, int disk, int side);
void flipDiskSide(NintacoAPI* api);
void ejectDisk(NintacoAPI* api);
void insertCoin(NintacoAPI* api);
void pressServiceButton(NintacoAPI* api);
void screamIntoMicrophone(NintacoAPI* api);
void glitch(NintacoAPI* api);
char* getFileInfo(NintacoAPI* api);
void setFullscreenMode(NintacoAPI* api, bool fullscreenMode);
void saveScreenshot(NintacoAPI* api);
void addCheat(NintacoAPI* api, int address, int value, int compare, 
      char* description, bool enabled);
void removeCheat(NintacoAPI* api, int address, int value, int compare);
void addGameGenie(NintacoAPI* api, char* gameGenieCode, char* description, 
      bool enabled);
void removeGameGenie(NintacoAPI* api, char* gameGenieCode);
void addProActionRocky(NintacoAPI* api, char* proActionRockyCode, 
      char* description, bool enabled);
void removeProActionRocky(NintacoAPI* api, char* proActionRockyCode);
int getPrgRomSize(NintacoAPI* api);
int readPrgRom(NintacoAPI* api, int index);
void writePrgRom(NintacoAPI* api, int index, int value);
int getChrRomSize(NintacoAPI* api);
int readChrRom(NintacoAPI* api, int index);
void writeChrRom(NintacoAPI* api, int index, int value);
int getStringWidth(NintacoAPI* api, char* str, bool monospaced);
int getCharsWidth(NintacoAPI* api, char* chars, bool monospaced);

#ifdef __cplusplus
}
#endif

#endif /* NINTACO_H */

