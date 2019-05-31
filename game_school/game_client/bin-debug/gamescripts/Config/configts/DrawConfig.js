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
var DrawConfig = (function (_super) {
    __extends(DrawConfig, _super);
    function DrawConfig(id, draw, draw2, facePosition, face, emotionPosition1, emotionPosition2, emotionPosition3) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.draw = draw;
        _this.draw2 = draw2;
        _this.facePosition = facePosition;
        _this.face = face;
        _this.emotionPosition1 = emotionPosition1;
        _this.emotionPosition2 = emotionPosition2;
        _this.emotionPosition3 = emotionPosition3;
        return _this;
    }
    DrawConfig.Init = function () {
        this.LoadRes();
    };
    DrawConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "DrawConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 8) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("DrawConfig");
        this.resLoaded = true;
    };
    DrawConfig.Add_Item = function (rs) {
        var arr_item_len_DrawConfig;
        var id = rs.ReadInt();
        var draw = rs.ReadString();
        var draw2 = rs.ReadString();
        arr_item_len_DrawConfig = rs.ReadShort();
        var facePosition = [];
        for (var i = 0; i < arr_item_len_DrawConfig; ++i)
            facePosition[i] =
                rs.ReadFloat();
        arr_item_len_DrawConfig = rs.ReadShort();
        var face = [];
        for (var i = 0; i < arr_item_len_DrawConfig; ++i)
            face[i] =
                rs.ReadString();
        arr_item_len_DrawConfig = rs.ReadShort();
        var emotionPosition1 = [];
        for (var i = 0; i < arr_item_len_DrawConfig; ++i)
            emotionPosition1[i] =
                rs.ReadFloat();
        arr_item_len_DrawConfig = rs.ReadShort();
        var emotionPosition2 = [];
        for (var i = 0; i < arr_item_len_DrawConfig; ++i)
            emotionPosition2[i] =
                rs.ReadFloat();
        arr_item_len_DrawConfig = rs.ReadShort();
        var emotionPosition3 = [];
        for (var i = 0; i < arr_item_len_DrawConfig; ++i)
            emotionPosition3[i] =
                rs.ReadFloat();
        var new_obj_DrawConfig = new DrawConfig(id, draw, draw2, facePosition, face, emotionPosition1, emotionPosition2, emotionPosition3);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_DrawConfig;
        this.array.push(new_obj_DrawConfig);
    };
    DrawConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "DrawConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    DrawConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    DrawConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    DrawConfig.resLoaded = false;
    DrawConfig.dic = {};
    DrawConfig.array = [];
    return DrawConfig;
}(BaseConfig));
__reflect(DrawConfig.prototype, "DrawConfig");
//# sourceMappingURL=DrawConfig.js.map