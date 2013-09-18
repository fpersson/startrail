/*
 * CFileLister.h
 * This file is part of startrail
 *
 * Copyright (C) 2011 - Fredrik Persson email fpersson.se@gmail.com
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

#ifndef CFileLister_H
#define CFileLister_H

#include <iostream>
#include <set>

#include <boost/filesystem.hpp>

/**
 * @class CFileLister
 * @author Fredrik Persson <fpersson.se@gmail.com>
 * @brief Listar alla filerna i en katalog.
 * @code
 * CFileLister FileLister;
 * std::set<std::string> filter;
 * filter.insert(".JPG");
 * filter.insert(".jpg");
 * std::vector<std::string> res = FileLister.listFiles("./test_data/", filter);
 * @endcode
 */
class CFileLister{
public:
  /**
   * @brief standard konstruktern gör inget vetting
   */
  CFileLister(){;}
  /**
   * @brief listar alla filer i given katalog
   * @param path
   * @param filter
   * @return vector med filnamn
   */
  std::vector<std::string> listFiles(std::string path, std::set<std::string> filter);
};

#endif
