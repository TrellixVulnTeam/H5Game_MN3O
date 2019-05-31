# -*- coding:utf-8 -*-
"""path config
"""

import os

#gobal path config
CWD = os.path.normpath(os.path.abspath(os.getcwd()))
ROOT_PATH = os.path.normpath(os.path.abspath(os.path.join(CWD, '../../')))
SRC_PATH = os.path.join(ROOT_PATH, 'src')
CONF_PATH = os.path.join(ROOT_PATH, '../../shared')
BIN_PATH = os.path.join(ROOT_PATH, 'bin')
RES_PATH = os.path.join(ROOT_PATH, '../res')

RES_GAME_CONF_PATH = os.path.join(RES_PATH, "game_conf")

#Author @sjz
SCHOOL_OLDPROTORISE = 'import "options.proto";'
SCHOOL_NEWPROTORISE = 'import "goole/protobuf/options.proto";'
SCHOOL_OLDPACKAGENAME = 'package pwngs.protocol.worldsrv;'
SCHOOL_NEWPACKAGENAME = 'package GeneralMes;'
NewROOT_PATH = os.path.normpath(os.path.abspath(os.path.join(CWD, '../../../../')))
NEW_SRC_PROJ_PATH = os.path.join(NewROOT_PATH,'game_client')

#RES_PROJECT_BUILD_PATH = os.path.join(RES_PATH,"project/
SRC_PROJ_PATH = os.path.join(ROOT_PATH, 'Assets')
SHARED_PWMSG_PATH = os.path.join(CONF_PATH,'pwmsg')

EXP_PATH = os.path.join(ROOT_PATH, '../..\game_client')
RES_PATH=os.path.join(ROOT_PATH, '..resource\config')


TOOL_PATH = os.path.join(ROOT_PATH, 'Tools')
PYTHON_TOOL_PATH = os.path.join(TOOL_PATH, 'py')
MAKO_PATH = os.path.join(PYTHON_TOOL_PATH, 'mako')

#res idx
TXT_IDX_EXT_NAME = ".txt_idx"
TXT_EXT_NAME = ".txt"
SCENE_BEGIN = "SCENE"
PREFAB_BEGIN = "PREFAB"
TEXTRUE_BEGIN = "TEXTURE"
TXT_BEGIN = "TXT"
XLS_EXT = ".xls"


#game conf
SRC_GAME_CONF_PATH = os.path.join(CONF_PATH, "config")
RES_GAME_CONF_FILE_PATH = os.path.join(RES_GAME_CONF_PATH, "Assets/conf")
EXP_GAME_CONF_CODE_PATH = os.path.join(EXP_PATH, "src\gamescripts\Config\configts")
EXP_GAME_CONF_BIN_PATH = os.path.join(EXP_PATH, "resource\\resource_json\config_json\\bytes")
EXP_GAME_CONF_CSV_PATH = os.path.join(EXP_PATH, "exp_conf_csv")
DST_GAME_CONF_CODE_PATH = os.path.join(SRC_PROJ_PATH, 'exp/conf')
DST_GAME_CONF_MSG_PATH = os.path.join(NEW_SRC_PROJ_PATH,'src/gamescripts/exp/msgdef')
DST_GAME_EXP_PATH = os.path.join(SRC_PROJ_PATH, 'exp')
DST_GAME_MSG_FACT_PATH = os.path.join(NEW_SRC_PROJ_PATH,'src/gamescripts/exp/fact')
DST_GAME_MSG_HANDLER_PATH = os.path.join(NEW_SRC_PROJ_PATH,'src/gamescripts/exp/msg')
DST_GAME_MSG_HELPER_PATH = os.path.join(NEW_SRC_PROJ_PATH,'src/gamescripts/exp/msghelper')


GAME_CONF_MAKO_TS = "Config_ts.mako"
GAME_CONF_FACT_MAKO_TS = "ConfFact_ts.mako"
GAME_CONF_MAKO_CS = "Config_cs.mako"
GAME_CONF_FACT_MAKO_CS = "ConfFact_cs.mako"
GAME_MSG_FACT_MAKO_TS = "MsgFact_ts.mako"
GAME_MSG_HANDLER_MAKO_TS = "MsgHandler_ts.mako"
GAME_MSG_HELPER_MAKO_CS = "MsgHelpr_cs.mako"
GAME_MSG_COMMON_HANDLER_MAKO_ts = "MsgCommonHandler_ts.mako"
GAME_MSG_COMMON_HELPER_MAKO_TS = "MsgCommonHelpr_ts.mako"
GAME_MSG_BEGIN_MAKO_TS = "MsgBegin_ts.mako"
GAME_MSG_END_MAKO_CS = "MsgEnd_ts.mako"

#max effect
MAX_EFFECT_SRC_EXT_NAME = '.eft'
MAX_EFFECT_DST_EXT_NAME = '.bytes'

#copy res path config
DST_SCRIPT_PATH = os.path.join(SRC_PROJ_PATH, 'script')
DST_SHADER_PATH = os.path.join(SRC_PROJ_PATH, 'Resources/exp_shader')
DST_RES_CODE_PATH = os.path.join(SRC_PROJ_PATH, 'exp/res')
DST_GUI_CODE_PATH = os.path.join(SRC_PROJ_PATH, 'exp/gui')

DST_RES_PATH = os.path.join(BIN_PATH, 'res')
DST_WEB_RES_PATH = os.path.join(BIN_PATH, 'webres')

