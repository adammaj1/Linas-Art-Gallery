#!/bin/bash
 
# script file for BASH 
# converts series of ppm images to animated gif
# using Image Magic
# 
# which bash
# save this file as g.sh
# chmod +x f.sh
# ./f.sh
 


# for all pgm files in this directory
for file in *.ppm ; do
  # b is name of file without extension
  b=$(basename $file .ppm)
  # convert  using ImageMagic
  convert $file -pointsize 80 -stroke blue -fill blue -gravity northeast -annotate 0 $b ${b}.gif
  echo $file
done

 
# convert gif files to animated gif
convert -delay 150   -loop 0   %d.gif[0-29] a150.gif
 
echo OK

convert -version 
# end
