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
var PlotGroupConfig = (function (_super) {
    __extends(PlotGroupConfig, _super);
    function PlotGroupConfig(plotGroupID, startDialogID, triggerType, icon, name, reward, reward_num) {
        var _this = _super.call(this) || this;
        _this.plotGroupID = plotGroupID;
        _this.startDialogID = startDialogID;
        _this.triggerType = triggerType;
        _this.icon = icon;
        _this.name = name;
        _this.reward = reward;
        _this.reward_num = reward_num;
        return _this;
    }
    PlotGroupConfig.Init = function () {
        this.LoadRes();
    };
    PlotGroupConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "PlotGroupConfig") {
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
        ConfFact.SetResLoad("PlotGroupConfig");
        this.resLoaded = true;
    };
    PlotGroupConfig.Add_Item = function (rs) {
        var arr_item_len_PlotGroupConfig;
        var plotGroupID = rs.ReadInt();
        var startDialogID = rs.ReadInt();
        var triggerType = rs.ReadInt();
        var icon = rs.ReadString();
        var name = rs.ReadString();
        arr_item_len_PlotGroupConfig = rs.ReadShort();
        var reward = [];
        for (var i = 0; i < arr_item_len_PlotGroupConfig; ++i)
            reward[i] =
                rs.ReadInt();
        arr_item_len_PlotGroupConfig = rs.ReadShort();
        var reward_num = [];
        for (var i = 0; i < arr_item_len_PlotGroupConfig; ++i)
            reward_num[i] =
                rs.ReadInt();
        var new_obj_PlotGroupConfig = new PlotGroupConfig(plotGroupID, startDialogID, triggerType, icon, name, reward, reward_num);
        if (this.ContainsKey(plotGroupID)) {
            return;
        }
        this.dic[plotGroupID] = new_obj_PlotGroupConfig;
        this.array.push(new_obj_PlotGroupConfig);
    };
    PlotGroupConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "PlotGroupConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    PlotGroupConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    PlotGroupConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    PlotGroupConfig.resLoaded = false;
    PlotGroupConfig.dic = {};
    PlotGroupConfig.array = [];
    return PlotGroupConfig;
}(BaseConfig));
__reflect(PlotGroupConfig.prototype, "PlotGroupConfig");
//# sourceMappingURL=PlotGroupConfig.js.map