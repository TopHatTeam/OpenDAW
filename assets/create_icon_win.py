# ----------------------------------------------
#  OpenDAW Project  
# 
#  Description:
#  This python script is used to create an icon file for the OpenDAW Application on Windows
# ----------------------------------------------

import os 
import subprocess

def create_icon():
    icon_path = "opendaw_ico/opendaw.ico"
    icon_array = [
        "od_icon_16x16.png", "od_icon_24x24.png",
        "od_icon_32x32.png", "od_icon_48x48.png",
        "od_icon_256x256.png"
    ]

    if not os.path.exists(icon_path):
        print(f"Icon file {icon_path} does not exist")
        print("Creating a new directory for icons...")
        os.makedirs("opendaw_ico", exist_ok=True)
        os.chdir("final")
        command = "icotool -c -o logo.ico " + " ".join(icon_array)
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        print(result.stdout)
        if result.returncode != 0:
            print(f"Error creating icon: {result.stderr}")
            print(" ")
            print("Likely issue: ")
            print("1. You ran this command on a UNIX-based Operating System")
            print("2. You're missing icotools which need to be installed")
            print(" ")
            print("How do to fix the issue(s): ")
            print("1. If you're running MacOS run the specific python script, 'create_icon_mac.py'")
        else:
            print(f"Icon created successfully at {icon_path}")
    else: 
        print(f"Icon file {icon_path} already exists. No action taken.")
    


create_icon()  
