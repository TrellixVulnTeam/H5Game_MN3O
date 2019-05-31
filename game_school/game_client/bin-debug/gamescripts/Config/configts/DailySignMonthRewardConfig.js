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
var DailySignMonthRewardConfig = (function (_super) {
    __extends(DailySignMonthRewardConfig, _super);
    function DailySignMonthRewardConfig(id, item_id, item_num) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.item_id = item_id;
        _this.item_num = item_num;
        return _this;
    }
    DailySignMonthRewardConfig.Init = function () {
        this.LoadRes();
    };
    DailySignMonthRewardConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "DailySignMonthRewardConfig") {
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
        ConfFact.SetResLoad("DailySignMonthRewardConfig");
        this.resLoaded = true;
    };
    DailySignMonthRewardConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var item_id = rs.ReadInt();
        var item_num = rs.ReadInt();
        var new_obj_DailySignMonthRewardConfig = new DailySignMonthRewardConfig(id, item_id, item_num);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_DailySignMonthRewardConfig;
        this.array.push(new_obj_DailySignMonthRewardConfig);
    };
    DailySignMonthRewardConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "DailySignMonthRewardConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    DailySignMonthRewardConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    DailySignMonthRewardConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    DailySignMonthRewardConfig.resLoaded = false;
    DailySignMonthRewardConfig.dic = {};
    DailySignMonthRewardConfig.array = [];
    return DailySignMonthRewardConfig;
}(BaseConfig));
__reflect(DailySignMonthRewardConfig.prototype, "DailySignMonthRewardConfig");
//# sourceMappingURL=DailySignMonthRewardConfig.js.map