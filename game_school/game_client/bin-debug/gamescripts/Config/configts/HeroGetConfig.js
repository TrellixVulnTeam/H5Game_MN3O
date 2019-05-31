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
var HeroGetConfig = (function (_super) {
    __extends(HeroGetConfig, _super);
    function HeroGetConfig(id, comment, costType, normalCost, tenTimesCost, freeCd, dailyMaxFree, normalPool, energyPool, firstHero, onSellHero, picture, viplevel) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.comment = comment;
        _this.costType = costType;
        _this.normalCost = normalCost;
        _this.tenTimesCost = tenTimesCost;
        _this.freeCd = freeCd;
        _this.dailyMaxFree = dailyMaxFree;
        _this.normalPool = normalPool;
        _this.energyPool = energyPool;
        _this.firstHero = firstHero;
        _this.onSellHero = onSellHero;
        _this.picture = picture;
        _this.viplevel = viplevel;
        return _this;
    }
    HeroGetConfig.Init = function () {
        this.LoadRes();
    };
    HeroGetConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "HeroGetConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 13) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("HeroGetConfig");
        this.resLoaded = true;
    };
    HeroGetConfig.Add_Item = function (rs) {
        var arr_item_len_HeroGetConfig;
        var id = rs.ReadInt();
        var comment = rs.ReadString();
        var costType = rs.ReadInt();
        var normalCost = rs.ReadInt();
        var tenTimesCost = rs.ReadInt();
        var freeCd = rs.ReadInt();
        var dailyMaxFree = rs.ReadInt();
        var normalPool = rs.ReadInt();
        var energyPool = rs.ReadInt();
        var firstHero = rs.ReadInt();
        arr_item_len_HeroGetConfig = rs.ReadShort();
        var onSellHero = [];
        for (var i = 0; i < arr_item_len_HeroGetConfig; ++i)
            onSellHero[i] =
                rs.ReadInt();
        var picture = rs.ReadString();
        var viplevel = rs.ReadInt();
        var new_obj_HeroGetConfig = new HeroGetConfig(id, comment, costType, normalCost, tenTimesCost, freeCd, dailyMaxFree, normalPool, energyPool, firstHero, onSellHero, picture, viplevel);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_HeroGetConfig;
        this.array.push(new_obj_HeroGetConfig);
    };
    HeroGetConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "HeroGetConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    HeroGetConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    HeroGetConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    HeroGetConfig.resLoaded = false;
    HeroGetConfig.dic = {};
    HeroGetConfig.array = [];
    return HeroGetConfig;
}(BaseConfig));
__reflect(HeroGetConfig.prototype, "HeroGetConfig");
//# sourceMappingURL=HeroGetConfig.js.map