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
var MainUIModel = (function (_super) {
    __extends(MainUIModel, _super);
    /**
     * 构造函数
     * @param $controller 所属模块
     */
    function MainUIModel($controller) {
        return _super.call(this, $controller) || this;
    }
    /**
    * 根据ID获得 ChapterConfig表数据 章节表
    * @param $ID 表ID
    */
    MainUIModel.prototype.GetFaceConfigByID = function (ID) {
        var array = FaceConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (ID == array[i].id) {
                return array[i];
            }
        }
        return null;
    };
    return MainUIModel;
}(BaseModel));
__reflect(MainUIModel.prototype, "MainUIModel");
//# sourceMappingURL=MainUIModel.js.map