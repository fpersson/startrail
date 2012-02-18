#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../src/CCfgReader.h"
#include "../src/CProjReader.h"

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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}
