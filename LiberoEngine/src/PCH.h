#pragma once

//*********************
// 3th party includes:
//*********************
// * SDL *
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// * GLFW *
#include <GLFW/glfw3.h>
#ifdef APIENTRY
#undef APIENTRY
#endif

// * Box2D *
#include <box2d/box2d.h>

// * VLD *
#include <vld.h>

// * DearIMGUI *
#include "ImGui/imgui.h"

#define NOMINMAX
// * Windows *
#include <windows.h>

// * XInput *
#include <xinput.h>

//***************
// STL includes:
//***************
#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>
#include <map>
#include <list>
#include <cmath>
#include <array>
#include <algorithm>
#include <functional>
#include <unordered_map>

//*************************
// Libero Global includes:
//*************************
#include "Logger.h"
