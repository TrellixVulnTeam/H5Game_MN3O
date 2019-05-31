class WechatUIController extends BaseController
{
    private wechatModel:WechatUIModel;//本模块的数据存储
    private wechatProxy:WechatUIProxy;//本模块的Proxy

    private wechatView:WechatUIView;//通信界面
    private fmcView:FriendMCommentUIView;//朋友圈发布消息和留言选择界面

    private dialoguiView:DialogueCommentUIView;//聊天
    private girlInfoView:GrilDetailedInfoUiView;//女孩信息页面
    private historyView:WeChatHistoryUIView;//聊天记录

    public constructor(){
        super();

        this.wechatModel = new WechatUIModel(this);
        this.wechatProxy = new WechatUIProxy(this);

        this.historyView=new WeChatHistoryUIView(this,LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.historyView,this.historyView);

        this.wechatView = new WechatUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.WechatUI, this.wechatView);

        this.fmcView = new FriendMCommentUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.FriendMCommentUI, this.fmcView);

        this.girlInfoView=new GrilDetailedInfoUiView(this,LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.GrilInfo,this.girlInfoView);

        this.dialoguiView=new DialogueCommentUIView(this,LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.Dialogue,this.dialoguiView);

         /**
         * 朋友圈
         */
        this.RegisterEvent(EventDef.announceInfo);
        this.RegisterEvent(EventDef.commentInfo);
        this.RegisterEvent(EventDef.updateFriendsInfo);
        this.RegisterEvent(EventDef.updateCommentInfo);

        /**聊天 */
        this.RegisterEvent(EventDef.InquireChatInfo);
        this.RegisterEvent(EventDef.OpenListByType);
        this.RegisterEvent(EventDef.OpendialogView);
        this.RegisterEvent(EventDef.BackDialogListView);
        this.RegisterEvent(EventDef.ActivationChatGroup);
        this.RegisterEvent(EventDef.OpendialogViewByChatId);

        /**通讯录 */
        this.RegisterEvent(EventDef.OpenAddressBookList);
        this.RegisterEvent(EventDef.OpenGirlInfoView);
        this.RegisterEvent(EventDef.CloseGirlInfoView);
        this.RegisterEvent(EventDef.OpenHistoryView);
    }


    public HandleEvent(ev:EventDef,le:LogicEvent){
        super.HandleEvent(ev,le);
        switch(ev)  {
            case EventDef.announceInfo:
             this. announceInfo(le.IntParam0);
            break;
             case EventDef.commentInfo:
             this.commentInfo(le.IntParam0);
            break;
             case EventDef.updateFriendsInfo:
             this.updateFriendsInfo(le.IntParam0,le.IntParam1);
            break;
             case EventDef.updateCommentInfo:
             this.updateCommentInfo(le.IntParam0,le.IntParam1);
            break;
             case EventDef.InquireChatInfo:
             this.InquireChatInfo();
            break;
             case EventDef.OpenListByType:
             this.OpenListByType(le.IntParam0);
            break;
             case EventDef.OpendialogView:
             this.OpendialogView(le.IntParam0,le.IntParam1);
            break;
             case EventDef.BackDialogListView:
             this.BackDialogListView(le.IntParam0);
            break;
             case EventDef.ActivationChatGroup:
             this.ActivationChatGroup(le.IntParam0);
            break;
             case EventDef.OpendialogViewByChatId:
             this.OpendialogViewByID(le.IntParam0,le.IntParam1);
            break;
             case EventDef.OpenAddressBookList:
             this.OpenAddressBookList();
            break;
             case EventDef.OpenGirlInfoView:
             this.OpenGirlInfoView(le.IntParam0)
            break;
             case EventDef.CloseGirlInfoView:
             this.CloseGirlInfoView();
            break;
             case EventDef.OpenHistoryView:
             this.OpenHistoryView(le.IntParam0);
            break;
        }
    }


    /**
     * 朋友圈发布消息
    */
    private announceInfo(id:number):void
    {
        this.fmcView.onSetAnnounceInfoId(id);
        App.ViewManager.open(ViewConst.FriendMCommentUI);
    }

    /**
     * 朋友圈留言
    */
    private commentInfo(id:number):void
    {
        this.fmcView.onSetCommentInfoId(id);
        App.ViewManager.open(ViewConst.FriendMCommentUI);
    }

    /**
     * 刷新朋友圈消息
    */
    private updateFriendsInfo(cfid:number, ctid:number):void
    {
        this.wechatView.friendMomentUI.onUpdateAnnounceInfo(cfid, ctid);
    }

     /**
     * 刷新留言
    */
    private updateCommentInfo(cfid:number, ctid:number):void
    {
        this.wechatView.friendMomentUI.onUpdateCommentInfo(cfid, ctid);
    }

    /**
     *  查询聊天信息
     */
    private InquireChatInfo(){
        this.wechatModel.InquireChatInfo();
    }

    /**
     * 通过类型打开列表
     */
    private OpenListByType(type:WeChatGroupType){
        if(type==WeChatGroupType.Flock){
            this.wechatView.chatListInfoUi.UpdateList(true,type,App.WechatManager.FlockList);
        }else{
            this.wechatView.chatListInfoUi.UpdateList(true,type,App.WechatManager.FiendList);
        }
    }

    /**
     * 打开通讯录
     */
    private OpenAddressBookList(){
        this.wechatView.addressBookView.UpdateList();
    }

    /**
     * 打开聊天
     */
    private OpendialogView(girlId:number=0,type:WechatUIType=WechatUIType.Wechat_chat){
        
        let info:ChatOwnList=App.WechatManager.GetChatListByownId(girlId);
        
        if(info){
              
        this.wechatView.chatListInfoUi.CleraItem();
         App.ViewManager.open(ViewConst.Dialogue);
         App.WechatManager.SetLaseTimerList(info);
         this.dialoguiView.OpenByOwner(info.ownId);

            }
             
            //   this.dialoguiView.openType=type;
            //   if(type==WechatUIType.Wechat_record)
            //    App.ViewManager.close(ViewConst.GrilInfo);
            //    App.ViewManager.close(ViewConst.WechatUI);
               
       
    }

    /**
     * 返回聊天列表
     */
    private BackDialogListView(type:WechatUIType=WechatUIType.Wechat_chat){
        App.ViewManager.close(ViewConst.Dialogue);
        App.ViewManager.open(ViewConst.WechatUI);
        this.wechatView.SelectUIByType(type);
    }
   
    /**
     * 激活聊天组
     */
    private ActivationChatGroup(id:number){
        App.WechatManager.AddActionChatToList(id,WeChatGroupStatus.ActivationNotTrigger,egret.getTimer());
    }

    /**
     * 打开聊天
     */
    private OpendialogViewByID(ownId:number,chatId:number){
        this.wechatView.chatListInfoUi. CleraItem();
        App.ViewManager.open(ViewConst.Dialogue);
        this.dialoguiView.OpenByChatID(ownId,chatId);
    }

    /**
     * 打开信息页面
     */
    private OpenGirlInfoView(girlid:number){
        App.ViewManager.open(ViewConst.GrilInfo);
        this.girlInfoView.InitViewInfo(girlid);
    }

     /**
     * 关闭
     */
    private CloseGirlInfoView(){
        	App.ViewManager.close(ViewConst.GrilInfo);
            this.wechatView.addressBookView.UpdateList();
    }

    /**
     * 打开聊天记录
     */
    private OpenHistoryView(girlId:number){
        App.ViewManager.open(ViewConst.historyView);
        this.historyView.InitView(App.WechatManager.GetChatListByownId(girlId).GetAllTriggered());
     }


}