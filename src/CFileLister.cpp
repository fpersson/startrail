/*
 * CFileLister.cpp
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

#include "CFileLister.h"

std::vector< std::string > CFileLister::listFiles(std::string path, std::set< std::string > filter){
  std::vector<std::string> retval;
  boost::filesystem::path p(path);
  boost::filesystem::directory_iterator endit;

  if(boost::filesystem::exists(p) && boost::filesystem::is_directory(p)){
    for(boost::filesystem::directory_iterator  dirit(p); dirit != endit; ++dirit ){
      if(filter.find(dirit->path().extension().string()) != filter.end()){
        retval.push_back(dirit->path().c_str());
      }
    }
  }
  return retval;
}