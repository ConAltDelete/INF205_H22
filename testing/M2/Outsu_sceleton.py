# -*- coding: utf-8 -*-

"""
Skeleton for first part of the blob-detection coursework as part of INF250
at NMBU (Autumn 2017).
"""

__author__ = "Yngve Mardal Moe"
__email__ = "yngve.m.moe@gmail.com"

import numpy as np
import matplotlib.pyplot as plt

def threshold(image, th=None):
    """Returns a binarised version of given image, thresholded at given value.

    Binarises the image using a global threshold `th`. Uses Otsu's method
    to find optimal thrshold value if the threshold variable is None. The
    returned image will be in the form of an 8-bit unsigned integer array
    with 255 as white and 0 as black.

    Parameters:
    -----------
    image : np.ndarray
        Image to binarise. If this image is a colour image then the last
        dimension will be the colour value (as RGB values).
    th : numeric
        Threshold value. Uses Otsu's method if this variable is None.

    Returns:
    --------
    binarised : np.ndarray(dtype=np.uint8)
        Image where all pixel values are either 0 or 255.
    """
    # Setup
    shape = np.shape(image)
    binarised = np.zeros([shape[0], shape[1]], dtype=np.uint8)

    if len(shape) == 3:
        image = image.mean(axis=2)
    elif len(shape) > 3:
        raise ValueError('Must be at 2D image')

    if th is None:
        th = otsu(image)
    # Start thresholding
    
    #for row in range(len(image)):
    #    for element in range(len(image[row])):
    #        binarised[row][element] = 255*(image[row][element]>=th)
    
    binarised = [[255*(image[row][element]>=th) for element in range(len(image[row]))]for row in range(len(image))]

    return binarised

def histogram(image):
    """Returns the image histogram with 256 bins.
    """
    # Setup
    shape = np.shape(image)
    histogram = np.zeros(256)

    if len(shape) == 3:
        image = image.mean(axis=2)
    elif len(shape) > 3:
        raise ValueError('Must be at 2D image')

    # Start to make the histogram

    for row in range(len(image)):
        for element in range(len(image[row])):
            wot = int(image[row][element])
            histogram[wot] += 1

    return histogram

def otsu(image):
    """Finds the optimal thresholdvalue of given image using Otsu's method.
    """
    hist = histogram(image)
    th = 0
    cum_hist = [0 for i in range(len(hist))]
    cum_hist[0] = hist[0]

    for i in range(1,len(hist)):
        cum_hist[i] = hist[i] + cum_hist[i-1]


    ## WRITE YOUR CODE HERE
    levels = range(256)

    sum_values = cum_hist[-1]

    t_vals = dict()

    for t in range(len(levels)):

        lower_sum = cum_hist[t]
        higher_sum = cum_hist[-1] - lower_sum


        if lower_sum == 0 or higher_sum == 0: # sanity check
            continue

        Wb=lower_sum/sum_values
        Wf=higher_sum/sum_values

        mean_b=sum([lev*hist[lev]  for lev in levels[:t+1]])/lower_sum
        mean_f=sum([lev*hist[lev]  for lev in levels[t+1:]])/higher_sum

        t_vals[t] = Wb*Wf*(mean_f-mean_b)**2

    th = max(t_vals, key=t_vals.get)
    return th


if __name__ == "__main__":
    img = plt.imread("bie_threshold.jpeg",format="jpeg")
    new_img = threshold(img)
    plt.imsave("biw_theshold_bin.jpeg",new_img,cmap="gray")
    plt.imshow(new_img,cmap="gray")
    plt.show()