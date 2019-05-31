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
 * 管理类基类
*/
var BaseManager = (function (_super) {
    __extends(BaseManager, _super);
    function BaseManager() {
        return _super.call(this) || this;
    }
    BaseManager.prototype.init = function () {
    };
    BaseManager.prototype.update = function () {
    };
    BaseManager.prototype.reset = function () {
    };
    BaseManager.prototype.destroy = function () {
    };
    return BaseManager;
}(BaseClass));
__reflect(BaseManager.prototype, "BaseManager");
//# sourceMappingURL=BaseManager.js.map