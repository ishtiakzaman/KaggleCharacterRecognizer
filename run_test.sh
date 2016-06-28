#!/bin/bash

echo "ID,Class"
while read -r line
do
  cmd="./../caffe/build/examples/cpp_classification/classification.bin "
  cmd+="deploy.prototxt "
  cmd+="cr_v3_iter_80000.caffemodel "
  cmd+="mean.binaryproto "
  cmd+="map_words.txt "
  cmd+="$line"
  result=$($cmd)
  result=${result##*--}
  result=${result#*- \"}
  result=${result%%\"*}
  result=${result#* }
  line=${line#*/}
  line=${line%.Bmp}
  echo $line,$result
done < test.txt