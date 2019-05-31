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
var CreatureRoleUIController = (function (_super) {
    __extends(CreatureRoleUIController, _super);
    function CreatureRoleUIController() {
        var _this = _super.call(this) || this;
        _this.creatureRoleUIModel = new CreatureRoleUIModel(_this);
        _this.creatureRoleUIProxy = new CreatureRoleUIProxy(_this);
        _this.creatureRole = new CreatureRoleUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.CreatureRoleUI, _this.creatureRole);
        return _this;
    }
    return CreatureRoleUIController;
}(BaseController));
__reflect(CreatureRoleUIController.prototype, "CreatureRoleUIController");
//# sourceMappingURL=CreatureRoleUIController.js.map