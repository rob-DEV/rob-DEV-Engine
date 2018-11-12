#pragma once

//--ENGINE GLOBAL CONFIGURATION--//


#ifndef _ENGINE_CONFIGURATION_H
#define _ENGINE_CONFIGURATION_H

#define _ENGINE_NAME  "rob-DEV-Engine"
#define _APPLICATION_NAME "rob-DEV-Engine"
#define _ENGINE_BUILD_NUMBER 1


#define _WIN_32_PLATFORM
//#define _MAC_PLATFORM 0
//#define _LINUX_PLATFORM 0


#ifndef _WIN_32_PLATFORM
#error Vulkan and OpenGL cannot be selected as the main graphics renderer at the same time. Check EngineConfig.h
#endif


//on off toggles 1 = True, 0 = False
#define _ENGINE_RENDERER_OPENGL 1
#define _ENGINE_RENDERER_VULKAN 0
#define _ENGINE_RENDERER_DIRECT3D 0

#if !_ENGINE_RENDERER_OPENGL && !_ENGINE_RENDERER_VULKAN && !_ENGINE_RENDERER_DIRECT3D
//using openGL as the default rendering engine
#define _ENGINE_RENDERER_OPENGL 1
#endif

#if _ENGINE_RENDERER_OPENGL && _ENGINE_RENDERER_VULKAN
#error Vulkan and OpenGL cannot be selected as the main graphics renderer at the same time. Check EngineConfig.h
#endif

//physical constants
#define _PHYSICS_G 55.89

#endif // !_ENGINE_CONFIGURATION_H



