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
var ModelConfig = (function (_super) {
    __extends(ModelConfig, _super);
    function ModelConfig(id, filename, bound_center, bound_size, size, position, animation, animation2, animationHurt, animationHurt2) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.filename = filename;
        _this.bound_center = bound_center;
        _this.bound_size = bound_size;
        _this.size = size;
        _this.position = position;
        _this.animation = animation;
        _this.animation2 = animation2;
        _this.animationHurt = animationHurt;
        _this.animationHurt2 = animationHurt2;
        return _this;
    }
    ModelConfig.Init = function () {
        this.LoadRes();
    };
    ModelConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "ModelConfig") {
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
        ConfFact.SetResLoad("ModelConfig");
        this.resLoaded = true;
    };
    ModelConfig.Add_Item = function (rs) {
        var arr_item_len_ModelConfig;
        var id = rs.ReadInt();
        var filename = rs.ReadString();
        arr_item_len_ModelConfig = rs.ReadShort();
        var bound_center = [];
        for (var i = 0; i < arr_item_len_ModelConfig; ++i)
            bound_center[i] =
                rs.ReadFloat();
        arr_item_len_ModelConfig = rs.ReadShort();
        var bound_size = [];
        for (var i = 0; i < arr_item_len_ModelConfig; ++i)
            bound_size[i] =
                rs.ReadFloat();
        var size = rs.ReadFloat();
        arr_item_len_ModelConfig = rs.ReadShort();
        var position = [];
        for (var i = 0; i < arr_item_len_ModelConfig; ++i)
            position[i] =
                rs.ReadInt();
        var animation = rs.ReadString();
        var animation2 = rs.ReadString();
        var animationHurt = rs.ReadString();
        var animationHurt2 = rs.ReadString();
        var new_obj_ModelConfig = new ModelConfig(id, filename, bound_center, bound_size, size, position, animation, animation2, animationHurt, animationHurt2);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_ModelConfig;
        this.array.push(new_obj_ModelConfig);
    };
    ModelConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "ModelConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    ModelConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    ModelConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    ModelConfig.resLoaded = false;
    ModelConfig.dic = {};
    ModelConfig.array = [];
    return ModelConfig;
}(BaseConfig));
__reflect(ModelConfig.prototype, "ModelConfig");
//# sourceMappingURL=ModelConfig.js.map