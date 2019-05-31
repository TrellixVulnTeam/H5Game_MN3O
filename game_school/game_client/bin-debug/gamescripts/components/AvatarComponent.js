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
 * 骨骼组件
 */
var AvatarComponent = (function (_super) {
    __extends(AvatarComponent, _super);
    function AvatarComponent() {
        return _super.call(this) || this;
    }
    Object.defineProperty(AvatarComponent.prototype, "AvatarMovieClip", {
        get: function () {
            return this.mMovieClip;
        },
        enumerable: true,
        configurable: true
    });
    AvatarComponent.prototype.start = function () {
        _super.prototype.start.call(this);
        this.mMovieClip = ObjectPool.pop("AvatarMovieClip");
        this.mMovieClip.Init(GameResGroupName.AvatarGroup, this.entity.avatarPath, this.entity.avatarName, this.entity, this.entity.oriScale);
        this.mMovieClip.start();
    };
    AvatarComponent.prototype.stop = function () {
        _super.prototype.stop.call(this);
        this.mMovieClip.stop();
        ObjectPool.push(this.mMovieClip);
        this.mMovieClip = null;
    };
    AvatarComponent.prototype.update = function (advancedTime) {
        _super.prototype.update.call(this, advancedTime);
        this.setPos();
        /*if(!this.entity.TestClientBitState(ClientBits.CLIENT_BIT_MOVING) && !this.entity.TestClientBitState(ClientBits.CLIENT_BIT_CASTING)){
        }*/
        if (this.mMovieClip) {
            this.mMovieClip.update(advancedTime);
        }
    };
    AvatarComponent.prototype.PlayAct = function (act, callback) {
        this.entity.action = act;
        if ((this.entity.action != this.mMovieClip.MovieClip.getCurrAction() || this.entity.dir != this.mMovieClip.MovieClip.getCurrDir())) {
            // console.log("PlayAct::::"+"id"+this.entity.uid+"      "+this.entity.basicattr.Name+"   "+ this.entity.action);
            this.mMovieClip.MovieClip.playAction(this.entity.action, this.entity.dir);
        }
        if (callback) {
            callback();
        }
    };
    AvatarComponent.prototype.setPos = function () {
        if (this.mMovieClip) {
            if (this.mMovieClip.Body.x != this.entity.position.x) {
                this.mMovieClip.Body.x = this.entity.position.x;
            }
            if (this.mMovieClip.Body.y != this.entity.position.y) {
                this.mMovieClip.Body.y = this.entity.position.y;
            }
        }
    };
    return AvatarComponent;
}(Component));
__reflect(AvatarComponent.prototype, "AvatarComponent");
//# sourceMappingURL=AvatarComponent.js.map