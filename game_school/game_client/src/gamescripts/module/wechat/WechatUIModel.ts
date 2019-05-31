class WechatUIModel extends BaseModel
{
    public constructor($controller:BaseController)
    {
        super($controller);
        this.InquireChatInfo();
    }

    //测试数据
    public InquireChatInfo(){
        for(let i=0;i<ChatGroupConfig.array.length;i++){
             App.WechatManager.AddActionChatToList(ChatGroupConfig.array[i].chatID,WeChatGroupStatus.ActivationNotTrigger,egret.getTimer());
        }
    }
 }

