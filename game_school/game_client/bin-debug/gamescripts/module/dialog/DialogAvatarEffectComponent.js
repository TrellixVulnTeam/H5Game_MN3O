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
var DialogAvatarEffectComponent = (function () {
    function DialogAvatarEffectComponent(group) {
        //要播放的特效
        this.mcEffectList = []; //这里的特效是NEW出来的
        this.mcEffectEvent = {};
        this.group = group;
        this.start();
    }
    DialogAvatarEffectComponent.prototype.start = function () {
        this.dealTime = 0;
        this.dealInterval = 0;
        this.isRuning = true;
    };
    DialogAvatarEffectComponent.prototype.stop = function () {
        this.dealTime = null;
        this.dealInterval = null;
        this.isRuning = false;
        this.type = null;
        this.group = null;
        for (var i = 0; i < this.mcEffectList.length; i++) {
            this.mcEffectList[i].stop();
        }
    };
    DialogAvatarEffectComponent.prototype.update = function (advancedTime) {
        for (var i = 0; i < this.mcEffectList.length; i++) {
            this.mcEffectList[i].update(advancedTime);
        }
    };
    /**
    * 播放特效
    * @param id 特效的ID
    * @param effectPosType 特效的位置类型
    * @param effectType 特效类型
    */
    DialogAvatarEffectComponent.prototype.PlayEffect = function (id, point, effectPosType, callback) {
        if (effectPosType === void 0) { effectPosType = 0; }
        var effectConf = EffectConfig.GetConfig(id);
        if (effectConf == null)
            return;
        this.AddEffect(id, point, effectPosType, callback);
    };
    //添加一个特效
    DialogAvatarEffectComponent.prototype.AddEffect = function (id, point, effectPosType, callback) {
        if (this.mcEffectEvent[id]) {
            this.mcEffectEvent[id].push(callback);
        }
        else {
            var callList = [];
            callList.push(callback);
            this.mcEffectEvent[id] = callList;
        }
        var effect = new DialogEffectComponent(id, this.group, this);
        this.mcEffectList.push(effect);
        effect.MovieClip.x = point.x;
        effect.MovieClip.y = point.y;
        effect.PlayEffect(id, effectPosType);
    };
    //移除一个特效
    DialogAvatarEffectComponent.prototype.RemoveEffect = function (id) {
        var index = -1;
        for (var i = 0; i < this.mcEffectList.length; i++) {
            if (id == this.mcEffectList[i].EffectID) {
                index = i;
                this.mcEffectList[i].stopMc();
            }
        }
        for (var key in this.mcEffectEvent) {
            if (key == id.toString()) {
                for (var index_1 = 0; index_1 < this.mcEffectEvent[key].length; index_1++) {
                    if (this.mcEffectEvent[key][index_1] != null) {
                        this.mcEffectEvent[key][index_1]();
                        this.mcEffectEvent[key].splice(index_1, 1);
                    }
                }
            }
        }
        if (index >= 0)
            this.mcEffectList.splice(index, 1);
    };
    DialogAvatarEffectComponent.prototype.RemoveAllEffect = function () {
        var array = [];
        for (var i = 0; i < this.mcEffectList.length; i++) {
            var oldeff = this.mcEffectList[i];
            array.push(oldeff.EffectID);
        }
        for (var i = 0; i < array.length; i++) {
            this.RemoveEffect(array[i]);
        }
    };
    return DialogAvatarEffectComponent;
}());
__reflect(DialogAvatarEffectComponent.prototype, "DialogAvatarEffectComponent");
var DialogEffectMovieClip = (function (_super) {
    __extends(DialogEffectMovieClip, _super);
    function DialogEffectMovieClip() {
        return _super.call(this) || this;
    }
    DialogEffectMovieClip.prototype.Init = function (gameResGroupName, mcpath, mcname, entity) {
        _super.prototype.Init.call(this, gameResGroupName, mcpath, mcname, entity);
    };
    DialogEffectMovieClip.prototype.SetEffectID = function (ID, mHand) {
        this.mEffectID = ID;
        this.mHand = mHand;
    };
    DialogEffectMovieClip.prototype.start = function () {
        _super.prototype.start.call(this);
    };
    DialogEffectMovieClip.prototype.stop = function () {
        _super.prototype.stop.call(this);
    };
    DialogEffectMovieClip.prototype.update = function (advancetime) {
        _super.prototype.update.call(this, advancetime);
        if (this.MovieClip)
            this.MovieClip.runAction(advancetime);
    };
    DialogEffectMovieClip.prototype.complateAction = function () {
        _super.prototype.complateAction.call(this);
        var playNum = this.MovieClip.GetPlayNum(); //获取播放次数,非循环的播放完毕会自毁
        if (playNum != 0) {
            this.mHand.RemoveEffect(this.mEffectID);
        }
    };
    return DialogEffectMovieClip;
}(MovieClipComponentBase));
__reflect(DialogEffectMovieClip.prototype, "DialogEffectMovieClip");
//# sourceMappingURL=DialogAvatarEffectComponent.js.map