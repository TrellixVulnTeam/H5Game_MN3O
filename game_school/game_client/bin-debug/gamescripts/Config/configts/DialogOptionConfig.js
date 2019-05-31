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
var DialogOptionConfig = (function (_super) {
    __extends(DialogOptionConfig, _super);
    function DialogOptionConfig(optionID, option1, optionContent1, optionContent2, optionContent3, optionContent4, nextDialog1, nextDialog2, nextDialog3, nextDialog4, reward, reward_num) {
        var _this = _super.call(this) || this;
        _this.optionID = optionID;
        _this.option1 = option1;
        _this.optionContent1 = optionContent1;
        _this.optionContent2 = optionContent2;
        _this.optionContent3 = optionContent3;
        _this.optionContent4 = optionContent4;
        _this.nextDialog1 = nextDialog1;
        _this.nextDialog2 = nextDialog2;
        _this.nextDialog3 = nextDialog3;
        _this.nextDialog4 = nextDialog4;
        _this.reward = reward;
        _this.reward_num = reward_num;
        return _this;
    }
    DialogOptionConfig.Init = function () {
        this.LoadRes();
    };
    DialogOptionConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "DialogOptionConfig") {
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
        ConfFact.SetResLoad("DialogOptionConfig");
        this.resLoaded = true;
    };
    DialogOptionConfig.Add_Item = function (rs) {
        var arr_item_len_DialogOptionConfig;
        var optionID = rs.ReadInt();
        var option1 = rs.ReadInt();
        var optionContent1 = rs.ReadString();
        var optionContent2 = rs.ReadString();
        var optionContent3 = rs.ReadString();
        var optionContent4 = rs.ReadString();
        var nextDialog1 = rs.ReadInt();
        var nextDialog2 = rs.ReadInt();
        var nextDialog3 = rs.ReadInt();
        var nextDialog4 = rs.ReadInt();
        arr_item_len_DialogOptionConfig = rs.ReadShort();
        var reward = [];
        for (var i = 0; i < arr_item_len_DialogOptionConfig; ++i)
            reward[i] =
                rs.ReadInt();
        arr_item_len_DialogOptionConfig = rs.ReadShort();
        var reward_num = [];
        for (var i = 0; i < arr_item_len_DialogOptionConfig; ++i)
            reward_num[i] =
                rs.ReadInt();
        var new_obj_DialogOptionConfig = new DialogOptionConfig(optionID, option1, optionContent1, optionContent2, optionContent3, optionContent4, nextDialog1, nextDialog2, nextDialog3, nextDialog4, reward, reward_num);
        if (this.ContainsKey(optionID)) {
            return;
        }
        this.dic[optionID] = new_obj_DialogOptionConfig;
        this.array.push(new_obj_DialogOptionConfig);
    };
    DialogOptionConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "DialogOptionConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    DialogOptionConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    DialogOptionConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    DialogOptionConfig.resLoaded = false;
    DialogOptionConfig.dic = {};
    DialogOptionConfig.array = [];
    return DialogOptionConfig;
}(BaseConfig));
__reflect(DialogOptionConfig.prototype, "DialogOptionConfig");
//# sourceMappingURL=DialogOptionConfig.js.map