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
 * 签到界面
*/
var DailySignUIView = (function (_super) {
    __extends(DailySignUIView, _super);
    function DailySignUIView($controller, $parent, key) {
        var _this = _super.call(this, $controller, $parent, key) || this;
        _this.gro_date_point_gap = 8;
        _this.dateItem_array = new Array();
        _this.gro_sign = $parent;
        _this.onInitUI();
        return _this;
    }
    DailySignUIView.prototype.onInitUI = function () {
        this.gro_sign_daily = this.gro_sign.getChildByName("gro_sign_daily");
        this.label_daily_des = this.gro_sign_daily.getChildByName("label_daily_des");
        this.gro_sign_daily_point = this.gro_sign_daily.getChildByName("gro_sign_daily_point");
        this.gro_sign_acc = this.gro_sign.getChildByName("gro_sign_acc");
        this.label_acc_des = this.gro_sign_acc.getChildByName("label_acc_des");
        this.gro_sign_acc_point = this.gro_sign_acc.getChildByName("gro_sign_acc_point");
        this.gro_cur_date = this.gro_sign.getChildByName("gro_cur_date");
        this.label_cur_week = this.gro_cur_date.getChildByName("label_cur_week");
        this.label_cur_date = this.gro_cur_date.getChildByName("label_cur_date");
        this.gro_date = this.gro_sign.getChildByName("gro_date");
        this.label_sign_des = this.gro_date.getChildByName("label_sign_des");
        this.gro_total_week = this.gro_date.getChildByName("gro_total_week");
        this.scro_date = this.gro_date.getChildByName("scro_date");
        this.gro_date_point = this.scro_date.getChildByName("gro_date_point");
        this.btn_sign = this.gro_sign.getChildByName("btn_sign");
        this.btn_buqian = this.gro_sign.getChildByName("btn_buqian");
        this.btn_sign.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClickSign, this);
        this.btn_buqian.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onSupplementSign, this);
        /**
         * 临时重置本地累签次数
        */
        this.label_cur_date.addEventListener(egret.TouchEvent.TOUCH_TAP, this.resetAccTimes, this);
    };
    DailySignUIView.prototype.resetAccTimes = function () {
        App.DailySignManager.setAccSignTime(0);
    };
    DailySignUIView.prototype.onChildGroupShow = function () {
        _super.prototype.onChildGroupShow.call(this);
        this.onSetUIInfo();
    };
    DailySignUIView.prototype.onChildGroupHide = function () {
    };
    /**
     * 签到界面信息
    */
    DailySignUIView.prototype.onSetUIInfo = function () {
        this.createAccRewardItem();
        this.createDateItem();
        this.setSignDescripte();
        this.setSignBtn();
    };
    /**
     * 累签奖励
    */
    DailySignUIView.prototype.createAccRewardItem = function () {
        if (this.sign_acc_item == null) {
            var info = App.DailySignManager.getCurAccRewardInfo();
            if (info != null) {
                this.sign_acc_item = new AccSignItem(info);
                this.sign_acc_item.setAccItemInfo(info);
                this.gro_sign_acc_point.addChild(this.sign_acc_item);
                StrConfigManager.SetLabelFormatById(this.label_acc_des, 11030, [info.times.toString()]);
            }
        }
    };
    /**
     * 日期item
    */
    DailySignUIView.prototype.createDateItem = function () {
        var _this = this;
        var days = App.DailySignManager.getCurMonthDays();
        var toDay = App.DailySignManager.nowDay;
        if (this.dateItem_array.length < days) {
            this.supplementEnptyDate();
            var _loop_1 = function (index) {
                var tempItem = new DateItem(index);
                tempItem.setDateItemInfo(toDay);
                tempItem.selectedDateBtn(function () {
                    _this.onSelectedCurDateInfo(tempItem);
                });
                this_1.gro_date_point.addChild(tempItem);
                if (index == toDay) {
                    this_1.date_today_item = tempItem;
                    this_1.date_cur_item = tempItem;
                    this_1.onSelectedCurDateInfo(tempItem);
                }
                this_1.dateItem_array.push(tempItem);
            };
            var this_1 = this;
            for (var index = 1; index <= days; index++) {
                _loop_1(index);
            }
        }
        else {
            this.onSelectedCurDateInfo(this.date_today_item);
        }
        if (App.DailySignManager.getCurMonthChangeLine()) {
            this.scro_date.viewport.scrollV = this.date_cur_item.height + this.gro_date_point_gap;
        }
    };
    DailySignUIView.prototype.supplementEnptyDate = function () {
        var emtpy = App.DailySignManager.getMouthEmptyDays();
        for (var index = 1; index <= emtpy; index++) {
            var tempItem = new DateItem(index);
            tempItem.setDateEmpty();
            this.gro_date_point.addChild(tempItem);
        }
    };
    /**
     * 设置当前选择 日期 奖励 按钮状态
    */
    DailySignUIView.prototype.onSelectedCurDateInfo = function (dateItem) {
        this.date_cur_item.hideCurDateImage();
        this.date_cur_item = dateItem;
        this.date_cur_item.showCurDateImage();
        this.setCurRewardItem();
        this.setSignBtn();
        this.label_cur_week.text = App.DailySignManager.getWeekByDate(dateItem.date);
        this.label_cur_date.text = dateItem.date.toString();
    };
    /**
     * 当前 签到奖励item
    */
    DailySignUIView.prototype.setCurRewardItem = function () {
        if (this.sign_cur_item == null) {
            var info = App.DailySignManager.getSignItemInfoByDate(this.date_cur_item.date);
            this.sign_cur_item = new DailySignItem(info);
            this.sign_cur_item.setDailyItemInfo(info);
            this.gro_sign_daily_point.addChild(this.sign_cur_item);
        }
        else {
            var info = App.DailySignManager.getSignItemInfoByDate(this.date_cur_item.date);
            this.sign_cur_item.setDailyItemInfo(info);
        }
        if (this.date_cur_item.date == this.date_today_item.date) {
            this.label_daily_des.text = StrConfigManager.getStrById(11000);
        }
        else if (this.date_cur_item.date == this.date_today_item.date + 1) {
            this.label_daily_des.text = StrConfigManager.getStrById(11001);
        }
        else {
            this.label_daily_des.text = StrConfigManager.getStrById(11002);
        }
    };
    /**
     * 设置签到补签按钮状态
    */
    DailySignUIView.prototype.setSignBtn = function () {
        if (this.date_today_item.date == this.date_cur_item.date) {
            this.btn_sign.visible = true;
            this.btn_buqian.visible = false;
            if (this.sign_cur_item.dailyInfo.isSign == false) {
                this.btn_sign.enabled = true;
            }
            else {
                this.btn_sign.enabled = false;
            }
        }
        else if (this.date_today_item.date > this.date_cur_item.date) {
            if (this.sign_cur_item.dailyInfo.isSign == false) {
                this.btn_sign.visible = false;
                this.btn_buqian.visible = true;
                this.btn_buqian.enabled = true;
            }
            else {
                this.btn_sign.visible = true;
                this.btn_sign.enabled = false;
                this.btn_buqian.visible = false;
            }
        }
        else {
            this.btn_sign.visible = true;
            this.btn_sign.enabled = false;
            this.btn_buqian.visible = false;
        }
    };
    /**
     * 签到奖励描述
    */
    DailySignUIView.prototype.setSignDescripte = function () {
        var accTimes = App.DailySignManager.accSignTimes;
        var lackTimes = this.sign_acc_item.accInfo.times - accTimes;
        if (lackTimes > 0) {
            var strs = [accTimes.toString(), lackTimes.toString(), this.sign_acc_item.accInfo.itemName];
            StrConfigManager.SetLabelFormatById(this.label_sign_des, 11017, strs);
        }
        else {
            if (App.DailySignManager.isLastAccRewardInfo()) {
                var strs = [accTimes.toString()];
                StrConfigManager.SetLabelFormatById(this.label_sign_des, 11032, strs);
            }
            else {
                var strs = [accTimes.toString(), this.sign_acc_item.accInfo.itemName];
                StrConfigManager.SetLabelFormatById(this.label_sign_des, 11018, strs);
            }
        }
    };
    /**
     * 签到
    */
    DailySignUIView.prototype.onClickSign = function () {
        var accTimes = App.DailySignManager.accSignTimes;
        App.DailySignManager.setAccSignTime(accTimes + 1);
        App.DailySignManager.reqTodaySign(this.sign_cur_item.dailyInfo.date);
        //设置奖励item
        var info = App.DailySignManager.getSignItemInfoByDate(this.date_today_item.date);
        this.sign_cur_item.setDailyItemInfo(info);
        //设置日期item
        this.date_today_item.setDateItemInfo(App.DailySignManager.nowDay);
        //设置按钮
        this.setSignBtn();
        this.setSignDescripte();
    };
    /**
     * 补签（弹出是否补签提示框）
    */
    DailySignUIView.prototype.onSupplementSign = function () {
        var titleStr = StrConfigManager.getStrById(11031);
        var str = StrConfigManager.GetStringFormatById(11022, [App.DailySignManager.supSignCost]);
        App.EventMgrHelper.PushEventEx(EventDef.SHOWHINTITEMUI, [this.sign_cur_item.itemDate], function () {
            this.sureSupplementSign();
            App.DailySignManager.supSignTimes++;
        }.bind(this), 0, 0, titleStr, str);
    };
    /**
     * 确定补签
    */
    DailySignUIView.prototype.sureSupplementSign = function () {
        var accTimes = App.DailySignManager.accSignTimes;
        App.DailySignManager.setAccSignTime(accTimes + 1);
        App.DailySignManager.reqTodaySign(this.sign_cur_item.dailyInfo.date);
        //设置奖励item
        var info = App.DailySignManager.getSignItemInfoByDate(this.date_cur_item.date);
        this.sign_cur_item.setDailyItemInfo(info);
        //设置日期item
        this.date_cur_item.setDateItemInfo(App.DailySignManager.nowDay);
        //设置按钮
        this.setSignBtn();
        //累签描述
        this.setSignDescripte();
    };
    /**
     * 更新累签奖励item
    */
    DailySignUIView.prototype.updateCurAccRewardItem = function () {
        var info = App.DailySignManager.getCurAccRewardInfo();
        if (info != null) {
            this.sign_acc_item.setAccItemInfo(info);
            StrConfigManager.SetLabelFormatById(this.label_acc_des, 11030, [info.times.toString()]);
            this.setSignDescripte();
        }
    };
    return DailySignUIView;
}(BaseEuiChildView));
__reflect(DailySignUIView.prototype, "DailySignUIView");
/**
 * 奖励item
*/
var RewardItem = (function (_super) {
    __extends(RewardItem, _super);
    function RewardItem(info) {
        var _this = _super.call(this, null, null) || this;
        _this.infoId = 0; //奖励物品ID
        _this.infoId = info.rewardId;
        _this.skinName = "resource/skins/SignIn_dayitem.exml";
        _this.initItem();
        _this.initChildrenVisible();
        _this.setItemInfo(info);
        return _this;
    }
    RewardItem.prototype.initItem = function () {
        var item = new UIItem();
        this.item = item;
        this.item_point.addChild(item);
    };
    RewardItem.prototype.initChildrenVisible = function () {
        this.btn_get.visible = false;
        this.image_ylq.visible = false;
        this.image_tishi.visible = false;
    };
    RewardItem.prototype.setItemInfo = function (info) {
        this.infoId = info.rewardId;
        this.itemDate = new Item();
        this.itemDate.init(info.rewardId, info.pic, info.rewardNum, info.itemName, 0);
        this.item.setItem(this.itemDate);
        this.item.UnLock();
    };
    return RewardItem;
}(BaseEuiView));
__reflect(RewardItem.prototype, "RewardItem");
/**
 * 签到奖励item
*/
var DailySignItem = (function (_super) {
    __extends(DailySignItem, _super);
    function DailySignItem(info) {
        return _super.call(this, info) || this;
    }
    /**
     * 签到奖励信息
    */
    DailySignItem.prototype.setDailyItemInfo = function (info) {
        this.dailyInfo = info;
        this.itemDate.init(info.rewardId, info.pic, info.rewardNum, info.itemName, 0);
        this.item.setItem(this.itemDate);
        this.image_ylq.visible = this.dailyInfo.isSign;
    };
    return DailySignItem;
}(RewardItem));
__reflect(DailySignItem.prototype, "DailySignItem");
/**
 * 累签奖励item
*/
var AccSignItem = (function (_super) {
    __extends(AccSignItem, _super);
    function AccSignItem(info) {
        var _this = _super.call(this, info) || this;
        _this.btn_get.addEventListener(egret.TouchEvent.TOUCH_TAP, _this.onClickGetCurAccReward, _this);
        return _this;
    }
    /**
     * 累签奖励数据
    */
    AccSignItem.prototype.setAccItemInfo = function (info) {
        this.accInfo = info;
        this.itemDate.init(info.rewardId, info.pic, info.rewardNum, info.itemName, 0);
        this.item.setItem(this.itemDate);
        this.image_ylq.visible = this.accInfo.isGet;
        this.btn_get.visible = this.accInfo.isGet == true ? false : this.accInfo.isCanGet;
        this.image_tishi.visible = this.accInfo.isGet == true ? false : this.accInfo.isCanGet;
    };
    /**
     * 领取累积奖励
    */
    AccSignItem.prototype.onClickGetCurAccReward = function () {
        App.DailySignManager.reqGetCurAccRewardItem();
    };
    return AccSignItem;
}(RewardItem));
__reflect(AccSignItem.prototype, "AccSignItem");
/**
 * 日期item
*/
var DateItem = (function (_super) {
    __extends(DateItem, _super);
    function DateItem(id) {
        var _this = _super.call(this, null, null) || this;
        _this.date = 0;
        _this.date = id;
        _this.skinName = "resource/skins/SignIn_date.exml";
        _this.initChildrenVisible();
        return _this;
    }
    DateItem.prototype.initChildrenVisible = function () {
        this.label_day.visible = false;
        this.label_def_day.visible = false;
        this.label_day.text = this.date.toString();
        this.label_def_day.text = this.date.toString();
        this.image_cur_sign.visible = false;
        this.image_alr_sign.visible = false;
    };
    DateItem.prototype.setDateItemInfo = function (toDay) {
        var info = App.DailySignManager.getSignItemInfoByDate(this.date);
        if (this.date < toDay) {
            this.label_day.visible = false;
            this.label_def_day.visible = true;
        }
        else {
            this.label_day.visible = true;
            this.label_def_day.visible = false;
        }
        if (this.date <= toDay) {
            this.image_alr_sign.visible = info.isSign; //是否已签到
        }
        else {
            this.image_alr_sign.visible = false; //今日以后都是未签到
        }
    };
    DateItem.prototype.selectedDateBtn = function (callback) {
        this.btn_select.addEventListener(egret.TouchEvent.TOUCH_TAP, callback, this);
    };
    DateItem.prototype.hideCurDateImage = function () {
        this.image_cur_sign.visible = false;
    };
    DateItem.prototype.showCurDateImage = function () {
        this.image_cur_sign.visible = true;
    };
    DateItem.prototype.setDateEmpty = function () {
        this.di.visible = false;
        this.label_day.visible = false;
        this.label_def_day.visible = false;
        this.image_cur_sign.visible = false;
        this.image_alr_sign.visible = false;
        this.btn_select.visible = false;
    };
    return DateItem;
}(BaseEuiView));
__reflect(DateItem.prototype, "DateItem");
//# sourceMappingURL=DailySignUIView.js.map