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
var MoveComponent = (function (_super) {
    __extends(MoveComponent, _super);
    function MoveComponent() {
        return _super.call(this) || this;
    }
    MoveComponent.prototype.start = function () {
        _super.prototype.start.call(this);
    };
    MoveComponent.prototype.stop = function () {
        _super.prototype.stop.call(this);
    };
    MoveComponent.prototype.update = function (advancedTime) {
        _super.prototype.update.call(this, advancedTime);
    };
    /**
     * 移动
     * @param point 坐标
     * @param callback 移动结束回调
     */
    MoveComponent.prototype.DoMove = function (point, callback, time) {
        if (time === void 0) { time = 500; }
        this.entity.AddClientBitState(ClientBits.CLIENT_BIT_MOVING);
        var avatarCom = this.entity.getComponent(ComponentType.Dragon);
        if (avatarCom) {
            avatarCom.PlayAct(ActionStr.Move);
        }
        //console.log(" posX = " + this.entity.position.x + " posY = " + this.entity.position.y)
        //console.log(" bodyX = " + avatarCom.body.x + " bodyY = " + avatarCom.body.y)
        //console.log(" pointX = " + point.x + " pointY = " + point.y)
        egret.Tween.get(this.entity.position /*avatarCom.body*/).to({ y: point.y, x: point.x /*, alpha: 1 */ }, time)
            .call(function () {
            this.entity.DelClientBitState(ClientBits.CLIENT_BIT_MOVING);
            if (callback) {
                callback();
            }
        }.bind(this));
    };
    return MoveComponent;
}(Component));
__reflect(MoveComponent.prototype, "MoveComponent");
//# sourceMappingURL=MoveComponent.js.map