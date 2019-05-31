/**
 * 
 */
class HintController extends BaseController {
    //本模块的数据存储
    private hintModel: HintModel;
    //本模块的所有UI
    private hintView: HintView;
    //本模块的Proxy
    private hintProxy: HintProxy;

    public constructor() {
        super();

        //初始化Model
        this.hintModel = new HintModel(this);

        //初始化UI
        this.hintView = new HintView(this, LayerManager.UI_Popup);
        App.ViewManager.register(ViewConst.Hint, this.hintView);

        //初始化Proxy
        this.hintProxy = new HintProxy(this);

        //注册模块间、模块内部事件监听
        this.RegisterEvent(EventDef.DialogSkip);
    }

    public HandleEvent(ev: EventDef, le: LogicEvent): void {
        super.HandleEvent(ev, le);
        if (EventDef.DialogSkip == ev) {
            this.onDialogSkip(le.StrParam0, le.StrParam1,le.Object0,le.Object1);
        }
    }

    /**
    * 
    * @param tishi 标题文字
    * @param text 文本内容
    * @param ensureLabel 确认按钮文本
    * @param cancelLabel 取消按钮文本
    * @param ensureClick 确认事件
    * @param cancelClick 取消事件 这个是空的话,就默认关闭自己
    */
    private onDialogSkip(tishi: string, text: string, ensureClick?: Function, cancelClick?: Function): void {
        App.ViewManager.open(ViewConst.Hint);
        this.hintView.setData(tishi, text, ensureClick, cancelClick);
    }

}