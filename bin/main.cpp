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
#include <Magick++.h> 
#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>
#include "CImageComposer.h"
#include "CCfgReader.h"

using namespace std;
using namespace Magick;

bool isTextFile(std::string str)
{
	size_t found_char;
	found_char = str.find_last_of(".");
	if(str.substr(found_char) == ".txt"){
		return true;
	}else{
		return false;
	}
}

/**
 * @brief experimentiell trådning
 */
void splitedWork(std::vector<std::string>)
{
  /** @todo skriv kod här*/
}

/**
 * Stödjer även en lista med filer nu.
 */
int main(int argc, char* argv[])
{
	if(argc < 3 && argc > 4){
		cout << "Startrail version 2.1\nGenerar en startrail bild utifrån en bildsammling."<< endl;
		cout << "\nANVÄNDS: startrail <path_to_files/my_files.txt> <path_to_dest/out.jpg>" << endl;
		cout << "         my_files.txt ska innhålla en lista på bildernas filnamn." << endl;
		cout << "ALT: startrail <fil_array> <path_to_dest/out.jpg>." << endl;
		cout << "ALT: startrail <fil_array> <path_to_dest/out.jpg><--treads=true>." << endl;
		cout << "\nUpphovsman: Fredrik Persson <fpersson.se@gmail.com>\nLicens: GPL" << endl;
	}else if(argc == 4){
		if(argv[4] == "--treads=true"){
		/**den trådade koden här.*/
		}else{
			cout << "Fuck you!!!" << endl;
		}
	}else{
		CImageComposer my;
		if(isTextFile(argv[1])){
			CConfigRead cfgRead(argv[1]);
			my.AddImages(cfgRead.GetFiles());
		}else{
			std::vector<std::string> strs;
			boost::split(strs, argv[1], boost::is_any_of("\t "));
			my.AddImages(strs);
		}
		my.Compose(argv[2]);
	}
	return 0;
}
