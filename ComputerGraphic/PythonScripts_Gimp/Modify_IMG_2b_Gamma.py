def GammaCurrent(img, gamma):
    for layer in img.layers:
            pdb.gimp_drawable_levels(layer, 0, 0, 1, 0, gamma, 0, 1, 0)

if '__main__' in __name__:
    img = gimp.image_list()[0]
    GammaCurrent(img, 2.0)
