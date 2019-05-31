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
var fightStartUIModel = (function (_super) {
    __extends(fightStartUIModel, _super);
    /**
     * 构造函数
     * @param $controller 所属模块
     */
    function fightStartUIModel($controller) {
        return _super.call(this, $controller) || this;
    }
    return fightStartUIModel;
}(BaseModel));
__reflect(fightStartUIModel.prototype, "fightStartUIModel");
//# sourceMappingURL=fightStartUIModel.js.map