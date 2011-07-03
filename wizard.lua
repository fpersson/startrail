#!/usr/bin/env lua
--package.cpath = "./?.so; ./?.dll"
require "libstartrail"

--! @fn split(str, pat)
--! @brief splitar upp en textsträng med önskat tecken.
--! @param str textsträng
--! @param pat tecken att splita vid
--! @return array
function split(str, pat)
   local t = {}
   local fpat = "(.-)" .. pat
   local last_end = 1
   local s, e, cap = str:find(fpat, 1)
   while s do
      if s ~= 1 or cap ~= "" then
	 table.insert(t,cap)
      end
      last_end = e+1
      s, e, cap = str:find(fpat, last_end)
   end
   if last_end <= #str then
      cap = str:sub(last_end)
      table.insert(t, cap)
   end
   return t
end

--! @brief Skapar en öppna dialog som tillåter multipla val.
--! @return array med filer
function openFile()
  hnd, msg = io.popen('kdialog --multiple --getopenfilename . "*.jpg *.JPG *.tiff |jpg and tiff Files"','r') 
  if hnd then
    for str in hnd:lines() do
      t = split(str, " ")
    end
    hnd:close()
  end
  return t
end

--! @brief Skapar en Sparasom dialog där användaren kan välja att spara jpg fil.
--! @return filnamn med sökväg att spara som
function saveAs()
  file = io.popen('kdialog --getsavefilename *.jpg "*.jpg *.JPG |jpg File"','r')
  retval = file:read("*a")
  file:close()
  return retval
end

--! @brief Visar en notify när arbetet är utfört.
--! @param str Meddelande att skriva i notify
function notify(str)
  cmd = string.format("%s%s", 'kdialog --title "Färdigt" --passivepopup ', str)
  os.execute(cmd)
end

--! @brief Skriver hur wizarden ska annvändas.
function printUsage()
  usageStr = "USAGE wizard.lua --gui | srcfiles.txt destfile.jpg"
  print(usageStr)
end

--! @brief huvudfunktionen.
--! @param argv argument vektor med första argumentet som --gui om man vill köra i GUI läge annars srcfile.txt och destfile.jpg
function main(argv)
  local nargs = table.getn(argv)
  if nargs == 1 then
    if argv[1] == "--gui" then
      srcFiles = openFile()
      destFile = saveAs()
      libstartrail.ComposeFromArray(srcFiles, destFile)
      notify(destFile)
    else
      printUsage()
    end
  elseif nargs == 2 then
    libstartrail.ComposeFromFile(argv[1], argv[2])
    print("Done...")
  else
    printUsage()
  end
end

main(arg)
 
