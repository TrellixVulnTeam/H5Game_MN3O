# -*- coding:utf-8 -*-

import os
import shutil
from config import *
from path_util import *

def copy_res():
	dir = os.getcwd()
	os.chdir(ROOT_PATH)

	if not os.path.exists(DST_GAME_CONF_CODE_PATH):
		os.mkdir(DST_GAME_CONF_CODE_PATH)
	else:
		clear_folder_exclude_type(DST_GAME_CONF_CODE_PATH, ".svn")
	copy_folder_type(EXP_GAME_CONF_CODE_PATH, DST_GAME_CONF_CODE_PATH, ".cs")

	os.chdir(dir)

if __name__ == '__main__':
	print "copy configcode begin..."
	copy_res()
	print "copy configcode successful"