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
 * 玩家信息管理
 */
var PlayerManager = (function (_super) {
    __extends(PlayerManager, _super);
    function PlayerManager() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    return PlayerManager;
}(PlayerBase));
__reflect(PlayerManager.prototype, "PlayerManager");
//# sourceMappingURL=PlayerManager.js.map