var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var DialogEffectComponent = (function () {
    function DialogEffectComponent(id, group, hand) {
        this.totalPlayNum = 1;
        this.group = group;
        this.mEffectID = id;
        this.mHand = hand;
        this.effConfig = EffectConfig.GetConfig(id);
        this.start();
    }
    DialogEffectComponent.prototype.start = function () {
        this.mMovieClip = ObjectPool.pop("DialogEffectMovieClip");
        this.mMovieClip.Init(GameResGroupName.BuffeffGroup, GameobjConst.Buffeffpath, this.effConfig.resourcesGroup, null);
        this.mMovieClip.start();
        this.mcParent = this.group;
    };
    DialogEffectComponent.prototype.stop = function () {
        if (this.mMovieClip) {
            this.mMovieClip.stop();
            ObjectPool.push(this.mMovieClip);
            this.mMovieClip = null;
            this.mcParent = null;
        }
    };
    DialogEffectComponent.prototype.update = function (advancedTime) {
        if (this.mMovieClip) {
            this.mMovieClip.update(advancedTime);
        }
    };
    /**
    * 播放特效
    * @param id 特效的ID
    * @param effectPosType 特效的位置类型
    */
    DialogEffectComponent.prototype.PlayEffect = function (id, effectPosType) {
        this.mEffectID = id;
        this.mMovieClip.SetEffectID(id, this.mHand);
        var effectConf = EffectConfig.GetConfig(id);
        if (effectConf == null)
            return;
        this.mEffectName = effectConf.effectResources;
        this.totalPlayNum = effectConf.repeat;
        this.setPos(effectPosType, new egret.Point(effectConf.position[0], effectConf.position[1]));
        this.startMc();
    };
    DialogEffectComponent.prototype.setPos = function (effctPosType, posPoint) {
        // var point: egret.Point = new egret.Point(); //最后取值的世界舞台坐标
        // let temp = this.mcParent.globalToLocal(point.x, point.y);
        // //加上偏移量     
        // temp.x += posPoint.x;
        // temp.y += posPoint.y;
        this.mMovieClip.MovieClip.x += posPoint.x;
        this.mMovieClip.MovieClip.y += posPoint.y;
    };
    DialogEffectComponent.prototype.startMc = function () {
        if (this.mEffectName) {
            // let skillComponent = <SkillComponent>this.entity.getComponent(ComponentType.Skill);
            // let target = skillComponent.GetTarget();
            // let dir = this.entity.dir;
            // if (!this.isCamp(this.entity, target)) {
            //     if (this.entity.dir == Dir.Left) {
            //         dir = Dir.Right;
            //     } else {
            //         dir = Dir.Left;
            //     }
            // }          
            this.mMovieClip.MovieClip.gotoAction(this.mEffectName, Dir.Left, true, this.totalPlayNum);
            this.mcParent.addChild(this.mMovieClip.MovieClip);
            // if (this.entity.dir == Dir.Top
            //     || this.entity.dir == Dir.TopLeft
            //     || this.entity.dir == Dir.TopRight) {
            //     this.mcParent.addChildAt(this.mMovieClip.MovieClip, 0);
            // } else {          
            // }
        }
    };
    DialogEffectComponent.prototype.stopMc = function () {
        if (this.mMovieClip)
            App.DisplayUtils.removeFromParent(this.mMovieClip.MovieClip);
        this.stop();
    };
    Object.defineProperty(DialogEffectComponent.prototype, "CurMovieClipData", {
        get: function () {
            return this.mMovieClip;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(DialogEffectComponent.prototype, "EffectName", {
        get: function () {
            return this.mEffectName;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(DialogEffectComponent.prototype, "EffectID", {
        get: function () {
            return this.mEffectID;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(DialogEffectComponent.prototype, "MovieClip", {
        get: function () {
            return this.mMovieClip.MovieClip;
        },
        enumerable: true,
        configurable: true
    });
    return DialogEffectComponent;
}());
__reflect(DialogEffectComponent.prototype, "DialogEffectComponent");
//# sourceMappingURL=DialogEffectComponent.js.map