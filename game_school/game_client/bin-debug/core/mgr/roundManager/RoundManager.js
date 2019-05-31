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
 * created by zsy on 2018-6-12.
 * 回合管理
 */
var RoundManager = (function (_super) {
    __extends(RoundManager, _super);
    function RoundManager() {
        var _this = _super.call(this) || this;
        _this.roundCount = 0; //回合数
        return _this;
    }
    RoundManager.prototype.RoundStart = function () {
    };
    RoundManager.prototype.RoundFinish = function () {
    };
    return RoundManager;
}(BaseClass));
__reflect(RoundManager.prototype, "RoundManager");
//# sourceMappingURL=RoundManager.js.map