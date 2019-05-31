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
 * created by sjz on 2018-5-31
 * 龙骨对象基类
 */
var DragonObjectBase = (function (_super) {
    __extends(DragonObjectBase, _super);
    function DragonObjectBase() {
        var _this = _super.call(this) || this;
        _this.originX = 0;
        _this.originY = 0;
        _this.originZ = 0;
        _this.trueY = 0;
        return _this;
    }
    DragonObjectBase.prototype.init = function (res_ske_json, armatureName, actionName, oriAction, playSpeed) {
        if (playSpeed === void 0) { playSpeed = 1; }
        App.TimerManager.doFrame(1, 0, this.onFrame, this);
        if (!this.armature) {
            this.armature = new DragonBonesArmatureContainer();
            this.addChild(this.armature);
        }
        this.armature.init();
        this.res_ske_json = res_ske_json + "_ske_json";
        this.armatureName = armatureName;
        this.actionArray = actionName;
        this.dragonBonesName = res_ske_json;
        this.playSpeed = playSpeed;
        this.oriAction = oriAction;
        RES.getResAsync(this.res_ske_json, this.LoadObjSkeJsonSuccess, this);
    };
    DragonObjectBase.prototype.LoadObjSkeJsonSuccess = function (data, key) {
        this.skeletonData = data;
        RES.getResAsync(data.name + "_tex_json", this.LoadObjTexJsonSuccess, this);
    };
    DragonObjectBase.prototype.LoadObjTexJsonSuccess = function (data, key) {
        this.textureData = data;
        RES.getResAsync(data.name + "_tex_png", this.LoadObjTexPngSuccess, this);
    };
    DragonObjectBase.prototype.LoadObjTexPngSuccess = function (data, key) {
        this.texturePng = data;
        App.DragonBonesFactory.initArmatureFile(this.skeletonData, this.texturePng, this.textureData);
        this.createArmature(this.armatureName, this.actionArray, this.dragonBonesName, this.playSpeed);
        if (!this.oriAction || this.oriAction == "" || this.oriAction == undefined)
            this.armature.play(this.actionArray[0], 0);
        else
            this.armature.play(this.oriAction, 0);
    };
    /**
     * 创建一个动画
     * @param armatureName 骨架数据名称
     * @param dragonBonesName - DragonBonesData 实例的缓存名称。 （如果未设置，将检索所有的 DragonBonesData 实例，当多个 DragonBonesData 实例中包含同名的骨架数据时，可能无法准确的创建出特定的骨架）
     *
     */
    DragonObjectBase.prototype.createArmature = function (armatureName, actionName, dragonBonesName, playSpeed) {
        if (playSpeed === void 0) { playSpeed = 1; }
        this.armature.register(App.DragonBonesFactory.makeArmature(armatureName, dragonBonesName, playSpeed), actionName);
    };
    DragonObjectBase.prototype.destory = function () {
        this.armature.stop();
        this.armature.destroy();
        App.TimerManager.remove(this.onFrame, this);
        App.DisplayUtils.removeFromParent(this);
        ObjectPool.push(this);
    };
    DragonObjectBase.prototype.onFrame = function (time) {
        this.update(time);
        this.setPos();
    };
    DragonObjectBase.prototype.setPos = function () {
        if (this.$getX() != this.originX) {
            this.$setX(this.originX);
        }
        if (this.$getY() != this.trueY) {
            this.$setY(this.trueY);
        }
    };
    DragonObjectBase.prototype.update = function (time) {
    };
    //预留
    DragonObjectBase.prototype.registerArmature = function (actionName) {
    };
    Object.defineProperty(DragonObjectBase.prototype, "x", {
        get: function () {
            return this.originX;
        },
        set: function (value) {
            this.originX = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(DragonObjectBase.prototype, "y", {
        get: function () {
            return this.originY;
        },
        set: function (value) {
            this.originY = value;
            this.trueY = this.originY + this.originZ;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(DragonObjectBase.prototype, "z", {
        get: function () {
            return this.originZ;
        },
        set: function (value) {
            this.originZ = value;
            this.trueY = this.originY + this.originZ;
        },
        enumerable: true,
        configurable: true
    });
    return DragonObjectBase;
}(egret.DisplayObjectContainer));
__reflect(DragonObjectBase.prototype, "DragonObjectBase");
//# sourceMappingURL=DragonObjectBase.js.map