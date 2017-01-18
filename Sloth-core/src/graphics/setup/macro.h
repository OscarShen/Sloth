#pragma once
#ifndef SLOTH_MACRO_H_
#define SLOTH_MACRO_H_

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define GLSL_MAX_LIGHTS 4
#define STATIC_VERTEX_FILE "src/shader/basic.vert"
#define STATIC_FRAGMENT_FILE "src/shader/basic.frag"
#define TERRAIN_VERTEX_FILE "src/shader/terrain.vert"
#define TERRAIN_FRAGMENT_FILE "src/shader/terrain.frag"

#define TERRAIN_SIZE 800.0f
#define TERRAIN_VERTEX_COUNT 128

#define PERSPECTIVE_FOV 45.0f
#define PERSPECTIVE_ASPECT (static_cast<float>(SCREEN_WIDTH)/SCREEN_HEIGHT)
#define PERSPECTIVE_NEAR_PLANE 0.1f
#define PERSPECTIVE_FAR_PLANE 1000.0f

#endif // !SLOTH_MACRO_H_
