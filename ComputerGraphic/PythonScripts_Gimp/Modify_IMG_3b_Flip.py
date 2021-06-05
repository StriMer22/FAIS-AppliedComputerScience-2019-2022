def FlipVertical(img):
    pdb.gimp_image_flip(img, ORIENTATION_VERTICAL)

if '__main__' in __name__:
    img = gimp.image_list()[0]
    FlipVertical(img)
