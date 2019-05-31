var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * girl基础信息  拥有的聊天信息，朋友圈信息等
 */
var GirlInfo = (function () {
    function GirlInfo(id, player) {
        this.girlId = 0; //表格id
        this.uid = ""; //唯一id
        this.friendlyNum = 0; //友好度
        this.headIcon = ""; //头像图片
        this.girlName = ""; //名称
        this.girlId = id;
        this.uid = App.MathUtils.uuid(10, 16);
        this.config = GirlConfig.GetConfig(id);
        this.headIcon = this.config.icon;
        this.girlName = this.config.name;
        this.player = player;
    }
    Object.defineProperty(GirlInfo.prototype, "GirlId", {
        get: function () { return this.girlId; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(GirlInfo.prototype, "Config", {
        get: function () { return this.config; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(GirlInfo.prototype, "UId", {
        get: function () { return this.uid; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(GirlInfo.prototype, "FriendlyNum", {
        get: function () { return this.friendlyNum; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(GirlInfo.prototype, "HeadIcon", {
        get: function () { return this.headIcon; },
        set: function (value) { this.headIcon = value; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(GirlInfo.prototype, "GirlName", {
        get: function () { return this.girlName; },
        set: function (value) { this.girlName = value; },
        enumerable: true,
        configurable: true
    });
    GirlInfo.prototype.SetFriendlyNum = function (value) {
        this.friendlyNum += value;
    };
    return GirlInfo;
}());
__reflect(GirlInfo.prototype, "GirlInfo");
//# sourceMappingURL=GirlInfo.js.map