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
/**
 * 设置本地数据
*/
var SettingDataManager = (function (_super) {
    __extends(SettingDataManager, _super);
    function SettingDataManager() {
        var _this = _super.call(this) || this;
        _this.isSaveKeyData(SettingConst.musicKey, "1");
        _this.isSaveKeyData(SettingConst.musicEffectkey, "1");
        _this.isSaveKeyData(SettingConst.gameEffect, "true");
        return _this;
    }
    /**
     * 初始key值
    */
    SettingDataManager.prototype.isSaveKeyData = function (str, key) {
        if (egret.localStorage.getItem(str) == null) {
            egret.localStorage.setItem(str, key);
        }
    };
    /**
     * 保存背景音乐值
    */
    SettingDataManager.prototype.setMusicSound = function (num) {
        App.SoundManager.setBgVolume(num);
        return egret.localStorage.setItem(SettingConst.musicKey, num.toString());
    };
    /**
     * 获得背景音乐值
    */
    SettingDataManager.prototype.getMusicSound = function () {
        return Number(egret.localStorage.getItem(SettingConst.musicKey));
    };
    /**
     * 保存背景音效值
    */
    SettingDataManager.prototype.setMusicEffectSound = function (num) {
        App.SoundManager.setEffectVolume(num);
        return egret.localStorage.setItem(SettingConst.musicEffectkey, num.toString());
    };
    /**
     * 获得背景音效值
    */
    SettingDataManager.prototype.getMusicEffectSound = function () {
        return Number(egret.localStorage.getItem(SettingConst.musicEffectkey));
    };
    /**
     * 游戏特效开启或关闭
    */
    SettingDataManager.prototype.turnOnOrOffGameEffect = function (bool) {
        return egret.localStorage.setItem(SettingConst.gameEffect, bool.toString());
    };
    /**
     * 游戏特效是否开启
    */
    SettingDataManager.prototype.isGameEffectOpen = function () {
        return egret.localStorage.getItem(SettingConst.gameEffect) == "true";
    };
    return SettingDataManager;
}(BaseClass));
__reflect(SettingDataManager.prototype, "SettingDataManager");
//# sourceMappingURL=SettingDataManager.js.map