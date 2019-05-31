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
 * 2014/11/23.
 * Timer管理器
 */
var TimerManager = (function (_super) {
    __extends(TimerManager, _super);
    /**
     * 构造函数
     */
    function TimerManager() {
        var _this = _super.call(this) || this;
        _this._handlers = new Array();
        _this._delHandlers = new Array();
        _this._currTime = egret.getTimer();
        _this._currFrame = 0;
        _this._count = 0;
        _this._timeScale = 1;
        egret.Ticker.getInstance().register(_this.onEnterFrame, _this);
        return _this;
    }
    /**
     * 设置时间参数
     * @param timeScale
     */
    TimerManager.prototype.setTimeScale = function (timeScale) {
        this._timeScale = timeScale;
    };
    Object.defineProperty(TimerManager.prototype, "TimeScale", {
        get: function () {
            return this._timeScale;
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 每帧执行函数
     * @param frameTime
     */
    TimerManager.prototype.onEnterFrame = function () {
        this._currFrame++;
        this._currTime = egret.getTimer();
        App.DebugUtils.start("TimerManager:");
        for (var i = 0; i < this._count; i++) {
            var handler = this._handlers[i];
            var t = handler.userFrame ? this._currFrame : this._currTime;
            if (t >= handler.exeTime) {
                App.DebugUtils.start(handler.method.toString());
                handler.method.call(handler.methodObj, (this._currTime - handler.dealTime) * this._timeScale);
                App.DebugUtils.stop(handler.method.toString());
                handler.dealTime = this._currTime;
                handler.exeTime += handler.delay;
                if (!handler.repeat) {
                    if (handler.repeatCount > 1) {
                        handler.repeatCount--;
                    }
                    else {
                        if (handler.complateMethod) {
                            handler.complateMethod.apply(handler.complateMethodObj);
                        }
                        this._delHandlers.push(handler);
                    }
                }
            }
        }
        while (this._delHandlers.length) {
            var handler = this._delHandlers.pop();
            this.remove(handler.method, handler.methodObj);
        }
        App.DebugUtils.stop("TimerManager:");
    };
    TimerManager.prototype.create = function (useFrame, delay, repeatCount, eventid, method, methodObj, complateMethod, complateMethodObj) {
        //参数监测
        if (delay < 0 || repeatCount < 0 || method == null) {
            return;
        }
        //先删除相同函数的计时
        this.remove(method, methodObj);
        //创建
        var handler = ObjectPool.pop("TimerHandler");
        handler.id = App.MathUtils.uuid(8, 16);
        handler.eventid = eventid;
        handler.userFrame = useFrame;
        handler.repeat = repeatCount == 0;
        handler.repeatCount = repeatCount;
        handler.delay = delay;
        handler.method = method;
        handler.methodObj = methodObj;
        handler.complateMethod = complateMethod;
        handler.complateMethodObj = complateMethodObj;
        handler.exeTime = delay + (useFrame ? this._currFrame : this._currTime);
        handler.dealTime = this._currTime;
        this._handlers.push(handler);
        this._count++;
        return handler;
    };
    /**
     *
     * 定时执行
     * @param delay 执行间隔:毫秒
     * @param repeatCount 执行次数, 0为无限次
     * @param method 执行函数
     * @param methodObj 执行函数所属对象
     * @param complateMethod 完成执行函数
     * @param complateMethodObj 完成执行函数所属对象
     *
     */
    TimerManager.prototype.doTimer = function (delay, repeatCount, method, methodObj, eventid, complateMethod, complateMethodObj) {
        if (eventid === void 0) { eventid = 0; }
        if (complateMethod === void 0) { complateMethod = null; }
        if (complateMethodObj === void 0) { complateMethodObj = null; }
        return this.create(false, delay, repeatCount, eventid, method, methodObj, complateMethod, complateMethodObj);
    };
    /**
     *
     * 定时执行
     * @param delay 执行间隔:帧频
     * @param repeatCount 执行次数, 0为无限次
     * @param method 执行函数
     * @param methodObj 执行函数所属对象
     * @param complateMethod 完成执行函数
     * @param complateMethodObj 完成执行函数所属对象
     *
     */
    TimerManager.prototype.doFrame = function (delay, repeatCount, method, methodObj, eventid, complateMethod, complateMethodObj) {
        if (eventid === void 0) { eventid = 0; }
        if (complateMethod === void 0) { complateMethod = null; }
        if (complateMethodObj === void 0) { complateMethodObj = null; }
        return this.create(true, delay, repeatCount, eventid, method, methodObj, complateMethod, complateMethodObj);
    };
    Object.defineProperty(TimerManager.prototype, "count", {
        /**
         * 定时器执行数量
         * @return
         *
         */
        get: function () {
            return this._count;
        },
        enumerable: true,
        configurable: true
    });
    TimerManager.prototype.remove = function (arg, arg2) {
        if (typeof arg == 'number') {
            for (var i = 0; i < this._count; i++) {
                var handler = this._handlers[i];
                if (handler.eventid == arg && handler.methodObj == arg2) {
                    this._handlers.splice(i, 1);
                    ObjectPool.push(handler);
                    this._count--;
                    break;
                }
            }
        }
        else if (typeof arg == 'string') {
            for (var i = 0; i < this._count; i++) {
                var handler = this._handlers[i];
                if (handler.id == arg && handler.methodObj == arg2) {
                    this._handlers.splice(i, 1);
                    ObjectPool.push(handler);
                    this._count--;
                    break;
                }
            }
        }
        else if (typeof arg == 'function') {
            for (var i = 0; i < this._count; i++) {
                var handler = this._handlers[i];
                if (handler.method == arg && handler.methodObj == arg2) {
                    this._handlers.splice(i, 1);
                    ObjectPool.push(handler);
                    this._count--;
                    break;
                }
            }
        }
    };
    /**
     * 清理
     * @param methodObj 要移除的函数对应的对象
     */
    TimerManager.prototype.removeAll = function (methodObj) {
        for (var i = 0; i < this._count; i++) {
            var handler = this._handlers[i];
            if (handler.methodObj == methodObj) {
                this._handlers.splice(i, 1);
                ObjectPool.push(handler);
                this._count--;
                i--;
            }
        }
    };
    TimerManager.prototype.isExists = function (arg, arg2) {
        if (typeof arg == 'function') {
            for (var i = 0; i < this._count; i++) {
                var handler = this._handlers[i];
                if (handler.method == arg && handler.methodObj == arg2) {
                    return true;
                }
            }
            return false;
        }
        else if (typeof arg == 'number') {
            for (var i = 0; i < this._count; i++) {
                var handler = this._handlers[i];
                if (handler.eventid == arg && handler.methodObj == arg2) {
                    return true;
                }
            }
            return false;
        }
        else if (typeof arg == 'string') {
            for (var i = 0; i < this._count; i++) {
                var handler = this._handlers[i];
                if (handler.id == arg && handler.methodObj == arg2) {
                    return true;
                }
            }
            return false;
        }
    };
    return TimerManager;
}(BaseClass));
__reflect(TimerManager.prototype, "TimerManager");
var TimerHandler = (function () {
    function TimerHandler() {
        this.id = "";
        this.eventid = 0;
        /**执行间隔*/
        this.delay = 0;
        /**重复执行次数*/
        this.repeatCount = 0;
        /**执行时间*/
        this.exeTime = 0;
        /**上次的执行时间*/
        this.dealTime = 0;
    }
    /**清理*/
    TimerHandler.prototype.clear = function () {
        this.method = null;
        this.methodObj = null;
        this.complateMethod = null;
        this.complateMethodObj = null;
    };
    return TimerHandler;
}());
__reflect(TimerHandler.prototype, "TimerHandler");
//# sourceMappingURL=TimerManager.js.map