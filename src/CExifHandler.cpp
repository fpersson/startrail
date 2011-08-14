#include "CExifHandler.h"

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

CExifHandler::CExifHandler() : numImages(1) {
}

void CExifHandler::count(){
  numImages++;
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
  
  t = exifData["Exif.Photo.ExposureTime"].toString();
  totalExposeureTime = pharseTime(t)*numImages;
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
  
  image->setExifData(exifData);
  image->setIptcData(iptcData);
  image->writeMetadata();
}

unsigned int const CExifHandler::pharseTime(std::string time){
  std::vector<std::string> strs;
  boost::split(strs, time, boost::is_any_of("\t "));
  return atoi(strs[0].c_str());
}


