class DrawCardsUIController extends BaseController
{
    private drawCardsModel:DrawCardsUIModel;//本模块的数据存储
    private drawCardsProxy:DrawCardsUIProxy;//本模块的Proxy
    private drawCardsView:DrawCardsUIView;//本模块的所有UI

    public constructor(){
        super();

        this.drawCardsModel = new DrawCardsUIModel(this);
        this.drawCardsProxy = new DrawCardsUIProxy(this);

        this.drawCardsView = new DrawCardsUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.DrawCardsUI, this.drawCardsView);
    }
}