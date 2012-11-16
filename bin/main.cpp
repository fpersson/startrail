/*
 * main.cpp
 * This file is part of startrail
 *
 * Copyright (C) 2010 - Fredrik Persson
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
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>
#include <set>

#include <boost/algorithm/string.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include <Magick++.h>

#include "config.h"
#include "CImageComposer.h"
#include "CCfgReader.h"
#include "CProjReader.h"
#include "CFileLister.h"

using namespace std;
using namespace Magick;

bool printHelp;

/**
 * @fn bool isTextFile(std::string str)
 * @brief Kollar om en fil är textfil (kollar efter .txt)
 * @param str
 * @return true om det är en textfil som slutar på .txt annars false
 */
bool isTextFile(std::string str){
  size_t found_char;
  found_char = str.find_last_of(".");
  if(str.substr(found_char) == ".txt"){
    return true;
  }else{
    return false;
  }
}

/**
 * @brief säkerställer att hjälpen bara skrivs en gång.
 */
void printHelpOnce(boost::program_options::options_description& d){
  if(!printHelp){
    cout << d << endl;
    cout << "Om:" << endl;
    cout << "Startrail version " << software_version << "\nGenerar en startrail bild utifrån en bildsammling."<< endl;
    cout << "Upphovsman: Fredrik Persson <fpersson.se@gmail.com>\nLicens: GPL" << endl;
    cout << "\nSyntax: ./startrail --input-file=./images/test.txt --dest-file=./minbild.jpg\n ALT:" << endl;
    cout << "\nSyntax: ./startrail --use-projectfile=./images/test.proj\n" << endl;
  }
  printHelp = true;
}

/**
 * @fn int main(int argc, char* argv[])
 * @brief Huvudfunktionen för ./bin/startrail
 */
int main(int argc, char* argv[]){
  CImageComposer my;
  printHelp = false;
  string srcFile;
  string destFile;

  boost::program_options::options_description desc("\nTillåtna argument");
  desc.add_options()
    ("help", "Hjälp.")
    ("version", "skriver ut versionsnumer")
    ("input-file", boost::program_options::value<std::string>(), "Anger en textfil med en lista av bildfiler.")
    ("input-dir", boost::program_options::value<std::string>(), "Läser in alla filerna i input-dir och slår samman dom.")
    ("dest-file", boost::program_options::value<std::string>(), "Anger målfilen som jpg")
    ("use-projectfile", boost::program_options::value<std::string>(), "Ange vilken .proj (projekt) fil som ska användas");

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    printHelpOnce(desc);
    return 1;
  }

  if(vm.count("version")){
    cout << "Startrail - ver: " << software_version << endl;
    return 1;
  }

  if(vm.count("dest-file") && vm.count("input-file")){
    srcFile = vm["input-file"].as<std::string>();
    destFile = vm["dest-file"].as<std::string>();
    if(isTextFile(srcFile)){
      CConfigRead cfgRead(srcFile);
      my.AddImages(cfgRead.GetFiles());
      my.Compose(destFile);
    }
  }else if(vm.count("dest-file") && vm.count("input-dir")){
    CFileLister FileList;
    std::set<std::string> filter;
    filter.insert(".jpg");
    filter.insert(".JPG");
    my.AddImages(FileList.listFiles(vm["input-dir"].as<std::string>(),filter));
    my.Compose(vm["dest-file"].as<std::string>());    
  }else if(vm.count("use-projectfile")){
    cout << "project file: " << vm["use-projectfile"].as<std::string>() << std::endl;
    CProjReader projReader(vm["use-projectfile"].as<std::string>());
    my.AddImages(projReader.GetFiles());
    my.Compose(projReader.getDestFile());
  }else{
    printHelpOnce(desc);
    return 1;
  }
  return 0;
}
