/*
 * CProjWriter.cpp
 * This file is part of startrail
 *
 * Copyright (C) 2012 - Fredrik Persson email fpersson.se@gmail.com
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

#include "CProjWriter.h"

void CProjWriter::Save(std::string projfile, std::string destfile, std::vector<std::string> files){
  boost::property_tree::ptree pt;

  pt.put("project.api_version", API_VERSION);
  pt.put("project.destfile", destfile);

  std::vector<std::string>::iterator it;
  for(it =  files.begin(); it < files.end(); ++it){
    pt.add("project.files.image", (*it));
  }
  
  boost::property_tree::write_info(projfile, pt);
}
