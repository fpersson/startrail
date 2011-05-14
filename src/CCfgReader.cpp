/*
 * CCfgReader.cpp
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
 
#include "CCfgReader.h"

CConfigRead::CConfigRead(string cfg)
{
	char* conf = (char*)cfg.c_str();
	string str;
	string path;
	string strImage;
	ifstream fin(conf);
	if(!fin){
		//cout << "Kunde inte läsa: " << cfg << endl;
	}else{
		path = GetFolder(cfg);
		while(!fin.eof()){
			fin >> str;
			strImage = path+"/"+str;
			files.push_back(strImage);
		}
	}
	fin.close();
}

CConfigRead::~CConfigRead()
{
	//TODO: Skriv destruktor
}

string CConfigRead::GetFolder(const string& cfg)
{
	size_t found_char;
	found_char = cfg.find_last_of("/\\");
	return cfg.substr(0, found_char);
}

 
