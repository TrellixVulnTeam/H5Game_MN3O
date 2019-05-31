var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/* 这个类,由BuffComponent管理*/
var AvatarBuffComponent = (function () {
    function AvatarBuffComponent(entity) {
        this.totalPlayNum = 0;
        this.entity = entity;
        this.start();
    }
    AvatarBuffComponent.prototype.start = function () {
        this.mMovieClip = ObjectPool.pop("AvatarBuffMovieClip", GameResGroupName.BuffeffGroup, this.entity.buffeffpath, this.entity.buffName, this.entity);
        this.mMovieClip.Init(GameResGroupName.BuffeffGroup, this.entity.buffeffpath, this.entity.buffName, this.entity);
        this.mMovieClip.start();
        var avatarComponent = this.entity.getComponent(ComponentType.Dragon);
        this.mcParent = avatarComponent.Body;
    };
    AvatarBuffComponent.prototype.stop = function () {
        this.mMovieClip.stop();
        ObjectPool.push(this.mMovieClip);
        this.mMovieClip = null;
        this.mcParent = null;
    };
    AvatarBuffComponent.prototype.update = function (advancedTime) {
        if (this.mMovieClip.MovieClip.parent) {
            this.mMovieClip.update(advancedTime);
        }
    };
    AvatarBuffComponent.prototype.PlayBuffEffect = function (name, buff, totalPlayNum) {
        if (totalPlayNum === void 0) { totalPlayNum = 0; }
        this.mbuffEffectName = name;
        this.totalPlayNum = totalPlayNum;
        //this.setPos(buff);
        this.startMc();
    };
    AvatarBuffComponent.prototype.setPos = function (buff) {
        var point = new egret.Point();
        //point.x += buff.MagicConfig.effectPosition[0];
        //point.y += buff.MagicConfig.effectPosition[1];
        this.mMovieClip.MovieClip.x = point.x;
        this.mMovieClip.MovieClip.y = point.y;
    };
    AvatarBuffComponent.prototype.startMc = function () {
        this.mMovieClip.MovieClip.gotoAction(this.mbuffEffectName, this.entity.dir, true, this.totalPlayNum);
        if (this.entity.dir == Dir.Top
            || this.entity.dir == Dir.TopLeft
            || this.entity.dir == Dir.TopRight) {
            this.mcParent.addChildAt(this.mMovieClip.MovieClip, 0);
        }
        else {
            this.mcParent.addChild(this.mMovieClip.MovieClip);
        }
    };
    AvatarBuffComponent.prototype.stopMc = function () {
        App.DisplayUtils.removeFromParent(this.mMovieClip.MovieClip);
        this.mMovieClip.MovieClip.x = 0;
        this.mMovieClip.MovieClip.y = 0;
    };
    AvatarBuffComponent.prototype.complateAction = function () {
        //this.stopMc();
    };
    Object.defineProperty(AvatarBuffComponent.prototype, "CurMovieClipData", {
        get: function () {
            return this.mMovieClip;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(AvatarBuffComponent.prototype, "BuffEffectName", {
        get: function () {
            return this.mbuffEffectName;
        },
        enumerable: true,
        configurable: true
    });
    return AvatarBuffComponent;
}());
__reflect(AvatarBuffComponent.prototype, "AvatarBuffComponent");
//# sourceMappingURL=AvatarBuffComponent.js.map