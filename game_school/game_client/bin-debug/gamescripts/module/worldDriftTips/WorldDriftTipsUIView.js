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
 * 飘字提示界面
 */
var WorldDriftTipsUIView = (function (_super) {
    __extends(WorldDriftTipsUIView, _super);
    function WorldDriftTipsUIView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.addEventListener(eui.UIEvent.COMPLETE, function () {
            _this.uiCompHandler($controller);
        }, _this);
        return _this;
    }
    WorldDriftTipsUIView.prototype.uiCompHandler = function ($controller) {
        this.fly.addEventListener(egret.Event.LEAVE_STAGE, this.onClose, this);
    };
    WorldDriftTipsUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.WorldDriftTipsUI);
    };
    WorldDriftTipsUIView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    WorldDriftTipsUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.label_content.text = this.content;
        this.fly.play(0);
        var time = 125; //动画播放时间//
        var intervalID = setInterval(function onTick() {
            time--;
            if (time < 0) {
                this.onClose();
                clearInterval(intervalID);
            }
        }.bind(this), 10);
    };
    WorldDriftTipsUIView.prototype.setContent = function (content) {
        this.content = content;
    };
    return WorldDriftTipsUIView;
}(BaseEuiView));
__reflect(WorldDriftTipsUIView.prototype, "WorldDriftTipsUIView");
//# sourceMappingURL=WorldDriftTipsUIView.js.map