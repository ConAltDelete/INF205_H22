import sys
import matplotlib.pyplot as plt
import Outsu_sceleton as OST
from math import atan,sin,cos

def moore_neighborhood(P,pre_cell):
    """
    p = (x,y), pre_cell = (x,y)
    """
    print("moore_neighborhood")
    MN = [(P[0]+x,P[1]+y) for x,y in [(-1, -1), (-1, 0), (-1, 1),(0, 1), (1, 1), (1, 0), (1, -1), (0, -1)]]
    MN_length = len(MN)
    start_clock = MN.index((pre_cell[0],pre_cell[1]))
    cell_array = MN[start_clock:] + MN[:start_clock]
    return cell_array



def contour_blob(I,X,label):
    """
        X er start koordinatet, I er (x,y):(V,label)
        return {(x,y):(V,label)}
    """
    print("contour_blob")
    B = {tuple(X):(I[X],label)}
    p = (X[0],X[1])
    s = X
    pre_cell = (p[0]-1,p[1])

    M = moore_neighborhood
    current_M = M(p,pre_cell)
    
    current_M.pop(0) # removes the pre_cell
    c = current_M.pop(0)
    while c != s:
        if I[c][0]:
            B.update({tuple(c):(I[c][0],label)})
            p = tuple(c)
            current_M = M(p,pre_cell)
            current_M.pop(0)
        
        pre_cell = tuple(c)
        if len(current_M) != 0:
            c = current_M.pop(0)
        else:
            break

    return B

def contour(I):
    """
        I is a binary image with 0 and 1, where 0 is the background
        returns {(x,y),(V,label)}
    """
    print("contour")
    label = 2

    contours = dict() # (x,y):(V,label)

    current_pix = [0,0] 

    max_coord = list(max(I, key= lambda P: P[0]**2+P[1]**2))
    max_coord[0] += 1 # to set it inside the margent

    while current_pix != max_coord:
            row = current_pix[0]
            col = current_pix[1]

            if I[tuple(current_pix)][0] and ((col,row) not in contours):
                contours.update(contour_blob(I,(col,row),label))
                label += 1
                current_pix = max([[x,y] for x,y in contours if (contours[(x,y)][1] == contours[(col,row)][1]) and (y == row)],key= lambda P: P[0])
                current_pix[0] += 1

            elif (col,row) in contours:
                current_pix = max([[x,y] for x,y in contours if (contours[(x,y)][1] == contours[(col,row)][1]) and (y==row)],key= lambda P: P[0])
                current_pix[0] += 1

            current_pix[0] += 1
            if current_pix[0] >= max_coord[0]:
                current_pix[0] = 0
                current_pix[1] += 1
    return contours

def euclid_dist_point(I,X):
    """
        I = {(x,y):(V,label)}
        X = (x,y)
    """
    print("euclid_dist_point")
    min_dist = X[0]**2+X[1]**2
    for Y in I:
        calc = (X[0]-Y[0])**2 + (X[1]-Y[1])**2
        if calc < min_dist:
            min_dist = calc
    return min_dist

def euclid_dist_map(M,I):
    """
        I = {(x,y):(V,label)}, M = {(x,y):(V,label)}
    """
    print("euclid_dist_map")
    labels_taken = []

    e_dist_map = dict()
    
    current_pix = [0,0]

    max_width = max(M,key = lambda P: M[P][0])

    max_coord = list(max(M,key = lambda P: P[0]**2+P[1]**2))
    max_coord[0] += 1

    while current_pix != max_coord:
        if tuple(current_pix) not in M:
            continue
        if (I[tuple(current_pix)][1] not in labels_taken):
            current_label = I[tuple(current_pix)][1]
            labels_taken.push(current_label)
            border_for_label = {p:I[p] for p in I if I[p][1] == current_label}
            pix_seed = tuple(current_pix)
            for P in (i for i in moore_neighborhood(pix_seed,(pix_seed[0]+1,pix_seed)) if i not in border_for_label): # henter piksel inni contour, ellers så vil bakgrunnen bli "fyllt" istedet.
                if contained(P,border_for_label):
                    pix_seed = P
                    break
            updated_I = b_floodfill(border_for_label,pix_seed,current_label,euclid_dist_point)
            e_dist_map.update(updated_I)

        elif I[tupel(current_pix)][1] in labels_taken:
                current_pix = max([[x,y] for x,y in I if (I[(x,y)][1] == I[(col,row)][1]) and (y == current_pix[1])],key= lambda P: P[0])
                current_pix[0] += 1

        current_pix[0] += 1
        if current_pix[0] > max_width:
            current_pix[0] = 0
            current_pix[1] += 1
    return e_dist_map

