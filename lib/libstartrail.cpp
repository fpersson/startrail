/*
 * libstartrail.cpp
 * This file is part of libstartrail
 *
 * Copyright (C) 2010 - Fredrik Persson <fpersson.se@gmail.com>
 *
 * libstartrail is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libstartrail is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libstartrail; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include <Magick++.h> 
#include <boost/algorithm/string.hpp>
#include "CImageComposer.h"
#include "CCfgReader.h"

extern "C"
{
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
}

using namespace std;
using namespace Magick;

/**
 * @fn static int ComposeFromFile(lua_State *L)
 * @brief Denna funktionen ska anropas om man vill lägga ihop filer från en textfil (configfil), argumenetan ska vara textfil, målfil. I från Lua ska denna anropas med ComposeFromFile
 * @param *L lua_State
 * @code
 * --Lua syntax:
 * libstartrail.ComposeFromFile("./images/test.txt", "./minbild.jpg")
 * @endcode
 * @example demo.lua
 */
static int ComposeFromFile(lua_State *L){
  CImageComposer ic;
  string srcFile = lua_tostring(L,1);
  string destFile = lua_tostring(L,2);

  CConfigRead cfgRead(srcFile);
  ic.AddImages(cfgRead.GetFiles());
  
  int err_state = ic.Compose(destFile);
  if(err_state == ic.SUCCEED){
    /** @todo skriv retur kod till lua */
  }else if(err_state == ic.INFILE_ERROR){
    /** @todo skriv returkod till lua */
  }else if(err_state == ic.DESTFILE_ERROR){
    /** @todo skriv returkod till lua */
  }
  return 1;
}

/**
 * @fn static int ComposeFromArray(lua_State *L)
 * @brief Denna funktionen ska anropas om man vill lägga ihop filer array, argumeneten skall vara array, målfil. I från Lua ska denna anropas med ComposeFromArray.
 * @param *L lua_State

 * @code
 * --Lua syntax:
 * array{"bild1.jpg", "bild2.jpg"}
 * libstartrail.ComposeFromArray(array, "./minbild.jpg")
 * @endcode
 */
static int ComposeFromArray(lua_State *L){
  CImageComposer ic;
  string destFile = lua_tostring(L,2);
  std::vector<std::string> srcFiles;

  lua_pushnil(L);
  while (lua_next(L, 1) != 0) {
    cout << lua_tostring(L,-1) << endl;
    srcFiles.push_back(lua_tostring(L,-1));
    lua_pop(L, 1);
  }
  ic.AddImages(srcFiles);
  
  int err_state = ic.Compose(destFile);
  if(err_state == ic.SUCCEED){
    /** @todo skriv retur kod till lua */
  }else if(err_state == ic.INFILE_ERROR){
    /** @todo skriv returkod till lua */
  }else if(err_state == ic.DESTFILE_ERROR){
    /** @todo skriv returkod till lua */
  }
  return 1;
}


/**
 * @note notera att det är viktigt att använda extern "C" här, annars funkar inte koden eftersom jag jobbar med c++
 */
extern "C"
{
    //regristerar funktionerna
    static const luaL_reg libstartrail[] = {
      {"ComposeFromFile",ComposeFromFile},
      {"ComposeFromArray",ComposeFromArray},
      {NULL,NULL}
    };

    /**
     * @brief Regristerar funktionerna så lua kan komma åt dom
     */
    LUALIB_API int luaopen_libstartrail(lua_State *L){
      luaL_register (L, "libstartrail", libstartrail);
      return 1;
    }
}
