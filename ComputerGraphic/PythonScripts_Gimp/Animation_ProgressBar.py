from gimpfu import *


def createGif(img):
    pdb.gimp_convert_indexed(img, 1, 0, 64, False, False, "")
    pdb.file_gif_save(img, pdb.gimp_image_get_active_drawable(img), "D:/progressBar.gif", "D:/progressBar.gif", True, 1, 100, 0)


def newImg(width, height):
    return pdb.gimp_image_new(width, height, 0)


def progressBar(Image, colorBackground, colorPoint):
    pdb.gimp_context_set_background(colorBackground)
    pdb.gimp_image_get_selection(Image)
    pdb.gimp_context_set_foreground(colorPoint)
    Image.add_layer(pdb.gimp_layer_new(Image, pdb.gimp_image_width(Image), pdb.gimp_image_height(Image), 1, 'progressBar', 100, 1)) 
    pdb.gimp_drawable_edit_fill(pdb.gimp_image_get_active_layer(Image), 0)

    x = 0

    while x < gimp.pdb.gimp_image_width(Image):
        Image.add_layer(pdb.gimp_layer_new(Image, pdb.gimp_image_width(Image), pdb.gimp_image_height(Image), 1, 'progressPoint', 100, 1))
        gimp.pdb.gimp_image_select_rectangle(Image, 2, x, 0, 25, pdb.gimp_image_height(Image))
        pdb.gimp_drawable_edit_fill(pdb.gimp_image_get_active_layer(Image), 1)
        x += 25


image = newImg(500, 100)
progressBar(image, "red", "blue")
pdb.gimp_display_new(image)
createGif(image)
