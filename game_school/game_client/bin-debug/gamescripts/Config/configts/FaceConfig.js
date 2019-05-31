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
var FaceConfig = (function (_super) {
    __extends(FaceConfig, _super);
    function FaceConfig(id, player_icon, face_icon, face_location, face_size) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.player_icon = player_icon;
        _this.face_icon = face_icon;
        _this.face_location = face_location;
        _this.face_size = face_size;
        return _this;
    }
    FaceConfig.Init = function () {
        this.LoadRes();
    };
    FaceConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "FaceConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 5) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("FaceConfig");
        this.resLoaded = true;
    };
    FaceConfig.Add_Item = function (rs) {
        var arr_item_len_FaceConfig;
        var id = rs.ReadInt();
        var player_icon = rs.ReadString();
        arr_item_len_FaceConfig = rs.ReadShort();
        var face_icon = [];
        for (var i = 0; i < arr_item_len_FaceConfig; ++i)
            face_icon[i] =
                rs.ReadString();
        arr_item_len_FaceConfig = rs.ReadShort();
        var face_location = [];
        for (var i = 0; i < arr_item_len_FaceConfig; ++i)
            face_location[i] =
                rs.ReadInt();
        arr_item_len_FaceConfig = rs.ReadShort();
        var face_size = [];
        for (var i = 0; i < arr_item_len_FaceConfig; ++i)
            face_size[i] =
                rs.ReadInt();
        var new_obj_FaceConfig = new FaceConfig(id, player_icon, face_icon, face_location, face_size);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_FaceConfig;
        this.array.push(new_obj_FaceConfig);
    };
    FaceConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "FaceConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    FaceConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    FaceConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    FaceConfig.resLoaded = false;
    FaceConfig.dic = {};
    FaceConfig.array = [];
    return FaceConfig;
}(BaseConfig));
__reflect(FaceConfig.prototype, "FaceConfig");
//# sourceMappingURL=FaceConfig.js.map