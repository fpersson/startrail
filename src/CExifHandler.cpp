#include "CExifHandler.h"

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

CExifHandler::CExifHandler() :
  m_numImages(1),
  m_useIptcInfo(false){
}

void CExifHandler::count(){
  m_numImages++;
}

void CExifHandler::updateExif(std::string file){
  unsigned int totalExposeureTime=0;
  std::string t = "";
  std::string comment = "";
  std::string software = "";
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(file);
  image->readMetadata();
  Exiv2::ExifData exifData = image->exifData();
  Exiv2::IptcData iptcData = image->iptcData();
  Exiv2::XmpData xmpData = image->xmpData();

  t = exifData["Exif.Photo.ExposureTime"].toString();
  totalExposeureTime = pharseTime(t)*m_numImages;
  exifData["Exif.Photo.ExposureTime"] = totalExposeureTime;
  exifData["Exif.Image.ShutterSpeedValue"] = totalExposeureTime;
  exifData["Exif.Photo.ShutterSpeedValue"] = totalExposeureTime;

  software.append(SOFTWARE_NAME);
  software.append(" ");
  software.append(software_version);
  comment.append("Created with ");
  comment.append(software);

  exifData["Exif.Photo.UserComment"] = comment;
  exifData["Exif.Image.ProcessingSoftware"] = software;
  exifData["Exif.Image.Software"] = software;

  iptcData["Iptc.Application2.Program"] = SOFTWARE_NAME;
  iptcData["Iptc.Application2.ProgramVersion"] = software_version;

  if(m_useIptcInfo == true){
    std::cout << "true" << std::endl;
    applayIptcInfoFile(xmpData);
    image->setXmpData(xmpData);
  }

  image->setExifData(exifData);
  image->setIptcData(iptcData);
  image->writeMetadata();
}

unsigned int const CExifHandler::pharseTime(std::string time){
  std::vector<std::string> strs;
  boost::split(strs, time, boost::is_any_of("\t "));
  return atoi(strs[0].c_str());
}

void CExifHandler::setIptcInfoFile(std::string file){
  if(boost::filesystem::exists(file)){
    m_iptcInfoFile = file;
    m_useIptcInfo = true;
  }else{
    m_useIptcInfo = false;
  }
}

void CExifHandler::applayIptcInfoFile(Exiv2::XmpData& xmp){
  boost::property_tree::ptree pt;
  std::cout << "Användardefinierat är: " << m_iptcInfoFile << std::endl;
  boost::property_tree::info_parser::read_info(m_iptcInfoFile, pt);

  m_iptc4xmpCore.CiAdrCity = pt.get<std::string>("iptc4xmpCore.CiAdrCity");
  m_iptc4xmpCore.CiAdrCtry = pt.get<std::string>("iptc4xmpCore.CiAdrCtry");
  m_iptc4xmpCore.CiAdrExtadr = pt.get<std::string>("iptc4xmpCore.CiAdrExtadr");
  m_iptc4xmpCore.CiAdrPcode = pt.get<std::string>("iptc4xmpCore.CiAdrPcode");
  m_iptc4xmpCore.CiUrlWork = pt.get<std::string>("iptc4xmpCore.CiUrlWork");
  m_iptc4xmpCore.CiAdrEmailWork = pt.get<std::string>("iptc4xmpCore.CiAdrEmailWork");

  xmp["Xmp.iptc.CiAdrCity"] = m_iptc4xmpCore.CiAdrCity;
  xmp["Xmp.iptc.CiAdrCtry"] = m_iptc4xmpCore.CiAdrCtry;
  xmp["Xmp.iptc.CiAdrExtadr"] = m_iptc4xmpCore.CiAdrExtadr;
  xmp["Xmp.iptc.CiAdrPcode"] = m_iptc4xmpCore.CiAdrPcode;
  xmp["Xmp.iptc.CiUrlWork"] = m_iptc4xmpCore.CiUrlWork;
  xmp["Xmp.iptc.CiAdrEmailWork"] = m_iptc4xmpCore.CiAdrEmailWork;
}
