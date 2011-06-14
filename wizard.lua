#!/usr/bin/env lua
--package.cpath = "./?.so; ./?.dll"
require "libstartrail"

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

--Jag använder kdialog
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

-- Välj savefil
function saveAs()
  file = io.popen('kdialog --getsavefilename *.jpg "*.jpg *.JPG |jpg File"','r')
  retval = file:read("*a")
  file:close()
  return retval
end

-- en Notify när allt är färdigt.
function notify(str)
  cmd = string.format("%s%s", 'kdialog --title "Färdigt" --passivepopup ', str)
  os.execute(cmd)
end

-- main funktion för snyggare kod
function main()
  srcFiles = openFile()
  destFile = saveAs()
  libstartrail.ComposeFromArray(srcFiles, destFile)
  notify(destFile)
end

-- ska skriva hur wizarden ska annvändas.
function printUsage()
  usageStr = "USAGE wizard.lua --gui | srcfiles.txt destfile.jpg"
  print(usageStr)
  --notify(usageStr)
end

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
 