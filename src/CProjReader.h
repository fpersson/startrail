/*
 * CProjReader.h
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

#ifndef CPROJREADER_H
#define CPROJREADER_H

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

#include "IReader.h"

/**
 * @class CProjReader 
 * @author Fredrik Persson <fpersson.se@gmail.com>
 * @brief CProjReader Hanterar projektfiler som bygger på boost ptree format, 
 * projektfilerna ska i första hand användas av det grafiska gränssnittet i QT, men kan även importeras standalone versionen.
 * 
 * En beskrivning på hur klassen används.
 * @code
 * ///Sample 1.2
 * ConfigRead reader("./myfile.proj");
 * std::vector<std::string> myVector = reader.GetFiles();
 * std::string destfile = reader.getDestFile();
 * @endcode
 */
class CProjReader : public IReader{
public:
  /**
   * @fn CProjReader::CProjReader(std::string cfg);
   * @brief
   * @param cfg
   */
  explicit CProjReader(std::string cfg);
  virtual ~CProjReader();
  
  virtual void ReadFile(std::string cfg);
  
  /**
   * @fn std::vector<std::string> GetFiles(){return m_files;}
   * @return files som std::vector<std::string>
   */
  virtual std::vector<std::string> GetFiles(){return m_files;}
  
  /**
   * @brief används inte än, utan finns bara för framtida bruk om jag ändrar projektfilens api:er
   */
  int getApiVersion(){return m_apiversion;}
  
  /**
   * @brief ger relativa sökvägen till målfilen.
   * @fn std::string getDestFile()
   * @return
   */
  std::string getDestFile(){return m_destfile;}
  
private:
  std::vector<std::string>m_files;
  int m_apiversion;
  std::string m_destfile;
  /**
   * @fn std::string GetFolder(const string& cfg);
   * @brief skapar sökvägen till filerna genom att bryta ner sökvägen till konfigfilen, detta gör konfigfilen måste ligga i samma mapp som bilderna. Funktionen bör vara lätt att porta till alternativa plattformar tex windows.
   * @param cfg referens till configfilen
   * @return string som anger sökvägen till filens katalog.
   * @todo Ev skriva om funktionen så filen inte måste ligga i samma katalog som bilderna.
   * @note Används inte än.
   */
  std::string GetFolder(const std::string& cfg);
};

#endif
