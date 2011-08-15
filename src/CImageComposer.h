/*
 * CImageComposer.h
 * This file is part of startrail
 *
 * Copyright (C) 2009 - Fredrik Persson
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

#ifndef __CIMAGECOMPOSER_H__
#define __CIMAGECOMPOSER_H__

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

#ifdef STAND_ALONE
  #include <boost/progress.hpp>
#endif

#include <Magick++.h>
#include "CExifHandler.h"

using namespace std;
using namespace Magick;

/**
 * @class CImageComposer
 * @author Fredrik Persson <fpersson.se@gmail.com>
 * @brief CImageComposer, använder sig av magick++ för att slåihop flertalet bilder, med lighten.
 * @todo skriv koden testbar
 * @todo implemetera ERR_CODE
 */
class CImageComposer
{
  public:
    enum ERR_CODE{
      /** Standard som anger att allt gick rätt till */
      SUCCED = 0,
      /** Kunde inte läsa in filen*/
      INFILE_ERROR,
      /** Kunde inte skriva till målfilen */
      DESTFILE_ERROR
    };

    /**
     * @brief En tom construkter för senare bruk, bör ej användas.
     */
    CImageComposer(){;}

    /**
     * @brief Konstrukter att använda i fall man inte vill ha utöka exifstöd
     * @param files vektor bildfiler
     */
    CImageComposer(const vector<string>& files);

    /**
     * @brief Konstrukter med stöd för utökad exif
     * @param files vektor med bildfiler
     * @param exiffile infofilen med exifdata.
     */
    CImageComposer(const string& exiffile);

    /**
     * @brief Slår samman bilderna till dest_file, vill man lägga till fler filer än de man skickar med konstruktorn måste man använda AddImages först innan man anropar Compose.
     * @param dest_file namnet på den fill man vill spara allt till
     */
    int Compose(const string& dest_file);

    /**
     * @brief Lägger till fler bilder i vektorn, funktionen måste användas innan man anropar Compose
     * @param newImages en vector innehållande en eller flera nya bilder.
     */
    void AddImages(vector<string> newImages);

    /**
     * @brief rensar hela listan med bilder.
     */
    void ClearImageList();

    ~CImageComposer(){};
  private:
    vector<string> file_list;
    CExifHandler m_exifHandle;
    Image base;
    Image layer;
};

#endif /* __CIMAGECOMPOSER_H__ */
