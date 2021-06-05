def FlipHorizontal(img):
    pdb.gimp_image_flip(img, ORIENTATION_HORIZONTAL)

if '__main__' in __name__:
    img = gimp.image_list()[0]
    FlipHorizontal(img)

