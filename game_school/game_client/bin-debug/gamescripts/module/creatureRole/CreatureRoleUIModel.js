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
var CreatureRoleUIModel = (function (_super) {
    __extends(CreatureRoleUIModel, _super);
    /**
     * 构造函数
     * @param $controller 所属模块
     */
    function CreatureRoleUIModel($controller) {
        return _super.call(this, $controller) || this;
    }
    return CreatureRoleUIModel;
}(BaseModel));
__reflect(CreatureRoleUIModel.prototype, "CreatureRoleUIModel");
//# sourceMappingURL=CreatureRoleUIModel.js.map