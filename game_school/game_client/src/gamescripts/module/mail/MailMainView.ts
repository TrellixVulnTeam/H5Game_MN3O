/**
 * 
 */
class MailMainView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    public get Model(): MailModel {
        return App.ControllerManager.getControllerModel(ControllerConst.Mail) as MailModel;
    }

    private btn_close: eui.Button;

    private btn_onedel: eui.Button;  //一键删除
    private btn_onekey: eui.Button;  //一键领取

    //整个UI的面板Group
    public scrollerCon: eui.Group;
    private mailItemArray: Array<MailItem> = [];

    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.MailMain);

        //this.Model.setMailDataArray();  //临时初始化的数据

        this.btn_close.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            this.onClose();
        }, this);

        this.btn_onedel.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onDel, this);

        this.btn_onekey.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onKey, this);
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
        if (this.Model.mailDataArray == null || this.Model.mailDataArray.length <= 0)
            this.Model.setMailDataArray();  //临时初始化的数据
        this.updataUI();
    }

    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    public close(...param: any[]): void {
        super.close(param);

    }

    //选择关卡页面
    private onArrow(): void {
        // 如果已经打开了,就不在重复打开了,或者出战UI是否已经打开了
        if (App.ViewManager.isShow(ViewConst.ChapterMseeag)
            || App.ViewManager.isShow(ViewConst.ChapterChoose)) {
            return;
        }
        App.ViewManager.open(ViewConst.ChapterChoose);
    }

    //刷新页面UI
    public updataUI(): void {
        this.createOrUpdateItem(this.Model.mailDataArray);

        for (var i: number = 0; i < this.mailItemArray.length; i++) {
            this.mailItemArray[i].setVisible(false);
        }

        for (var i: number = 0; i < this.Model.mailDataArray.length; i++) {
            this.mailItemArray[i].setData(this.Model.mailDataArray[i]);
            this.mailItemArray[i].setVisible(true);
        }
    }

    public createOrUpdateItem(listCount: Array<MailData>): void {
        //创建UI chapterItem
        for (var i: number = this.mailItemArray.length; i < listCount.length; i++) {
            var mailItem: MailItem = new MailItem();
            mailItem.init(this);
            this.scrollerCon.addChild(mailItem);
            this.mailItemArray.push(mailItem);
        }
    }

    public selectMail(id: number): void {
        App.EventMgrHelper.PushEvent(EventDef.SELECTMAIL_C2S,id);
    }


    private onDel(): void {
        let array: Array<number> = [];

        for (let i: number = 0; i < this.Model.mailDataArray.length; i++) {
            if (this.Model.mailDataArray[i].isNew == false && this.Model.mailDataArray[i].isGet()) //
            {
                array.push(this.Model.mailDataArray[i].mailID);
                // this.Model.mailDataArray.splice(i, 1);
            }
        }

        for (let i: number = 0; i < array.length; i++) {
            this.Model.delMailDataByID(array[i]);
        }
        
       App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S);
    }


    //一键领取
    private onKey(): void {
        for (let i: number = 0; i < this.Model.mailDataArray.length; i++) {
            if (this.Model.mailDataArray[i].isNew == true)
                this.Model.mailDataArray[i].isNew = false;
            this.Model.mailDataArray[i].clearItems();
        }
    App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S);
    }

}

class MailItem extends eui.Component {
    constructor() {
        super();
        this.skinName = "resource/skins/Mail_item.exml";
    }

    private mHandView: MailMainView;
    private mailID: number;


    private label_title: eui.Label;
    private label_mess: eui.Label;

    private button_open: eui.Button;
    private image_news: eui.Image;

    public setVisible(v: boolean): void {
        this.visible = v;
    }

    //刷新数据
    public init(view: MailMainView): void {
        if (view == null)
            return;
        this.mHandView = view;
        this.button_open.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
    }

    //设置数据
    public setData(data: MailData): void {
        if (data == null)
            return;
        this.mailID = data.mailID;
        this.label_title.text = data.mailName;
        this.label_mess.text = data.mailMes;

        this.image_news.visible = data.IsNew;
    }

    //设置位置
    public setPos(posX: number, posY: number): void {
        this.x = posX;
        this.y = posY;
    }

    private onClick(): void {
        this.mHandView.selectMail(this.mailID);
    }
}