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
var DrawCardsUIController = (function (_super) {
    __extends(DrawCardsUIController, _super);
    function DrawCardsUIController() {
        var _this = _super.call(this) || this;
        _this.drawCardsModel = new DrawCardsUIModel(_this);
        _this.drawCardsProxy = new DrawCardsUIProxy(_this);
        _this.drawCardsView = new DrawCardsUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.DrawCardsUI, _this.drawCardsView);
        return _this;
    }
    return DrawCardsUIController;
}(BaseController));
__reflect(DrawCardsUIController.prototype, "DrawCardsUIController");
//# sourceMappingURL=DrawCardsUIController.js.map