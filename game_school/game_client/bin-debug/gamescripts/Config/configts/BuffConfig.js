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
var BuffConfig = (function (_super) {
    __extends(BuffConfig, _super);
    function BuffConfig(ID, name, desc, descPara, imageSet, Icon, isIconDisplay, friendlyLevel, dispelType, time, settlePriority, settleType, timeType, group, groupPriority, liveStyle, defaultLayers, maxLayers, controlBit, effectID1, effectID2, effectID3, effectID4, effectID5, effect, effectDelay, effectPosType) {
        var _this = _super.call(this) || this;
        _this.ID = ID;
        _this.name = name;
        _this.desc = desc;
        _this.descPara = descPara;
        _this.imageSet = imageSet;
        _this.Icon = Icon;
        _this.isIconDisplay = isIconDisplay;
        _this.friendlyLevel = friendlyLevel;
        _this.dispelType = dispelType;
        _this.time = time;
        _this.settlePriority = settlePriority;
        _this.settleType = settleType;
        _this.timeType = timeType;
        _this.group = group;
        _this.groupPriority = groupPriority;
        _this.liveStyle = liveStyle;
        _this.defaultLayers = defaultLayers;
        _this.maxLayers = maxLayers;
        _this.controlBit = controlBit;
        _this.effectID1 = effectID1;
        _this.effectID2 = effectID2;
        _this.effectID3 = effectID3;
        _this.effectID4 = effectID4;
        _this.effectID5 = effectID5;
        _this.effect = effect;
        _this.effectDelay = effectDelay;
        _this.effectPosType = effectPosType;
        return _this;
    }
    BuffConfig.Init = function () {
        this.LoadRes();
    };
    BuffConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "BuffConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 27) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("BuffConfig");
        this.resLoaded = true;
    };
    BuffConfig.Add_Item = function (rs) {
        var ID = rs.ReadInt();
        var name = rs.ReadString();
        var desc = rs.ReadString();
        var descPara = rs.ReadString();
        var imageSet = rs.ReadString();
        var Icon = rs.ReadString();
        var isIconDisplay = rs.ReadBool();
        var friendlyLevel = rs.ReadInt();
        var dispelType = rs.ReadInt();
        var time = rs.ReadInt();
        var settlePriority = rs.ReadInt();
        var settleType = rs.ReadInt();
        var timeType = rs.ReadInt();
        var group = rs.ReadInt();
        var groupPriority = rs.ReadInt();
        var liveStyle = rs.ReadInt();
        var defaultLayers = rs.ReadInt();
        var maxLayers = rs.ReadInt();
        var controlBit = rs.ReadInt();
        var effectID1 = rs.ReadInt();
        var effectID2 = rs.ReadInt();
        var effectID3 = rs.ReadInt();
        var effectID4 = rs.ReadInt();
        var effectID5 = rs.ReadInt();
        var effect = rs.ReadInt();
        var effectDelay = rs.ReadInt();
        var effectPosType = rs.ReadInt();
        var new_obj_BuffConfig = new BuffConfig(ID, name, desc, descPara, imageSet, Icon, isIconDisplay, friendlyLevel, dispelType, time, settlePriority, settleType, timeType, group, groupPriority, liveStyle, defaultLayers, maxLayers, controlBit, effectID1, effectID2, effectID3, effectID4, effectID5, effect, effectDelay, effectPosType);
        if (this.ContainsKey(ID)) {
            return;
        }
        this.dic[ID] = new_obj_BuffConfig;
        this.array.push(new_obj_BuffConfig);
    };
    BuffConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "BuffConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    BuffConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    BuffConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    BuffConfig.resLoaded = false;
    BuffConfig.dic = {};
    BuffConfig.array = [];
    return BuffConfig;
}(BaseConfig));
__reflect(BuffConfig.prototype, "BuffConfig");
//# sourceMappingURL=BuffConfig.js.map