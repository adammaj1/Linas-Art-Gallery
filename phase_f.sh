#!/bin/bash
 
# script file for BASH 
# converts series of ppm images to animated gif
# using Image Magic
# 
# which bash
# save this file as phase_f.sh
# chmod +x phase_f.sh
# ./phase_f.sh
 


# for all pgm files in this directory
for file in *.ppm ; do
  # b is name of file without extension
  b=$(basename $file .ppm)
  # convert  using ImageMagic
  convert $file -pointsize 80 -stroke white -fill white -gravity northeast -annotate 0 $b ${b}.gif
  echo $file
done

 
# convert gif files to animated gif
convert -delay 150   -loop 0   %d.gif[0-29] -resize 600x600 phase_f.gif
 
echo OK

convert -version 
# end
