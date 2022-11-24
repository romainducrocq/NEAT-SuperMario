#ifndef _NINTACO_HPP
#define _NINTACO_HPP
  
#include <stdbool.h> 

namespace nintaco
{

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

typedef int (*AccessPointListener)(nintaco::NintacoAPI* api, int accessPointType,
    int address, int value);
typedef void (*ActivateListener)(nintaco::NintacoAPI* api);
typedef void (*ControllersListener)(nintaco::NintacoAPI* api);
typedef void (*DeactivateListener)(nintaco::NintacoAPI* api);
typedef void (*FrameListener)(nintaco::NintacoAPI* api);
typedef void (*ScanlineCycleListener)(nintaco::NintacoAPI* api, int scanline,
    int scanlineCycle, int address, bool rendering);
typedef void (*ScanlineListener)(nintaco::NintacoAPI* api, int scanline);
typedef void (*SpriteZeroListener)(nintaco::NintacoAPI* api, int scanline,
    int scanlineCycle);
typedef void (*StatusListener)(nintaco::NintacoAPI* api, char* message);
typedef void (*StopListener)(nintaco::NintacoAPI* api);

nintaco::NintacoAPI* newNintacoAPI(char*host, int port);
void run(nintaco::NintacoAPI* api);
void getPixels(nintaco::NintacoAPI* api, int* pixels);
void addActivateListener(nintaco::NintacoAPI* api, nintaco::ActivateListener listener);
void removeActivateListener(nintaco::NintacoAPI* api, nintaco::ActivateListener listener);
void addDeactivateListener(nintaco::NintacoAPI* api, nintaco::DeactivateListener listener);
void removeDeactivateListener(nintaco::NintacoAPI* api, nintaco::DeactivateListener listener);
void addStopListener(nintaco::NintacoAPI* api, nintaco::StopListener listener);
void removeStopListener(nintaco::NintacoAPI* api, nintaco::StopListener listener);
void addAccessPointListener3(nintaco::NintacoAPI* api, nintaco::AccessPointListener listener,
    int32_t accessPointType, int32_t minAddress, int32_t maxAddress,
        int32_t bank);
void addAccessPointListener2(nintaco::NintacoAPI* api, nintaco::AccessPointListener listener,
    int32_t accessPointType, int32_t minAddress, int32_t maxAddress);
void addAccessPointListener(nintaco::NintacoAPI* api, nintaco::AccessPointListener listener,
    int32_t accessPointType, int32_t address);
void removeAccessPointListener(nintaco::NintacoAPI* api, nintaco::AccessPointListener listener);
void addControllersListener(nintaco::NintacoAPI* api, nintaco::ControllersListener listener);
void removeControllersListener(nintaco::NintacoAPI* api, nintaco::ControllersListener listener);
void addFrameListener(nintaco::NintacoAPI* api, nintaco::FrameListener listener);
void removeFrameListener(nintaco::NintacoAPI* api, nintaco::FrameListener listener);
void addScanlineListener(nintaco::NintacoAPI* api, nintaco::ScanlineListener listener,
    int32_t scanline);
void removeScanlineListener(nintaco::NintacoAPI* api, nintaco::ScanlineListener listener);
void addScanlineCycleListener(nintaco::NintacoAPI* api, nintaco::ScanlineCycleListener listener,
    int32_t scanline, int32_t scanlineCycle);
void removeScanlineCycleListener(nintaco::NintacoAPI* api,
                                 nintaco::ScanlineCycleListener listener);
void addSpriteZeroListener(nintaco::NintacoAPI* api, nintaco::SpriteZeroListener listener);
void removeSpriteZeroListener(nintaco::NintacoAPI* api, nintaco::SpriteZeroListener listener);
void addStatusListener(nintaco::NintacoAPI* api, nintaco::StatusListener listener);
void removeStatusListener(nintaco::NintacoAPI* api, nintaco::StatusListener listener);

/* AUTOGENERATED CONTENT FOLLOWS. DO NOT MODIFY. */
void setPaused(nintaco::NintacoAPI* api, bool paused);
bool isPaused(nintaco::NintacoAPI* api);
int getFrameCount(nintaco::NintacoAPI* api);
int getA(nintaco::NintacoAPI* api);
void setA(nintaco::NintacoAPI* api, int A);
int getS(nintaco::NintacoAPI* api);
void setS(nintaco::NintacoAPI* api, int S);
int getPC(nintaco::NintacoAPI* api);
void setPC(nintaco::NintacoAPI* api, int PC);
int getX(nintaco::NintacoAPI* api);
void setX(nintaco::NintacoAPI* api, int X);
int getY(nintaco::NintacoAPI* api);
void setY(nintaco::NintacoAPI* api, int Y);
int getP(nintaco::NintacoAPI* api);
void setP(nintaco::NintacoAPI* api, int P);
bool isN(nintaco::NintacoAPI* api);
void setN(nintaco::NintacoAPI* api, bool N);
bool isV(nintaco::NintacoAPI* api);
void setV(nintaco::NintacoAPI* api, bool V);
bool isD(nintaco::NintacoAPI* api);
void setD(nintaco::NintacoAPI* api, bool D);
bool isI(nintaco::NintacoAPI* api);
void setI(nintaco::NintacoAPI* api, bool I);
bool isZ(nintaco::NintacoAPI* api);
void setZ(nintaco::NintacoAPI* api, bool Z);
bool isC(nintaco::NintacoAPI* api);
void setC(nintaco::NintacoAPI* api, bool C);
int getPPUv(nintaco::NintacoAPI* api);
void setPPUv(nintaco::NintacoAPI* api, int v);
int getPPUt(nintaco::NintacoAPI* api);
void setPPUt(nintaco::NintacoAPI* api, int t);
int getPPUx(nintaco::NintacoAPI* api);
void setPPUx(nintaco::NintacoAPI* api, int x);
bool isPPUw(nintaco::NintacoAPI* api);
void setPPUw(nintaco::NintacoAPI* api, bool w);
int getCameraX(nintaco::NintacoAPI* api);
void setCameraX(nintaco::NintacoAPI* api, int scrollX);
int getCameraY(nintaco::NintacoAPI* api);
void setCameraY(nintaco::NintacoAPI* api, int scrollY);
int getScanline(nintaco::NintacoAPI* api);
int getDot(nintaco::NintacoAPI* api);
bool isSpriteZeroHit(nintaco::NintacoAPI* api);
void setSpriteZeroHit(nintaco::NintacoAPI* api, bool sprite0Hit);
int getScanlineCount(nintaco::NintacoAPI* api);
void requestInterrupt(nintaco::NintacoAPI* api);
void acknowledgeInterrupt(nintaco::NintacoAPI* api);
int peekCPU(nintaco::NintacoAPI* api, int address);
int readCPU(nintaco::NintacoAPI* api, int address);
void writeCPU(nintaco::NintacoAPI* api, int address, int value);
int peekCPU16(nintaco::NintacoAPI* api, int address);
int readCPU16(nintaco::NintacoAPI* api, int address);
void writeCPU16(nintaco::NintacoAPI* api, int address, int value);
int peekCPU32(nintaco::NintacoAPI* api, int address);
int readCPU32(nintaco::NintacoAPI* api, int address);
void writeCPU32(nintaco::NintacoAPI* api, int address, int value);
int readPPU(nintaco::NintacoAPI* api, int address);
void writePPU(nintaco::NintacoAPI* api, int address, int value);
int readPaletteRAM(nintaco::NintacoAPI* api, int address);
void writePaletteRAM(nintaco::NintacoAPI* api, int address, int value);
int readOAM(nintaco::NintacoAPI* api, int address);
void writeOAM(nintaco::NintacoAPI* api, int address, int value);
bool readGamepad(nintaco::NintacoAPI* api, int gamepad, int button);
void writeGamepad(nintaco::NintacoAPI* api, int gamepad, int button, bool value);
bool isZapperTrigger(nintaco::NintacoAPI* api);
void setZapperTrigger(nintaco::NintacoAPI* api, bool zapperTrigger);
int getZapperX(nintaco::NintacoAPI* api);
void setZapperX(nintaco::NintacoAPI* api, int x);
int getZapperY(nintaco::NintacoAPI* api);
void setZapperY(nintaco::NintacoAPI* api, int y);
void setColor(nintaco::NintacoAPI* api, int color);
int getColor(nintaco::NintacoAPI* api);
void setClip(nintaco::NintacoAPI* api, int x, int y, int width, int height);
void clipRect(nintaco::NintacoAPI* api, int x, int y, int width, int height);
void resetClip(nintaco::NintacoAPI* api);
void copyArea(nintaco::NintacoAPI* api, int x, int y, int width, int height, int dx,
              int dy);
void drawLine(nintaco::NintacoAPI* api, int x1, int y1, int x2, int y2);
void drawOval(nintaco::NintacoAPI* api, int x, int y, int width, int height);
void drawPolygon(nintaco::NintacoAPI* api, int* xPoints, int* yPoints, int nPoints);
void drawPolyline(nintaco::NintacoAPI* api, int* xPoints, int* yPoints, int nPoints);
void drawRect(nintaco::NintacoAPI* api, int x, int y, int width, int height);
void drawRoundRect(nintaco::NintacoAPI* api, int x, int y, int width, int height,
                   int arcWidth, int arcHeight);
void draw3DRect(nintaco::NintacoAPI* api, int x, int y, int width, int height,
                bool raised);
void drawArc(nintaco::NintacoAPI* api, int x, int y, int width, int height,
             int startAngle, int arcAngle);
void fill3DRect(nintaco::NintacoAPI* api, int x, int y, int width, int height,
                bool raised);
void fillArc(nintaco::NintacoAPI* api, int x, int y, int width, int height,
             int startAngle, int arcAngle);
void fillOval(nintaco::NintacoAPI* api, int x, int y, int width, int height);
void fillPolygon(nintaco::NintacoAPI* api, int* xPoints, int* yPoints, int nPoints);
void fillRect(nintaco::NintacoAPI* api, int x, int y, int width, int height);
void fillRoundRect(nintaco::NintacoAPI* api, int x, int y, int width, int height,
                   int arcWidth, int arcHeight);
void drawChar(nintaco::NintacoAPI* api, char c, int x, int y);
void drawChars(nintaco::NintacoAPI* api, char* data, int offset, int length, int x,
               int y, bool monospaced);
void drawString(nintaco::NintacoAPI* api, char* str, int x, int y, bool monospaced);
void createSprite(nintaco::NintacoAPI* api, int id, int width, int height, int* pixels);
void drawSprite(nintaco::NintacoAPI* api, int id, int x, int y);
void setPixel(nintaco::NintacoAPI* api, int x, int y, int color);
int getPixel(nintaco::NintacoAPI* api, int x, int y);
void powerCycle(nintaco::NintacoAPI* api);
void reset(nintaco::NintacoAPI* api);
void deleteSprite(nintaco::NintacoAPI* api, int id);
void setSpeed(nintaco::NintacoAPI* api, int percent);
void stepToNextFrame(nintaco::NintacoAPI* api);
void showMessage(nintaco::NintacoAPI* api, char* message);
char* getWorkingDirectory(nintaco::NintacoAPI* api);
char* getContentDirectory(nintaco::NintacoAPI* api);
void openFile(nintaco::NintacoAPI* api, char* fileName);
void openArchiveEntry(nintaco::NintacoAPI* api, char* archiveFileName,
                      char* entryFileName);
char** getArchiveEntries(nintaco::NintacoAPI* api, char* archiveFileName);
char* getDefaultArchiveEntry(nintaco::NintacoAPI* api, char* archiveFileName);
void openDefaultArchiveEntry(nintaco::NintacoAPI* api, char* archiveFileName);
void closeFile(nintaco::NintacoAPI* api);
void saveState(nintaco::NintacoAPI* api, char* stateFileName);
void loadState(nintaco::NintacoAPI* api, char* stateFileName);
void quickSaveState(nintaco::NintacoAPI* api, int slot);
void quickLoadState(nintaco::NintacoAPI* api, int slot);
void setTVSystem(nintaco::NintacoAPI* api, char* tvSystem);
char* getTVSystem(nintaco::NintacoAPI* api);
int getDiskSides(nintaco::NintacoAPI* api);
void insertDisk(nintaco::NintacoAPI* api, int disk, int side);
void flipDiskSide(nintaco::NintacoAPI* api);
void ejectDisk(nintaco::NintacoAPI* api);
void insertCoin(nintaco::NintacoAPI* api);
void pressServiceButton(nintaco::NintacoAPI* api);
void screamIntoMicrophone(nintaco::NintacoAPI* api);
void glitch(nintaco::NintacoAPI* api);
char* getFileInfo(nintaco::NintacoAPI* api);
void setFullscreenMode(nintaco::NintacoAPI* api, bool fullscreenMode);
void saveScreenshot(nintaco::NintacoAPI* api);
void addCheat(nintaco::NintacoAPI* api, int address, int value, int compare,
              char* description, bool enabled);
void removeCheat(nintaco::NintacoAPI* api, int address, int value, int compare);
void addGameGenie(nintaco::NintacoAPI* api, char* gameGenieCode, char* description,
                  bool enabled);
void removeGameGenie(nintaco::NintacoAPI* api, char* gameGenieCode);
void addProActionRocky(nintaco::NintacoAPI* api, char* proActionRockyCode,
                       char* description, bool enabled);
void removeProActionRocky(nintaco::NintacoAPI* api, char* proActionRockyCode);
int getPrgRomSize(nintaco::NintacoAPI* api);
int readPrgRom(nintaco::NintacoAPI* api, int index);
void writePrgRom(nintaco::NintacoAPI* api, int index, int value);
int getChrRomSize(nintaco::NintacoAPI* api);
int readChrRom(nintaco::NintacoAPI* api, int index);
void writeChrRom(nintaco::NintacoAPI* api, int index, int value);
int getStringWidth(nintaco::NintacoAPI* api, char* str, bool monospaced);
int getCharsWidth(nintaco::NintacoAPI* api, char* chars, bool monospaced);

}

#endif /* _NINTACO_HPP */

