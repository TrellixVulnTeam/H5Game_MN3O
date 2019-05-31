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
var GuiConfig = (function (_super) {
    __extends(GuiConfig, _super);
    function GuiConfig(id, ResName, PosZ, EscClose, exclusion, hidemainui, ReadyToLoad, readyLoadGroup, switchSceneIsClose, dungeonHide, onlyHide, showloading, needFreeRes, AudioOfOpen, AudioOfClose, CanToTop) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.ResName = ResName;
        _this.PosZ = PosZ;
        _this.EscClose = EscClose;
        _this.exclusion = exclusion;
        _this.hidemainui = hidemainui;
        _this.ReadyToLoad = ReadyToLoad;
        _this.readyLoadGroup = readyLoadGroup;
        _this.switchSceneIsClose = switchSceneIsClose;
        _this.dungeonHide = dungeonHide;
        _this.onlyHide = onlyHide;
        _this.showloading = showloading;
        _this.needFreeRes = needFreeRes;
        _this.AudioOfOpen = AudioOfOpen;
        _this.AudioOfClose = AudioOfClose;
        _this.CanToTop = CanToTop;
        return _this;
    }
    GuiConfig.Init = function () {
        this.LoadRes();
    };
    GuiConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "GuiConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 16) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("GuiConfig");
        this.resLoaded = true;
    };
    GuiConfig.Add_Item = function (rs) {
        var arr_item_len_GuiConfig;
        var id = rs.ReadInt();
        var ResName = rs.ReadString();
        var PosZ = rs.ReadInt();
        var EscClose = rs.ReadBool();
        arr_item_len_GuiConfig = rs.ReadShort();
        var exclusion = [];
        for (var i = 0; i < arr_item_len_GuiConfig; ++i)
            exclusion[i] =
                rs.ReadInt();
        arr_item_len_GuiConfig = rs.ReadShort();
        var hidemainui = [];
        for (var i = 0; i < arr_item_len_GuiConfig; ++i)
            hidemainui[i] =
                rs.ReadInt();
        var ReadyToLoad = rs.ReadBool();
        arr_item_len_GuiConfig = rs.ReadShort();
        var readyLoadGroup = [];
        for (var i = 0; i < arr_item_len_GuiConfig; ++i)
            readyLoadGroup[i] =
                rs.ReadString();
        var switchSceneIsClose = rs.ReadBool();
        var dungeonHide = rs.ReadBool();
        var onlyHide = rs.ReadBool();
        var showloading = rs.ReadBool();
        var needFreeRes = rs.ReadBool();
        var AudioOfOpen = rs.ReadString();
        var AudioOfClose = rs.ReadString();
        var CanToTop = rs.ReadBool();
        var new_obj_GuiConfig = new GuiConfig(id, ResName, PosZ, EscClose, exclusion, hidemainui, ReadyToLoad, readyLoadGroup, switchSceneIsClose, dungeonHide, onlyHide, showloading, needFreeRes, AudioOfOpen, AudioOfClose, CanToTop);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_GuiConfig;
        this.array.push(new_obj_GuiConfig);
    };
    GuiConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "GuiConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    GuiConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    GuiConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    GuiConfig.resLoaded = false;
    GuiConfig.dic = {};
    GuiConfig.array = [];
    return GuiConfig;
}(BaseConfig));
__reflect(GuiConfig.prototype, "GuiConfig");
//# sourceMappingURL=GuiConfig.js.map