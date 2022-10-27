import findNoN
import matplotlib.pyplot as plt
import Outsu_sceleton as OST

pic = plt.imread("./grey_pic_2.tiff")

gray_img = [[pic[y][x][0] for x in range(len(pic[0]))] for y in range(len(pic))]

#H_L = [
#        [-1,-1,-1],
#        [-1,8,-1],
#        [-1,-1,-1]
#    ]

#Laplace = findNoN.apply_filter(gray_img,H_L)

binary = findNoN.Closeing(OST.threshold(gray_img),findNoN.circle_mask(5))

binary = [[int(binary[y][x] > 0) for x in range(len(binary[0]))] for y in range(len(binary))]

binary = findNoN.conv2dict(binary)

contour_pic = findNoN.contour(binary)

filled_binary = dict()

labels_taken = []

for C in contour_pic:
    if contor_pic[C][1] in labels_taken:
        continue
    fetched_label = {(x,y):contour_pic[(x,y)] for x,y in contour_pic if contour_pic[(x,y)][1] == countour_pic[C][1]}

    avg_coord = findNoN.average_coord(fetched_label)
    
    blob = findNoN.fillHoles(avg_coord,fetched_label)

    filled_binary.update(blob)

    labels_taken.push(contour_pic[C][1])



plt.imshow(filled_binary,cmap="gray")
plt.show()
