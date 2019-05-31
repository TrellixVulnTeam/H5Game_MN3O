var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var ColorConst = (function () {
    function ColorConst() {
    }
    ColorConst.Yellow_Light = 0xFFFF00; //亮黄
    ColorConst.Red_Light = 0xFF0000; //红
    ColorConst.Green_Light = 0x008000; //绿
    return ColorConst;
}());
__reflect(ColorConst.prototype, "ColorConst");
//# sourceMappingURL=ColorConst.js.map