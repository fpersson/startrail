/*
 * CProjWriter.h
 * This file is part of startrail
 *
 * Copyright (C) 2012 - Fredrik Persson
 *
 * startrail is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * startrail is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with startrail; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */  

#ifndef __CPROJWRITER_H__
#define __CPROJWRITER_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>

#include "boost/filesystem/operations.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/config.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/foreach.hpp>

/**
 * Hårdkodad konstant för API_VERSION
 */
#define API_VERSION "1"

/**
 * @brief Sparar projekt fil, enligt boost-info filer och följande struktur.
 * @code
 * project
 * {
 *     api_version 1
 *     destfile "./dir/test.jpg"
 *     files
 *     {
 *         image "./test_data/f1.jpg"
 *         image "./test_data/f2.jpg"
 *     }
 * }
 * @endcode
 */
class CProjWriter{
public:
  CProjWriter(){;}
  /**
   * @brief sparar data till projfile, api-version anges ej då den är hårdkodad
   * @param std::string projfile datafilen att spara till
   * @param std::string destfile projektets målfil.
   * @param std::vector<std::string> files filer som ingår i projektet.
   */
  void Save(std::string projfile, std::string destfile, std::vector<std::string> files);
};


#endif