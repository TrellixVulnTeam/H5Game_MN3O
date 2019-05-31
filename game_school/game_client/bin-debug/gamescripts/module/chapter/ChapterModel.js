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
var ChapterModel = (function (_super) {
    __extends(ChapterModel, _super);
    /**
     * 构造函数
     * @param $controller 所属模块
     */
    function ChapterModel($controller) {
        var _this = _super.call(this, $controller) || this;
        //是否第一次打开章节
        _this.isFirstOpenChapter = true;
        //当先选择的章节信息
        _this.curSelectChapter = 1;
        //当前的战斗关卡
        _this.curCheckPoint = 1;
        //章节的最大进度
        _this.maxChapter = 1;
        _this.checkPointDataArray = [];
        return _this;
    }
    //设置数据
    ChapterModel.prototype.setCheckPointData = function () {
    };
    /**
    * 根据ID获得 ChapterConfig表数据 章节表
    * @param $ID 表ID
    */
    ChapterModel.prototype.GetChapterConfigByID = function (ID) {
        var array = ChapterConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (ID == array[i].id) {
                return array[i];
            }
        }
        return null;
    };
    /**
    * 根据章节ID获得 CheckPointConfig 关卡表
    * @param $ID 章节ID
    */
    ChapterModel.prototype.GetCheckPointConfigListByChapterID = function (chapterID) {
        var array = CheckPointConfig.array;
        var resultArray = [];
        for (var i = 0; i < array.length; i++) {
            if (chapterID == array[i].chapter) {
                resultArray.push(array[i]);
            }
        }
        return resultArray;
    };
    /**
    * 根据ID获得 CheckPointConfig 关卡表
    * @param $ID 表ID
    */
    ChapterModel.prototype.GetCheckPointConfigByID = function (ID) {
        var array = CheckPointConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (ID == array[i].id) {
                return array[i];
            }
        }
        return null;
    };
    return ChapterModel;
}(BaseModel));
__reflect(ChapterModel.prototype, "ChapterModel");
var checkPointData = (function () {
    function checkPointData() {
        this.isOpen = false;
    }
    return checkPointData;
}());
__reflect(checkPointData.prototype, "checkPointData");
//# sourceMappingURL=ChapterModel.js.map