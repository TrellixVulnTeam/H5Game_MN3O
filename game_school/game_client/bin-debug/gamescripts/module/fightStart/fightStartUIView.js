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
var fightStartUIView = (function (_super) {
    __extends(fightStartUIView, _super);
    function fightStartUIView($controller, $parent) {
        return _super.call(this, $controller, $parent) || this;
    }
    fightStartUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.FightStartUI);
    };
    fightStartUIView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    return fightStartUIView;
}(BaseEuiView));
__reflect(fightStartUIView.prototype, "fightStartUIView");
//# sourceMappingURL=fightStartUIView.js.map