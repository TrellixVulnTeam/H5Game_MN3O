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
var CheckPointConfig = (function (_super) {
    __extends(CheckPointConfig, _super);
    function CheckPointConfig(id, chapter, checkpoint_name, coordinate, checkpoint_type, front_id, unlockLevel, battle_bg, plot, battle, request, awardAttr, suggestPower, consume, dailyChance, exp, money, frist_reward, normal_reward) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.chapter = chapter;
        _this.checkpoint_name = checkpoint_name;
        _this.coordinate = coordinate;
        _this.checkpoint_type = checkpoint_type;
        _this.front_id = front_id;
        _this.unlockLevel = unlockLevel;
        _this.battle_bg = battle_bg;
        _this.plot = plot;
        _this.battle = battle;
        _this.request = request;
        _this.awardAttr = awardAttr;
        _this.suggestPower = suggestPower;
        _this.consume = consume;
        _this.dailyChance = dailyChance;
        _this.exp = exp;
        _this.money = money;
        _this.frist_reward = frist_reward;
        _this.normal_reward = normal_reward;
        return _this;
    }
    CheckPointConfig.Init = function () {
        this.LoadRes();
    };
    CheckPointConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "CheckPointConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 19) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("CheckPointConfig");
        this.resLoaded = true;
    };
    CheckPointConfig.Add_Item = function (rs) {
        var arr_item_len_CheckPointConfig;
        var id = rs.ReadInt();
        var chapter = rs.ReadInt();
        var checkpoint_name = rs.ReadString();
        arr_item_len_CheckPointConfig = rs.ReadShort();
        var coordinate = [];
        for (var i = 0; i < arr_item_len_CheckPointConfig; ++i)
            coordinate[i] =
                rs.ReadInt();
        var checkpoint_type = rs.ReadInt();
        var front_id = rs.ReadInt();
        var unlockLevel = rs.ReadInt();
        var battle_bg = rs.ReadString();
        var plot = rs.ReadInt();
        arr_item_len_CheckPointConfig = rs.ReadShort();
        var battle = [];
        for (var i = 0; i < arr_item_len_CheckPointConfig; ++i)
            battle[i] =
                rs.ReadInt();
        arr_item_len_CheckPointConfig = rs.ReadShort();
        var request = [];
        for (var i = 0; i < arr_item_len_CheckPointConfig; ++i)
            request[i] =
                rs.ReadInt();
        var awardAttr = rs.ReadInt();
        var suggestPower = rs.ReadInt();
        var consume = rs.ReadInt();
        var dailyChance = rs.ReadInt();
        var exp = rs.ReadInt();
        var money = rs.ReadInt();
        var frist_reward = rs.ReadInt();
        var normal_reward = rs.ReadInt();
        var new_obj_CheckPointConfig = new CheckPointConfig(id, chapter, checkpoint_name, coordinate, checkpoint_type, front_id, unlockLevel, battle_bg, plot, battle, request, awardAttr, suggestPower, consume, dailyChance, exp, money, frist_reward, normal_reward);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_CheckPointConfig;
        this.array.push(new_obj_CheckPointConfig);
    };
    CheckPointConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "CheckPointConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    CheckPointConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    CheckPointConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    CheckPointConfig.resLoaded = false;
    CheckPointConfig.dic = {};
    CheckPointConfig.array = [];
    return CheckPointConfig;
}(BaseConfig));
__reflect(CheckPointConfig.prototype, "CheckPointConfig");
//# sourceMappingURL=CheckPointConfig.js.map