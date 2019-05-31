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
 *
 */
var CreatureRoleUIProxy = (function (_super) {
    __extends(CreatureRoleUIProxy, _super);
    function CreatureRoleUIProxy($controller) {
        return _super.call(this, $controller) || this;
        //注册从服务器返回消息的监听
        //this.receiveServerMsg(CreatureRoleUIConst.creature_success, this.creatureSuccess, this);
    }
    return CreatureRoleUIProxy;
}(BaseProxy));
__reflect(CreatureRoleUIProxy.prototype, "CreatureRoleUIProxy");
//# sourceMappingURL=CreatureRoleUIProxy.js.map