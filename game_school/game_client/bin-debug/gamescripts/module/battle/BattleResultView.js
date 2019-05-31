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
 * 战斗结算
 */
var BattleResultView = (function (_super) {
    __extends(BattleResultView, _super);
    function BattleResultView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        /**
         * 临时指引标记（战斗结算界面）
        */
        _this.isFirstGuide = false;
        return _this;
    }
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    BattleResultView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.BattleResult);
        this.isFirstGuide = App.GuideManager.getIsGuide;
        this.btn_ok.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            if (_this.isFirstGuide) {
                _this.addFirstGuide(); //退出界面播放剧情
            }
            else {
                App.SceneManager.runScene(SceneConsts.UI);
                App.ViewManager.open(ViewConst.MainUI);
                _this.onClose();
            }
        }, this);
    };
    /**
     * 临时指引1（退出结算界面）
    */
    BattleResultView.prototype.addFirstGuide = function () {
        this.isFirstGuide = false;
        App.SceneManager.runScene(SceneConsts.UI);
        this.onClose();
        //临时播剧情
        App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 104, function () {
            App.ViewManager.close(ViewConst.Dialog);
            App.ViewManager.open(ViewConst.ChapterChoose); //打开章节界面
        }.bind(this), 0, 0, "", "");
        // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 104, function () {
        //     App.ViewManager.close(ViewConst.Dialog);
        //     App.ViewManager.open(ViewConst.ChapterChoose);//打开章节界面
        // });
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    BattleResultView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    BattleResultView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    BattleResultView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    return BattleResultView;
}(BaseEuiView));
__reflect(BattleResultView.prototype, "BattleResultView");
//# sourceMappingURL=BattleResultView.js.map