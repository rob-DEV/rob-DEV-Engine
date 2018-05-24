#pragma once

//--ENGINE GLOBAL CONFIGURATION--//


#ifndef _ENGINE_CONFIGURATION_H
#define _ENGINE_CONFIGURATION_H

#define _WIN32_PLATFORM
//#define _MAC_PLATFORM 0
//#define _LINUX_PLATFORM 0

//on off toggles 1 = True, 0 = False
#define ENGINE_RENDERER_OPENGL 0
#define ENGINE_RENDERER_VULKAN 1

#if ENGINE_RENDERER_OPENGL && ENGINE_RENDERER_VULKAN
#error Vulkan and OpenGL cannot be selected as the main graphics renderer at the same time. Check EngineConfig.h
#endif`

#endif // !_ENGINE_CONFIGURATION_H



