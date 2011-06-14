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
#include <boost/progress.hpp>
#include <Magick++.h>  

using namespace std;
using namespace Magick;

/**
 * @class CImageComposer 
 * @author Fredrik Persson <fpersson.se@gmail.com>
 * @brief CImageComposer, använder sig av magick++ för att slåihop flertalet bilder, med lighten.
 * @todo skriv koden testbar
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
    CImageComposer(){;}
    CImageComposer(const vector<string>& files);
    int Compose(const string& dest_file);
    void AddImages(vector<string> newImages);
    void ClearImageList();
    ~CImageComposer(){};
  private:
    vector<string> file_list;
    Image base;
    Image layer;
};

#endif /* __CIMAGECOMPOSER_H__ */
