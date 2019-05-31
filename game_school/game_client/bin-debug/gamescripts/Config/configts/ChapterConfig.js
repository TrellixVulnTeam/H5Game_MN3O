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
var ChapterConfig = (function (_super) {
    __extends(ChapterConfig, _super);
    function ChapterConfig(id, chapter_num, chapter_name, type, star_condition, star_reward, chapter_reward, chapter_id, chapter_bg, chapter_music) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.chapter_num = chapter_num;
        _this.chapter_name = chapter_name;
        _this.type = type;
        _this.star_condition = star_condition;
        _this.star_reward = star_reward;
        _this.chapter_reward = chapter_reward;
        _this.chapter_id = chapter_id;
        _this.chapter_bg = chapter_bg;
        _this.chapter_music = chapter_music;
        return _this;
    }
    ChapterConfig.Init = function () {
        this.LoadRes();
    };
    ChapterConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "ChapterConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 10) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("ChapterConfig");
        this.resLoaded = true;
    };
    ChapterConfig.Add_Item = function (rs) {
        var arr_item_len_ChapterConfig;
        var id = rs.ReadInt();
        var chapter_num = rs.ReadString();
        var chapter_name = rs.ReadString();
        var type = rs.ReadInt();
        arr_item_len_ChapterConfig = rs.ReadShort();
        var star_condition = [];
        for (var i = 0; i < arr_item_len_ChapterConfig; ++i)
            star_condition[i] =
                rs.ReadInt();
        arr_item_len_ChapterConfig = rs.ReadShort();
        var star_reward = [];
        for (var i = 0; i < arr_item_len_ChapterConfig; ++i)
            star_reward[i] =
                rs.ReadInt();
        var chapter_reward = rs.ReadInt();
        arr_item_len_ChapterConfig = rs.ReadShort();
        var chapter_id = [];
        for (var i = 0; i < arr_item_len_ChapterConfig; ++i)
            chapter_id[i] =
                rs.ReadInt();
        var chapter_bg = rs.ReadString();
        var chapter_music = rs.ReadString();
        var new_obj_ChapterConfig = new ChapterConfig(id, chapter_num, chapter_name, type, star_condition, star_reward, chapter_reward, chapter_id, chapter_bg, chapter_music);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_ChapterConfig;
        this.array.push(new_obj_ChapterConfig);
    };
    ChapterConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "ChapterConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    ChapterConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    ChapterConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    ChapterConfig.resLoaded = false;
    ChapterConfig.dic = {};
    ChapterConfig.array = [];
    return ChapterConfig;
}(BaseConfig));
__reflect(ChapterConfig.prototype, "ChapterConfig");
//# sourceMappingURL=ChapterConfig.js.map