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
 * 龙骨组件
 */
var DragonComponent = (function (_super) {
    __extends(DragonComponent, _super);
    function DragonComponent() {
        var _this = _super.call(this) || this;
        _this.actionArray = [
            "attack",
            "chant",
            "dead",
            "hit01",
            "hit02",
            "hit03",
            "hit04",
            "idle",
            "run",
            "skill",
            "win"
        ];
        return _this;
    }
    DragonComponent.prototype.start = function () {
        _super.prototype.start.call(this);
        if (!this.body) {
            this.body = new egret.DisplayObjectContainer(); // ObjectPool.pop("egret.DisplayObjectContainer");
        }
        this.body.x = 0;
        this.body.y = 0;
        this.body.removeChildren();
        this.entity.gameView.addChild(this.body);
        if (!this.mDragon) {
            this.mDragon = new DragonCombatantObject(); // ObjectPool.pop("DragonCombatantObject");
        }
        this.mDragon.x = 0;
        this.mDragon.y = 0;
        this.body.addChild(this.mDragon);
        this.mDragon.init(this.entity.avatarName, "armatureName", this.actionArray, ActionStr.Stand);
        this.mDragon.armature.touchEnabled = true;
        //this.mDragon.armature.$addListener(egret.TouchEvent.TOUCH_BEGIN, this.TurnDragon, this);
        this.body.scaleX = this.entity.oriScale;
        this.body.scaleY = this.entity.oriScale;
        this.TurnDragon(this.entity.camp == Camp.Friendly);
    };
    DragonComponent.prototype.TurnDragon = function (positive) {
        if (positive === void 0) { positive = undefined; }
        if (positive == undefined) {
            if (this.positive) {
                this.mDragon.armature.skewY = 180;
            }
            else {
                this.mDragon.armature.skewY = 0;
            }
            this.positive = !positive;
            return;
        }
        if (positive)
            this.mDragon.armature.skewY = 0;
        else
            this.mDragon.armature.skewY = 180;
        this.positive = positive;
    };
    DragonComponent.prototype.ArmatureClick = function () {
    };
    DragonComponent.prototype.stop = function () {
        _super.prototype.stop.call(this);
        this.mDragon.destory();
        App.DisplayUtils.removeFromParent(this.body);
        ObjectPool.push(this.body);
        App.DisplayUtils.removeFromParent(this.mDragon);
        ObjectPool.push(this.mDragon);
    };
    DragonComponent.prototype.update = function (advancedTime) {
        _super.prototype.update.call(this, advancedTime);
        this.setPos();
    };
    DragonComponent.prototype.PlayAct = function (act, playNum, callback) {
        if (playNum === void 0) { playNum = 1; }
        if (!act || act == "") {
            if (callback) {
                callback();
            }
            return;
        }
        if (act == ActionStr.Stand || act == ActionStr.Move) {
            this.playNum = 0;
        }
        else {
            this.playNum = playNum;
        }
        this.mDragon.armature.play(act, this.playNum);
        this.currentAction = act;
        if (act != ActionStr.Stand) {
            var endCallback_1 = function () {
                if (this.playNum != 0 && this.currentAction != ActionStr.Die) {
                    this.mDragon.armature.play(ActionStr.Stand, 0);
                    this.currentAction = ActionStr.Stand;
                }
                this.mDragon.armature.removeCompleteCallFunc(endCallback_1, act);
                if (callback) {
                    callback();
                }
            }.bind(this);
            this.mDragon.armature.addCompleteCallFunc(endCallback_1, act);
        }
    };
    DragonComponent.prototype.setPos = function () {
        if (this.Body.x != this.entity.position.x) {
            this.Body.x = this.entity.position.x;
        }
        if (this.Body.y != this.entity.position.y) {
            this.Body.y = this.entity.position.y;
        }
    };
    Object.defineProperty(DragonComponent.prototype, "Body", {
        get: function () { return this.body; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(DragonComponent.prototype, "MDragon", {
        get: function () { return this.mDragon; },
        enumerable: true,
        configurable: true
    });
    ;
    return DragonComponent;
}(Component));
__reflect(DragonComponent.prototype, "DragonComponent");
//# sourceMappingURL=DragonComponent.js.map