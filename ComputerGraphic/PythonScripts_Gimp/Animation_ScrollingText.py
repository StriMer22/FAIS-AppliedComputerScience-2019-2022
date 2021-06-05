#!/usr/bin/env python
# -*- coding: utf-8 -*-

from gimpfu import *


def createGif(img):
    pdb.gimp_convert_indexed(img, 1, 0, 64, False, False, "")
    pdb.file_gif_save(img, pdb.gimp_image_get_active_drawable(img), "D:/scrollingText.gif", "D:/scrollingText.gif", True, 1,
                      100, 0)


def newImg(width, height):
    return pdb.gimp_image_new(width, height, 0)


def scrollingText(img, frames, txt, font, color, bg_color):
    for i in range(frames + 27):
        img.new_layer("Layer")
        background = pdb.gimp_image_get_active_drawable(img)
        pdb.gimp_context_set_foreground(bg_color)
        pdb.gimp_edit_fill(background, 0)
        textLay = pdb.gimp_text_layer_new(img, txt, font, img.height * 0.8, 0)
        img.add_layer(textLay, 0)
        pdb.gimp_layer_set_offsets(textLay, -i * 25, img.height * 0.1)
        pdb.gimp_text_layer_set_color(textLay, color)
        textLay2 = pdb.gimp_text_layer_new(img, txt, font, img.height * 0.8, 0)
        img.add_layer(textLay2, 0)
        pdb.gimp_layer_set_offsets(textLay2, -i * 25 + textLay.width, img.height * 0.1)
        pdb.gimp_text_layer_set_color(textLay2, color)
        pdb.gimp_image_merge_down(img, img.layers[1], 0)
        pdb.gimp_image_merge_down(img, img.layers[0], 0)


image = newImg(600, 200)
scrollingText(image, 30, u"Przewijający się tekst.", "Calibri", "red", "white")
pdb.gimp_display_new(image)
createGif(image)
