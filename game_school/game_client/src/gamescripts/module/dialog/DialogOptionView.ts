/**
 * 
 */
class DialogOptionView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    private image_background: eui.Image;

    private Group_choose: eui.Group;
    private optionItemArray: Array<OptionItem> = [];

    public get Model(): DialogModel {
        return App.ControllerManager.getControllerModel(ControllerConst.Dialog) as DialogModel;
    }


    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.DialogOption);
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
        //TweenManager.scaleTween(this.Group_choose, this, 1, 249, () => { });
        this.updataUI();
    }

    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    public close(...param: any[]): void {
        super.close(param);
    }


    //刷新页面UI
    public updataUI(): void {
        var con: DialogOptionConfig = this.Model.GetDialogOptionConfigByOptionID(this.Model.curDialogConf.optionID);

        this.createOrUpdateItem(con);

        for (var i: number = 0; i < this.optionItemArray.length; i++) {
            this.optionItemArray[i].setVisible(false);
        }

        if (con.optionContent1 != "") {
            this.optionItemArray[0].setData(0, con.optionContent1, con.nextDialog1);
            this.optionItemArray[0].setVisible(true);
        }
        if (con.optionContent2 != "") {
            this.optionItemArray[1].setData(0, con.optionContent2, con.nextDialog2);
            this.optionItemArray[1].setVisible(true);
        }
        if (con.optionContent3 != "") {
            this.optionItemArray[2].setData(0, con.optionContent3, con.nextDialog3);
            this.optionItemArray[2].setVisible(true);
        }
        if (con.optionContent4 != "") {
            this.optionItemArray[3].setData(0, con.optionContent4, con.nextDialog4);
            this.optionItemArray[3].setVisible(true);
        }

    }

    public createOrUpdateItem(con: DialogOptionConfig): void {
        //创建UI chapterItem
        for (var i: number = this.optionItemArray.length; i < con.option1; i++) {
            var optionItem: OptionItem = new OptionItem();
            optionItem.init(this);
            this.Group_choose.addChild(optionItem);
            this.optionItemArray.push(optionItem);
        }
    }

    public onClickOptionItem(optionIndex: number, nextDialogID: number): void {
        App.EventMgrHelper.PushEvent(EventDef.SelectDialogOption, optionIndex, nextDialogID);
        //App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.SELECTOPTION_C2C, optionIndex, nextDialogID);
        this.onClose();
    }
}

class OptionItem extends eui.Component {
    public constructor() {
        super();
        this.skinName = "resource/skins/Dialogue_choose_item.exml";
    }
    private mHandView: DialogOptionView;

    private index: number;
    private nextDialogID: number;

    public label_dia: eui.Label;
    public button_dia: eui.Button;

    public init(view: DialogOptionView): void {
        if (view == null)
            return;
        this.mHandView = view;
        this.button_dia.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
    }

    public setData(index: number, str: string, nextDialogID: number): void {
        this.index = index;
        this.label_dia.text = str;
        this.nextDialogID = nextDialogID;
    }

    public setVisible(v: boolean): void {
        this.visible = v;
    }

    private onClick(): void {
        this.mHandView.onClickOptionItem(this.index, this.nextDialogID);
    }
}
