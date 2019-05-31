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
var ChapterChooseView = (function (_super) {
    __extends(ChapterChooseView, _super);
    function ChapterChooseView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.chapterBtnArray = [];
        _this.chapterChooseItemArray = []; //暂时无用了
        //临时指引1(第一章按鈕 打开关卡界面）
        _this.isFirstGuide = false;
        _this.chapterChooseBtnItemArray = [];
        return _this;
    }
    Object.defineProperty(ChapterChooseView.prototype, "Model", {
        get: function () {
            return App.ControllerManager.getControllerModel(ControllerConst.Chapter);
        },
        enumerable: true,
        configurable: true
    });
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    ChapterChooseView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        //this.skinName = "resource/skins/Chapter_choose.exml";
        this.skinName = App.ViewManager.getSkin(ViewConst.ChapterChoose);
        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnBackClick, this);
        this.isFirstGuide = App.GuideManager.getIsGuide;
        if (this.isFirstGuide) {
            this.isFirstGuide = false;
            this.addFirstGuide(); //指引
        }
        for (var i = 0; i < this.chapterChooseItemGroup.$children.length; i++) {
            var btn = this.chapterChooseItemGroup.getChildAt(i);
            this.chapterBtnArray.push(btn);
        }
        //this.updataUI();
    };
    /**
     * 临时指引1（第一次进入章节界面，点击章节按钮1，打开关卡界面）
    */
    ChapterChooseView.prototype.addFirstGuide = function () {
        var _this = this;
        this.validateNow();
        this.chapterChooseItemGroup.validateNow();
        var btn = this.chapterChooseItemGroup.getChildAt(0);
        var mask = new GuideMask(btn, function () {
            _this.onClose();
            App.ViewManager.open(ViewConst.Chapter);
        }, "", true, (btn.width / 6));
        this.addChild(mask);
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    ChapterChooseView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    ChapterChooseView.prototype.open = function () {
        var _this = this;
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        if (this.Model.isFirstOpenChapter) {
            this.Model.isFirstOpenChapter = false;
        }
        TweenManager.scaleTween(this.chapterChooseGroup, this, 1, 249, function () {
            _this.updataUI();
        });
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    ChapterChooseView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    //刷新页面UI
    ChapterChooseView.prototype.updataUI = function () {
        //this.createOrUpdateItem(ChapterConfig.array);
        if (ChapterConfig.array.length <= this.chapterBtnArray.length) {
            //for (var i: number = ChapterConfig.array.length; i < this.chapterBtnArray.length; i++) {
            for (var i = 0; i < this.chapterBtnArray.length; i++) {
                this.chapterBtnArray[i].enabled = false;
            }
        }
        var index = ChapterConfig.array.length;
        if (index > this.chapterBtnArray.length) {
            index = this.chapterBtnArray.length;
        }
        for (var i = this.chapterChooseBtnItemArray.length; i < index; i++) {
            var item = new ChapterChooseBtnItem();
            this.chapterChooseBtnItemArray.push(item);
        }
        for (var i = 0; i < index; i++) {
            var item = this.chapterChooseBtnItemArray[i];
            item.init(this.chapterBtnArray[i], ChapterConfig.array[i], this);
        }
    };
    ChapterChooseView.prototype.createOrUpdateItem = function (listCount) {
        //创建UI chapterItem
        for (var i = this.chapterChooseItemArray.length; i < listCount.length; i++) {
            var chapterChoose;
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
    };
    //返回按钮事件
    ChapterChooseView.prototype.onBtnBackClick = function () {
        TweenManager.scaleTween(this.chapterChooseGroup, this, 0, 249, function () {
            App.ViewManager.close(ViewConst.ChapterChoose);
            if (!App.ViewManager.isShow(ViewConst.Chapter))
                App.ViewManager.open(ViewConst.Chapter);
        }.bind(this));
    };
    ChapterChooseView.prototype.selectChapter = function (chapterID) {
        // if (this.Model.curSelectChapter == chapterID)
        //     return;
        App.EventMgrHelper.PushEvent(EventDef.SelectChapter, chapterID);
        //this.applyFunc(ChapterConst.SELECTCHAPTEREVENT_C2C, chapterID);
        this.onBtnBackClick();
    };
    return ChapterChooseView;
}(BaseEuiView));
__reflect(ChapterChooseView.prototype, "ChapterChooseView");
var ChapterChooseBtnItem = (function () {
    function ChapterChooseBtnItem() {
    }
    ChapterChooseBtnItem.prototype.init = function (btn, data, view) {
        if (btn == null || view == null || data == null) {
            return;
        }
        this.btn = btn;
        this.mHandView = view;
        this.con = data;
        this.btn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
        var image = this.btn.getChildAt(0);
        image.pixelHitTest = true;
        this.SetData();
    };
    ChapterChooseBtnItem.prototype.SetData = function () {
        if (this.mHandView.Model.maxChapter >= this.con.id) {
            this.btn.enabled = true;
        }
    };
    ChapterChooseBtnItem.prototype.onClick = function () {
        this.mHandView.selectChapter(this.con.id);
    };
    return ChapterChooseBtnItem;
}());
__reflect(ChapterChooseBtnItem.prototype, "ChapterChooseBtnItem");
var ChapterChooseItem = (function (_super) {
    __extends(ChapterChooseItem, _super);
    function ChapterChooseItem() {
        return _super.call(this) || this;
    }
    ChapterChooseItem.prototype.init = function (data, view) {
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
    };
    //设置位置
    ChapterChooseItem.prototype.setPos = function (posX, posY) {
        this.x = posX;
        this.y = posY;
    };
    ChapterChooseItem.prototype.onClick = function () {
        this.mHandView.selectChapter(this.con.id);
    };
    return ChapterChooseItem;
}(eui.Component));
__reflect(ChapterChooseItem.prototype, "ChapterChooseItem");
var ChapterChooseLeftItem = (function (_super) {
    __extends(ChapterChooseLeftItem, _super);
    function ChapterChooseLeftItem() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/skins/Chapter_choose_left.exml";
        return _this;
    }
    return ChapterChooseLeftItem;
}(ChapterChooseItem));
__reflect(ChapterChooseLeftItem.prototype, "ChapterChooseLeftItem");
var ChapterChooseRightItem = (function (_super) {
    __extends(ChapterChooseRightItem, _super);
    function ChapterChooseRightItem() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/skins/Chapter_choose_right.exml";
        return _this;
    }
    return ChapterChooseRightItem;
}(ChapterChooseItem));
__reflect(ChapterChooseRightItem.prototype, "ChapterChooseRightItem");
//# sourceMappingURL=ChapterChooseView.js.map