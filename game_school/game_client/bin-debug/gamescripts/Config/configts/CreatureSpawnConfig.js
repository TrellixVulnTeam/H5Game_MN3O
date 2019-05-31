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
var CreatureSpawnConfig = (function (_super) {
    __extends(CreatureSpawnConfig, _super);
    function CreatureSpawnConfig(id, templet, level, attrMethod, attrID) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.templet = templet;
        _this.level = level;
        _this.attrMethod = attrMethod;
        _this.attrID = attrID;
        return _this;
    }
    CreatureSpawnConfig.Init = function () {
        this.LoadRes();
    };
    CreatureSpawnConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "CreatureSpawnConfig") {
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
        ConfFact.SetResLoad("CreatureSpawnConfig");
        this.resLoaded = true;
    };
    CreatureSpawnConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var templet = rs.ReadInt();
        var level = rs.ReadInt();
        var attrMethod = rs.ReadInt();
        var attrID = rs.ReadInt();
        var new_obj_CreatureSpawnConfig = new CreatureSpawnConfig(id, templet, level, attrMethod, attrID);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_CreatureSpawnConfig;
        this.array.push(new_obj_CreatureSpawnConfig);
    };
    CreatureSpawnConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "CreatureSpawnConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    CreatureSpawnConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    CreatureSpawnConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    CreatureSpawnConfig.resLoaded = false;
    CreatureSpawnConfig.dic = {};
    CreatureSpawnConfig.array = [];
    return CreatureSpawnConfig;
}(BaseConfig));
__reflect(CreatureSpawnConfig.prototype, "CreatureSpawnConfig");
//# sourceMappingURL=CreatureSpawnConfig.js.map