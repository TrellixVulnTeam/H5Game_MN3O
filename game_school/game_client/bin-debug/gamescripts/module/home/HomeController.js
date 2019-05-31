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
 */
var HomeController = (function (_super) {
    __extends(HomeController, _super);
    function HomeController() {
        return _super.call(this) || this;
        //this.proxy = new HomeProxy(this);
        //this.homeView = new HomeView(this, LayerManager.UI_Main);
        //App.ViewManager.register(ViewConst.Home, this.homeView);
    }
    return HomeController;
}(BaseController));
__reflect(HomeController.prototype, "HomeController");
//# sourceMappingURL=HomeController.js.map