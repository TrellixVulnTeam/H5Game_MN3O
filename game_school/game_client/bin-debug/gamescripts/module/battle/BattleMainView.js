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
 * 战斗主界面
 */
var BattleMainView = (function (_super) {
    __extends(BattleMainView, _super);
    function BattleMainView($controller, $parent) {
        return _super.call(this, $controller, $parent) || this;
        //this.skinName="resource/skins/MainBattle.exml";
    }
    BattleMainView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
    };
    BattleMainView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    BattleMainView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
    };
    BattleMainView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    return BattleMainView;
}(BaseEuiView));
__reflect(BattleMainView.prototype, "BattleMainView");
//# sourceMappingURL=BattleMainView.js.map