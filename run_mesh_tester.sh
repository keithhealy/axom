#!/bin/bash

rm output.txt
rm -rf mesh_tester_runs 
mkdir mesh_tester_runs 
for i in {1..25}
do
  bin/mesh_tester -i ../porsche.stl -r 2 -p 3 --skipWeld &>> output.txt
  cp example.txt mesh_tester_runs/example$i.txt
done

grep -i "intersecting tri pairs" output.txt > numberOfIntersections.txt


