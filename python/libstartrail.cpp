/*
 * libstartrail.cpp
 * This file is part of libstartrail
 *
 * Copyright (C) 2010 - Fredrik Persson <fpersson.se@gmail.com>
 *
 * libstartrail is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libstartrail is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libstartrail; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include <Magick++.h> 
#include <boost/algorithm/string.hpp>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "CImageComposer.h"
#include "CCfgReader.h"

using namespace std;
using namespace Magick;
using namespace boost::python;

typedef std::vector<std::string> StringList;

/**
 * @brief Adaptor klass för CConfigRead så python kan komma åt vectorn som boost::python::list i stället.
 */
class ConfigReader{
public:
  ConfigReader(std::string cfg){
    CConfigRead reader(cfg);
    m_files = reader.GetFiles();
  }
  
  StringList GetFiles(){return m_files;}

private:
  StringList m_files;
};

/**
 * @class ImageComposer
 * @brief Adaptor klass för CImageCompser då boost::python inte hanterar stl::vector
 * @example test.py
 */
class ImageComposer{
public:
  ImageComposer(StringList sl) : m_composer(sl){;}
  void Compose(std::string destfile){m_composer.Compose(destfile);}
  void AddImages(StringList sl){m_composer.AddImages(sl);}
  void ClearImageList(){m_composer.ClearImageList();}
private:
  CImageComposer m_composer;
};

/**
 * @brief binder klasserna i startrail mot python
 */
BOOST_PYTHON_MODULE(lib_pystartrail){
  class_<StringList>("StringList")
    .def(vector_indexing_suite<StringList>());

  class_<ConfigReader>("ConfigRead", init<std::string>())
    .def("GetFiles", &ConfigReader::GetFiles);

  class_<ImageComposer>("ImageComposer", init<StringList>())
    .def("Compose", &ImageComposer::Compose)
    .def("AddImages", &ImageComposer::AddImages)
    .def("ClearImageList", &ImageComposer::ClearImageList);
}