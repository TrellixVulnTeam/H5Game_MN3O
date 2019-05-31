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
var DragonObjectTest = (function (_super) {
    __extends(DragonObjectTest, _super);
    function DragonObjectTest() {
        return _super.call(this) || this;
    }
    DragonObjectTest.prototype.init = function (res_ske_json, armatureName, actionName, oriAction, playSpeed) {
        if (playSpeed === void 0) { playSpeed = 1; }
        _super.prototype.init.call(this, res_ske_json, armatureName, actionName, oriAction, playSpeed);
    };
    DragonObjectTest.prototype.destory = function () {
        _super.prototype.destory.call(this);
    };
    DragonObjectTest.prototype.update = function (timer) {
        _super.prototype.update.call(this, timer);
    };
    return DragonObjectTest;
}(DragonObjectBase));
__reflect(DragonObjectTest.prototype, "DragonObjectTest");
//# sourceMappingURL=DragonObjectTest.js.map