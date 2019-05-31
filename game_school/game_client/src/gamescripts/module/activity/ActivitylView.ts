/**
 * 
 */
class ActivityView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    public get Model(): ActivityModel {
        return App.ControllerManager.getControllerModel(ControllerConst.MainActivity) as ActivityModel;
    }

    private btn_back: eui.Button;

    //奖励
    private gro_list: eui.Group;
    private itemArray: Array<ActivityItem> = [];
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.MainActivity);
        this.Model.initActivityArray();

        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            this.onClose();
        }, this);

        this.updataUI();
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
        //TweenManager.scaleTween(this.chapterChooseGroup, this, 1, 249, () => { });
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
        let array = this.Model.activityConArray;
        this.createOrUpdateItem(array);

        for (var i: number = 0; i < this.itemArray.length; i++) {
            this.itemArray[i].setVisible(false);
        }

        for (var i: number = 0; i < array.length; i++) {
            this.itemArray[i].setData(array[i]);
            this.itemArray[i].setVisible(true);
        }
    }

    public createOrUpdateItem(listCount: Array<ActivityClientConfig>): void {
        for (var i: number = this.itemArray.length; i < listCount.length; i++) {
            var item: ActivityItem = new ActivityItem();
            item.init(this);
            this.gro_list.addChild(item);
            this.itemArray.push(item);
        }
    }

    public selectActivity(con: ActivityClientConfig): void {
        switch (con.click_type) {
            case 1:  //打开UI页面
                this.onClose();
                App.ViewManager.open(con.click_para1);
                break;
            case 2: //打开剧情
                this.onClose();
                App.ViewManager.close(ViewConst.MainUI);
                App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, con.click_para1, function () {
                    App.ViewManager.close(ViewConst.Dialog);
                    App.ViewManager.open(ViewConst.MainUI);
                }.bind(this), 0, 0, "", "");
                // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, con.click_para1, () => {
                //     App.ViewManager.close(ViewConst.Dialog);
                //     App.ViewManager.open(ViewConst.MainUI);
                // });
                break;

        }
    }

}

class ActivityItem extends eui.Component {
    constructor() {
        super();
        this.skinName = App.ViewManager.getSkin(ViewConst.MainActivityItem);
    }

    private mHandView: ActivityView;
    private data: ActivityClientConfig;

    //-------------------ui组件
    private image_back: eui.Image;
    private image_news: eui.Image;
    private image_type: eui.Image;
    private label_time: eui.Label;
    private btn_go: eui.Button;
    //----------------------------------------------------------


    public init(view: ActivityView): void {
        if (view == null)
            return;
        this.mHandView = view;
        this.btn_go.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
    }

    public setData(data: ActivityClientConfig): void {
        if (data == null)
            return;
        this.data = data;

        this.image_back.source = data.contentPicture;
        this.image_news.visible = false;
        this.image_type.visible = false;
        this.label_time.visible = false;
    }

    /**/
    public setVisible(v: boolean): void {
        this.visible = v;
    }

    //设置位置
    public setPos(posX: number, posY: number): void {
        this.x = posX;
        this.y = posY;
    }

    private onClick(): void {
        this.mHandView.selectActivity(this.data);
    }
}