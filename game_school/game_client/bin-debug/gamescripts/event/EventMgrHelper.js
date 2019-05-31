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
 * @author sjz
 * @time 2018-8-13 19:10
 */
var EventMgrHelper = (function (_super) {
    __extends(EventMgrHelper, _super);
    function EventMgrHelper() {
        var _this = _super.call(this) || this;
        _this.mDicHandler = new Dictionary(true);
        _this.mListEvent = null;
        _this.paramArray = [new Array(), new Array()];
        _this.mParamIndex = 0;
        App.TimerManager.doFrame(1, 0, _this.update, _this);
        _this.mListEvent = _this.paramArray[_this.mParamIndex];
        return _this;
    }
    EventMgrHelper.prototype.RegisterEventHandler = function (ed, handler) {
        var lh;
        if (this.mDicHandler.TryGetValue(ed) != null) {
            lh = this.mDicHandler.TryGetValue(ed);
            lh.push(handler);
        }
        else {
            lh = new Array();
            lh.push(handler);
            this.mDicHandler.Add(ed, lh);
        }
    };
    EventMgrHelper.prototype.UnRegisterEventHandler = function (ed, handler) {
        var lh;
        if (this.mDicHandler.TryGetValue(ed) != null) {
            lh = this.mDicHandler.TryGetValue(ed);
            for (var i = 0; i < lh.length; ++i) {
                if (lh[i] == handler) {
                    lh.splice(i, 1);
                    return;
                }
            }
        }
    };
    EventMgrHelper.prototype.PushEvent = function (ed, intdata0, intdata1, strData0, strData1, checkSameEvent) {
        if (intdata0 === void 0) { intdata0 = -1; }
        if (intdata1 === void 0) { intdata1 = -1; }
        if (strData0 === void 0) { strData0 = ""; }
        if (strData1 === void 0) { strData1 = ""; }
        if (checkSameEvent === void 0) { checkSameEvent = false; }
        if (checkSameEvent) {
            if (this.ExistEvent(ed)) {
                return;
            }
        }
        var le = this.CreateLogicEvent();
        le.Event = ed;
        le.IntParam0 = intdata0;
        le.IntParam1 = intdata1;
        le.StrParam0 = strData0;
        le.StrParam1 = strData1;
        this.Push(le);
    };
    EventMgrHelper.prototype.PushEventEx = function (ed, object0, object1, data0, data1, strData0, strData1, object2, checkSameEvent) {
        if (object2 === void 0) { object2 = null; }
        if (checkSameEvent === void 0) { checkSameEvent = false; }
        if (checkSameEvent) {
            if (this.ExistEvent(ed)) {
                return;
            }
        }
        var le = this.CreateLogicEvent();
        le.Event = ed;
        le.Object0 = object0;
        le.Object1 = object1;
        le.IntParam0 = data0;
        le.IntParam1 = data1;
        le.StrParam0 = strData0;
        le.StrParam1 = strData1;
        le.Object2 = object2;
        this.Push(le);
    };
    EventMgrHelper.prototype.Push = function (le) {
        this.mListEvent.push(le);
        if (this.mListEvent.length > 50) {
            var i = 0;
            ++i;
        }
    };
    EventMgrHelper.prototype.CreateLogicEvent = function () {
        return LogicEvent.CreateEvent();
    };
    EventMgrHelper.prototype.ExistEvent = function (le) {
        for (var i = 0; i < this.mListEvent.length; ++i) {
            if (this.mListEvent[i].Event == le) {
                return true;
            }
        }
        return false;
    };
    EventMgrHelper.prototype.update = function (advancetime) {
        if (this.mListEvent != null && this.mListEvent.length == 0) {
            return;
        }
        var oldEvent = this.mListEvent;
        this.mParamIndex = (this.mParamIndex + 1) % 2;
        this.mListEvent = this.paramArray[this.mParamIndex];
        for (var i = 0; i < oldEvent.length; ++i) {
            var le = oldEvent[i];
            var lh = void 0;
            if (this.mDicHandler.TryGetValue(le.Event) == null) {
                continue;
            }
            lh = this.mDicHandler.TryGetValue(le.Event);
            for (var j = 0; j < lh.length; ++j) {
                try {
                    lh[j].HandleEvent(le.Event, le);
                }
                catch (Error) {
                    Log.Error(Error);
                }
            }
            if (!le.Locked) {
                LogicEvent.DestroyEvent(le);
            }
        }
        oldEvent = [];
    };
    return EventMgrHelper;
}(BaseClass));
__reflect(EventMgrHelper.prototype, "EventMgrHelper");
//# sourceMappingURL=EventMgrHelper.js.map