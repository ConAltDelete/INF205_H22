# -*- coding: utf-8 -*-
"""
Course : DAT300 - h2021

Script to create a json parameter file
"""

import json


def create_file():
    """Define parameters in a dictionary and save them to a json-file"""
    parameters = dict(
            data_path="data",
            dropout_rate=0.5,
            learning_rate=0.0001,
            batch_size=256,
            epochs=3,
            model_name="mnist_model"
    )
    # Save the json file
    with open('params.json', 'w') as outfile:
        json.dump(parameters, outfile)
    

if __name__ == "__main__":
    create_file()