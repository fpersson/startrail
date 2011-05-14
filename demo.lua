--package.cpath = "./?.so; ./?.dll"
require "libstartrail"

--Variant 1, med textfil som innehåller alla filerna som ska bearbetas.
libstartrail.ComposeFromFile("./images/test.txt", "./minbild.jpg")

 --Variant 2, med en lista på alla filer som ska berabetas, 
 --det är upp till användaren själv att fantisera ut hur listan ska skapas.

files = {"./images/IMG_3271.JPG",
	"./images/IMG_3272.JPG",
	"./images/IMG_3273.JPG",
	"./images/IMG_3274.JPG",
	"./images/IMG_3275.JPG",
	"./images/IMG_3276.JPG"
	}
libstartrail.ComposeFromArray(files, "./minbild_2.jpg")
