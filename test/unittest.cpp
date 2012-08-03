#define BOOST_TEST_MAIN
#include <vector>
#include <string>
#include <stdio.h>
#include <boost/test/included/unit_test.hpp>
#include "../src/CCfgReader.h"
#include "../src/CProjReader.h"
#include "../src/CProjWriter.h"

BOOST_AUTO_TEST_CASE(ConfigReaderTest_inittest){
    CConfigRead reader("./test_data/testfile1.txt");
    std::vector<std::string> res = reader.GetFiles();

    BOOST_CHECK("./test_data/f1.jpg" == res[0]);
    BOOST_CHECK("./test_data/f2.jpg" == res[1]);
    BOOST_CHECK("./test_data/f3.jpg" == res[2]);
}

BOOST_AUTO_TEST_CASE(ProjectReader_init){
  CProjReader reader("./test_data/testfile1.proj");
  int api_ver = reader.getApiVersion();
  std::string destfile = reader.getDestFile();
  
  BOOST_CHECK(1 == api_ver);
  BOOST_CHECK("./dir/test.jpg" == destfile);    
}

BOOST_AUTO_TEST_CASE(ProjectReader_files){
  CProjReader reader("./test_data/testfile1.proj");
  std::vector<std::string> res = reader.GetFiles();
  
  BOOST_CHECK("./test_data/f1.jpg" == res[0]);
  BOOST_CHECK("./test_data/f2.jpg" == res[1]);
  BOOST_CHECK("./test_data/f3.jpg" == res[2]);    
}

BOOST_AUTO_TEST_CASE(ProjectReader_WriteRead){
  std::string testfile = "./test_data/foo.proj";
  std::vector<std::string> files;
  
  files.push_back("./test_data/f1.jpg");
  files.push_back("./test_data/f2.jpg");
  files.push_back("./test_data/f3.jpg");
  
  CProjWriter writer;
  writer.Save(testfile, "./dir/test.jpg", files );
  
  CProjReader reader(testfile);
  int api_ver = reader.getApiVersion();
  std::string destfile = reader.getDestFile();
  std::vector<std::string> res = reader.GetFiles();
  
  BOOST_CHECK(1 == api_ver);
  BOOST_CHECK("./dir/test.jpg" == destfile);
  
  BOOST_CHECK("./test_data/f1.jpg" == res[0]);
  BOOST_CHECK("./test_data/f2.jpg" == res[1]);
  BOOST_CHECK("./test_data/f3.jpg" == res[2]);
  
  if( remove(testfile.c_str()) != 0){
    std::cout << "Error: could not delete " << testfile << std::endl;
  }
}
