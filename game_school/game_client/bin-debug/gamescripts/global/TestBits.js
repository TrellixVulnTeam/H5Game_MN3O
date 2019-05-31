var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var TestBits = (function () {
    function TestBits() {
    }
    TestBits.TestMagicEffectBits = function (nflags, Bits) {
        return (nflags & Bits) == Bits;
    };
    TestBits.TestDisperseCcontent = function (nflags, Disperse) {
        return (nflags & Disperse) == Disperse;
    };
    TestBits.TestCamp = function (nflags, camp) {
        return (nflags & camp) == camp;
    };
    TestBits.TestBuffControlTypeBits = function (nflags, arg) {
        return (nflags & arg) == arg;
    };
    return TestBits;
}());
__reflect(TestBits.prototype, "TestBits");
//# sourceMappingURL=TestBits.js.map