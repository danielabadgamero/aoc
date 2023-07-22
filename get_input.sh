#!/bin/bash

day=$2
if [[ $day -lt 10 ]]; then
	day="0$day"
fi
curl --cookie "session=$AOC_ID" https://adventofcode.com/$1/day/$2/input \
	> ./$1/$day/input
