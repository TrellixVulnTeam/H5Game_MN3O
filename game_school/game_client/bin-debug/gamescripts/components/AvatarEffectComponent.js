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
var AvatarEffectComponent = (function (_super) {
    __extends(AvatarEffectComponent, _super);
    function AvatarEffectComponent() {
        var _this = _super.call(this) || this;
        //要播放的特效
        _this.mcEffectList = []; //这里的特效是NEW出来的
        _this.mcEffectEvent = {};
        return _this;
    }
    AvatarEffectComponent.prototype.start = function () {
        _super.prototype.start.call(this);
    };
    AvatarEffectComponent.prototype.stop = function () {
        _super.prototype.stop.call(this);
        for (var i = 0; i < this.mcEffectList.length; i++) {
            this.RemoveEffect(this.mcEffectList[i].EffectID);
            // this.mcEffectList[i].stopMc();
        }
    };
    AvatarEffectComponent.prototype.update = function (advancedTime) {
        _super.prototype.update.call(this, advancedTime);
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
    AvatarEffectComponent.prototype.PlayEffect = function (id, effectPosType, effectType, callback) {
        var effectConf = EffectConfig.GetConfig(id);
        if (effectConf == null)
            return;
        this.AddEffect(id, effectPosType, effectType, callback);
    };
    //添加一个特效
    AvatarEffectComponent.prototype.AddEffect = function (id, effectPosType, effectType, callback) {
        if (this.mcEffectEvent[id]) {
            this.mcEffectEvent[id].push(callback);
        }
        else {
            var callList = [];
            callList.push(callback);
            this.mcEffectEvent[id] = callList;
        }
        var effect = new EffectComponent(id, this.entity, effectType, this);
        this.mcEffectList.push(effect);
        // console.log("AddEffect::"+"  "+id+"  :"+this.entity.basicattr.Name +"  :"+this.entity.uid);              
        effect.PlayEffect(id, effectPosType);
    };
    //移除一个特效
    AvatarEffectComponent.prototype.RemoveEffect = function (id) {
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
    return AvatarEffectComponent;
}(Component));
__reflect(AvatarEffectComponent.prototype, "AvatarEffectComponent");
var EffectMovieClip = (function (_super) {
    __extends(EffectMovieClip, _super);
    function EffectMovieClip() {
        return _super.call(this) || this;
    }
    EffectMovieClip.prototype.Init = function (gameResGroupName, mcpath, mcname, entity, scale) {
        if (scale === void 0) { scale = 1; }
        _super.prototype.Init.call(this, gameResGroupName, mcpath, mcname, entity, scale);
    };
    EffectMovieClip.prototype.SetEffectID = function (ID, avatarEffectComponent) {
        this.mEffectID = ID;
        this.avatarEffectComponent = avatarEffectComponent;
    };
    EffectMovieClip.prototype.start = function (_body) {
        _super.prototype.start.call(this, _body);
    };
    EffectMovieClip.prototype.stop = function () {
        _super.prototype.stop.call(this, false); //这里涉及到移除body,特效的body,就是人,所以这里不能移除这个body,这个false,绝对不能删
    };
    EffectMovieClip.prototype.update = function (advancetime) {
        _super.prototype.update.call(this, advancetime);
        if (this.MovieClip) {
            this.MovieClip.runAction(advancetime);
        }
    };
    EffectMovieClip.prototype.complateAction = function () {
        _super.prototype.complateAction.call(this);
        var playNum = this.MovieClip.GetPlayNum(); //获取播放次数,非循环的播放完毕会自毁
        if (playNum != 0) {
            // console.log("complateAction::"+"    name:"+this.Entity.basicattr.Name+"    uid:"+this.Entity.uid+"   id"+this.mEffectID);
            this.avatarEffectComponent.RemoveEffect(this.mEffectID);
        }
    };
    return EffectMovieClip;
}(MovieClipComponentBase));
__reflect(EffectMovieClip.prototype, "EffectMovieClip");
//# sourceMappingURL=AvatarEffectComponent.js.map