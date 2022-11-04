# -*- coding: utf-8 -*-
"""
Title: Simple MNIST convnet
Author: [fchollet](https://twitter.com/fchollet)
Date created: 2015/06/19
Last modified: 2020/04/21
Description: A simple convnet that achieves ~99% test accuracy on MNIST.

Modified for DAT300 - h2021.

NB! This script must be run from a terminal window.
"""


import numpy as np
import pandas as pd
import tensorflow as tf
from tensorflow.keras import layers, optimizers
import time
import argparse
import json


# Start timer
tic = time.time()

# NEW STUFF
#=============================================================================
def read_json(filename):
    with open(filename, 'r') as infile:
        d = json.load(infile)
    return d

# Handling the arguments passed to python
ap = argparse.ArgumentParser()
ap.add_argument("experiment_dir")
args = vars(ap.parse_args())

parameter_file = f"{args['experiment_dir']}/params.json"
parameter_dict = read_json(parameter_file)

#data_path = "data"
#dropout_rate = 0.3
#learning_rate = 0.001
#batch_size = 256
#epochs = 3
#model_name = "mnist_model"
#output_dir = "results" # Where the results should be saved

data_path = parameter_dict["data_path"]
dropout_rate = parameter_dict["dropout_rate"]
learning_rate = parameter_dict["learning_rate"]
batch_size = parameter_dict["batch_size"]
epochs = parameter_dict["epochs"]
model_name = parameter_dict["model_name"]

output_dir = args["experiment_dir"] # Where the results should be saved

#=============================================================================

#=================
# Prepare the data
#=================
num_classes = 10
input_shape = (28, 28, 1)

# Load the data, split between train and test sets
x_train = np.load(f"{data_path}/x_train.npy")
y_train = np.load(f"{data_path}/labels.npy")
x_test = np.load(f"{data_path}/x_test.npy")

# Scale images to the [0, 1] range
x_train = x_train.astype("float32") / 255
x_test = x_test.astype("float32") / 255
# Make sure images have shape (28, 28, 1)
x_train = np.expand_dims(x_train, -1)
x_test = np.expand_dims(x_test, -1)
print("x_train shape:", x_train.shape)
print("Number of train samples: ", x_train.shape[0])
print("Number of test samples: ", x_test.shape[0])

# convert class vectors to binary class matrices (one-hot encoding)
y_train = tf.keras.utils.to_categorical(y_train, num_classes)

#=================
## Build the model
#=================
model = tf.keras.Sequential(
    [
        tf.keras.Input(shape=input_shape),
        layers.Conv2D(32, kernel_size=(3, 3), activation="relu"),
        layers.MaxPooling2D(pool_size=(2, 2)),
        layers.Conv2D(64, kernel_size=(3, 3), activation="relu"),
        layers.MaxPooling2D(pool_size=(2, 2)),
        layers.Flatten(),
        layers.Dropout(dropout_rate),
        layers.Dense(num_classes, activation="softmax"),
    ]
)

model.summary()

#=================
# Train the model
#=================

model.compile(
    loss="categorical_crossentropy",
    optimizer=optimizers.Adam(learning_rate),
    metrics=["accuracy"]
)

history = model.fit(
    x_train,
    y_train,
    epochs=epochs,
    batch_size=batch_size,
    verbose=0,
    validation_split=0.1
)

train_score = model.evaluate(x_train, y_train, verbose=0)
print(f"Train loss: {train_score[0]:.3f}")
print(f"Train accuracy: {train_score[1]:.3f}")

#================
# Make prediction
#================
y_pred = np.argmax(model.predict(x_test, verbose=0), axis=1) 

#=============
# Save results
#=============

model.save(f"{output_dir}/{model_name}.h5")

# Save Losses
df = pd.DataFrame({"loss": history.history["loss"],
                   "accuracy": history.history["accuracy"],
                   "val_loss": history.history["val_loss"],
                   "val_accuracy": history.history["accuracy"]})
df.to_csv(f"{output_dir}/losses.csv", index=False)

# Save prediction file to submit to kaggle
df_pred = pd.DataFrame({"id": np.arange(len(y_pred)), "label": y_pred})
df_pred.to_csv(f"{output_dir}/ypred.csv", index=False, header=True)

toc = time.time()
print(f"Done in {(toc - tic):.1f} seconds")
