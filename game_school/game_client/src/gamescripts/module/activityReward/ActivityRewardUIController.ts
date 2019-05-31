class ActivityRewardUIController extends BaseController
{
    private activityRewardModel:ActivityRewardUIModel;
    private activityRewardProxy:ActivityRewardUIProxy;
    private activityRewardView:ActivityRewardUIView;

    public constructor()
    {
        super();

        this.activityRewardModel = new ActivityRewardUIModel(this);
        this.activityRewardProxy = new ActivityRewardUIProxy(this);

        this.activityRewardView = new ActivityRewardUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.ActivityRewardUI, this.activityRewardView);

        this.RegisterEvent(EventDef.ActivityReward_dailySign);
    }

    public HandleEvent(ev: EventDef, le: LogicEvent): void 
    {
        super.HandleEvent(ev, le);
        if (EventDef.ActivityReward_dailySign == ev) 
        {
            this.UpdateCurAccRewardItem();
        }
    }

    /**
     * 成功领取累签奖励
    */
    private UpdateCurAccRewardItem():void
    {
         this.activityRewardView.dailySignUI.updateCurAccRewardItem();
    }
}