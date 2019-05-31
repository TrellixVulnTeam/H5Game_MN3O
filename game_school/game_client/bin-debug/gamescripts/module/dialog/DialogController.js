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
var DialogController = (function (_super) {
    __extends(DialogController, _super);
    function DialogController() {
        var _this = _super.call(this) || this;
        //初始化Model
        _this.dialogModel = new DialogModel(_this);
        //初始化UI
        _this.dialogView = new DialogView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.Dialog, _this.dialogView);
        _this.dialogOptionView = new DialogOptionView(_this, LayerManager.UI_Popup);
        App.ViewManager.register(ViewConst.DialogOption, _this.dialogOptionView);
        //初始化Proxy
        _this.dialogProxy = new DialogProxy(_this);
        _this.RegisterEvent(EventDef.PlayPlotGroup);
        _this.RegisterEvent(EventDef.SelectDialogOption);
        return _this;
    }
    DialogController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        if (EventDef.PlayPlotGroup == ev) {
            this.onPlayPlotGriup(le.Object0, le.Object1);
        }
        else if (EventDef.SelectDialogOption == ev) {
            this.onSelectOption(le.IntParam0, le.IntParam1);
        }
    };
    DialogController.prototype.onPlayPlotGriup = function (plotGroupID, callBack) {
        if (plotGroupID <= 0) {
            if (callBack)
                callBack();
            return;
        }
        App.ViewManager.open(ViewConst.Dialog);
        this.dialogModel.curPlotGroupID = plotGroupID;
        this.dialogModel.GoOutCallBack = callBack;
        this.dialogView.start();
    };
    /**
    * 选择选项
    * @param optionIndex 选项的index
    * @param nextDialogID 对应的下一个对话
    */
    DialogController.prototype.onSelectOption = function (optionIndex, nextDialogID) {
        this.dialogView.SetNextDialog(nextDialogID);
    };
    return DialogController;
}(BaseController));
__reflect(DialogController.prototype, "DialogController");
//# sourceMappingURL=DialogController.js.map