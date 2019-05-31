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
var BattleConfig = (function (_super) {
    __extends(BattleConfig, _super);
    function BattleConfig(id, icon, round, boss_battle, dialogue_front, dialogue_tail, battle_bg, battle_music, monster1, monster2, monster3, monster4, monster5, monster6) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.icon = icon;
        _this.round = round;
        _this.boss_battle = boss_battle;
        _this.dialogue_front = dialogue_front;
        _this.dialogue_tail = dialogue_tail;
        _this.battle_bg = battle_bg;
        _this.battle_music = battle_music;
        _this.monster1 = monster1;
        _this.monster2 = monster2;
        _this.monster3 = monster3;
        _this.monster4 = monster4;
        _this.monster5 = monster5;
        _this.monster6 = monster6;
        return _this;
    }
    BattleConfig.Init = function () {
        this.LoadRes();
    };
    BattleConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "BattleConfig") {
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
        ConfFact.SetResLoad("BattleConfig");
        this.resLoaded = true;
    };
    BattleConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var icon = rs.ReadString();
        var round = rs.ReadInt();
        var boss_battle = rs.ReadBool();
        var dialogue_front = rs.ReadInt();
        var dialogue_tail = rs.ReadInt();
        var battle_bg = rs.ReadString();
        var battle_music = rs.ReadString();
        var monster1 = rs.ReadInt();
        var monster2 = rs.ReadInt();
        var monster3 = rs.ReadInt();
        var monster4 = rs.ReadInt();
        var monster5 = rs.ReadInt();
        var monster6 = rs.ReadInt();
        var new_obj_BattleConfig = new BattleConfig(id, icon, round, boss_battle, dialogue_front, dialogue_tail, battle_bg, battle_music, monster1, monster2, monster3, monster4, monster5, monster6);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_BattleConfig;
        this.array.push(new_obj_BattleConfig);
    };
    BattleConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "BattleConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    BattleConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    BattleConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    BattleConfig.resLoaded = false;
    BattleConfig.dic = {};
    BattleConfig.array = [];
    return BattleConfig;
}(BaseConfig));
__reflect(BattleConfig.prototype, "BattleConfig");
//# sourceMappingURL=BattleConfig.js.map