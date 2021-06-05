from gimpfu import *
from gimpenus import *
import colorsys

def newImg(width, height):
    image = pdb.gimp_image_new(width, height, 0)
    pdb.gimp_display_new(image)
    return image.new_layer()

def fillRect(img, x, y, wid, hig, color):
    temporary = pdb.gimp_image_get_active_layer(img)
    foreground = pdb.gimp_context_get_foreground()
    pdb.gimp_context_set_foreground(color)
    img.new_layer("Rectangle")
    pdb.gimp_image_select_rectangle(img, 0, x, y, wid, hig)
    pdb.gimp_edit_fill(pdb.gimp_image_get_active_layer(img), 0)
    pdb.gimp_context_set_foreground(foreground)
    pdb.gimp_image_set_active_layer(img, temporary)
    pdb.gimp_selection_none(img)

def FillCirc(Img, x, y, r, color):
    temporary = pdb.gimp_image_get_active_layer(Img)
    foreground = pdb.gimp_context_get_foreground()
    pdb.gimp_context_set_foreground(color)
    Img.new_layer("Circle")
    pdb.gimp_image_select_ellipse(Img, 0, x, y, r, r)
    pdb.gimp_edit_fill(pdb.gimp_image_get_active_drawable(Img), 0)
    pdb.gimp_context_set_foreground(foreground)
    pdb.gimp_image_set_active_layer(Img, temporary)
    pdb.gimp_selection_none(Img)

def checkerboard(Img, sat=0.0, hue=0.0):
    drawable = pdb.gimp_image_get_active_drawable(Img)
