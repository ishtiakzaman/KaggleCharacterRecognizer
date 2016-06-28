#!/bin/bash

for file in test_original/*.Bmp
  do convert $file -resize 100x100\! -colorspace Gray test/${file##*/}
done
