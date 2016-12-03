#pragma once
#ifndef SLOTH_INPUT_H_
#define SLOTH_INPUT_H_
#include "Window.h"
#include <array>

/*! @brief The key or mouse button was released.
*
*  The key or mouse button was released.
*/
#define SLOTH_RELEASE                0
/*! @brief The key or mouse button was pressed.
*
*  The key or mouse button was pressed.
*/
#define SLOTH_PRESS                  1
/*! @brief The key was held down until it repeated.
*
*  The key was held down until it repeated.
*/
#define SLOTH_REPEAT                 2

/* The unknown key */
#define SLOTH_KEY_UNKNOWN            -1

/* Printable keys */
#define SLOTH_KEY_SPACE              32
#define SLOTH_KEY_APOSTROPHE         39  /* ' */
#define SLOTH_KEY_COMMA              44  /* , */
#define SLOTH_KEY_MINUS              45  /* - */
#define SLOTH_KEY_PERIOD             46  /* . */
#define SLOTH_KEY_SLASH              47  /* / */
#define SLOTH_KEY_0                  48
#define SLOTH_KEY_1                  49
#define SLOTH_KEY_2                  50
#define SLOTH_KEY_3                  51
#define SLOTH_KEY_4                  52
#define SLOTH_KEY_5                  53
#define SLOTH_KEY_6                  54
#define SLOTH_KEY_7                  55
#define SLOTH_KEY_8                  56
#define SLOTH_KEY_9                  57
#define SLOTH_KEY_SEMICOLON          59  /* ; */
#define SLOTH_KEY_EQUAL              61  /* = */
#define SLOTH_KEY_A                  65
#define SLOTH_KEY_B                  66
#define SLOTH_KEY_C                  67
#define SLOTH_KEY_D                  68
#define SLOTH_KEY_E                  69
#define SLOTH_KEY_F                  70
#define SLOTH_KEY_G                  71
#define SLOTH_KEY_H                  72
#define SLOTH_KEY_I                  73
#define SLOTH_KEY_J                  74
#define SLOTH_KEY_K                  75
#define SLOTH_KEY_L                  76
#define SLOTH_KEY_M                  77
#define SLOTH_KEY_N                  78
#define SLOTH_KEY_O                  79
#define SLOTH_KEY_P                  80
#define SLOTH_KEY_Q                  81
#define SLOTH_KEY_R                  82
#define SLOTH_KEY_S                  83
#define SLOTH_KEY_T                  84
#define SLOTH_KEY_U                  85
#define SLOTH_KEY_V                  86
#define SLOTH_KEY_W                  87
#define SLOTH_KEY_X                  88
#define SLOTH_KEY_Y                  89
#define SLOTH_KEY_Z                  90
#define SLOTH_KEY_LEFT_BRACKET       91  /* [ */
#define SLOTH_KEY_BACKSLASH          92  /* \ */
#define SLOTH_KEY_RIGHT_BRACKET      93  /* ] */
#define SLOTH_KEY_GRAVE_ACCENT       96  /* ` */
#define SLOTH_KEY_WORLD_1            161 /* non-US #1 */
#define SLOTH_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define SLOTH_KEY_ESCAPE             256
#define SLOTH_KEY_ENTER              257
#define SLOTH_KEY_TAB                258
#define SLOTH_KEY_BACKSPACE          259
#define SLOTH_KEY_INSERT             260
#define SLOTH_KEY_DELETE             261
#define SLOTH_KEY_RIGHT              262
#define SLOTH_KEY_LEFT               263
#define SLOTH_KEY_DOWN               264
#define SLOTH_KEY_UP                 265
#define SLOTH_KEY_PAGE_UP            266
#define SLOTH_KEY_PAGE_DOWN          267
#define SLOTH_KEY_HOME               268
#define SLOTH_KEY_END                269
#define SLOTH_KEY_CAPS_LOCK          280
#define SLOTH_KEY_SCROLL_LOCK        281
#define SLOTH_KEY_NUM_LOCK           282
#define SLOTH_KEY_PRINT_SCREEN       283
#define SLOTH_KEY_PAUSE              284
#define SLOTH_KEY_F1                 290
#define SLOTH_KEY_F2                 291
#define SLOTH_KEY_F3                 292
#define SLOTH_KEY_F4                 293
#define SLOTH_KEY_F5                 294
#define SLOTH_KEY_F6                 295
#define SLOTH_KEY_F7                 296
#define SLOTH_KEY_F8                 297
#define SLOTH_KEY_F9                 298
#define SLOTH_KEY_F10                299
#define SLOTH_KEY_F11                300
#define SLOTH_KEY_F12                301
#define SLOTH_KEY_F13                302
#define SLOTH_KEY_F14                303
#define SLOTH_KEY_F15                304
#define SLOTH_KEY_F16                305
#define SLOTH_KEY_F17                306
#define SLOTH_KEY_F18                307
#define SLOTH_KEY_F19                308
#define SLOTH_KEY_F20                309
#define SLOTH_KEY_F21                310
#define SLOTH_KEY_F22                311
#define SLOTH_KEY_F23                312
#define SLOTH_KEY_F24                313
#define SLOTH_KEY_F25                314
#define SLOTH_KEY_KP_0               320
#define SLOTH_KEY_KP_1               321
#define SLOTH_KEY_KP_2               322
#define SLOTH_KEY_KP_3               323
#define SLOTH_KEY_KP_4               324
#define SLOTH_KEY_KP_5               325
#define SLOTH_KEY_KP_6               326
#define SLOTH_KEY_KP_7               327
#define SLOTH_KEY_KP_8               328
#define SLOTH_KEY_KP_9               329
#define SLOTH_KEY_KP_DECIMAL         330
#define SLOTH_KEY_KP_DIVIDE          331
#define SLOTH_KEY_KP_MULTIPLY        332
#define SLOTH_KEY_KP_SUBTRACT        333
#define SLOTH_KEY_KP_ADD             334
#define SLOTH_KEY_KP_ENTER           335
#define SLOTH_KEY_KP_EQUAL           336
#define SLOTH_KEY_LEFT_SHIFT         340
#define SLOTH_KEY_LEFT_CONTROL       341
#define SLOTH_KEY_LEFT_ALT           342
#define SLOTH_KEY_LEFT_SUPER         343
#define SLOTH_KEY_RIGHT_SHIFT        344
#define SLOTH_KEY_RIGHT_CONTROL      345
#define SLOTH_KEY_RIGHT_ALT          346
#define SLOTH_KEY_RIGHT_SUPER        347
#define SLOTH_KEY_MENU               348

#define SLOTH_KEY_LAST               SLOTH_KEY_MENU

#define SLOTH_MOUSE_X_OFFSET		 0
#define SLOTH_MOUSE_Y_OFFSET		 1

class Input {
public:
	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	static bool isKeyPressed(int code);
	static double mouseMove(int code);
private:
	static std::array<bool, 512> keys;
	static std::array<double, 2> mouse;

	static double lastX, lastY;
	static bool firstMouse;
};

#endif // !SLOTH_INPUT_H_
