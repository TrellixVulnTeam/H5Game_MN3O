var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var __extends = this && this.__extends || function __extends(t, e) { 
 function r() { 
 this.constructor = t;
}
for (var i in e) e.hasOwnProperty(i) && (t[i] = e[i]);
r.prototype = e.prototype, t.prototype = new r();
};
/**
 *
 */
var ActivityView = (function (_super) {
    __extends(ActivityView, _super);
    function ActivityView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.itemArray = [];
        return _this;
    }
    Object.defineProperty(ActivityView.prototype, "Model", {
        get: function () {
            return App.ControllerManager.getControllerModel(ControllerConst.MainActivity);
        },
        enumerable: true,
        configurable: true
    });
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    ActivityView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.MainActivity);
        this.Model.initActivityArray();
        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            _this.onClose();
        }, this);
        this.updataUI();
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    ActivityView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    ActivityView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        //TweenManager.scaleTween(this.chapterChooseGroup, this, 1, 249, () => { });
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    ActivityView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    //刷新页面UI
    ActivityView.prototype.updataUI = function () {
        var array = this.Model.activityConArray;
        this.createOrUpdateItem(array);
        for (var i = 0; i < this.itemArray.length; i++) {
            this.itemArray[i].setVisible(false);
        }
        for (var i = 0; i < array.length; i++) {
            this.itemArray[i].setData(array[i]);
            this.itemArray[i].setVisible(true);
        }
    };
    ActivityView.prototype.createOrUpdateItem = function (listCount) {
        for (var i = this.itemArray.length; i < listCount.length; i++) {
            var item = new ActivityItem();
            item.init(this);
            this.gro_list.addChild(item);
            this.itemArray.push(item);
        }
    };
    ActivityView.prototype.selectActivity = function (con) {
        switch (con.click_type) {
            case 1://打开UI页面
                this.onClose();
                App.ViewManager.open(con.click_para1);
                break;
            case 2://打开剧情
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
    };
    return ActivityView;
}(BaseEuiView));
__reflect(ActivityView.prototype, "ActivityView");
var ActivityItem = (function (_super) {
    __extends(ActivityItem, _super);
    function ActivityItem() {
        var _this = _super.call(this) || this;
        _this.skinName = App.ViewManager.getSkin(ViewConst.MainActivityItem);
        return _this;
    }
    //----------------------------------------------------------
    ActivityItem.prototype.init = function (view) {
        if (view == null)
            return;
        this.mHandView = view;
        this.btn_go.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
    };
    ActivityItem.prototype.setData = function (data) {
        if (data == null)
            return;
        this.data = data;
        this.image_back.source = data.contentPicture;
        this.image_news.visible = false;
        this.image_type.visible = false;
        this.label_time.visible = false;
    };
    /**/
    ActivityItem.prototype.setVisible = function (v) {
        this.visible = v;
    };
    //设置位置
    ActivityItem.prototype.setPos = function (posX, posY) {
        this.x = posX;
        this.y = posY;
    };
    ActivityItem.prototype.onClick = function () {
        this.mHandView.selectActivity(this.data);
    };
    return ActivityItem;
}(eui.Component));
__reflect(ActivityItem.prototype, "ActivityItem");
//# sourceMappingURL=ActivitylView.js.map