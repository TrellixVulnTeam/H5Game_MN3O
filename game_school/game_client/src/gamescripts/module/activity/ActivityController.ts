/**
 * 
 */
class ActivityController extends BaseController {
    //本模块的数据存储
    private activityModel: ActivityModel;
    //本模块的所有UI
    private activityView: ActivityView;

    //本模块的Proxy
    private activityProxy: ActivityProxy;

    public constructor() {
        super();

        //初始化Model
        this.activityModel = new ActivityModel(this);
        //初始化UI
        this.activityView = new ActivityView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.MainActivity, this.activityView);

        //初始化Proxy
        this.activityProxy = new ActivityProxy(this);

        // //注册模块间、模块内部事件监听
        // this.registerFunc(MailConst.UPDATADATA_C2S, this.onUpdataData, this);

        // this.registerFunc(MailConst.SELECTMAIL_C2S, this.onSelectMail, this);
    }


    //选择章节事件
    private onUpdataData(chapterId: number): void {
       
    }

    private onSelectMail(id: number): void {
      
    }

}