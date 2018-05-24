#pragma once
//GARUANTEE INCLUDE ORDER
#include "../../include/EngineConfig.h"


#if (ENGINE_RENDERER_VULKAN)

#ifdef _WIN32_PLATFORM 
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <vulkan.h>

#ifndef _GLFW_H
#define _GLFW_H
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#endif // !_GLFW_H

#endif



