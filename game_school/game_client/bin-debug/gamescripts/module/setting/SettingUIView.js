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
var SettingUIView = (function (_super) {
    __extends(SettingUIView, _super);
    function SettingUIView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.addEventListener(eui.UIEvent.COMPLETE, _this.uiCompHandler, _this);
        return _this;
    }
    SettingUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.SettingUI);
    };
    SettingUIView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    SettingUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.onOpenUI();
        this.onInitBtnState();
    };
    SettingUIView.prototype.onOpenUI = function () {
        this.Group_set.rotation = 100;
        egret.Tween.get(this.Group_set, {})
            .to({ rotation: 0 }, 200);
    };
    SettingUIView.prototype.onInitBtnState = function () {
        this.music_set.value = App.SoundManager.getBgVolume() * 10;
        this.sound_set.value = App.SoundManager.getEffectVolume() * 10;
    };
    SettingUIView.prototype.uiCompHandler = function () {
        this.Group_set.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.onSetValue, this);
        this.music_set.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.onSetMusicSounc, this);
        this.sound_set.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.onSetMusicEffect, this);
        this.effect_set.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.onSetGameEffect, this);
        this.btn_save.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onSaveSetted, this);
        this.btn_close.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onSaveSetted, this);
    };
    SettingUIView.prototype.onSetValue = function () {
        App.SoundManager.setBgVolume((this.music_set.value / 10));
        App.SoundManager.setEffectVolume((this.sound_set.value / 10));
    };
    SettingUIView.prototype.onSetMusicSounc = function () {
        App.SoundManager.setBgVolume((this.music_set.value / 10));
    };
    SettingUIView.prototype.onSetMusicEffect = function () {
        App.SoundManager.setEffectVolume((this.sound_set.value / 10));
    };
    SettingUIView.prototype.onSetGameEffect = function () {
        //this.effect_set.value = 1;
    };
    SettingUIView.prototype.onSaveSetted = function () {
        if (App.SettingDataManager.setMusicSound(this.music_set.value / 10) &&
            App.SettingDataManager.setMusicEffectSound(this.sound_set.value / 10)) {
            this.onClose();
        }
    };
    return SettingUIView;
}(BaseEuiView));
__reflect(SettingUIView.prototype, "SettingUIView");
//# sourceMappingURL=SettingUIView.js.map