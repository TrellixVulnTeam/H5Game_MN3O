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
 * Created by yangsong on 2017/10/11.
 */
var HeadComponent = (function (_super) {
    __extends(HeadComponent, _super);
    function HeadComponent() {
        var _this = _super.call(this) || this;
        //血条和BUFF走在这个下面
        _this.mGroup = null;
        _this.currentCamp = Camp.Friendly;
        return _this;
    }
    HeadComponent.prototype.start = function () {
        _super.prototype.start.call(this);
        // this. avatarComponent = <AvatarComponent>this.entity.getComponent(ComponentType.Avatar);
        this.avatarComponent = this.entity.getComponent(ComponentType.Dragon);
        this.createGroup(this.avatarComponent.Body);
        //this.createNameTxt(avatarComponent.AvatarMovieClip.Body);
        // this.createTitleTxt(avatarComponent.AvatarMovieClip.Body);
        // this.createhpslider(  this.avatarComponent.AvatarMovieClip.Body);
    };
    //创建包裹血条和BUFF图标的Group
    HeadComponent.prototype.createGroup = function (parent) {
        this.mGroup = new BattleSkins();
        parent.addChild(this.mGroup);
        this.mGroup.x = 0;
        this.mGroup.y = -310;
    };
    HeadComponent.prototype.createNameTxt = function (parent) {
        this.nameTxt = new eui.Label();
        this.nameTxt.size = 18;
        this.nameTxt.textColor = 0xFFFFFF;
        this.nameTxt.width = 100;
        this.nameTxt.height = 20;
        this.nameTxt.textAlign = egret.HorizontalAlign.CENTER;
        this.nameTxt.strokeColor = 0x000000;
        this.nameTxt.stroke = 2;
        this.nameTxt.text = this.entity.basicattr.Name;
        this.nameTxt.y = -30;
        AnchorUtil.setAnchorX(this.nameTxt, 0.5);
        //this.nameTxt.anchorOffsetX = 20; 
        parent.addChild(this.nameTxt);
    };
    HeadComponent.prototype.createTitleTxt = function (parent) {
        this.titleTxt = new eui.Label();
        this.titleTxt.size = 18;
        this.titleTxt.textColor = 0x87CEEB;
        this.titleTxt.width = 100;
        this.titleTxt.height = 20;
        this.titleTxt.textAlign = egret.HorizontalAlign.CENTER;
        this.titleTxt.strokeColor = 0x000000;
        this.titleTxt.stroke = 2;
        this.titleTxt.text = this.entity.basicattr.Title;
        this.titleTxt.y = -60;
        AnchorUtil.setAnchorX(this.titleTxt, 0.5);
        //this.titleTxt.anchorOffsetX = 20; 
        parent.addChild(this.titleTxt);
    };
    HeadComponent.prototype.createhpslider = function (camp) {
        if (this.mGroup == null)
            return;
        this.hpslider = new BattleBlood();
        this.hpslider.minimum = 0;
        this.hpslider.maximum = this.entity.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);
        this.hpslider.value = this.entity.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);
        ;
        if (camp == Camp.Friendly)
            AnchorUtil.setAnchorX(this.hpslider, 0.8);
        else
            AnchorUtil.setAnchorX(this.hpslider, 0.4);
        this.mGroup.Blood_Group.addChild(this.hpslider);
    };
    HeadComponent.prototype.changehpslider = function (value) {
        if (value <= 0) {
            value = 0;
        }
        if (!this.hpslider) {
            return;
        }
        if (value >= this.hpslider.maximum)
            this.hpslider.maximum = value;
        this.hpslider.setValue(value);
    };
    HeadComponent.prototype.addBuffItem = function (icon, buffID) {
        if (this.mGroup == null)
            return;
        this.mGroup.addBuffItem(icon, buffID);
    };
    HeadComponent.prototype.removeBuffItem = function (buffID) {
        if (this.mGroup == null)
            return;
        this.mGroup.removeBuffItem(buffID);
    };
    HeadComponent.prototype.removeAllBuffItem = function () {
        if (this.mGroup == null)
            return;
        this.mGroup.removeAllBuffItem();
    };
    HeadComponent.prototype.getBuffItem = function (buffID) {
        if (this.mGroup == null)
            return null;
        return this.mGroup.getBuffItem(buffID);
    };
    HeadComponent.prototype.stop = function () {
        _super.prototype.stop.call(this);
        App.DisplayUtils.removeFromParent(this.nameTxt);
        this.nameTxt = null;
        App.DisplayUtils.removeFromParent(this.titleTxt);
        this.titleTxt = null;
        App.DisplayUtils.removeFromParent(this.hpslider);
        this.hpslider = null;
        //Group最后移除,先移除一下里面包含的BUFF
        this.removeAllBuffItem();
        App.DisplayUtils.removeFromParent(this.mGroup);
        this.mGroup = null;
    };
    HeadComponent.prototype.update = function (advancedTime) {
        _super.prototype.update.call(this, advancedTime);
        if (this.mGroup.y == 0) {
            this.mGroup.y = -this.avatarComponent.Body.height - 125;
        }
    };
    return HeadComponent;
}(Component));
__reflect(HeadComponent.prototype, "HeadComponent");
/* 放血条的panle*/
var BattleSkins = (function (_super) {
    __extends(BattleSkins, _super);
    function BattleSkins() {
        var _this = _super.call(this) || this;
        //单一列表的最大BUFFITEM数量
        _this.maxBuffIitenNum = 5;
        _this.buffList2 = [];
        _this.buffList1 = [];
        _this.skinName = "resource/eui_skins/Battle_blood_skins.exml";
        AnchorUtil.setAnchorX(_this.Buff_Group1, 0.25);
        AnchorUtil.setAnchorX(_this.Buff_Group2, 0.25);
        return _this;
    }
    BattleSkins.prototype.init = function (data, view) {
        if (view == null || data == null) {
            return;
        }
    };
    BattleSkins.prototype.addBuffItem = function (icon, buffID) {
        if (this.buffList1 == null)
            this.buffList1 = [];
        if (this.buffList2 == null)
            this.buffList2 = [];
        //先判断1列表是不是满了,1列表要是满了,就加进2列表
        if (this.buffList1.length == this.maxBuffIitenNum) {
            var item = new BattleItem();
            item.setBuffIcon(icon, buffID);
            this.buffList2.push(item);
            this.Buff_Group2.addChild(item);
        }
        else {
            var item = new BattleItem();
            item.setBuffIcon(icon, buffID);
            this.buffList1.push(item);
            this.Buff_Group1.addChild(item);
        }
    };
    BattleSkins.prototype.removeBuffItem = function (buffID) {
        var index = -1;
        for (var i = 0; i < this.buffList1.length; i++) {
            var id = this.buffList1[i].getBuffID();
            if (id = buffID) {
                index = i;
                App.DisplayUtils.removeFromParent(this.buffList1[i]);
            }
        }
        if (index >= 0) {
            this.buffList1.splice(index, 1);
            return;
        }
        for (var i = 0; i < this.buffList2.length; i++) {
            var id = this.buffList2[i].getBuffID();
            if (id = buffID) {
                index = i;
                App.DisplayUtils.removeFromParent(this.buffList2[i]);
            }
        }
        if (index >= 0) {
            this.buffList2.splice(index, 1);
        }
    };
    BattleSkins.prototype.removeAllBuffItem = function () {
        for (var i = 0; i < this.buffList1.length; i++) {
            App.DisplayUtils.removeFromParent(this.buffList1[i]);
        }
        this.buffList1 = null;
        for (var i = 0; i < this.buffList2.length; i++) {
            App.DisplayUtils.removeFromParent(this.buffList2[i]);
        }
        this.buffList2 = null;
    };
    BattleSkins.prototype.getBuffItem = function (buffID) {
        //先从1表查找数据
        for (var i = 0; i < this.buffList1.length; i++) {
            var id = this.buffList1[i].getBuffID();
            if (id = buffID)
                return this.buffList1[i];
        }
        for (var i = 0; i < this.buffList2.length; i++) {
            var id = this.buffList2[i].getBuffID();
            if (id = buffID)
                return this.buffList2[i];
        }
        return null;
    };
    return BattleSkins;
}(eui.Component));
__reflect(BattleSkins.prototype, "BattleSkins");
var BattleItem = (function (_super) {
    __extends(BattleItem, _super);
    function BattleItem() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/eui_skins/Item_Buff.exml";
        return _this;
    }
    BattleItem.prototype.setBuffIcon = function (icon, buffID) {
        this.image_bufficon.source = icon;
        this.buffID = buffID;
    };
    BattleItem.prototype.getBuffID = function () {
        return this.buffID;
    };
    return BattleItem;
}(eui.Component));
__reflect(BattleItem.prototype, "BattleItem");
/* 血条 */
var BattleBlood = (function (_super) {
    __extends(BattleBlood, _super);
    function BattleBlood() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/eui_skins/Pro_battle_blood.exml";
        _this.oriWidth = _this.thumb.width;
        return _this;
    }
    BattleBlood.prototype.setLabel = function (str) {
        this.labelDisplay.text = str;
    };
    BattleBlood.prototype.setValue = function (num) {
        var max = this.maximum.toString();
        var current = num.toString();
        this.setLabel(current + "/" + this.maximum);
        this.pendingValue = num;
        this.thumb.width = this.oriWidth * (num / this.maximum);
    };
    return BattleBlood;
}(eui.HSlider));
__reflect(BattleBlood.prototype, "BattleBlood");
//# sourceMappingURL=HeadComponent.js.map