def list2dict(M):
    """
        M = [[V]]
        return {(x,y):(V,label)}
    """
    print("list2dict")
    I = dict()

    for row in range(len(M)):
        for col in range(len(M[0])):
            if M[row][col] == 0:
                continue
            I[(col,row)] = (M[row][col],0)
    return I

def b_floodfill(I,X,label,f):
    """
        I is all points on boarder, f(I,p)
    """
    print("b_floodfill")
    S = []
    S.push(X)
    new_I = dict(I)
    while len(S) != 0:
        p = S.pop()
        if p not in I: # figure something out...
            new_I[p] = (f(I,p),label)
            S.push((p[0]+1,p[1]))
            S.push((p[0],p[1]+1))
            S.push((p[0]-1,p[1]))
            S.push((p[0],p[1]-1))
    return new_I

def fillHoles(I,X):
    """
        seed X = (x,y), I = {(x,y),(V,label)} for boarder
    """
    print("fillHoles")
    blob = dict(I)
    s = []
    s.push(X)
    while len(S) != 0:
        p = S.pop()
        if p not in I: # figure something out...
            blob[p] = (1,label)
            S.push((p[0]+1,p[1]))
            S.push((p[0],p[1]+1))
            S.push((p[0]-1,p[1]))
            S.push((p[0],p[1]-1))
    return blob

def contained(X,I):
    """
        I, contour, {(x,y):(V,label)}
        X, point, (x,y)
    """
    print("contained") 
    i = j = len(I)-1
    
    polyX,ployY = [],[]
    
    for P in I:
        polyX.append(P[0])
        polyY.append(P[1])

    odd_nodes = False

    for i in range(len(I)):
        if ((ployY[i] < X[1]) and (polyY[j] >= X[1])) or ( (ployY[j] < X[1]) and (polyY[i] >= y) ):
            if (polyX[i] + (y-polyY[i])/(polyY[j]-polyY[i]) * (polyX[j]-polyX[i])) < X[0]:
                odd_nodes = not(add_nodes)
        j = i
    return odd_nodes

def maxima_check(I,X):
    """
    I = {(x,y):(V,label)}, X = (x,y)
    """
    print("maxima_check")
    pix_next = [(X[0] + x,X[1] + y,I[(X[0] + x,X[1] + y)] if (X[0] + x,X[1] + y) in I else 0) for x in range(-1,1) for y in range(-1,1) if not((x == 0) and (y==0))]
    return I[X] >= max(pix_next,key = lambda P: P[2])

def find_maximas(M):
    """
        M = {(x,y):(V,label)}
    """
    print("find_maximas")
    maximas = dict()
    for P in M:
        if maxima_check(M,P):
            maximas.update(P)
    
    return maximas

def watershed(I):
    """
        I = {(x,y):(V,label)}
    """
    print("watershed")
    segments = dict(I)
    
    segments_contours = contour(segments)

    segments_maximums = find_maximas(segments_contours)

    segments = euclid_dist_map(segments,segments_maximum)

    return segments


def average_coord(coords):
    """
        coords er {(x,y):(V,label)}
    """
    print("average_coord")
    x = 0
    y = 0
    length = 0
    i = 1
    for P in coords:
        x += (P[0]-x)/i
        y += (P[1]-y)/i
        i += 1

    return (x,y)

def central_moment(coords,p,q):
    """
        mu_pq(I), coord = {(x,y):(V,label)}
    """
    print("central_moment")
    x,y = average_coords(coords)

    my = 0

    for Y in coords:
        for YX in Y:
          my += YX[2]* (YX[0]-x)**p * (YX[1]-y)**q

    return my

