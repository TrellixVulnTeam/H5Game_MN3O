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
var ActivityClientConfig = (function (_super) {
    __extends(ActivityClientConfig, _super);
    function ActivityClientConfig(id, sort, activityName, contentPicture, level, timeType, startTime, endTime, time, rewardEndTime, click_type, click_para1) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.sort = sort;
        _this.activityName = activityName;
        _this.contentPicture = contentPicture;
        _this.level = level;
        _this.timeType = timeType;
        _this.startTime = startTime;
        _this.endTime = endTime;
        _this.time = time;
        _this.rewardEndTime = rewardEndTime;
        _this.click_type = click_type;
        _this.click_para1 = click_para1;
        return _this;
    }
    ActivityClientConfig.Init = function () {
        this.LoadRes();
    };
    ActivityClientConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "ActivityClientConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 12) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("ActivityClientConfig");
        this.resLoaded = true;
    };
    ActivityClientConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var sort = rs.ReadInt();
        var activityName = rs.ReadString();
        var contentPicture = rs.ReadString();
        var level = rs.ReadInt();
        var timeType = rs.ReadInt();
        var startTime = rs.ReadString();
        var endTime = rs.ReadString();
        var time = rs.ReadBool();
        var rewardEndTime = rs.ReadString();
        var click_type = rs.ReadInt();
        var click_para1 = rs.ReadInt();
        var new_obj_ActivityClientConfig = new ActivityClientConfig(id, sort, activityName, contentPicture, level, timeType, startTime, endTime, time, rewardEndTime, click_type, click_para1);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_ActivityClientConfig;
        this.array.push(new_obj_ActivityClientConfig);
    };
    ActivityClientConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "ActivityClientConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    ActivityClientConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    ActivityClientConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    ActivityClientConfig.resLoaded = false;
    ActivityClientConfig.dic = {};
    ActivityClientConfig.array = [];
    return ActivityClientConfig;
}(BaseConfig));
__reflect(ActivityClientConfig.prototype, "ActivityClientConfig");
//# sourceMappingURL=ActivityClientConfig.js.map