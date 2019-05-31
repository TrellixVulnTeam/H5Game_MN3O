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
var RoleNameConfig = (function (_super) {
    __extends(RoleNameConfig, _super);
    function RoleNameConfig(id, fristname, name) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.fristname = fristname;
        _this.name = name;
        return _this;
    }
    RoleNameConfig.Init = function () {
        this.LoadRes();
    };
    RoleNameConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "RoleNameConfig") {
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
        ConfFact.SetResLoad("RoleNameConfig");
        this.resLoaded = true;
    };
    RoleNameConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var fristname = rs.ReadString();
        var name = rs.ReadString();
        var new_obj_RoleNameConfig = new RoleNameConfig(id, fristname, name);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_RoleNameConfig;
        this.array.push(new_obj_RoleNameConfig);
    };
    RoleNameConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "RoleNameConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    RoleNameConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    RoleNameConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    RoleNameConfig.resLoaded = false;
    RoleNameConfig.dic = {};
    RoleNameConfig.array = [];
    return RoleNameConfig;
}(BaseConfig));
__reflect(RoleNameConfig.prototype, "RoleNameConfig");
//# sourceMappingURL=RoleNameConfig.js.map