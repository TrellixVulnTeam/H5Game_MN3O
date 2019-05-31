var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * 系统设置 本地数据
*/
var SettingConst = (function () {
    function SettingConst() {
    }
    SettingConst.musicKey = "musicKey"; //音量//
    SettingConst.musicEffectkey = "musicEffectkey"; //音效//
    SettingConst.gameEffect = "gameEffect"; //特效//
    return SettingConst;
}());
__reflect(SettingConst.prototype, "SettingConst");
//# sourceMappingURL=SettingConst.js.map