#pragma once

//------------------------ Common is a header that would gonna be using for inside of the project and outside of the project -------------------------------//
//------------------------ Eyeryone that using my library also need to know about Core, So under Core include Common.h.      -------------------------------//
//------------------------ If I need something within it then outside people need it but outside people only use Core.h      -------------------------------//
//------------------------ So you include Common.h here so outside people see Common                                         -------------------------------//
//------------------------ Internally to references Common the way to use is Precompiled header file                         -------------------------------//
//------------------------ Some times people add project but not they are sure they are using empty project                  -------------------------------//
//------------------------ They will use stdafx.h file is definition is precompiled header file                              -------------------------------//
//------------------------ Will go in Common and copy the whole file to replace the #include "Common.h" line                 -------------------------------//
//------------------------ Recursively do the same thing for all the #include line.Eventually get to cpp file                -------------------------------//
//------------------------ Cpp you don't need to include so the copy and paste is kind of stop                               -------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------ Common represent the trunk that is external then include into Core                                -------------------------------//
//------------------------ Because our User need to see it                                                                   -------------------------------//
//------------------------ But our library also need to see it,so we include into Precompiled.h                                -------------------------------//

#include "Common.h"

#include "DebugUtil.h"
#include "TimeUtil.h"