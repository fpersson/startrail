#include "CProjReader.h"

CProjReader::CProjReader(std::string cfg)
{
  ReadFile(cfg);
}

CProjReader::~CProjReader()
{
  //TODO: Skriv destruktor
}

void CProjReader::ReadFile(std::string cfg){
  boost::property_tree::ptree pt;
  boost::property_tree::info_parser::read_info(cfg, pt);
  
  m_apiversion = pt.get<int>("project.api_version");
  m_destfile = pt.get<std::string>("project.destfile");
  
  BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("project.files")){
    m_files.push_back(v.second.data());
  }
}

std::string CProjReader::GetFolder(const std::string& cfg)
{
  size_t found_char;
  found_char = cfg.find_last_of("/\\");
  return cfg.substr(0, found_char);
} 
