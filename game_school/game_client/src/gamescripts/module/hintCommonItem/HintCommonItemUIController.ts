/**
 * item提示框controller
 */
class HintCommonItemUIController extends BaseController
{
    private hintCommonview:HintCommonItemUIView;

    public constructor()
    {
        super();

        this.hintCommonview = new HintCommonItemUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.HintCommonItemUI, this.hintCommonview);

        this.RegisterEvent(EventDef.SHOWHINTITEMUI);
    }

    public HandleEvent(ev:EventDef,le:LogicEvent){
        super.HandleEvent(ev,le);
        switch(ev){
            case EventDef.SHOWHINTITEMUI:
                this.onSetContent(le.StrParam0,le.StrParam0,le.Object0,le.Object1,le.Object2);
            break;
        }
    }

    private onSetContent(tishi: string, text: string, items:Item[], ensureClick?: Function, cancelClick?: Function): void 
    {
        if (items != null && items.length > 0)
        {
            App.ViewManager.open(ViewConst.HintCommonItemUI);
            this.hintCommonview.onSetContent(tishi, text, items, ensureClick, cancelClick);
        }
    }
}
