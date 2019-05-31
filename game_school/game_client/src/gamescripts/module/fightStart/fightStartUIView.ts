class fightStartUIView extends BaseEuiView 
{
    private musicbtn: eui.Button;
    private closebtn: eui.Button;
    private applybtn: eui.Button;

    public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);
    }

    public initUI():void
    {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.FightStartUI);
    }

    public initData(): void 
    {
        super.initData();
    }
}