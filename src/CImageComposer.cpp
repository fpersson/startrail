/*
 * CImageComposer.cpp
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
 
#include "CImageComposer.h"

/**
 * @fn CImageComposer::CImageComposer(const vector<string>& files)
 * @param files std::vector med std::string
 * @brief
 */
CImageComposer::CImageComposer(const vector<string>& files)
{
  file_list=files;
}

/**
 * @fn int CImageComposer::Compose(const string& dest_file)
 * @param dest_file målfilen
 * @brief slår i hop bilderna LightenCompositeOp och skapar dest_file.
 * @todo Fixa till så att denna funktionen returerar ett enklelt felmeddelande om något går snett.
 */
int CImageComposer::Compose(const string& dest_file)
{
  base.read(file_list[0]);
  vector<string>::iterator i;
  string obj;
  for(i=file_list.begin()+1; i < file_list.end(); i++){
    layer.read(*i);
    base.composite(layer, 0,0 , LightenCompositeOp);
    exif.count();
  }
  base.write(dest_file);
  exif.updateExif(dest_file);
  return 0;
}

/**
 *@brief Lägger till fler filer i listan
 *@param newImages Lista av bilder som ska läggas till.
 */
void CImageComposer::AddImages(vector<string> newImages)
{
  vector<string>::iterator i;
  for(i=newImages.begin(); i < newImages.end(); i++){
    file_list.push_back(*i);
  }
}

/**
 *@brief tömmer listan med filnamnen.
 */
void CImageComposer::ClearImageList()
{
  file_list.clear();
}

