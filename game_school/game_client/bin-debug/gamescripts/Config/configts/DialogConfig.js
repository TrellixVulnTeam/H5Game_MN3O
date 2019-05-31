var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var __extends = this && this.__extends || function __extends(t, e) { 
 function r() { 
 this.constructor = t;
}
for (var i in e) e.hasOwnProperty(i) && (t[i] = e[i]);
r.prototype = e.prototype, t.prototype = new r();
};
var DialogConfig = (function (_super) {
    __extends(DialogConfig, _super);
    function DialogConfig(dialogID, nextDialogID, dialogType, optionID, cgPath, npcID, npcName, faceIndex, faceSymbol, faceSymbolPos, pos, content, background, sound, soundDelay, voice, music, startSceneEffect, endSceneEffect) {
        var _this = _super.call(this) || this;
        _this.dialogID = dialogID;
        _this.nextDialogID = nextDialogID;
        _this.dialogType = dialogType;
        _this.optionID = optionID;
        _this.cgPath = cgPath;
        _this.npcID = npcID;
        _this.npcName = npcName;
        _this.faceIndex = faceIndex;
        _this.faceSymbol = faceSymbol;
        _this.faceSymbolPos = faceSymbolPos;
        _this.pos = pos;
        _this.content = content;
        _this.background = background;
        _this.sound = sound;
        _this.soundDelay = soundDelay;
        _this.voice = voice;
        _this.music = music;
        _this.startSceneEffect = startSceneEffect;
        _this.endSceneEffect = endSceneEffect;
        return _this;
    }
    DialogConfig.Init = function () {
        this.LoadRes();
    };
    DialogConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "DialogConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 19) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("DialogConfig");
        this.resLoaded = true;
    };
    DialogConfig.Add_Item = function (rs) {
        var arr_item_len_DialogConfig;
        var dialogID = rs.ReadInt();
        var nextDialogID = rs.ReadInt();
        var dialogType = rs.ReadInt();
        var optionID = rs.ReadInt();
        var cgPath = rs.ReadString();
        var npcID = rs.ReadInt();
        var npcName = rs.ReadString();
        var faceIndex = rs.ReadInt();
        var faceSymbol = rs.ReadInt();
        var faceSymbolPos = rs.ReadInt();
        var pos = rs.ReadInt();
        var content = rs.ReadString();
        var background = rs.ReadString();
        var sound = rs.ReadString();
        var soundDelay = rs.ReadInt();
        var voice = rs.ReadString();
        var music = rs.ReadString();
        arr_item_len_DialogConfig = rs.ReadShort();
        var startSceneEffect = [];
        for (var i = 0; i < arr_item_len_DialogConfig; ++i)
            startSceneEffect[i] =
                rs.ReadInt();
        arr_item_len_DialogConfig = rs.ReadShort();
        var endSceneEffect = [];
        for (var i = 0; i < arr_item_len_DialogConfig; ++i)
            endSceneEffect[i] =
                rs.ReadInt();
        var new_obj_DialogConfig = new DialogConfig(dialogID, nextDialogID, dialogType, optionID, cgPath, npcID, npcName, faceIndex, faceSymbol, faceSymbolPos, pos, content, background, sound, soundDelay, voice, music, startSceneEffect, endSceneEffect);
        if (this.ContainsKey(dialogID)) {
            return;
        }
        this.dic[dialogID] = new_obj_DialogConfig;
        this.array.push(new_obj_DialogConfig);
    };
    DialogConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "DialogConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    DialogConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    DialogConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    DialogConfig.resLoaded = false;
    DialogConfig.dic = {};
    DialogConfig.array = [];
    return DialogConfig;
}(BaseConfig));
__reflect(DialogConfig.prototype, "DialogConfig");
//# sourceMappingURL=DialogConfig.js.map