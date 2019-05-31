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
var BlackScreenConfig = (function (_super) {
    __extends(BlackScreenConfig, _super);
    function BlackScreenConfig(id, nextId, content) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.nextId = nextId;
        _this.content = content;
        return _this;
    }
    BlackScreenConfig.Init = function () {
        this.LoadRes();
    };
    BlackScreenConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "BlackScreenConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 3) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("BlackScreenConfig");
        this.resLoaded = true;
    };
    BlackScreenConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var nextId = rs.ReadInt();
        var content = rs.ReadString();
        var new_obj_BlackScreenConfig = new BlackScreenConfig(id, nextId, content);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_BlackScreenConfig;
        this.array.push(new_obj_BlackScreenConfig);
    };
    BlackScreenConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "BlackScreenConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    BlackScreenConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    BlackScreenConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    BlackScreenConfig.resLoaded = false;
    BlackScreenConfig.dic = {};
    BlackScreenConfig.array = [];
    return BlackScreenConfig;
}(BaseConfig));
__reflect(BlackScreenConfig.prototype, "BlackScreenConfig");
//# sourceMappingURL=BlackScreenConfig.js.map