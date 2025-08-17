# ----------------------------------------------
#  OpenDAW Project  
# 
#  Description:
#  This python script is used to create an icon file for the OpenDAW Application on MacOS
# ----------------------------------------------

import os
import subprocess

def create_icon():
    icon_path = "opendaw.iconset/opendaw.icns"
    out_folder = "opendaw.iconset"
    icon_array = [
        "od_icon_16x16.png", "od_icon_32x32.png", "od_icon_32x32", "od_icon_64x64.png",
        "od_icon_128x128.png", "od_icon_256x256.png", "od_icon_256x256.png", "od_icon_512x512.png",
        "od_icon_512x512.png", "od_icon_1024x1024.png"
    ]
    size = [16, 32, 64, 128, 512, 1024]

    out_name = [
        "icon_16x16.png", "icon_16x16@2x.png", "icon_32x32.png", "icon_32x32@2.png",
        "icon_128x128.png", "icon_128x128@2.png", "icon_256x256.png", "icon_256x256@2.png"
        "icon_512x512.png", "icon_512x512@2.png"
    ]

    if not os.path.exists(icon_path):
        print(f"Icon file {icon_path} does not exist")
        print("Creating a new directory for icons...")
        os.makedirs(f"{out_folder}", exist_ok=True)
        for src, name in zip(icon_array, out_name):
            out_file = os.path.join(out_folder, name)
            subprocess.run(["sips", "-z", str(size), str(size), str(icon_array), "--out", out_file])
        icns_path = "opendaw.icns"
        subprocess.run(["iconutil", "-c", "icns", out_folder, "-o", icns_path])
        print(f"Created {icns_path}")
    else: 
        print("Icon already created")
            
        
create_icon()