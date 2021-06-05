def BriConCurrent(img, b, c):
    pdb.gimp_drawable_brightness_contrast(pdb.gimp_image_get_active_drawable(img) , b, c) 

if '__main__' in __name__:
    img = gimp.image_list()[0]
    BriConCurrent(img, 0.3, 0.2)
   
