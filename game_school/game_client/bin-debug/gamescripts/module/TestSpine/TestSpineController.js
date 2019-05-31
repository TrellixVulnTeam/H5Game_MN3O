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
 *
 */
var TestSpineController = (function (_super) {
    __extends(TestSpineController, _super);
    function TestSpineController() {
        var _this = _super.call(this) || this;
        //初始化UI
        _this.testSpineView = new TestSpineView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.TestSpine, _this.testSpineView);
        return _this;
    }
    return TestSpineController;
}(BaseController));
__reflect(TestSpineController.prototype, "TestSpineController");
//# sourceMappingURL=TestSpineController.js.map