def find_axis(I):
    """
        Let I be a set of points for a area., I = (x,y,V)
    """
    print("find_axis")
    mu20 = central_moment(I,2,0)
    mu02 = central_moment(I,0,2)
    mu11 = central_moment(I,1,1)

    r_a = ((mu20+mu02+((mu20 - mu02)**2 + 4*mu11**2)**0.5)/(len(I[0])*len(I)))**0.5
    r_b = ((mu20+mu02-((mu20 - mu02)**2 + 4*mu11**2)**0.5)/(len(I[0])*len(I)))**0.5
    teta = 0.5*atan((2*mu11)/(mu20-mu02))

    return (min(r_a,r_b),max(r_a,r_b),teta)

def para_ellips(x,y,ra,rb,theta):
    print("para_ellips")
    return lambda t: (x+cos(theta)*ra*cos(t)-sin(theta)*rb*sin(t),y+sin(theta)*ra*cos(theta)+cos(theta)*rb*sin(t))

def Invert(I,max_int=255):
    """
    I er binert
    """
    print("Invert")
    length = len(I)
    width = len(I[0])
    new_I = [[max_int*int(not(I[r][c])) for c in range(width)] for r in range(length)]
    return new_I

def Reflect(I):
    print("Reflect")
    length = len(I)
    width = len(I[0])
    new_I = [[I[w][l] for w in range(width)] for l in range(length)]
    
    return new_I

def conv2list(H,width,hight):
    """
    H = {(x,y):(V,label)}
    """
    print("conv2list")
    img = [[0 for x in range(width)] for y in range(hight)]

    for P in H:
        img[y][x] = H[P][0]

    return img

def conv2dict(H):
    print("conv2dict")
    mid_x = int((len(H)-1)/2)
    mid_y = int((len(H[0])-1)/2)

    dic_H = dict()

    for r in range(len(H)):
        for c in range(len(H[0])):
            dic_H[(r - mid_x,c - mid_y)] = (H[r][c],0)
    return dic_H

def Dilate(I,H,max_int=255):
    """
        H er oddetall i lengde og bredde med (0,0) i middle.
        I er binært bilde.
    """
    print("Dilate")
    length = len(I)
    width = len(I[0])
    new_I = [[0 for _ in range(width)] for _ in range(length)]
    
    H_dict = conv2dict(H)

    for H_value in H_dict:
        if not(H_dict[H_value]):
            continue
        for row in range(length):
            for col in range(width):
                if I[row][col] != max_int:
                    continue
                if ((row + H_value[0]) >= length) or ((col + H_value[1]) >= width):
                    continue
                if ((row + H_value[0]) < 0) or ((col + H_value[1]) < 0):
                    continue
                new_I[row + H_value[0]][col + H_value[1]] = max_int

    return new_I

def apply_filter(I,H):
    print("apply_filter")
    length = len(I)
    width  = len(I[0])
    scale_down = 1/sum([sum([abs(b) for b in a]) for a in H])
    new_img = [[0 for c in range(width)] for r in range(length) ]

    H_dict = conv2dict(H)
    
    for row in range(length):
        for col in range(width):
            temp_sum = 0
            for val in H_dict:
                if H_dict[val] == 0:
                    continue
                trans_index_x = col + val[0]
                trans_index_y = row + val[1]
                if (trans_index_x >= width) or (trans_index_x < 0) or (trans_index_y >= length) or (trans_index_y < 0):
                    continue
                temp_sum += max(H_dict[val]*I[trans_index_y][trans_index_x],0)
            new_img[row][col] = int(scale_down*temp_sum)
    return new_img


def Erodion(I,H,max_int=255):
    print("Erodion")
    I_inv = Invert(I,max_int)
    H_ref = Reflect(H)
    new_I = Invert(Dilate(I_inv,H_ref,max_int))
    return new_I

def Opening(I,H,max_int=255):
    print("Opening")
    return Dilate(Erodion(I,H,max_int),H,max_int)

def Closeing(I,H,max_int=255):
    print("Closeing")
    return Erodion(Dilate(I,H,max_int),H,max_int)

