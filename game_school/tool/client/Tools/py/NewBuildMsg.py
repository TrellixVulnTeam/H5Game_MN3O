# -*- coding:utf-8 -*-

import os
import sys
import shutil
import pck_msg
from config import  *
from path_util import  *

#proto原始文件路径
protofilepath = os.path.join(SHARED_PWMSG_PATH,'worldsrv.proto')
#根目录
#客户端协议存放目录
c_proto_filename = 'worldsrv.proto'
c_msg_json_filename = 'servermessage.json'
c_proto_filepath = os.path.join(NewROOT_PATH,'game_client/protobuf/protofile')
c_msg_json_filepath = os.path.join(NewROOT_PATH,'game_client/resource/resource_json/config_json/proto')
cmd_path =os.path.join(NewROOT_PATH,'game_client')

def clearoldfile(clientprotopath,clientjsonpath):
    # 清除旧文件
    # clientfilepath(客户端目录)-->rotobuf/protofile
    # clientjsonfilepath(客户端目录)-->resource/resource_json/config_json/proto/servermessage.json
    clear_folder_type(clientprotopath, ".proto")
    clear_folder_type(clientjsonpath, ".json")
    return True

def CopyProtoFileToClientPath():
    #拷贝服务器proto文件到客户端目录
    #protopath(存放目录)
    #clientfilepath(客户端目录)-->rotobuf/protofile

    clientprotofilepath = os.path.join(c_proto_filepath,c_proto_filename)
    shutil.copyfileobj(open(protofilepath,'r'),open(clientprotofilepath,'w'))
    file_data = ""
    with open(clientprotofilepath,'r') as f:
        for line in f:
            if SCHOOL_OLDPROTORISE in line:
                line = line.replace(SCHOOL_OLDPROTORISE,SCHOOL_NEWPROTORISE)
            if SCHOOL_OLDPACKAGENAME in line:
                line = line.replace(SCHOOL_OLDPACKAGENAME,SCHOOL_NEWPACKAGENAME)
            file_data+=line
        f.close()
    with open(clientprotofilepath, 'w') as f:
        f.write(file_data)
        f.close()

    message_jsondic={}
    with open(clientprotofilepath) as f:
        for line in f:
            if 'message' in line:
                current_message = line.split(' ')
                if '{' in current_message[1]:
                    next_info = f.next()
                    if 'msgid' in next_info:
                        msgid = next_info.split('=')[1].replace(';','').strip('\n')
                        msgid = msgid.replace(' ','')
                        msg = current_message[1].replace('{','').strip('\n')
                        msg = msg.replace(' ', '')
                        message_jsondic[msgid]=msg
                else:
                    next_info = f.next()
                    if '{' in next_info:
                        next_info = f.next()
                        if 'msgid' in next_info:
                            msgid = next_info.split('=')[1].replace(';', '').strip('\n')
                            msgid = msgid.replace(' ','')
                            msg = current_message[1].replace('{', '').strip('\n')
                            msg = msg.replace(' ','')
                            message_jsondic[msgid] = msg
        f.close()
    msg_jsonInfo = "{\n"
    for inx, k in enumerate(message_jsondic):
        if inx < len(message_jsondic)-1:
            msg_jsonInfo += '"' + k + '"' + ':' + '"' + message_jsondic[k] + '",\n'
        else:
            msg_jsonInfo += '"' + k + '"' + ':' + '"' + message_jsondic[k] + '"\n'
    msg_jsonInfo += '}'

    msg_jsonfilepath = os.path.join(c_msg_json_filepath,c_msg_json_filename)
    with open(msg_jsonfilepath,'w+') as f:
        f.write(msg_jsonInfo)
        f.close()

    msgdef_Info = "class MsgDef{\n    public constructor(){}\n"
    for inx, k in enumerate(message_jsondic):
        msgdef_Info += '    public static msgid_' + message_jsondic[k] +'=' + k +';\n'
    msgdef_Info += '}'
    msgid_def_filepath = os.path.join(DST_GAME_CONF_MSG_PATH,'MsgDef.ts')
    with open(msgid_def_filepath,'w+') as f:
        f.write(msgdef_Info)
        f.close()

    return True

if __name__ == '__main__':
    print("begin generate by NewBuildMsg")
    clearoldfile(c_proto_filepath, c_msg_json_filepath)
    CopyProtoFileToClientPath()
    pck_msg.pack_msg_dir(DST_GAME_CONF_MSG_PATH,
                         DST_GAME_MSG_FACT_PATH,
                         DST_GAME_MSG_HANDLER_PATH,
                         DST_GAME_MSG_HELPER_PATH)
    os.chdir(cmd_path)
    os.system('pb-egret generate')
    print("success generate by NewBuildMsg")

    #注册消息

    exit()