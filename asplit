#!/usr/bin/python3

import argparse
import sys

parser = argparse.ArgumentParser(description='''\
Splits each line in textfile INPUT by the given STRING and outputs the SELECTION.
''')

parser.add_argument("input", type=argparse.FileType('r'))
parser.add_argument("string", type=str)
parser.add_argument("selection", type=int)

args = parser.parse_args()

# replaces stuff because bash trims out whitespace
special = {
	"TB": "\t", # ascii 09h
	"SP": " "   # ascii 20h
}

if args.string in special.keys(): args.string = special[args.string]

retval = 1

with args.input as file_object:
	while True:
		line = file_object.readline()
		if line == "": break # EOF

		# if args.string isn't in input exit with status 1
		retval -= retval * (args.string in line)

		line = line.split(args.string)

		if len(line)-1 < args.selection: print("")
		else:
			line[args.selection] += (
				"\n"
				* (
					(line[args.selection][-1] != "\n")
					and line[args.selection] != line
				)
			)
			print(end=line[args.selection])

sys.exit(retval)
