# -*- coding:utf-8 -*-

import os
import sys
import shutil
import pck_msg
import zipfile
from config import  *
from path_util import  *

cmd_path =os.path.join(NewROOT_PATH,'game_client')
bin_path = os.path.join(NewROOT_PATH,'game_client\\bin-release\\web')
jsZipPath = os.path.join(TOOL_PATH,'scripts/jszip.min.js')


def egretBuild():
    os.chdir(cmd_path)
    os.system('egret build game_client -e')
    print("\nPlease Enter The Version Number:")
    version = input()
    os.system('egret publish game_client --version '+str(version))

    new_versionpath = os.path.join(bin_path,str(version))
    newjsZipPath = os.path.join(new_versionpath,'jszip.min.js')

    shutil.copyfileobj(open(jsZipPath, 'r'), open(newjsZipPath, 'w'))

    jsfiles_path = os.path.join(new_versionpath,'js')

    compress(jsfiles_path,os.path.join(new_versionpath,"main.min.js.zip"))
    compress(jsfiles_path,os.path.join(new_versionpath,"egret.zip"))
    rename(new_versionpath,'.zip','.cfg')

def compress(get_files_path, set_files_path):
    f = zipfile.ZipFile(set_files_path , 'w', zipfile.ZIP_DEFLATED )
    for dirpath, dirnames, filenames in os.walk( get_files_path ):
        fpath = dirpath.replace(get_files_path,'') #注意2
        fpath = fpath and fpath + os.sep or ''     #注意2
        for filename in filenames:
            if 'main.min.js.zip' in set_files_path:
                if 'main' in filename:
                    f.write(os.path.join(dirpath, filename), fpath + filename)
            else:
                if 'main' not in filename:
                    f.write(os.path.join(dirpath, filename), fpath + filename)

    f.close()

def rename(set_files_path,change_file_type,type):
    for (path, dirs, files) in os.walk(set_files_path):
        for filename in files:
            ext= os.path.splitext(filename)[1]#取得文件类型，注意它还带着点号
            if(ext== change_file_type):
                print "----------------"
                newname= filename.replace(change_file_type, type)
                oldpath= path+ "\\" + filename
                newpath= path+ "\\" + newname
                try:
                    os.rename(oldpath, newpath)
                    print('rename success ',newpath)
                except BaseException, e:
                   print(str(e))


if __name__ == '__main__':
    egretBuild()
    exit()