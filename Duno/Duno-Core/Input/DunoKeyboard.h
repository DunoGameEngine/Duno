#pragma once
#include <vector>
#include <iostream>
using namespace std;

/* All the key codes */
#define DUNO_KEY_UNKNOWN            -1
#define DUNO_KEY_SPACE              32
#define DUNO_KEY_APOSTROPHE         39
#define DUNO_KEY_COMMA              44
#define DUNO_KEY_MINUS              45
#define DUNO_KEY_PERIOD             46
#define DUNO_KEY_SLASH              47
#define DUNO_KEY_0                  48
#define DUNO_KEY_1                  49
#define DUNO_KEY_2                  50
#define DUNO_KEY_3                  51
#define DUNO_KEY_4                  52
#define DUNO_KEY_5                  53
#define DUNO_KEY_6                  54
#define DUNO_KEY_7                  55
#define DUNO_KEY_8                  56
#define DUNO_KEY_9                  57
#define DUNO_KEY_SEMICOLON          59
#define DUNO_KEY_EQUAL              61
#define DUNO_KEY_A                  65
#define DUNO_KEY_B                  66
#define DUNO_KEY_C                  67
#define DUNO_KEY_D                  68
#define DUNO_KEY_E                  69
#define DUNO_KEY_F                  70
#define DUNO_KEY_G                  71
#define DUNO_KEY_H                  72
#define DUNO_KEY_I                  73
#define DUNO_KEY_J                  74
#define DUNO_KEY_K                  75
#define DUNO_KEY_L                  76
#define DUNO_KEY_M                  77
#define DUNO_KEY_N                  78
#define DUNO_KEY_O                  79
#define DUNO_KEY_P                  80
#define DUNO_KEY_Q                  81
#define DUNO_KEY_R                  82
#define DUNO_KEY_S                  83
#define DUNO_KEY_T                  84
#define DUNO_KEY_U                  85
#define DUNO_KEY_V                  86
#define DUNO_KEY_W                  87
#define DUNO_KEY_X                  88
#define DUNO_KEY_Y                  89
#define DUNO_KEY_Z                  90
#define DUNO_KEY_LEFT_BRACKET       91
#define DUNO_KEY_BACKSLASH          92
#define DUNO_KEY_RIGHT_BRACKET      93
#define DUNO_KEY_GRAVE_ACCENT       96
#define DUNO_KEY_WORLD_1            161
#define DUNO_KEY_WORLD_2            162
#define DUNO_KEY_ESCAPE             256
#define DUNO_KEY_ENTER              257
#define DUNO_KEY_TAB                258
#define DUNO_KEY_BACKSPACE          259
#define DUNO_KEY_INSERT             260
#define DUNO_KEY_DELETE             261
#define DUNO_KEY_RIGHT              262
#define DUNO_KEY_LEFT               263
#define DUNO_KEY_DOWN               264
#define DUNO_KEY_UP                 265
#define DUNO_KEY_PAGE_UP            266
#define DUNO_KEY_PAGE_DOWN          267
#define DUNO_KEY_HOME               268
#define DUNO_KEY_END                269
#define DUNO_KEY_CAPS_LOCK          280
#define DUNO_KEY_SCROLL_LOCK        281
#define DUNO_KEY_NUM_LOCK           282
#define DUNO_KEY_PRINT_SCREEN       283
#define DUNO_KEY_PAUSE              284
#define DUNO_KEY_F1                 290
#define DUNO_KEY_F2                 291
#define DUNO_KEY_F3                 292
#define DUNO_KEY_F4                 293
#define DUNO_KEY_F5                 294
#define DUNO_KEY_F6                 295
#define DUNO_KEY_F7                 296
#define DUNO_KEY_F8                 297
#define DUNO_KEY_F9                 298
#define DUNO_KEY_F10                299
#define DUNO_KEY_F11                300
#define DUNO_KEY_F12                301
#define DUNO_KEY_F13                302
#define DUNO_KEY_F14                303
#define DUNO_KEY_F15                304
#define DUNO_KEY_F16                305
#define DUNO_KEY_F17                306
#define DUNO_KEY_F18                307
#define DUNO_KEY_F19                308
#define DUNO_KEY_F20                309
#define DUNO_KEY_F21                310
#define DUNO_KEY_F22                311
#define DUNO_KEY_F23                312
#define DUNO_KEY_F24                313
#define DUNO_KEY_F25                314
#define DUNO_KEY_KP_0               320
#define DUNO_KEY_KP_1               321
#define DUNO_KEY_KP_2               322
#define DUNO_KEY_KP_3               323
#define DUNO_KEY_KP_4               324
#define DUNO_KEY_KP_5               325
#define DUNO_KEY_KP_6               326
#define DUNO_KEY_KP_7               327
#define DUNO_KEY_KP_8               328
#define DUNO_KEY_KP_9               329
#define DUNO_KEY_KP_DECIMAL         330
#define DUNO_KEY_KP_DIVIDE          331
#define DUNO_KEY_KP_MULTIPLY        332
#define DUNO_KEY_KP_SUBTRACT        333
#define DUNO_KEY_KP_ADD             334
#define DUNO_KEY_KP_ENTER           335
#define DUNO_KEY_KP_EQUAL           336
#define DUNO_KEY_LEFT_SHIFT         340
#define DUNO_KEY_LEFT_CONTROL       341
#define DUNO_KEY_LEFT_ALT           342
#define DUNO_KEY_LEFT_SUPER         343
#define DUNO_KEY_RIGHT_SHIFT        344
#define DUNO_KEY_RIGHT_CONTROL      345
#define DUNO_KEY_RIGHT_ALT          346
#define DUNO_KEY_RIGHT_SUPER        347
#define DUNO_KEY_MENU               348
#define DUNO_KEY_LAST               DUNO_KEY_MENU

/* Handles key events */
class DunoKeyboard
{
public:
	/* add a key that has been pressed */
	static void addKey(int key) { keysPressed.push_back(key); };
	/* remove a key when it has been released */
	static void removeKey(int key) { keysPressed.erase(std::find(keysPressed.begin(), keysPressed.end(), key)); };

	/* Returns if a key has been pressed */
	static bool isKeyDown(int key) { return std::find(keysPressed.begin(), keysPressed.end(), key) != keysPressed.end(); };
private:
	/* Stores the keys that have been pressed */
	static vector<int> keysPressed;
};