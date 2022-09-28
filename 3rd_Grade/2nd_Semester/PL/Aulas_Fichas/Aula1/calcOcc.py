#!/usr/bin/env python3

import sys

#txt = open("input.txt").read()
txt = sys.stdin.read()
print(txt)

occ = {}
for pal in txt.split():
    if pal in occ:
        occ[pal] +=1
    else:
        occ[pal] = 1

for k,v in occ.items():
    print(v, "\t", k)

