/**
 */
class LoadingController extends BaseController{

    private loadingView:LoadingView;

    public constructor(){
        super();

        //初始化UI
        this.loadingView = new LoadingView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.Loading, this.loadingView);

        this.RegisterEvent(EventDef.LoadingRes_progress);
        this.RegisterEvent(EventDef.LoadingConfig_progress);
    }

    public HandleEvent(ev: EventDef, le: LogicEvent): void 
    {
        super.HandleEvent(ev, le);
        if (EventDef.LoadingRes_progress == ev) 
        {
            this.setProgress(le.IntParam0, le.IntParam1);
        }
        else if (EventDef.LoadingConfig_progress == ev) 
        {
            this.configLoadingProgress(le.IntParam0, le.IntParam1);
        }
    }

    private setProgress(current:number, total:number):void
    {
        this.loadingView.setProgress(current, total);
    }
    
    private configLoadingProgress(current:number, total:number):void
    {
        this.loadingView.configLoadingProgress(current, total);
    }
}
