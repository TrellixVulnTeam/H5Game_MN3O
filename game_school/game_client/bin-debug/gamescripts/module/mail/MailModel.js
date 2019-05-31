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
 */
var MailModel = (function (_super) {
    __extends(MailModel, _super);
    /**
     * 构造函数
     * @param $controller 所属模块
     */
    function MailModel($controller) {
        var _this = _super.call(this, $controller) || this;
        _this.mailDataArray = [];
        return _this;
    }
    MailModel.prototype.setMailDataArray = function () {
        var maxNum = App.RandomUtils.limit(8, 12); //取一个最
        for (var i = 0; i < maxNum; i++) {
            var data = new MailData();
            data.init(i, "名字" + i, "我是邮件消息" + i);
            this.mailDataArray.push(data);
            var itemNum = App.RandomUtils.limit(1, 3);
            for (var j = 0; j < itemNum; j++) {
                var item = new Item();
                item.init(j, "skill_001_png", 10, "道具" + i, 5);
                data.addItem(item);
            }
        }
    };
    MailModel.prototype.getMailDataByID = function (id) {
        for (var i = 0; i < this.mailDataArray.length; i++) {
            if (this.mailDataArray[i].mailID == id)
                return this.mailDataArray[i];
        }
        return null;
    };
    MailModel.prototype.delMailDataByID = function (id) {
        for (var i = 0; i < this.mailDataArray.length; i++) {
            if (this.mailDataArray[i].mailID == id)
                this.mailDataArray.splice(i, 1);
        }
    };
    MailModel.prototype.setMailDataIsNewByID = function (id) {
        for (var i = 0; i < this.mailDataArray.length; i++) {
            if (this.mailDataArray[i].mailID == id) {
                this.mailDataArray[i].isNew = false;
            }
        }
    };
    return MailModel;
}(BaseModel));
__reflect(MailModel.prototype, "MailModel");
var MailData = (function () {
    function MailData() {
        this.items = null;
    }
    MailData.prototype.init = function (id, name, mes) {
        this.mailID = id;
        this.mailName = name;
        this.mailMes = mes;
        this.isNew = true;
    };
    MailData.prototype.addItem = function (item) {
        if (this.items == null)
            this.items = [];
        this.items.push(item);
    };
    MailData.prototype.removeItem = function (id) {
        for (var i = 0; i < this.items.length; i++) {
            if (this.items[i].ItemClientID == id)
                this.items.splice(i, 1);
        }
    };
    MailData.prototype.clearItems = function () {
        this.items.splice(0, this.items.length);
        // let array: Array<number> = [];
        // for (let i: number = 0; i < this.items.length; i++) {
        //     array.push(this.items[i].ItemClientID);
        // }
        // for (let i: number = 0; i < array.length; i++) {
        //     this.removeItem(array[i]);
        // }
    };
    Object.defineProperty(MailData.prototype, "IsNew", {
        get: function () {
            if (this.isNew == false && this.isGet())
                return false;
            else
                return true;
        },
        enumerable: true,
        configurable: true
    });
    //是否已经领取
    MailData.prototype.isGet = function () {
        if (this.items == null || this.items.length <= 0)
            return true;
        else
            return false;
    };
    return MailData;
}());
__reflect(MailData.prototype, "MailData");
//# sourceMappingURL=MailModel.js.map