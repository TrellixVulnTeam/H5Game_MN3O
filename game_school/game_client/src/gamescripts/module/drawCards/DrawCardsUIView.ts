class DrawCardsUIView extends BaseEuiView 
{
    public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);
    }

    public initUI():void
    {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.DrawCardsUI);
    }

    public initData(): void 
    {
        super.initData();
    }
}