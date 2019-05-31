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
 * 战斗编辑页面
 */
var BattleEditMainView = (function (_super) {
    __extends(BattleEditMainView, _super);
    function BattleEditMainView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        /**
         * 临时指引标记
        */
        _this.isFirstGuide = false;
        return _this;
    }
    BattleEditMainView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.BattleEdit);
        this.isFirstGuide = App.GuideManager.getIsGuide;
        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.close(ViewConst.BattleEdit);
            App.ViewManager.open(ViewConst.BattleArray);
        }, this);
    };
    BattleEditMainView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    BattleEditMainView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        App.EventMgrHelper.PushEvent(EventDef.UpdateArrayList);
    };
    /**
     * 刷新UI
     */
    BattleEditMainView.prototype.UpdateUI = function (allHero) {
        for (var i = 0; i < allHero.length; i++) {
            if (i < this.scrollerCon.numElements) {
                var tempItem = this.scrollerCon.getChildAt(i);
                tempItem.UpdateUI(allHero[i]);
            }
            else {
                var tempItem = new HeroInfoItem(this.width);
                tempItem.UpdateUI(allHero[i]);
                this.scrollerCon.addChild(tempItem);
            }
        }
        if (this.isFirstGuide) {
            this.isFirstGuide = false;
            this.addFirstGuide();
        }
    };
    /**
     * 临时指引1（第一次进入英雄选择界面，选择第二个英雄上阵）
    */
    BattleEditMainView.prototype.addFirstGuide = function () {
        var item = this.scrollerCon.getChildAt(1);
        if (item != null) {
            this.validateNow();
            var itemtemp = new HeroInfoItem(item.width);
            itemtemp.width = item.width;
            itemtemp.height = item.height;
            itemtemp.x = item.localToGlobal().x;
            itemtemp.y = item.localToGlobal().y;
            itemtemp.UpdateUI(item.heroInfo);
            var mask = new GuideMask(itemtemp, function () {
                App.ViewManager.close(ViewConst.BattleEdit);
                App.EventMgrHelper.PushEvent(EventDef.AddHero, item.heroInfoId);
            }, "", false);
            this.addChild(mask);
        }
    };
    return BattleEditMainView;
}(BaseEuiView));
__reflect(BattleEditMainView.prototype, "BattleEditMainView");
/**
 * 英雄信息条
 */
var HeroInfoItem = (function (_super) {
    __extends(HeroInfoItem, _super);
    function HeroInfoItem(wid) {
        var _this = _super.call(this) || this;
        _this.heroInfoId = 0;
        _this.heroInfo = null;
        _this.percentWidth = 100;
        _this.width = wid;
        _this.skinName = App.ViewManager.getSkin(ViewConst.HeroInfoItem);
        return _this;
    }
    HeroInfoItem.prototype.UpdateUI = function (heroinfo) {
        this.heroInfoId = heroinfo.id;
        this.heroInfo = heroinfo;
        this.mConfig = CreatureTempletConfig.GetConfig(heroinfo.id);
        this.player.source = this.mConfig.icon;
        this.label_name.text = this.mConfig.name;
        this.image_wcz.visible = !heroinfo.belong;
        this.image_ycz.visible = heroinfo.belong;
        this.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.close(ViewConst.BattleEdit);
            App.EventMgrHelper.PushEvent(EventDef.AddHero, heroinfo.id);
        }.bind(this), this);
    };
    return HeroInfoItem;
}(eui.Component));
__reflect(HeroInfoItem.prototype, "HeroInfoItem");
//# sourceMappingURL=BattleEditMainView.js.map