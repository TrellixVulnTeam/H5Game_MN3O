/**
 * 
 */
class ChapterChooseView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    public get Model(): ChapterModel {
        return App.ControllerManager.getControllerModel(ControllerConst.Chapter) as ChapterModel;
    }

    private chapterChooseGroup: eui.Group;

    private chapterBtnArray: Array<eui.Button> = [];

    //页面Item集合
    private chapterChooseItemGroup: eui.Group;
    private chapterChooseItemArray: Array<ChapterChooseItem> = []; //暂时无用了
    private btn_back: eui.Button;//返回

    //临时指引1(第一章按鈕 打开关卡界面）
    private isFirstGuide: boolean = false;

    private chapterChooseBtnItemArray: Array<ChapterChooseBtnItem> = [];

    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        //this.skinName = "resource/skins/Chapter_choose.exml";
        this.skinName = App.ViewManager.getSkin(ViewConst.ChapterChoose);
        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnBackClick, this);

        this.isFirstGuide = App.GuideManager.getIsGuide;
        if (this.isFirstGuide) {
            this.isFirstGuide = false;
            this.addFirstGuide();//指引
        }

        for (var i: number = 0; i < this.chapterChooseItemGroup.$children.length; i++) {
            let btn = this.chapterChooseItemGroup.getChildAt(i);
            this.chapterBtnArray.push(btn as eui.Button);
        }
        //this.updataUI();
    }

    /**
     * 临时指引1（第一次进入章节界面，点击章节按钮1，打开关卡界面）
    */
    public addFirstGuide() {
        this.validateNow();
        this.chapterChooseItemGroup.validateNow();
        let btn = this.chapterChooseItemGroup.getChildAt(0) as eui.Button;
        let mask = new GuideMask(btn, () => {
            this.onClose();
            App.ViewManager.open(ViewConst.Chapter);
        }, "", true, (btn.width / 6));
        this.addChild(mask);
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

        if (this.Model.isFirstOpenChapter) {
            this.Model.isFirstOpenChapter = false;
        }

        TweenManager.scaleTween(this.chapterChooseGroup, this, 1, 249, () => {
            this.updataUI();
        });
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
        //this.createOrUpdateItem(ChapterConfig.array);
        if (ChapterConfig.array.length <= this.chapterBtnArray.length) {
            //for (var i: number = ChapterConfig.array.length; i < this.chapterBtnArray.length; i++) {
            for (var i: number = 0; i < this.chapterBtnArray.length; i++) { //默认都是关闭的
                this.chapterBtnArray[i].enabled = false;
            }
        }

        let index = ChapterConfig.array.length;
        if (index > this.chapterBtnArray.length) {
            index = this.chapterBtnArray.length;
        }

        for (var i: number = this.chapterChooseBtnItemArray.length; i < index; i++) {
            let item = new ChapterChooseBtnItem();
            this.chapterChooseBtnItemArray.push(item);
        }

        for (var i: number = 0; i < index; i++) {
            let item = this.chapterChooseBtnItemArray[i];
            item.init(this.chapterBtnArray[i], ChapterConfig.array[i], this);
        }
    }

    private createOrUpdateItem(listCount: Array<ChapterConfig>): void {
        //创建UI chapterItem
        for (var i: number = this.chapterChooseItemArray.length; i < listCount.length; i++) {
            var chapterChoose: ChapterChooseItem;

            if (i % 2 == 0) {
                chapterChoose = new ChapterChooseLeftItem();
            }
            else {
                chapterChoose = new ChapterChooseRightItem();
            }

            chapterChoose.init(listCount[i], this);
            this.chapterChooseItemGroup.addChild(chapterChoose);
            this.chapterChooseItemArray.push(chapterChoose);
        }
    }


    //返回按钮事件
    private onBtnBackClick(): void {
        TweenManager.scaleTween(this.chapterChooseGroup, this, 0, 249,
            function () {
                App.ViewManager.close(ViewConst.ChapterChoose);
                if (!App.ViewManager.isShow(ViewConst.Chapter))
                    App.ViewManager.open(ViewConst.Chapter);
            }.bind(this)
        );
    }

    public selectChapter(chapterID: number): void {
        // if (this.Model.curSelectChapter == chapterID)
        //     return;
        App.EventMgrHelper.PushEvent(EventDef.SelectChapter, chapterID);
        //this.applyFunc(ChapterConst.SELECTCHAPTEREVENT_C2C, chapterID);
        this.onBtnBackClick();
    }
}

class ChapterChooseBtnItem {

    public constructor() {
    }

    private btn: eui.Button;
    private mHandView: ChapterChooseView;
    //传进来的表数据
    private con: ChapterConfig;

    public init(btn: eui.Button, data: ChapterConfig, view: ChapterChooseView): void {
        if (btn == null || view == null || data == null) {
            return;
        }
        this.btn = btn;
        this.mHandView = view;
        this.con = data;
        this.btn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
        let image: eui.Image = this.btn.getChildAt(0) as eui.Image;
        image.pixelHitTest = true;

        this.SetData();
    }

    public SetData() {
        if (this.mHandView.Model.maxChapter >= this.con.id) {
            this.btn.enabled = true;
        }
    }

    private onClick(): void {
        this.mHandView.selectChapter(this.con.id);
    }
}

class ChapterChooseItem extends eui.Component {

    public constructor() {
        super();
    }

    private mHandView: ChapterChooseView;
    //传进来的表数据
    private con: ChapterConfig;

    //是否锁定状态
    public image_lock: eui.Image;
    public label_num: eui.Label;
    public label_name: eui.Label;
    //课程是否已经通过
    public label_type: eui.Label;
    //课程星星数量
    public label_star: eui.Label;

    public btn_choose: eui.Button;

    public init(data: ChapterConfig, view: ChapterChooseView): void {
        if (view == null || data == null) {
            return;
        }
        this.con = data;
        this.mHandView = view;
        this.label_num.text = data.chapter_num;
        this.label_name.text = data.chapter_name;
        this.label_type.text = "课程未通过";
        this.label_star.text = " x 0";

        this.setPos(0, (data.id - 1) * this.height);

        //if (data.id == 1) {
        this.image_lock.visible = false;
        //}

        this.btn_choose.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
    }

    //设置位置
    public setPos(posX: number, posY: number): void {
        this.x = posX;
        this.y = posY;
    }

    private onClick(): void {
        this.mHandView.selectChapter(this.con.id);
    }
}

class ChapterChooseLeftItem extends ChapterChooseItem {
    constructor() {
        super();
        this.skinName = "resource/skins/Chapter_choose_left.exml";
    }

}

class ChapterChooseRightItem extends ChapterChooseItem {
    constructor() {
        super();
        this.skinName = "resource/skins/Chapter_choose_right.exml";
    }
}