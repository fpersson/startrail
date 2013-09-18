/*
 * CExifHandler.h
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

#ifndef CExifHandler_H
#define CExifHandler_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>

#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/config.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

#include <config.h>

const std::string SOFTWARE_NAME = "Startrail";
/**
 * @brief iptc4xmpCore, kontakt info för bildens upphovsman, lagras i en boost info fil med samma namn och utsende.
 */
struct iptc4xmpCore_t {
  /** @brief stad */
  std::string CiAdrCity;
  /** @brief land */
  std::string CiAdrCtry;
  /** @brief gata */
  std::string CiAdrExtadr;
  /** @brief postnummer */
  std::string CiAdrPcode;
  /** @brief email */
  std::string CiAdrEmailWork;
  /** @brief webpage */
  std::string CiUrlWork;
};

/**
 * @class CExifHandler
 * @author Fredrik Persson <fpersson.se@gmail.com>
 * @brief Klassen ansvarar för att räkna upp antalet bilder som används i montaget och räknar ut den totala slutartiden (i sekunder). För att minimera io så öppnas bara sista filen i serien för läsning av exif, sedan multipliceras slutartiden med antalet bilder och den nya beräknade slutartiden.
 * @note Initialvärdet är 1
 */
class CExifHandler {
public:
  CExifHandler();

  /**
   * @fn count()
   * @brief räknar upp med +1
   */
  void count();

  /**
   * @fn updateExif(std::string file)
   * @brief Uppdaterar exif-/iptc-data för slutartiden, samt lägger till taggen "startrail" och en lite kommentar om att bilden är stackad med startrail ver n.n
   * @param file
   */
  void updateExif(std::string file);

  /**
   * @fn pharseTime(std::string time)
   * @brief Då exiv2 ger tiden som sträng is stil med "30 s" eller än värre "1/100 s" måste man parsa ut tiden så man kan räkna med den.
   * @param time som sträng
   * @return time som float
   * @todo gör så man även kan hantera kortare slutartider än 1s även om ingen kommer behöva det.
   * @note hanterar inte tider kortare än 1 sekund
   */
  unsigned int const pharseTime(std::string time);

  /**
   * @brief testar om infofilen finns och finns den sätts m_useIptcInfo till true
   * @param file en boost .info fil
   */
  void setIptcInfoFile(std::string file);
private:
  /**
   * @brief Lägger till info från .info filen, funktionen både läser info filen och lägger till infon i jpgfilen.
   * @param xmp en referens till xmp data.
   */
  void applayIptcInfoFile(Exiv2::XmpData& xmp);

  int m_numImages;
  bool m_useIptcInfo;
  std::string m_iptcInfoFile;
  iptc4xmpCore_t m_iptc4xmpCore;
};

#endif
