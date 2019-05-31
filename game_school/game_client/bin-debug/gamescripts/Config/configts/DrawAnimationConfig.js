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
var DrawAnimationConfig = (function (_super) {
    __extends(DrawAnimationConfig, _super);
    function DrawAnimationConfig(id, drawID, drawScale, type, face, sound, soundDelay, liveTime, extraResource1) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.drawID = drawID;
        _this.drawScale = drawScale;
        _this.type = type;
        _this.face = face;
        _this.sound = sound;
        _this.soundDelay = soundDelay;
        _this.liveTime = liveTime;
        _this.extraResource1 = extraResource1;
        return _this;
    }
    DrawAnimationConfig.Init = function () {
        this.LoadRes();
    };
    DrawAnimationConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "DrawAnimationConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 9) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("DrawAnimationConfig");
        this.resLoaded = true;
    };
    DrawAnimationConfig.Add_Item = function (rs) {
        var arr_item_len_DrawAnimationConfig;
        var id = rs.ReadInt();
        var drawID = rs.ReadInt();
        var drawScale = rs.ReadFloat();
        var type = rs.ReadInt();
        var face = rs.ReadInt();
        arr_item_len_DrawAnimationConfig = rs.ReadShort();
        var sound = [];
        for (var i = 0; i < arr_item_len_DrawAnimationConfig; ++i)
            sound[i] =
                rs.ReadString();
        arr_item_len_DrawAnimationConfig = rs.ReadShort();
        var soundDelay = [];
        for (var i = 0; i < arr_item_len_DrawAnimationConfig; ++i)
            soundDelay[i] =
                rs.ReadInt();
        var liveTime = rs.ReadInt();
        var extraResource1 = rs.ReadString();
        var new_obj_DrawAnimationConfig = new DrawAnimationConfig(id, drawID, drawScale, type, face, sound, soundDelay, liveTime, extraResource1);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_DrawAnimationConfig;
        this.array.push(new_obj_DrawAnimationConfig);
    };
    DrawAnimationConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "DrawAnimationConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    DrawAnimationConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    DrawAnimationConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    DrawAnimationConfig.resLoaded = false;
    DrawAnimationConfig.dic = {};
    DrawAnimationConfig.array = [];
    return DrawAnimationConfig;
}(BaseConfig));
__reflect(DrawAnimationConfig.prototype, "DrawAnimationConfig");
//# sourceMappingURL=DrawAnimationConfig.js.map