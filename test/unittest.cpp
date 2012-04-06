#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdio.h>
#include "../src/CCfgReader.h"
#include "../src/CProjReader.h"
#include "../src/CProjWriter.h"

TEST(ConfigReaderTest, inittest){
  CConfigRead reader("./test_data/testfile1.txt");
  std::vector<std::string> res = reader.GetFiles();
  EXPECT_EQ("./test_data/f1.jpg", res[0]);
  EXPECT_EQ("./test_data/f2.jpg", res[1]);
  EXPECT_EQ("./test_data/f3.jpg", res[2]);
}

TEST(ProjectReader, init){
  CProjReader reader("./test_data/testfile1.proj");
  int api_ver = reader.getApiVersion();
  std::string destfile = reader.getDestFile();
  
  EXPECT_EQ(1, api_ver);
  EXPECT_EQ("./dir/test.jpg", destfile);
}

TEST(ProjectReader, files){
  CProjReader reader("./test_data/testfile1.proj");
  std::vector<std::string> res = reader.GetFiles();
  
  EXPECT_EQ("./test_data/f1.jpg", res[0]);
  EXPECT_EQ("./test_data/f2.jpg", res[1]);
  EXPECT_EQ("./test_data/f3.jpg", res[2]);
}

TEST(ProjectReader, WriteRead){
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
  
  EXPECT_EQ(1, api_ver);
  EXPECT_EQ("./dir/test.jpg", destfile);
  
  EXPECT_EQ("./test_data/f1.jpg", res[0]);
  EXPECT_EQ("./test_data/f2.jpg", res[1]);
  EXPECT_EQ("./test_data/f3.jpg", res[2]);
  
  if( remove(testfile.c_str()) != 0){
    std::cout << "Error: could not delete " << testfile << std::endl;
  }
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}
