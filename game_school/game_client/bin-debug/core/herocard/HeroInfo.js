var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var HeroData = (function () {
    function HeroData(id) {
    }
    Object.defineProperty(HeroData.prototype, "UId", {
        get: function () { return this.uid; },
        enumerable: true,
        configurable: true
    });
    return HeroData;
}());
__reflect(HeroData.prototype, "HeroData");
//# sourceMappingURL=HeroInfo.js.map