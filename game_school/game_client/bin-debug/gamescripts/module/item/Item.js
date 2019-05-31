var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var Item = (function () {
    function Item() {
    }
    Object.defineProperty(Item.prototype, "ItemClientID", {
        get: function () {
            return this.itemID;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Item.prototype, "ItemIcon", {
        get: function () {
            return this.itemIcon;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Item.prototype, "ItemNum", {
        get: function () {
            return this.itemNum;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Item.prototype, "ItemName", {
        get: function () {
            return this.itemName;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Item.prototype, "ItemLv", {
        get: function () {
            return this.itemLv;
        },
        enumerable: true,
        configurable: true
    });
    Item.prototype.init = function (id, icon, num, name, lv) {
        this.itemID = id;
        this.itemIcon = icon;
        this.itemNum = num;
        this.itemName = name;
        this.itemLv = lv;
    };
    return Item;
}());
__reflect(Item.prototype, "Item");
//# sourceMappingURL=Item.js.map