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
var VideoUtils = (function (_super) {
    __extends(VideoUtils, _super);
    function VideoUtils() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    VideoUtils.prototype.PlayVideo = function (loadimg, videourl, callback) {
        // if(App.DeviceUtils.IsMobile){
        //     // let video = document.getElementById("SVideo");
        //     // window["PlayVideo"](true,null,null,videourl,callback);
        //     window["PlayeVideoOnMobile"]("resource/assets/video/"+videourl,"resource/assets/video/"+loadimg,callback);移动端QQ浏览器会有bug
        // }
        // else
        {
            //http://res.w360.jygs.yx-g.com/school
            var webview_1 = new WebView("http://res.w360.jygs.yx-g.com/school/video.html");
            webview_1.x = 0;
            webview_1.y = 0;
            webview_1.height = 1334;
            webview_1.width = 750;
            webview_1.show();
            App.TimerManager.doTimer(1000, 1, function () {
                var all = webview_1.iframe.contentWindow.document.all;
                var video;
                for (var i = 0; i < all.length; i++) {
                    if (all[i].nodeName == "VIDEO") {
                        video = all[i];
                    }
                }
                if (video) {
                    window["PlayVideo"](video, "resource/assets/video/" + loadimg, "resource/assets/video/" + videourl, function () {
                        if (callback) {
                            callback();
                        }
                        webview_1.destroy();
                    });
                }
            }, this);
        }
    };
    return VideoUtils;
}(BaseClass));
__reflect(VideoUtils.prototype, "VideoUtils");
//# sourceMappingURL=VideoUtils.js.map