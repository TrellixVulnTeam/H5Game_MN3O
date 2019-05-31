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
 */
var SimpleLoading = (function (_super) {
    __extends(SimpleLoading, _super);
    function SimpleLoading() {
        var _this = _super.call(this) || this;
        _this.dobj = null;
        _this.isShow = false;
        _this.init();
        return _this;
    }
    SimpleLoading.prototype.init = function () {
        this.totalNum = ConfFact.ConfigCount();
        this.dobj = new egret.DisplayObjectContainer();
        RES.getResByUrl("resource/assets/bg/loading1.png", function (texture) {
            this.img = new egret.Bitmap();
            this.img.texture = texture;
            this.dobj.addChild(this.img);
            RES.getResByUrl("resource/assets/bg/loading2.png", function (texture) {
                this.probg = new egret.Bitmap();
                this.probg.texture = texture;
                this.probg.x = (App.StageUtils.getWidth() - this.probg.width) / 2;
                this.probg.y = App.StageUtils.getHeight() / 2;
                this.dobj.addChild(this.probg);
                RES.getResByUrl("resource/assets/bg/loading3.png", function (texture) {
                    this.proimg = new egret.Bitmap();
                    this.proimg.texture = texture;
                    this.proimg.x = (App.StageUtils.getWidth() - this.proimg.width) / 2;
                    this.proimg.y = App.StageUtils.getHeight() / 2;
                    this.dobj.addChild(this.proimg);
                    this.label = new egret.TextField();
                    this.label.size = 30;
                    this.label.textColor = 0xcc7c76;
                    this.dobj.addChild(this.label);
                }, this, RES.ResourceItem.TYPE_IMAGE);
            }, this, RES.ResourceItem.TYPE_IMAGE);
        }, this, RES.ResourceItem.TYPE_IMAGE);
    };
    SimpleLoading.prototype.showLoading = function () {
        this.isShow = true;
        App.StageUtils.getStage().addChild(this.dobj);
    };
    SimpleLoading.prototype.hideLoading = function () {
        if (this.dobj && this.dobj.parent) {
            App.StageUtils.getStage().removeChild(this.dobj);
        }
        this.isShow = false;
    };
    SimpleLoading.prototype.enterFrame = function () {
        if (this.isShow && this.label != null && this.proimg != null) {
            this.label.text = "config loading " + ConfFact.GetLoadedConfigName().length + " / " + this.totalNum;
            this.label.x = (App.StageUtils.getWidth() - this.label.width) / 2;
            this.label.y = App.StageUtils.getHeight() / 2 - this.proimg.height * 2;
            this.proimg.scrollRect = new egret.Rectangle(0, 0, this.proimg.width * (21 / this.totalNum), this.proimg.height);
        }
    };
    SimpleLoading.prototype.initFinish = function (callback) {
        var intervalID = setInterval(function onTick() {
            if (this.label != null && this.proimg != null) {
                callback();
                clearInterval(intervalID);
            }
        }.bind(this), 1);
    };
    return SimpleLoading;
}(BaseClass));
__reflect(SimpleLoading.prototype, "SimpleLoading");
//# sourceMappingURL=SimpleLoading.js.map