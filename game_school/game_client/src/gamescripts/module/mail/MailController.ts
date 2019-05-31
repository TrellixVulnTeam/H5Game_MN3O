/**
 * 
 */
class MailController extends BaseController {
    //本模块的数据存储
    private mailModel: MailModel;
    //本模块的所有UI
    private mailMainView: MailMainView;
    private mailDetailView: MailDetailView;

    //本模块的Proxy
    private mailProxy: MailProxy;

    public constructor() {
        super();

        //初始化Model
        this.mailModel = new MailModel(this);

        //初始化UI
        this.mailMainView = new MailMainView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.MailMain, this.mailMainView);

        this.mailDetailView = new MailDetailView(this, LayerManager.UI_Popup)
        App.ViewManager.register(ViewConst.MailDetail, this.mailDetailView);

        //初始化Proxy
        this.mailProxy = new MailProxy(this);

         this.RegisterEvent(EventDef.UPDATADATA_C2S);   
         this.RegisterEvent(EventDef.SELECTMAIL_C2S);   
    }

    public HandleEvent(ev:EventDef,le:LogicEvent){
        super.HandleEvent(ev,le);
        switch(ev){
            case EventDef.UPDATADATA_C2S:
            this.onUpdataData(le.IntParam0);
            break;
            case EventDef.SELECTMAIL_C2S:
            this.onSelectMail(le.IntParam0);
            break;
        }
    }

    //选择章节事件
    private onUpdataData(chapterId: number): void {
        this.mailMainView.updataUI();
    }

    private onSelectMail(id: number): void {
        App.ViewManager.open(ViewConst.MailDetail);
        this.mailDetailView.setData(id);
    }

}