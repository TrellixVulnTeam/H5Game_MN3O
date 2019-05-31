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
 * 战斗确认界面
 */
var ChapterMseeagView = (function (_super) {
    __extends(ChapterMseeagView, _super);
    function ChapterMseeagView($controller, $parent) {
        return _super.call(this, $controller, $parent) || this;
    }
    Object.defineProperty(ChapterMseeagView.prototype, "Model", {
        get: function () {
            return App.ControllerManager.getControllerModel(ControllerConst.Chapter);
        },
        enumerable: true,
        configurable: true
    });
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    ChapterMseeagView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.ChapterMseeag);
        this.btn_close.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            TweenManager.scaleTween(_this, _this, 0, 249, function () {
                _this.onClose();
            });
        }, this);
        this.btn_battle.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.SceneManager.runScene(SceneConsts.CCG_FIGHT, _this.Model.curCheckPoint);
            _this.onClose();
        }, this);
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    ChapterMseeagView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    ChapterMseeagView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        TweenManager.scaleTween(this, this, 1, 249, function () {
        });
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    ChapterMseeagView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    return ChapterMseeagView;
}(BaseEuiView));
__reflect(ChapterMseeagView.prototype, "ChapterMseeagView");
//# sourceMappingURL=ChapterMseeagView.js.map