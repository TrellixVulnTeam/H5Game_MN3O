var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/*
* @class MyBitset
* @file MyBitset.ts
* @brief 位集
**/
var MyBitset = (function () {
    function MyBitset(bitNum) {
        this.mBits = [];
        this.mBits.length = (bitNum % 32) == 0 ? bitNum / 32 : (bitNum / 32) + 1;
    }
    MyBitset.prototype.GetBitset = function (index) {
        var num = index >> 6; // index/32;
        var bit = index % 32; //index % 32;
        return (this.mBits[num] & (1 << bit)) != 0;
    };
    MyBitset.prototype.SetBitSet = function (index, value) {
        var num = index >> 6; // index/32;
        var bit = index % 32; //index % 32;
        if (value) {
            this.mBits[num] |= (1 << bit);
        }
        else {
            this.mBits[num] &= ~(1 << bit);
        }
    };
    return MyBitset;
}());
__reflect(MyBitset.prototype, "MyBitset");
//# sourceMappingURL=MyBitset.js.map