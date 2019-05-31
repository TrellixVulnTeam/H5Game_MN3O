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
var RandomPoolConfig = (function (_super) {
    __extends(RandomPoolConfig, _super);
    function RandomPoolConfig(id, comment, randNum, item1, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, item13, item14, item15, item16, item17, item18, item19, item20) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.comment = comment;
        _this.randNum = randNum;
        _this.item1 = item1;
        _this.item2 = item2;
        _this.item3 = item3;
        _this.item4 = item4;
        _this.item5 = item5;
        _this.item6 = item6;
        _this.item7 = item7;
        _this.item8 = item8;
        _this.item9 = item9;
        _this.item10 = item10;
        _this.item11 = item11;
        _this.item12 = item12;
        _this.item13 = item13;
        _this.item14 = item14;
        _this.item15 = item15;
        _this.item16 = item16;
        _this.item17 = item17;
        _this.item18 = item18;
        _this.item19 = item19;
        _this.item20 = item20;
        return _this;
    }
    RandomPoolConfig.Init = function () {
        this.LoadRes();
    };
    RandomPoolConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "RandomPoolConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 23) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("RandomPoolConfig");
        this.resLoaded = true;
    };
    RandomPoolConfig.Add_Item = function (rs) {
        var arr_item_len_RandomPoolConfig;
        var id = rs.ReadInt();
        var comment = rs.ReadString();
        var randNum = rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item1 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item1[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item2 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item2[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item3 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item3[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item4 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item4[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item5 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item5[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item6 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item6[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item7 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item7[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item8 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item8[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item9 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item9[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item10 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item10[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item11 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item11[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item12 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item12[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item13 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item13[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item14 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item14[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item15 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item15[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item16 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item16[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item17 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item17[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item18 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item18[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item19 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item19[i] =
                rs.ReadInt();
        arr_item_len_RandomPoolConfig = rs.ReadShort();
        var item20 = [];
        for (var i = 0; i < arr_item_len_RandomPoolConfig; ++i)
            item20[i] =
                rs.ReadInt();
        var new_obj_RandomPoolConfig = new RandomPoolConfig(id, comment, randNum, item1, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, item13, item14, item15, item16, item17, item18, item19, item20);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_RandomPoolConfig;
        this.array.push(new_obj_RandomPoolConfig);
    };
    RandomPoolConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "RandomPoolConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    RandomPoolConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    RandomPoolConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    RandomPoolConfig.resLoaded = false;
    RandomPoolConfig.dic = {};
    RandomPoolConfig.array = [];
    return RandomPoolConfig;
}(BaseConfig));
__reflect(RandomPoolConfig.prototype, "RandomPoolConfig");
//# sourceMappingURL=RandomPoolConfig.js.map