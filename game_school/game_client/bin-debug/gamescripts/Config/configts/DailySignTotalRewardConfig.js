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
var DailySignTotalRewardConfig = (function (_super) {
    __extends(DailySignTotalRewardConfig, _super);
    function DailySignTotalRewardConfig(id, item_id, item_num) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.item_id = item_id;
        _this.item_num = item_num;
        return _this;
    }
    DailySignTotalRewardConfig.Init = function () {
        this.LoadRes();
    };
    DailySignTotalRewardConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "DailySignTotalRewardConfig") {
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
        ConfFact.SetResLoad("DailySignTotalRewardConfig");
        this.resLoaded = true;
    };
    DailySignTotalRewardConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var item_id = rs.ReadInt();
        var item_num = rs.ReadInt();
        var new_obj_DailySignTotalRewardConfig = new DailySignTotalRewardConfig(id, item_id, item_num);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_DailySignTotalRewardConfig;
        this.array.push(new_obj_DailySignTotalRewardConfig);
    };
    DailySignTotalRewardConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "DailySignTotalRewardConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    DailySignTotalRewardConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    DailySignTotalRewardConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    DailySignTotalRewardConfig.resLoaded = false;
    DailySignTotalRewardConfig.dic = {};
    DailySignTotalRewardConfig.array = [];
    return DailySignTotalRewardConfig;
}(BaseConfig));
__reflect(DailySignTotalRewardConfig.prototype, "DailySignTotalRewardConfig");
//# sourceMappingURL=DailySignTotalRewardConfig.js.map