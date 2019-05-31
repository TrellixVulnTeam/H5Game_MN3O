class FriendlinessTipsUIController extends BaseController
{
    private FriendlinessTipsView:FriendlinessTipsUIView;//友好度提示界面

    public constructor(){
        super();

        this.FriendlinessTipsView = new FriendlinessTipsUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.FriendlinessTipsUI, this.FriendlinessTipsView);

        this.RegisterEvent(EventDef.Friendliness_tips);
    }

    public HandleEvent(ev: EventDef, le: LogicEvent): void 
    {
        super.HandleEvent(ev, le);
        if (EventDef.Friendliness_tips == ev) 
        {
            this.onSetContent(le.StrParam0);
        }
    }

    private onSetContent(content: string): void {
        if (content == null)
            return;

        this.FriendlinessTipsView.setContent(content);
        App.ViewManager.open(ViewConst.FriendlinessTipsUI);
    }
}