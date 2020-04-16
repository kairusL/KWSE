//------------------------ You can include your code in Precompiled.h                                                        -------------------------------//
//------------------------ Cpp you don't need to include so the copy and paste is kind of stop                               -------------------------------//
//------------------------ If your stuff in the header every changes you will have to do the whole copy and paste again      -------------------------------//
//------------------------ So better include the stuff you wont change in Precompiled                                        -------------------------------//
//------------------------ Ex:Good guidline is that everything is outside of our library, should put in Precompiled.h        -------------------------------//
//------------------------ In case everything in Common.h are all standard headers                                           -------------------------------//
//------------------------ None part of our library, are just somethings will use                                            -------------------------------//
//------------------------ So we precompiled them and Cache them somewhere                                                   -------------------------------//
//------------------------ This is why Precompiled.h and .cpp are for                                                        -------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------Later on you will have a file and that file include Precompiled.h                                 -------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------If you use this technique                                                                         -------------------------------//
//-------------------------Every cpp file in your library need to include Precompiled.h first thing                          -------------------------------//
//----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-------------------------Normailly would do is go to Project->Properties                                                   -------------------------------//
//-------------------------Under C++ Section -> Precompiled headers                                                          -------------------------------//
//-------------------------This is how to specifies how to use these files to be precompiled linked stuff                    -------------------------------//
//-------------------------Default Precompiled header: stdafx.h                                                              -------------------------------//

#pragma once

#include "Common.h"