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
var UIHintConfig = (function (_super) {
    __extends(UIHintConfig, _super);
    function UIHintConfig(id, type, okText, cancelText, countDown) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.type = type;
        _this.okText = okText;
        _this.cancelText = cancelText;
        _this.countDown = countDown;
        return _this;
    }
    UIHintConfig.Init = function () {
        this.LoadRes();
    };
    UIHintConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "UIHintConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 5) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("UIHintConfig");
        this.resLoaded = true;
    };
    UIHintConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var type = rs.ReadInt();
        var okText = rs.ReadString();
        var cancelText = rs.ReadString();
        var countDown = rs.ReadInt();
        var new_obj_UIHintConfig = new UIHintConfig(id, type, okText, cancelText, countDown);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_UIHintConfig;
        this.array.push(new_obj_UIHintConfig);
    };
    UIHintConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "UIHintConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    UIHintConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    UIHintConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    UIHintConfig.resLoaded = false;
    UIHintConfig.dic = {};
    UIHintConfig.array = [];
    return UIHintConfig;
}(BaseConfig));
__reflect(UIHintConfig.prototype, "UIHintConfig");
//# sourceMappingURL=UIHintConfig.js.map