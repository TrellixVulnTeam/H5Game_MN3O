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
 * 视频播放UI,控制层
 * @constructor {sjz}
 * @data {2018-6-27}
 */
var VideoPlayUIController = (function (_super) {
    __extends(VideoPlayUIController, _super);
    function VideoPlayUIController() {
        var _this = _super.call(this) || this;
        _this.videoview = new VideoPlayUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.VideoPlayUI, _this.videoview);
        return _this;
    }
    return VideoPlayUIController;
}(BaseController));
__reflect(VideoPlayUIController.prototype, "VideoPlayUIController");
//# sourceMappingURL=VideoPlayUIController.js.map