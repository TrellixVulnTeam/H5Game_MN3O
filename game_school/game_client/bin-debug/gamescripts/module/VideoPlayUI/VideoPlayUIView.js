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
 * 视频播放UI,视图层
 * @constructor {sjz}
 * @data {2018-6-27}
 */
var VideoPlayUIView = (function (_super) {
    __extends(VideoPlayUIView, _super);
    function VideoPlayUIView(controller, parent) {
        var _this = _super.call(this, controller, parent) || this;
        _this.mIsEnteredUIScene = false; //首次进入UIScene显示登陆界面
        return _this;
    }
    VideoPlayUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
    };
    VideoPlayUIView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    VideoPlayUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.VideoPlayUI);
        this.btn_play.addEventListener(egret.TouchEvent.TOUCH_TAP, this.PlayVideo, this);
    };
    VideoPlayUIView.prototype.PlayVideo = function () {
        this.PlayGroup.visible = false;
        App.VideoUtils.PlayVideo("video_default.png", "start.mp4", function () {
            if (this.mIsEnteredUIScene == false) {
                this.mIsEnteredUIScene = true;
                App.ViewManager.close(ViewConst.VideoPlayUI);
                App.ViewManager.open(ViewConst.Login);
            }
        }.bind(this));
    };
    return VideoPlayUIView;
}(BaseEuiView));
__reflect(VideoPlayUIView.prototype, "VideoPlayUIView");
//# sourceMappingURL=VideoPlayUIView.js.map