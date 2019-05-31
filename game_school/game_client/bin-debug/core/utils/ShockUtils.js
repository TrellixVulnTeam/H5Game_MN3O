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
 * 震动
 */
var ShockUtils = (function (_super) {
    __extends(ShockUtils, _super);
    function ShockUtils() {
        var _this = _super.call(this) || this;
        _this.MAP = 0;
        _this.SPRITE = 1;
        _this.FREE = 1;
        _this.mapPoss = [new egret.Point(0, 3), new egret.Point(0, 0), new egret.Point(0, -2)];
        _this.spritePoss = [new egret.Point(5, 0), new egret.Point(-5, 0), new egret.Point(5, 0)];
        _this._shockLength = 0;
        _this._shockCount = 0;
        _this._rx = 0;
        _this._ry = 0;
        _this._type = 0;
        _this._dir = 0; //方向,FREE专用
        _this._repeatCount = 0;
        return _this;
    }
    ShockUtils.prototype.destroy = function () {
        this.stop();
    };
    ShockUtils.prototype.shock = function (type, target, repeatCount) {
        if (type === void 0) { type = 0; }
        if (target === void 0) { target = null; }
        if (repeatCount === void 0) { repeatCount = 3; }
        if (this._target) {
            return;
        }
        this._type = type;
        this._target = target;
        if (this._type == this.MAP) {
            this._shockPoss = this.mapPoss.concat();
            this._shockLength = this._shockPoss.length;
        }
        else if (this._type == this.SPRITE) {
            this._shockPoss = this.spritePoss.concat();
            this._shockLength = this._shockPoss.length;
        }
        this.start(repeatCount);
    };
    ShockUtils.prototype.start = function (num) {
        if (num === void 0) { num = 1; }
        this.repeatCount = num;
        this._shockCount = 0;
        if (this._target) {
            if (this._type != this.MAP) {
                this._rx = this._target.x;
            }
            this._ry = this._target.y;
            App.TimerManager.doFrame(1, 0, this.onShockEnter, this);
        }
    };
    ShockUtils.prototype.stop = function () {
        if (this._target) {
            if (this._type != this.MAP) {
                this._target.x = this._rx;
            }
            this._target.y = this._ry;
            App.TimerManager.remove(this.onShockEnter, this);
        }
        this._target = null;
    };
    ShockUtils.prototype.onShockEnter = function (time) {
        var maxCount = this._shockLength * this._repeatCount;
        if (this._shockCount >= maxCount) {
            this.stop();
            return;
        }
        var index = this._shockCount % this._shockLength;
        var pos = this._shockPoss[index];
        if (this._target) {
            if (this._type != this.MAP) {
                this._target.x = this._rx + pos.x;
            }
            this._target.y = this._ry + pos.y;
        }
        this._shockCount++;
    };
    Object.defineProperty(ShockUtils.prototype, "repeatCount", {
        get: function () {
            return this._repeatCount;
        },
        set: function (value) {
            this._repeatCount = value;
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 自定义抖动
     * @param target 要抖动的物体
     * @param repeatCount 要抖动的次数
     * @param dir 要抖动的方向
     * @param size 抖动的幅度,或者说,大小
     */
    ShockUtils.prototype.shockFree = function (target, repeatCount, dir, size, callback) {
        if (target === void 0) { target = null; }
        if (repeatCount === void 0) { repeatCount = 3; }
        if (dir === void 0) { dir = 1; }
        if (size === void 0) { size = 3; }
        if (this._target) {
            return;
        }
        this._type = this.FREE;
        this._target = target;
        this._dir = dir;
        this._freecallback = callback;
        var freePoss;
        switch (dir) {
            case 1:
                freePoss = [new egret.Point(0, size), new egret.Point(0, 0), new egret.Point(0, -size)];
                break;
            case 2:
                freePoss = [new egret.Point(size, 0), new egret.Point(-size, 0), new egret.Point(size, 0)];
                break;
            case 3:
                freePoss = [new egret.Point(size, size), new egret.Point(-size, 0), new egret.Point(size, -size)];
                break;
        }
        this._shockPoss = freePoss.concat();
        this._shockLength = this._shockPoss.length;
        this.startFree(repeatCount, dir);
    };
    ShockUtils.prototype.startFree = function (num, dir) {
        if (num === void 0) { num = 1; }
        this.repeatCount = num;
        this._shockCount = 0;
        if (this._target) {
            switch (dir) {
                case 1:
                    this._ry = this._target.y;
                    break;
                case 2:
                    this._rx = this._target.x;
                    break;
                case 3:
                    this._rx = this._target.x;
                    this._ry = this._target.y;
                    break;
            }
            App.TimerManager.doFrame(1, 0, this.onFreeShockEnter, this);
        }
    };
    ShockUtils.prototype.stopFree = function () {
        if (this._target) {
            switch (this._dir) {
                case 1:
                    this._target.y = this._ry;
                    break;
                case 2:
                    this._target.x = this._rx;
                    break;
                case 3:
                    this._target.x = this._rx;
                    this._target.y = this._ry;
                    break;
            }
            App.TimerManager.remove(this.onFreeShockEnter, this);
        }
        this._target = null;
    };
    ShockUtils.prototype.onFreeShockEnter = function (time) {
        var maxCount = this._shockLength * this._repeatCount;
        if (this._shockCount >= maxCount) {
            this.stopFree();
            if (this._freecallback != null)
                this._freecallback();
            return;
        }
        var index = this._shockCount % this._shockLength;
        var pos = this._shockPoss[index];
        if (this._target) {
            switch (this._dir) {
                case 1:
                    this._target.y = this._ry + pos.y;
                    break;
                case 2:
                    this._target.x = this._rx + pos.x;
                    break;
                case 3:
                    this._target.x = this._rx + pos.x;
                    this._target.y = this._ry + pos.y;
                    break;
            }
        }
        this._shockCount++;
    };
    return ShockUtils;
}(BaseClass));
__reflect(ShockUtils.prototype, "ShockUtils");
//# sourceMappingURL=ShockUtils.js.map