#pragma once


#ifndef _ENGINE_CORE_INCLUDE_H
#define _ENGINE_CORE_INCLUDE_H

#include "EngineConfig.h"

//GLOBAL CORE ENGINE INCLUDE
//used mainly by the user in their own game scripts as an engine extension for core engine functionality
#include "../time/time.h"
#include "../input/input.h"
#include "../entity/game_object.h"
#include "../buildsystems/scene_manager.h"
#include "../io/filesystem/virtual_file_system.h"

using namespace Engine::Core;
using namespace Engine::Core::Entities;
using namespace Engine::Core::IO;

#endif
