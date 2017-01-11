#!/bin/env python3
import fileinput
import re
import hashlib
import random
from PIL import Image, ImageFont, ImageDraw

def random_color(s):
    return "#%06x" % (int(hashlib.sha1(s.encode()).hexdigest(), 16) % (0xffffff))

input = fileinput.input().readline()
input = input.strip()[1:-1]
input = re.findall(r'\s*(\d+\:\d+,\s\d+\:\d+)\s*', input)

im = Image.new('RGB', (100,80), (0,0,0))
dr = ImageDraw.Draw(im)

for rect in input:
    color = random_color(rect)

    print(rect)
    dr.rectangle(((int(rect.split(',')[0].split(':')[0]),int(rect.split(',')[1].split(':')[0])),
                  (int(rect.split(',')[0].split(':')[1]),int(rect.split(',')[1].split(':')[1]))),
                 fill="#00000000", outline = color)

im.save("rectangle.png")
