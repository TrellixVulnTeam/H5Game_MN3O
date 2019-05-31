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
var SceneEffectConfig = (function (_super) {
    __extends(SceneEffectConfig, _super);
    function SceneEffectConfig(id, type, para1, para2, para3, para4, para5) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.type = type;
        _this.para1 = para1;
        _this.para2 = para2;
        _this.para3 = para3;
        _this.para4 = para4;
        _this.para5 = para5;
        return _this;
    }
    SceneEffectConfig.Init = function () {
        this.LoadRes();
    };
    SceneEffectConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "SceneEffectConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 7) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("SceneEffectConfig");
        this.resLoaded = true;
    };
    SceneEffectConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var type = rs.ReadInt();
        var para1 = rs.ReadInt();
        var para2 = rs.ReadInt();
        var para3 = rs.ReadInt();
        var para4 = rs.ReadInt();
        var para5 = rs.ReadFloat();
        var new_obj_SceneEffectConfig = new SceneEffectConfig(id, type, para1, para2, para3, para4, para5);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_SceneEffectConfig;
        this.array.push(new_obj_SceneEffectConfig);
    };
    SceneEffectConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "SceneEffectConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    SceneEffectConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    SceneEffectConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    SceneEffectConfig.resLoaded = false;
    SceneEffectConfig.dic = {};
    SceneEffectConfig.array = [];
    return SceneEffectConfig;
}(BaseConfig));
__reflect(SceneEffectConfig.prototype, "SceneEffectConfig");
//# sourceMappingURL=SceneEffectConfig.js.map