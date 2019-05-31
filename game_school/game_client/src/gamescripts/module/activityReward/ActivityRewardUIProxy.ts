class ActivityRewardUIProxy extends BaseProxy
{
    public constructor($controller:BaseController)
    {
        super($controller);

        //注册从服务器返回消息的监听
        //this.receiveServerMsg(ActivityRewardUIConst.sign, this.sign, this);
    }
}