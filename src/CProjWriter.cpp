#include "CProjWriter.h"

void CProjWriter::Save(std::string projfile, std::string destfile, std::vector<std::string> files){
  boost::property_tree::ptree pt;

  pt.put("project.api_version", API_VERSION);
  pt.put("project.destfile", destfile);

  std::vector<std::string>::iterator it;
  for(it =  files.begin(); it < files.end(); it++){
    pt.add("project.files.image", (*it));
  }
  
  boost::property_tree::write_info(projfile, pt);
}
