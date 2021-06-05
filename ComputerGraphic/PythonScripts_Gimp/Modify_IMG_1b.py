 def BriConAll(img, b, c):
        for layer in img.layers:
            pdb.gimp_drawable_brightness_contrast(layer, b, c)


if '__main__' in __name__:
    img = gimp.image_list()[0]
    BriConAll(img, 0.3, 0.2)
