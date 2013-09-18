/*
 * CProjReader.cpp
 * This file is part of startrail
 *
 * Copyright (C) 2011 - Fredrik Persson <fpersson.se@gmail.com>
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

#include "CProjReader.h"

CProjReader::CProjReader(std::string cfg)
{
  ReadFile(cfg);
}

CProjReader::~CProjReader()
{
  //TODO: Skriv destruktor
}

void CProjReader::ReadFile(std::string cfg){
  boost::property_tree::ptree pt;
  boost::property_tree::info_parser::read_info(cfg, pt);
  
  m_apiversion = pt.get<int>("project.api_version");
  m_destfile = pt.get<std::string>("project.destfile");
  
  BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("project.files")){
    m_files.push_back(v.second.data());
  }
}

std::string CProjReader::GetFolder(const std::string& cfg)
{
  size_t found_char;
  found_char = cfg.find_last_of("/\\");
  return cfg.substr(0, found_char);
} 
