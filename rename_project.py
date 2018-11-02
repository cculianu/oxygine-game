#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys

def replace_data(str, src, dest):
    str = str.replace(src, dest)
    return str

def rename_item(path, src, dest):

    left, right = os.path.split(path)
    right = replace_data(right, src, dest)
    new_name = os.path.join(left, right)
    if path != new_name:
        os.rename(path, new_name)
        print("renaming\n  {}\n  -> {} ".format(path, new_name))

def process_file(path, src, dest):


    try:
        with open(path, "rb") as fp:
            data = fp.read()

        data = data.decode('utf-8')
        data = replace_data(data, src, dest)
        data = data.encode('utf-8')

        with open(path, "wb") as fp:
            fp.write(data)

    except:
        pass



    rename_item(path, src, dest)


def process_dir(path, src, dest):	
    items = os.listdir(path)
    for item in items:
        pt = os.path.join(path, item)
        if os.path.isdir(pt):
            process_dir(pt, src, dest)
        else:
            process_file(pt, src, dest)

    rename_item(path, src, dest)



if __name__ == "__main__":	
    new_name = sys.argv[1]
    #tool automatically renames all files/folders/data to <new_name>
    process_dir("my_awesome_game", "my_awesome_game", new_name)
    process_file(".gitignore", "my_awesome_game", new_name)

