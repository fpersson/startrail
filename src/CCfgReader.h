/*
 * CCfgReader.h
 * This file is part of startrail
 *
 * Copyright (C) 2009 - Fredrik Persson email fpersson.se@gmail.com
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
 
#ifndef CCfgReader_H
#define CCfgReader_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include "IReader.h"

/**
 * @class CConfigRead 
 * @author Fredrik Persson <fpersson.se@gmail.com>
 * @brief CConfigRead Oviktigklass för att läsa in en konfigfil bestående av en textfil med en massa filnamn, ett namn per rad.
 * 
 * En beskrivning på hur klassen används.
 * @code
 * ///Sample 1.1
 * CConfigRead reader("./test_data/testfile1.txt");
 * std::vector<std::string> res = reader.GetFiles();
 * @endcode
 */
class CConfigRead : public IReader
{
  public:
    /**
     * @fn CConfigRead::CConfigRead(std::string cfg);
     * @brief
     * @param cfg
     */
    explicit CConfigRead(std::string cfg);
    virtual ~CConfigRead();
    
    virtual void ReadFile(std::string cfg);
    
    /**
     * @fn std::vector<std::string> GetFiles(){return files;}
     * @return files as std::vector<std::string>
     */
    virtual std::vector<std::string> GetFiles(){return files;}
  private:
    std::vector<std::string>files;
    /**
    * @fn std::string GetFolder(const string& cfg);
    * @brief skapar sökvägen till filerna genom att bryta ner sökvägen till konfigfilen, detta gör konfigfilen måste ligga i samma mapp som bilderna. Funktionen bör vara lätt att porta till alternativa plattformar tex windows.
    * @param cfg referens till configfilen
    * @return string som anger sökvägen till filens katalog.
    * @todo Ev skriva om funktionen så filen inte måste ligga i samma katalog som bilderna.
    */
    std::string GetFolder(const std::string& cfg);
};

#endif /* __CCfgReader_H__ */
