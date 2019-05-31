/**
 * 飘字提示controller
 */
class WorldDriftTipsUIController extends BaseController
{
    private worldDriftView:WorldDriftTipsUIView;

    public constructor()
    {
        super();

        this.worldDriftView = new WorldDriftTipsUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.WorldDriftTipsUI, this.worldDriftView);

        this.RegisterEvent(EventDef.Setdrift_world);
    }

    public HandleEvent(ev: EventDef, le: LogicEvent): void 
    {
        super.HandleEvent(ev, le);
        if (EventDef.Setdrift_world == ev) 
        {
            this.onSetContent(le.StrParam0);
        }
    }

    private onSetContent(content:string): void 
    {
        if (content == null)
            return;

        this.worldDriftView.setContent(content);
        App.ViewManager.open(ViewConst.WorldDriftTipsUI);
    }
}
