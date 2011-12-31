#!/usr/bin/python
import lib_pystartrail

ConfReader = lib_pystartrail.ConfigRead("./images/test.txt")
composer = lib_pystartrail.ImageComposer(ConfReader.GetFiles())
composer.Compose("./testing.jpg")