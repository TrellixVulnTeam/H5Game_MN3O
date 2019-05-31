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
var GuideConfig = (function (_super) {
    __extends(GuideConfig, _super);
    function GuideConfig(id, closeLevel, triggerType, triggerKey, countdown, endType, para1, para2, type, ui, itemName, arrow, des, desPos) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.closeLevel = closeLevel;
        _this.triggerType = triggerType;
        _this.triggerKey = triggerKey;
        _this.countdown = countdown;
        _this.endType = endType;
        _this.para1 = para1;
        _this.para2 = para2;
        _this.type = type;
        _this.ui = ui;
        _this.itemName = itemName;
        _this.arrow = arrow;
        _this.des = des;
        _this.desPos = desPos;
        return _this;
    }
    GuideConfig.Init = function () {
        this.LoadRes();
    };
    GuideConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "GuideConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 14) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("GuideConfig");
        this.resLoaded = true;
    };
    GuideConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var closeLevel = rs.ReadInt();
        var triggerType = rs.ReadInt();
        var triggerKey = rs.ReadInt();
        var countdown = rs.ReadInt();
        var endType = rs.ReadInt();
        var para1 = rs.ReadInt();
        var para2 = rs.ReadInt();
        var type = rs.ReadInt();
        var ui = rs.ReadInt();
        var itemName = rs.ReadString();
        var arrow = rs.ReadInt();
        var des = rs.ReadString();
        var desPos = rs.ReadInt();
        var new_obj_GuideConfig = new GuideConfig(id, closeLevel, triggerType, triggerKey, countdown, endType, para1, para2, type, ui, itemName, arrow, des, desPos);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_GuideConfig;
        this.array.push(new_obj_GuideConfig);
    };
    GuideConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "GuideConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    GuideConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    GuideConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    GuideConfig.resLoaded = false;
    GuideConfig.dic = {};
    GuideConfig.array = [];
    return GuideConfig;
}(BaseConfig));
__reflect(GuideConfig.prototype, "GuideConfig");
//# sourceMappingURL=GuideConfig.js.map