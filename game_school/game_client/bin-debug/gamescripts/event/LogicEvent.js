var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * @author sjz
 * @time 2018-8-13 19:10
 */
var LogicEvent = (function () {
    function LogicEvent() {
        this.NUMBER_MIN_STR = "MIN";
        this.NUMBER_MAX_STR = "MAX";
        this.NUMBER_DEFAULT_STR = "DEFAULT";
        this.mEvent = EventDef.NONE;
        this.mIntParam0 = -1;
        this.mIntParam1 = -1;
        this.mStrParam0 = "";
        this.mStrParam1 = "";
        this.mLocked = false;
        this.mDicParam0 = new Dictionary(true);
    }
    LogicEvent.prototype.Reset = function () {
        this.mEvent = EventDef.NONE;
        this.mIntParam0 = -1;
        this.mIntParam1 = -1;
        this.mStrParam0 = "";
        this.mStrParam1 = "";
        this.mObject0 = null;
        this.mObject1 = null;
        this.mDicParam0.Clear();
    };
    LogicEvent.CreateEvent = function () {
        var le = this.msEventPool.Alloc();
        if (le != null) {
            return le;
        }
        return new LogicEvent();
    };
    LogicEvent.DestroyEvent = function (le) {
        le.Reset();
        this.msEventPool.Free(le);
    };
    Object.defineProperty(LogicEvent.prototype, "Event", {
        get: function () {
            return this.mEvent;
        },
        set: function (value) {
            this.mEvent = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LogicEvent.prototype, "Locked", {
        get: function () {
            return this.mLocked;
        },
        set: function (value) {
            this.mLocked = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LogicEvent.prototype, "IntParam0", {
        get: function () {
            return this.mIntParam0;
        },
        set: function (value) {
            this.mIntParam0 = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LogicEvent.prototype, "IntParam1", {
        get: function () {
            return this.mIntParam1;
        },
        set: function (value) {
            this.mIntParam1 = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LogicEvent.prototype, "StrParam0", {
        get: function () {
            return this.mStrParam0;
        },
        set: function (value) {
            this.mStrParam0 = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LogicEvent.prototype, "StrParam1", {
        get: function () {
            return this.mStrParam1;
        },
        set: function (value) {
            this.mStrParam1 = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LogicEvent.prototype, "Object0", {
        get: function () {
            return this.mObject0;
        },
        set: function (value) {
            this.mObject0 = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LogicEvent.prototype, "Object1", {
        get: function () {
            return this.mObject1;
        },
        set: function (value) {
            this.mObject1 = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LogicEvent.prototype, "Object2", {
        get: function () {
            return this.mObject2;
        },
        set: function (value) {
            this.mObject2 = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LogicEvent.prototype, "DicParam0", {
        get: function () {
            return this.mDicParam0;
        },
        set: function (value) {
            this.mDicParam0 = value;
        },
        enumerable: true,
        configurable: true
    });
    LogicEvent.msEventPool = new MemoryPool(50);
    return LogicEvent;
}());
__reflect(LogicEvent.prototype, "LogicEvent");
//# sourceMappingURL=LogicEvent.js.map