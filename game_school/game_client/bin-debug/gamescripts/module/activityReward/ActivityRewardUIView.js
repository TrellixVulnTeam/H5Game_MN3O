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
var ActivityRewardUIType;
(function (ActivityRewardUIType) {
    ActivityRewardUIType[ActivityRewardUIType["ActivityReward_sign"] = 0] = "ActivityReward_sign";
    ActivityRewardUIType[ActivityRewardUIType["ActivityReward_cost"] = 1] = "ActivityReward_cost";
    ActivityRewardUIType[ActivityRewardUIType["ActivityReward_vip"] = 2] = "ActivityReward_vip";
    ActivityRewardUIType[ActivityRewardUIType["ActivityReward_other"] = 3] = "ActivityReward_other";
})(ActivityRewardUIType || (ActivityRewardUIType = {}));
/**
 * 签到界面
*/
var ActivityRewardUIView = (function (_super) {
    __extends(ActivityRewardUIView, _super);
    function ActivityRewardUIView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.btnGroup = new eui.RadioButtonGroup(); //按钮组//
        _this.bulbs = new Array(); //红点组//
        _this.groupArray = Array(); //界面控件组//
        _this.childViewArray = Array(); //界面组//
        /**
         * 临时指引标记
        */
        _this.isFirstGuide = false;
        _this.addEventListener(eui.UIEvent.COMPLETE, function () {
            _this.uiCompHandler($controller);
        }, _this);
        return _this;
    }
    ActivityRewardUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.ActivityRewardUI);
        this.isFirstGuide = App.GuideManager.getIsGuide;
    };
    ActivityRewardUIView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    ActivityRewardUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.openDefaultUI();
        this.updateBtnBulb();
        if (this.isFirstGuide) {
            this.isFirstGuide = false;
            this.addFirstGuide();
        }
    };
    /**
     * 临时指引1（第一次进入活动界面签到页签，点击签到按钮）
    */
    ActivityRewardUIView.prototype.addFirstGuide = function () {
        var _this = this;
        var btn_sign = this.gro_sign.getChildByName("btn_sign");
        if (btn_sign != null) {
            this.validateNow();
            var mask = new GuideMask(btn_sign, function () {
                _this.dailySignUI.onClickSign();
                _this.onClose();
                App.ViewManager.open(ViewConst.MainUI);
            }, "", true, (btn_sign.width / 2), 0);
            this.addChild(mask);
        }
    };
    ActivityRewardUIView.prototype.close = function () {
        _super.prototype.close.call(this);
        for (var index = 0; index < this.childViewArray.length; index++) {
            this.childViewArray[index].onChildGroupHide();
        }
    };
    /**
     * 暂时默认打开
    */
    ActivityRewardUIView.prototype.openDefaultUI = function () {
        //this.btn_0.selected = true;//页签按钮相关暂时屏蔽
        this.openGroupUI(ActivityRewardUIType.ActivityReward_sign);
    };
    ActivityRewardUIView.prototype.uiCompHandler = function ($controller) {
        this.addChildUIView($controller);
        this.addChildGroupUI();
        //this.onSetBtnGroup();//页签按钮相关暂时屏蔽
        //this.onSetBtnBulb();//页签按钮相关暂时屏蔽
        this.back.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClose, this);
    };
    ActivityRewardUIView.prototype.addChildUIView = function ($controller) {
        this.dailySignUI = new DailySignUIView($controller, this.gro_sign, this._key);
        this.childViewArray.push(this.dailySignUI);
    };
    ActivityRewardUIView.prototype.addChildGroupUI = function () {
        this.groupArray.push(this.gro_sign);
        this.groupArray.push(this.gro_cost);
        this.groupArray.push(this.gro_vip);
        this.groupArray.push(this.gro_other);
    };
    ActivityRewardUIView.prototype.onSetBtnGroup = function () {
        this.btnGroup.addEventListener(eui.UIEvent.CHANGE, this.selectUIHandler, this);
        this.btn_0.value = ActivityRewardUIType.ActivityReward_sign;
        this.btn_1.value = ActivityRewardUIType.ActivityReward_cost;
        this.btn_2.value = ActivityRewardUIType.ActivityReward_vip;
        this.btn_3.value = ActivityRewardUIType.ActivityReward_other;
        this.btn_0.group = this.btnGroup;
        this.btn_1.group = this.btnGroup;
        this.btn_2.group = this.btnGroup;
        this.btn_3.group = this.btnGroup;
    };
    ActivityRewardUIView.prototype.onSetBtnBulb = function () {
        this.bulbs.push(this.image_bulb0);
        this.bulbs.push(this.image_bulb1);
        this.bulbs.push(this.image_bulb2);
        this.bulbs.push(this.image_bulb3);
    };
    ActivityRewardUIView.prototype.selectUIHandler = function (evt) {
        this.btnGroup = evt.target;
        this.openGroupUI(this.btnGroup.selectedValue);
    };
    /**
     * 打开子界面
    */
    ActivityRewardUIView.prototype.openGroupUI = function (type) {
        for (var index = 0; index < this.groupArray.length; index++) {
            if (type == index) {
                this.groupArray[index].visible = true;
                if (index < this.childViewArray.length) {
                    this.childViewArray[index].onChildGroupShow();
                }
            }
            else {
                this.groupArray[index].visible = false;
                if (index < this.childViewArray.length) {
                    this.childViewArray[index].onChildGroupHide();
                }
            }
        }
    };
    /**
     * 刷新红点
    */
    ActivityRewardUIView.prototype.updateBtnBulb = function () {
        for (var index = 0; index < this.bulbs.length; index++) {
            if (0 == index) {
                this.bulbs[index].visible = true;
            }
            else {
                this.bulbs[index].visible = false;
            }
        }
    };
    return ActivityRewardUIView;
}(BaseEuiView));
__reflect(ActivityRewardUIView.prototype, "ActivityRewardUIView");
//# sourceMappingURL=ActivityRewardUIView.js.map