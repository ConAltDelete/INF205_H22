# -*- coding: utf-8 -*-
"""
Course : DAT300 - h2021

Simple script to read a .json parameter file.
The script must be run from a terminal window
"""
import argparse
import json


ap = argparse.ArgumentParser()
ap.add_argument("parameter_file")
ap.add_argument("output_dir")
args = vars(ap.parse_args())
parameter_file = args["parameter_file"]
output_dir = args["output_dir"]


def read_params(filename):
    with open(filename, 'r') as infile:
        d = json.load(infile)
    return d

parameter_dict = read_params(parameter_file)
print("Success!")
print(parameter_dict)