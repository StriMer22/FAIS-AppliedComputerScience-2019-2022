def Caption(img):
    font_size = 0.1 * img.height
    tx_lay = pdb.gimp_text_layer_new(img, img.filename.split("\\")[-1], "Arial", font_size, 0)
    img.add_layer(tx_lay, 0)
    pdb.gimp_layer_set_offsets(tx_lay, 0, img.height - font_size)
    pdb.gimp_text_layer_set_color(tx_lay, (255, 255, 255, 1.0))

if '__main__' in __name__:
    img = gimp.image_list()[0]
    Caption(img)

