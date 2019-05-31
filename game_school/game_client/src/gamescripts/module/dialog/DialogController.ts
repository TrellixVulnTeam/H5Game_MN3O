/**
 * 
 */
class DialogController extends BaseController {
    //本模块的数据存储
    private dialogModel: DialogModel;
    //本模块的所有UI
    private dialogView: DialogView;
    private dialogOptionView: DialogOptionView;

    //本模块的Proxy
    private dialogProxy: DialogProxy;

    public constructor() {
        super();

        //初始化Model
        this.dialogModel = new DialogModel(this);

        //初始化UI
        this.dialogView = new DialogView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.Dialog, this.dialogView);

        this.dialogOptionView = new DialogOptionView(this, LayerManager.UI_Popup);
        App.ViewManager.register(ViewConst.DialogOption, this.dialogOptionView);

        //初始化Proxy
        this.dialogProxy = new DialogProxy(this);

        this.RegisterEvent(EventDef.PlayPlotGroup);
        this.RegisterEvent(EventDef.SelectDialogOption);
    }

    public HandleEvent(ev: EventDef, le: LogicEvent): void {
        super.HandleEvent(ev, le);
        if (EventDef.PlayPlotGroup == ev) {
            this.onPlayPlotGriup(le.Object0, le.Object1);
        }
        else if (EventDef.SelectDialogOption == ev) {
            this.onSelectOption(le.IntParam0, le.IntParam1);
        }
    }


    private onPlayPlotGriup(plotGroupID: number, callBack?: Function): void {
        if (plotGroupID <= 0) {
            if (callBack)
                callBack();
            return;
        }

        App.ViewManager.open(ViewConst.Dialog);
        this.dialogModel.curPlotGroupID = plotGroupID;
        this.dialogModel.GoOutCallBack = callBack;
        this.dialogView.start();
    }

    /**
    * 选择选项
    * @param optionIndex 选项的index
    * @param nextDialogID 对应的下一个对话
    */
    private onSelectOption(optionIndex: number, nextDialogID: number) {
        this.dialogView.SetNextDialog(nextDialogID);
    }
}