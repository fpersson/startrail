#include "CFileLister.h"

std::vector< std::string > CFileLister::listFiles(std::string path, std::set< std::string > filter){
  std::vector<std::string> retval;
  boost::filesystem::path p(path);
  boost::filesystem::directory_iterator endit;

  if(boost::filesystem::exists(p) && boost::filesystem::is_directory(p)){
    for(boost::filesystem::directory_iterator  dirit(p); dirit != endit; ++dirit ){
      if(filter.find(dirit->path().extension().string()) != filter.end()){
        retval.push_back(dirit->path().c_str());
      }
    }
  }
  return retval;
}