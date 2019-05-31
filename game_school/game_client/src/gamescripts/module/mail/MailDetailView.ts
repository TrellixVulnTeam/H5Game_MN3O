/**
 * 
 */
class MailDetailView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    public get Model(): MailModel {
        return App.ControllerManager.getControllerModel(ControllerConst.Mail) as MailModel;
    }

    private star: egret.tween.TweenGroup;

    private mMailID: number;
    private mMailData: MailData;

    private btn_close: eui.Button;
    private btn_get: eui.Button;
    private btn_del: eui.Button;

    private label_mail: eui.Label;
    private label_name: eui.Label;

    //奖励
    private group_reward: eui.Group;
    private itemArray: Array<UIItem> = [];
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.MailDetail);

        this.btn_close.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            this.onClose();
        }, this);

        this.btn_get.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onGet, this);
        this.btn_del.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onDel, this);
    }

    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    public initData(): void {
        super.initData();
    }

    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    public open(...param: any[]): void {
        super.open(param);
        this.star.play(0);
        //TweenManager.scaleTween(this.chapterChooseGroup, this, 1, 249, () => { });
    }

    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    public close(...param: any[]): void {
        super.close(param);
    }


    public setData(id: number): void {
        this.mMailID = id;
        this.mMailData = this.Model.getMailDataByID(id);
        this.label_name.text = this.mMailData.mailName;
        this.label_mail.text = this.mMailData.mailMes;

        this.Model.setMailDataIsNewByID(id);
        this.updataRewardItem();
        App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S,id);
    }


    //一键删除所以已读
    private onDel(): void {
        if (this.mMailData.isGet())
            this.Model.delMailDataByID(this.mMailID);
          App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S,this.mMailID);
        this.onClose();
    }


    //一键领取
    private onGet(): void {
        //TODO,临时
        this.mMailData.clearItems();
        App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S,this.mMailID);
        this.onClose();
    }


    //刷新页面UI
    public updataRewardItem(): void {
        this.createOrUpdateItem(this.mMailData.items);

        for (var i: number = 0; i < this.itemArray.length; i++) {
            this.itemArray[i].setVisible(false);
        }

        for (var i: number = 0; i < this.mMailData.items.length; i++) {
            this.itemArray[i].setItem(this.mMailData.items[i]);
            this.itemArray[i].UnLock();
            this.itemArray[i].setVisible(true);
        }
    }

    public createOrUpdateItem(listCount: Array<Item>): void {
        //创建UI chapterItem
        for (var i: number = this.itemArray.length; i < listCount.length; i++) {
            var item: UIItem = new UIItem();
            this.group_reward.addChild(item);
            this.itemArray.push(item);
        }
    }

}
