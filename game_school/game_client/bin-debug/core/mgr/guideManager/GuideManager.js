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
var TriggerType;
(function (TriggerType) {
    TriggerType[TriggerType["Trigger_No"] = 0] = "Trigger_No";
    TriggerType[TriggerType["Trigger_Plot"] = 1] = "Trigger_Plot";
    TriggerType[TriggerType["Trigger_Fighting"] = 2] = "Trigger_Fighting";
})(TriggerType || (TriggerType = {}));
/**
 * 指引管理
*/
var GuideManager = (function (_super) {
    __extends(GuideManager, _super);
    function GuideManager() {
        var _this = _super.call(this) || this;
        _this.isGuide = "newPlayerGuide00"; //指引
        _this.isSaveKeyData(_this.isGuide, "true");
        return _this;
    }
    /**
     * 初始key值
    */
    GuideManager.prototype.isSaveKeyData = function (str, key) {
        if (egret.localStorage.getItem(str) == null) {
            egret.localStorage.setItem(str, key);
        }
    };
    GuideManager.prototype.setIsGuide = function (bool) {
        return egret.localStorage.setItem(this.isGuide, bool.toString());
    };
    Object.defineProperty(GuideManager.prototype, "getIsGuide", {
        get: function () {
            return egret.localStorage.getItem(this.isGuide) == "true";
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 剧情指引
    */
    GuideManager.prototype.guidePlotById = function (strId) {
        var config = GuideConfig.GetConfig(strId);
        if (config != null && config.triggerType == TriggerType.Trigger_Plot) {
            App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, config.para2, function () {
                App.ViewManager.close(ViewConst.Dialog);
            }.bind(this), 0, 0, "", "");
            // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, config.para2, function () {
            //     App.ViewManager.close(ViewConst.Dialog);
            // });
        }
    };
    return GuideManager;
}(BaseManager));
__reflect(GuideManager.prototype, "GuideManager");
/**
 * 指引锁屏
*/
var GuideMask = (function (_super) {
    __extends(GuideMask, _super);
    function GuideMask(child, callBack, str, isBtn, adjustX, adjustY) {
        if (isBtn === void 0) { isBtn = true; }
        if (adjustX === void 0) { adjustX = 0; }
        if (adjustY === void 0) { adjustY = 0; }
        var _this = _super.call(this, null, null) || this;
        _this.btn = null;
        _this.item = null;
        _this.skinName = "resource/skins/New_player_guide.exml";
        if (isBtn) {
            _this.initChildBtn(child, str);
        }
        else {
            _this.item = child;
            _this.addChild(_this.item);
        }
        _this.initChildMc(adjustX, adjustY);
        _this.addBtnEventListener(callBack);
        return _this;
    }
    GuideMask.prototype.initChildBtn = function (btn, str) {
        var newBtn = new eui.Button();
        newBtn.skinName = btn.skinName;
        newBtn.width = btn.width;
        newBtn.height = btn.height;
        newBtn.x = btn.localToGlobal().x;
        newBtn.y = btn.localToGlobal().y;
        newBtn.label = str;
        this.btn = newBtn;
        this.addChild(this.btn);
    };
    GuideMask.prototype.initChildMc = function (adjustX, adjustY) {
        var data = RES.getRes("ui_effect_json");
        var txtr = RES.getRes("ui_effect_png");
        var mcFactory = new egret.MovieClipDataFactory(data, txtr);
        this.movieClip = new egret.MovieClip(mcFactory.generateMovieClipData("ui_effect"));
        this.movieClip.x = this.btn == null ? this.item.x : (this.btn.x < 0 ? 0 : this.btn.x);
        this.movieClip.x += adjustX;
        this.movieClip.y = this.btn == null ? this.item.y : this.btn.y;
        this.movieClip.y += adjustY;
        this.movieClip.gotoAndPlay("dianji_2", -1);
        this.addChild(this.movieClip);
    };
    GuideMask.prototype.addBtnEventListener = function (callBack) {
        var _this = this;
        if (this.btn != null) {
            this.btn.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
                if (callBack != null) {
                    callBack();
                }
                _this.hide();
            }, this);
        }
        else {
            this.item.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
                if (callBack != null) {
                    callBack();
                }
                _this.hide();
            }, this);
        }
    };
    GuideMask.prototype.hide = function () {
        if (this.btn != null) {
            this.removeChild(this.btn);
        }
        if (this.item != null) {
            this.removeChild(this.item);
        }
        this.removeChild(this.movieClip);
        this.removeFromParent();
    };
    return GuideMask;
}(BaseEuiView));
__reflect(GuideMask.prototype, "GuideMask");
//# sourceMappingURL=GuideManager.js.map