def colour2grayscale(red,green,blue):
    return int(min(red,green,blue))

def gradient2D(I, angle = False, max_int = 255):
    """
        I is a gray scale image.
    """
    print("gradient2D")
    x_axis = [
                [-1, 0, 1],
                [-2, 0, 2],
                [-1, 0, 1]
            ]
    y_axis = [
                [-1,-2,-1],
                [ 0, 0, 0],
                [ 1, 2, 1]
            ]

    x_axis_img = apply_filter(I,x_axis)
    y_axis_img = apply_filter(I,y_axis)

    grad_map = [[0 for x in range(len(I[0]))] for y in range(len(I))]

    for row in zip(x_axis_img,y_axis_img,range(len(I))):
        for col in zip(row[0],row[1],range(len(I[0]))):
            if angle:
                grad_map[row[2]][col[2]] = ((col[0]**2 + col[1]**2)**0.5, atan(col[1]/col[0]))
            else:
                grad_map[row[2]][col[2]] = (col[0]**2 + col[1]**2)**0.5

    return grad_map

def grayscale_img(img):
    print("grayscale_img")
    length = len(img)
    width = len(img[0])
    
    new_img = [[0 for x in range(width)] for y in range(length) ]

    for row in range(length):
        for v in range(width):
            new_img[row][v] = colour2grayscale(img[row,v,0],img[row,v,1],img[row,v,2])
        
    return new_img

def circle_mask(r):
    print("circle_mask")
    mask = [[ int(((x - r)**2 + (y - r)**2)**0.5 <= r) for x in range(int(2*r +1))] for y in range(int(2*r +1))]
    return mask

if __name__ == "__main__":
    pic = sys.argv[1:]

    if len(pic) > 1: 
        raise ValueError("This program takes only one file")

    pic = plt.imread(pic[0])[500:3450,200:5100]
    print(len(pic),len(pic[0]))
    print("calcs colours")
    gray_pic_all = grayscale_img(pic)
    #red_pic   = []
    #green_pic = []
    #blue_pic  = []
    #max_vals = []
    #for y in range(len(pic)):
    #    red_row = []
    #    green_row = []
    #    blue_row = []
    #    for x in range(len(pic[0])):
    #        pixel = pic[y][x]
    #        red_row.append(pixel[0])
    #        green_row.append(pixel[1])
    #        blue_row.append(pixel[2])
    #    red_pic.append(red_row)
    #    green_pic.append(green_row)
    #    blue_pic.append(blue_row)

    #grad_red_pic = gradient2D(red_pic)
    #grad_green_pic = gradient2D(green_pic)
    #grad_blue_pic = gradient2D(blue_pic)
    #grad_gray_pic = gradient2D(gray_pic_all)
    
    #grey_pic = [[max(int(grad_red_pic[y][x]),int(grad_green_pic[y][x]),int(grad_blue_pic[y][x]),int(grad_gray_pic[y][x])) for x in range(len(pic[0]))] for y in range(len(pic))]#grayscale_img(pic)
    #print("Outsu thresholding...")
    
    #grad_map = gradient2D(grey_pic)
    bin_grad = OST.threshold(gray_pic_all) #,25)
    #print("outsu: Done")


    #inv_bin = Invert(bin_pic)

    H = circle_mask(4)
    for row in H:
        print(row)
    

    #bin_grad = Opening(bin_grad,H)
    
    close_inv_bin = bin_grad

    for _ in range(5):
        close_inv_bin = Erodion(close_inv_bin,H)

    for _ in range(5):
        close_inv_bin = Dilate(close_inv_bin,H)
    
    #dic_pic = conv2dict(bin_grad)

    #for P in dic_pic:
    #    dic_pic[P][0] = int(dic_pic[P][0] > 0)
    
    #watershed_pic = watershed(dic_pic)


    #plt.imsave("./watershed.tiff",conv2list(watershed_pic,len(pic[0]),len(pic)), cmap="gray")
    plt.imsave("./cleaning_pic.jpeg",close_inv_bin, cmap="gray")
    #plt.imshow(bin_grad, cmap="gray")
    #plt.show()

