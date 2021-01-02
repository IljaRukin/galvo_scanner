import numpy as np
import matplotlib.pyplot as plt
import csv

x = []
y = []
p = []

with open('graphic.hpgl') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=';')
    for parsed in csv_reader:
        for line in parsed:
            if line[0]=='P' and len(line)>2:
                pen = '0'
                if line[1]=='D':
                    pen = '1'
                val = line[2:].split(',')[::-1]
                while val:
                    x.append(str(4095-int(val.pop())))
                    y.append((val.pop()))
                    p.append((pen))

f = open('graphic.cpp','w')
f.write('#include <avr/pgmspace.h>\n')
f.write('#define ARR_LENGTH ')
f.write(str(len(p)))
f.write('\n')
f.write('const bool pen[] = {')
for e in p:
    f.write(e+',')
f.write('};\n')
f.write('const uint16_t xval[] PROGMEM = {')
for e in x:
    f.write(e+',')
f.write('};\n')
f.write('const uint16_t yval[] PROGMEM = {')
for e in y:
    f.write(e+',')
f.write('};\n')
f.close()
