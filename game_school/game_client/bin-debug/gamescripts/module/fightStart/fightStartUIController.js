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
var fightStartUIController = (function (_super) {
    __extends(fightStartUIController, _super);
    function fightStartUIController() {
        var _this = _super.call(this) || this;
        _this.fightStartModel = new fightStartUIModel(_this);
        _this.fightStartProxy = new fightStartUIProxy(_this);
        _this.fightStartView = new fightStartUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.FightStartUI, _this.fightStartView);
        return _this;
    }
    return fightStartUIController;
}(BaseController));
__reflect(fightStartUIController.prototype, "fightStartUIController");
//# sourceMappingURL=fightStartUIController.js.map