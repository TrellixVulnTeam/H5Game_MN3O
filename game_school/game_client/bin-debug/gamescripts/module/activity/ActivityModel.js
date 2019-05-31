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
var ActivityModel = (function (_super) {
    __extends(ActivityModel, _super);
    /**
     * 构造函数
     * @param $controller 所属模块
     */
    function ActivityModel($controller) {
        var _this = _super.call(this, $controller) || this;
        _this.activityConArray = [];
        return _this;
    }
    ActivityModel.prototype.initActivityArray = function () {
        function _sort(a, b) {
            return a.sort - b.sort;
        }
        var array = ActivityClientConfig.array;
        this.activityConArray = array.splice(0); //数组的深拷贝
        this.activityConArray.sort(_sort);
    };
    return ActivityModel;
}(BaseModel));
__reflect(ActivityModel.prototype, "ActivityModel");
//# sourceMappingURL=ActivityModel.js.map