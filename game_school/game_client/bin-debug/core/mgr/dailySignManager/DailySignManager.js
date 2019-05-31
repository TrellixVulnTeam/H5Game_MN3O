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
 * 签到管理类
*/
var DailySignManager = (function (_super) {
    __extends(DailySignManager, _super);
    function DailySignManager() {
        var _this = _super.call(this) || this;
        _this.now = new Date(); //当前日期
        _this.nowDayOfWeek = _this.now.getDay(); //今天本周的第几天
        _this.nowDay = _this.now.getDate(); //当前日期
        _this.nowMonth = _this.now.getMonth(); //当前月份
        _this.nowYear = _this.now.getFullYear(); //当前年份
        _this.supSignFirst = 0; //第一次补签消耗
        _this.supSignAdd = 0; //补签累加消耗
        _this.supSignMax = 0; //最大补签消耗
        _this.supSignTimes = 0;
        //临时数据
        _this.accSignTime = "accSignTime"; //累签次数
        _this.sign_reward_array = new Array(); //签到奖励数据
        _this.acc_reward_array = new Array(); //累签奖励数据
        _this.cur_acc_reward_info = null;
        _this.isSaveKeyData(_this.accSignTime, "0");
        _this.loadSignData();
        _this.supSignFirst = Number(PublicConstConfig.GetConfig(2).value);
        _this.supSignAdd = Number(PublicConstConfig.GetConfig(3).value);
        _this.supSignMax = Number(PublicConstConfig.GetConfig(4).value);
        return _this;
    }
    Object.defineProperty(DailySignManager.prototype, "supSignCost", {
        /**
         * 获取补签消耗数量
        */
        get: function () {
            return ((this.supSignFirst + this.supSignAdd * this.supSignTimes) < this.supSignMax ? (this.supSignFirst + this.supSignAdd * this.supSignTimes) : this.supSignMax).toString();
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 初始key值
    */
    DailySignManager.prototype.isSaveKeyData = function (str, key) {
        if (egret.localStorage.getItem(str) == null) {
            egret.localStorage.setItem(str, key);
        }
    };
    /**
     * 设置累签次数
    */
    DailySignManager.prototype.setAccSignTime = function (num) {
        return egret.localStorage.setItem(this.accSignTime, num.toString());
    };
    Object.defineProperty(DailySignManager.prototype, "accSignTimes", {
        /**
         * 获得当前累签次数
        */
        get: function () {
            return Number(egret.localStorage.getItem(this.accSignTime));
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 加载 签到和累签 数据
    */
    DailySignManager.prototype.loadSignData = function () {
        /**
         * 签到奖励数据
        */
        for (var index = 0; index < DailySignMonthRewardConfig.array.length; index++) {
            var config = DailySignMonthRewardConfig.array[index];
            var tempInfo = new DailyInfo(config.id, config.item_id, config.item_num);
            this.sign_reward_array.push(tempInfo);
        }
        /**
         * 累签奖励数据
        */
        for (var index = 0; index < DailySignTotalRewardConfig.array.length; index++) {
            var config = DailySignTotalRewardConfig.array[index];
            var tempInfo = new AccInfo(config.id, config.item_id, config.item_num);
            this.acc_reward_array.push(tempInfo);
        }
        this.updateAllAccRewardInfo();
        this.setCurAccRewardInfo();
    };
    /**
     * 刷新所有累签奖励数据
    */
    DailySignManager.prototype.updateAllAccRewardInfo = function () {
        for (var index = 0; index < this.acc_reward_array.length; index++) {
            if (this.accSignTimes >= this.acc_reward_array[index].times) {
                this.acc_reward_array[index].setIsCanGet(true);
            }
            else {
                this.acc_reward_array[index].setIsCanGet(false);
            }
        }
    };
    /**
     * 设置当前累签奖励数据
    */
    DailySignManager.prototype.setCurAccRewardInfo = function () {
        for (var index = 0; index < this.acc_reward_array.length; index++) {
            if (this.acc_reward_array[index].isCanGet) {
                if (this.acc_reward_array[index].isGet == false) {
                    this.cur_acc_reward_info = this.acc_reward_array[index];
                    break;
                }
            }
            else if (this.accSignTimes < this.acc_reward_array[index].times) {
                this.cur_acc_reward_info = this.acc_reward_array[index];
                break;
            }
        }
    };
    /**
     * 获得当前累积奖励
    */
    DailySignManager.prototype.getCurAccRewardInfo = function () {
        return this.cur_acc_reward_info;
    };
    /**
     * 本月最后一个累签奖励
    */
    DailySignManager.prototype.isLastAccRewardInfo = function () {
        return this.cur_acc_reward_info.times == this.acc_reward_array[this.acc_reward_array.length - 1].times && this.cur_acc_reward_info.isCanGet == true && this.cur_acc_reward_info.isGet == true;
    };
    /**
     * 获得签到奖励
    */
    DailySignManager.prototype.getSignItemInfoByDate = function (date) {
        var info;
        for (var index = 0; index < this.sign_reward_array.length; index++) {
            if (date <= this.sign_reward_array[index].date) {
                info = this.sign_reward_array[index];
                break;
            }
        }
        return info;
    };
    Object.defineProperty(DailySignManager.prototype, "getAllSignReward", {
        /**
         * 获取所有签到奖励数据
        */
        get: function () {
            return this.sign_reward_array;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(DailySignManager.prototype, "getAllAccReward", {
        /**
         * 获取所有累签奖励数据
        */
        get: function () {
            return this.acc_reward_array;
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 请求签到
    */
    DailySignManager.prototype.reqTodaySign = function (date) {
        var info;
        for (var index = 0; index < this.sign_reward_array.length; index++) {
            if (date <= this.sign_reward_array[index].date) {
                info = this.sign_reward_array[index];
                this.sign_reward_array[index].isSign = true;
                break;
            }
        }
        var str = StrConfigManager.GetStringFormatById(11029, [info.itemName]);
        App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, str);
        this.updateAllAccRewardInfo();
        this.setCurAccRewardInfo();
        App.EventMgrHelper.PushEvent(EventDef.ActivityReward_dailySign);
    };
    /**
     * 请求领取累签奖励
    */
    DailySignManager.prototype.reqGetCurAccRewardItem = function () {
        var info = this.cur_acc_reward_info;
        var str = StrConfigManager.GetStringFormatById(11029, [info.itemName]);
        App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, str);
        this.cur_acc_reward_info.setIsGet(true);
        this.cur_acc_reward_info.setIsCanGet(false);
        this.updateAllAccRewardInfo();
        this.setCurAccRewardInfo();
        App.EventMgrHelper.PushEvent(EventDef.ActivityReward_dailySign);
    };
    DailySignManager.prototype.addTiem = function () {
        this.nowYear += (this.nowYear < 2000) ? 1900 : 0;
    };
    /**
     * 格式化日期：yyyy-MM-dd
    */
    DailySignManager.prototype.formatDate = function (date) {
        var myyear = date.getFullYear();
        var mymonth = date.getMonth() + 1;
        var myweekday = date.getDate();
        if (mymonth < 10) {
            mymonth = "0" + mymonth;
        }
        if (myweekday < 10) {
            myweekday = "0" + myweekday;
        }
        return (myyear + "-" + mymonth + "-" + myweekday);
    };
    /**
     * 获得本周的开始日期
    */
    DailySignManager.prototype.getWeekStartDate = function () {
        this.addTiem();
        var weekStartDate = new Date(this.nowYear, this.nowMonth, this.nowDay - this.nowDayOfWeek);
        return this.formatDate(weekStartDate);
    };
    /**
     * 获得本周的结束日期
    */
    DailySignManager.prototype.getWeekEndDate = function () {
        this.addTiem();
        var weekEndDate = new Date(this.nowYear, this.nowMonth, this.nowDay + (6 - this.nowDayOfWeek));
        return this.formatDate(weekEndDate);
    };
    /**
     * 获得本月的开始日期
    */
    DailySignManager.prototype.getMonthStartDate = function () {
        this.addTiem();
        var monthStartDate = new Date(this.nowYear, this.nowMonth, 1);
        return this.formatDate(monthStartDate);
    };
    /**
     * 获得本月的结束日期
    */
    DailySignManager.prototype.getMonthEndDate = function () {
        this.addTiem();
        var monthEndDate = new Date(this.nowYear, this.nowMonth, this.getMonthDays(this.nowMonth));
        return this.formatDate(monthEndDate);
    };
    /**
     * 获得当月的天数
    */
    DailySignManager.prototype.getCurMonthDays = function () {
        return this.getMonthDays(this.nowMonth);
    };
    /**
     * 获得某月的天数
    */
    DailySignManager.prototype.getMonthDays = function (myMonth) {
        this.addTiem();
        var monthStartDate = new Date(this.nowYear, myMonth, 1);
        var monthEndDate = new Date(this.nowYear, myMonth + 1, 1);
        var days = (monthEndDate - monthStartDate) / (1000 * 60 * 60 * 24);
        return days;
    };
    DailySignManager.prototype.getMouthEmptyDays = function () {
        return (7 + this.nowDayOfWeek - this.nowDay % 7) % 7;
    };
    DailySignManager.prototype.getCurMonthChangeLine = function () {
        var overFour = this.getCurMonthDays() % 7 - (7 - this.getMouthEmptyDays());
        var toOver = this.getCurMonthDays() - this.nowDay;
        if (overFour > 0 && toOver < overFour) {
            return true;
        }
        else {
            return false;
        }
    };
    DailySignManager.prototype.getWeekByDate = function (index) {
        var str = "";
        var num = (index + this.getMouthEmptyDays()) % 7;
        if (num == 0) {
            str += StrConfigManager.getStrById(11009);
        }
        else if (num == 1) {
            str += StrConfigManager.getStrById(11003);
        }
        else if (num == 2) {
            str += StrConfigManager.getStrById(11004);
        }
        else if (num == 3) {
            str += StrConfigManager.getStrById(11005);
        }
        else if (num == 4) {
            str += StrConfigManager.getStrById(11006);
        }
        else if (num == 5) {
            str += StrConfigManager.getStrById(11007);
        }
        else if (num == 6) {
            str += StrConfigManager.getStrById(11008);
        }
        return str;
    };
    return DailySignManager;
}(BaseClass));
__reflect(DailySignManager.prototype, "DailySignManager");
/**
 * 奖励物品信息
*/
var RewardInfo = (function () {
    function RewardInfo(id, num) {
        this.rewardId = 0; //奖励Id
        this.pic = ""; //图片名
        this.itemName = ""; //物品名
        this.rewardNum = 0; //奖励物品数量
        this.rewardId = id;
        this.rewardNum = num;
        var config = ItemCommonConfig.GetConfig(id);
        if (config != null) {
            this.pic = config.icon;
            this.itemName = config.name;
        }
    }
    return RewardInfo;
}());
__reflect(RewardInfo.prototype, "RewardInfo");
/**
 * 签到奖励
*/
var DailyInfo = (function (_super) {
    __extends(DailyInfo, _super);
    function DailyInfo(date, id, num) {
        var _this = _super.call(this, id, num) || this;
        _this.date = 0; //日期
        _this.isSign = false; //是否已签到
        _this.date = date;
        return _this;
    }
    return DailyInfo;
}(RewardInfo));
__reflect(DailyInfo.prototype, "DailyInfo");
/**
 * 累签奖励
*/
var AccInfo = (function (_super) {
    __extends(AccInfo, _super);
    function AccInfo(times, id, num) {
        var _this = _super.call(this, id, num) || this;
        _this.times = 0; //累积时长
        _this.isGet = false; //是否已领取
        _this.isCanGet = false; //是否可以领取
        _this.times = times;
        return _this;
    }
    AccInfo.prototype.setIsGet = function (bool) {
        this.isGet = bool;
    };
    AccInfo.prototype.setIsCanGet = function (bool) {
        this.isCanGet = bool;
    };
    return AccInfo;
}(RewardInfo));
__reflect(AccInfo.prototype, "AccInfo");
//# sourceMappingURL=DailySignManager.js.map