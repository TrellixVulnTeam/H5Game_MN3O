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
var AvatarMovieClip = (function (_super) {
    __extends(AvatarMovieClip, _super);
    function AvatarMovieClip() {
        return _super.call(this) || this;
    }
    AvatarMovieClip.prototype.Init = function (gameResGroupName, mcpath, mcname, entity, scale) {
        _super.prototype.Init.call(this, gameResGroupName, mcpath, mcname, entity, scale);
    };
    AvatarMovieClip.prototype.start = function () {
        _super.prototype.start.call(this);
    };
    AvatarMovieClip.prototype.stop = function () {
        _super.prototype.stop.call(this);
    };
    AvatarMovieClip.prototype.update = function (advancetime) {
        _super.prototype.update.call(this, advancetime);
        if ((this.Entity.action != this.MovieClip.getCurrAction() || this.Entity.dir != this.MovieClip.getCurrDir())) {
            // console.log("update+id"+this.Entity.uid+"      "+this.Entity.basicattr.Name+"   "+ this.Entity.action);
            //this.MovieClip.DispatchEvent();
            this.MovieClip.playAction(this.Entity.action, this.Entity.dir);
        }
        this.MovieClip.runAction(advancetime);
    };
    AvatarMovieClip.prototype.complateAction = function () {
        _super.prototype.complateAction.call(this);
        if (this.MovieClip.getCurrAction() == Action.Die) {
            App.FightManager.removeplayer(this.Entity);
        }
        else {
            this.Entity.action = Action.Stand;
            this.MovieClip.gotoAction(this.Entity.action, this.Entity.dir);
        }
    };
    return AvatarMovieClip;
}(MovieClipComponentBase));
__reflect(AvatarMovieClip.prototype, "AvatarMovieClip");
//# sourceMappingURL=AvatarMovieClip.js.map