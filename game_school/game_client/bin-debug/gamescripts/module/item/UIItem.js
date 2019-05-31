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
var UIItem = (function (_super) {
    __extends(UIItem, _super);
    function UIItem() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/skins/Item_icon.exml";
        return _this;
    }
    Object.defineProperty(UIItem.prototype, "ItemClientID", {
        //----------------------------------------------------------
        get: function () {
            return this.itemID;
        },
        enumerable: true,
        configurable: true
    });
    //设置数据
    UIItem.prototype.setItem = function (item) {
        if (item == null)
            return;
        this.itemID = item.ItemClientID;
        this.image_item.source = item.ItemIcon;
        this.label_num.text = item.ItemNum.toString();
        this.label_lv.text = item.ItemLv.toString();
        this.label_name.text = item.ItemName;
        if (item.ItemLv != 0) {
            this.label_lv.visible = true;
        }
        else {
            this.label_lv.visible = false;
        }
        if (item.ItemNum != 0) {
            this.label_num.visible = true;
        }
        else {
            this.label_num.visible = false;
        }
    };
    /**/
    UIItem.prototype.setVisible = function (v) {
        this.visible = v;
    };
    UIItem.prototype.Lock = function () {
        if (this.image_black.visible != null) {
            this.image_black.visible = true;
        }
    };
    UIItem.prototype.UnLock = function () {
        if (this.image_black.visible != null) {
            this.image_black.visible = false;
        }
    };
    UIItem.prototype.SetItemCount = function (str) {
        if (this.label_num != null)
            this.label_num.text = str;
    };
    //预留方法 0/100 这种
    UIItem.prototype.SetCostCount = function (has, need) {
        var mCostLabel = null;
        if (mCostLabel != null) {
            if (need > has) {
                mCostLabel.textColor = ColorConst.Red_Light; //红色              
            }
            else {
                mCostLabel.textColor = ColorConst.Green_Light; //绿色
            }
            mCostLabel.text = has.toString() + "/" + need.toString();
        }
    };
    UIItem.prototype.SetItemImage = function (iconName) {
        this.image_item.source = iconName;
    };
    UIItem.prototype.SetItemImageGray = function (isGray, allChildren) {
        //预留,白鹭能需要滤镜实现
    };
    //设置位置
    UIItem.prototype.setPos = function (posX, posY) {
        this.x = posX;
        this.y = posY;
    };
    UIItem.prototype.onClick = function () {
    };
    return UIItem;
}(eui.Component));
__reflect(UIItem.prototype, "UIItem");
//# sourceMappingURL=UIItem.js.map