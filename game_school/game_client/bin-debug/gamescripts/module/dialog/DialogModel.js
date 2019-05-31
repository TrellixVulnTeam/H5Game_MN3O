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
var DialogModel = (function (_super) {
    __extends(DialogModel, _super);
    function DialogModel($controller) {
        return _super.call(this, $controller) || this;
    }
    /**
    * 根据ID获得 ChapterConfig表数据 章节表
    * @param $ID 表ID
    */
    DialogModel.prototype.GetDialogConfigByID = function (ID) {
        var array = DialogConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (ID == array[i].dialogID) {
                return array[i];
            }
        }
        return null;
    };
    DialogModel.prototype.GetDialogGroupDataByDialogGroupID = function (plotGroupID) {
        var array = PlotGroupConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (plotGroupID == array[i].plotGroupID) {
                return array[i];
            }
        }
        return null;
    };
    DialogModel.prototype.GetDialogOptionConfigByOptionID = function (optionID) {
        var array = DialogOptionConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (optionID == array[i].optionID) {
                return array[i];
            }
        }
        return null;
    };
    //遍历 BlackScreenConfig 表
    DialogModel.prototype.GetBlackScreenConfigArray = function (startID) {
        var array = [];
        var nextID = startID;
        while (nextID != -1) {
            var con = BlackScreenConfig.GetConfig(nextID);
            nextID = con.nextId;
            array.push(con);
        }
        return array;
    };
    return DialogModel;
}(BaseModel));
__reflect(DialogModel.prototype, "DialogModel");
//# sourceMappingURL=DialogModel.js.map