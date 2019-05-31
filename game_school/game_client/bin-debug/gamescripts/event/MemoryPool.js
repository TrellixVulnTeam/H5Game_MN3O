var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * @author sjz
 * @time 2018-8-13 19:09
 */
var MemoryPool = (function () {
    function MemoryPool(maxSize) {
        if (maxSize === void 0) { maxSize = 10; }
        /**
         * @description 切勿单独操作此数组，如需增删请引用封装的函数
         * @description 此数组在此用作模拟队列来处理数据，遵循先进先出，所以请勿单独操作此数组
         */
        this.mobjs = new Array();
        this.mMaxSize = 10;
    }
    Object.defineProperty(MemoryPool.prototype, "Count", {
        get: function () {
            return this.mobjs.length;
        },
        enumerable: true,
        configurable: true
    });
    MemoryPool.prototype.Alloc = function () {
        var t = null;
        if (this.mobjs.length > 0) {
            t = this.mobjs.shift();
        }
        return t;
    };
    MemoryPool.prototype.Free = function (t) {
        if (this.mobjs.length < this.mMaxSize) {
            this.mobjs.push(t);
        }
    };
    MemoryPool.prototype.Dispose = function () {
        this.mobjs.slice(0, this.mobjs.length);
    };
    return MemoryPool;
}());
__reflect(MemoryPool.prototype, "MemoryPool");
//# sourceMappingURL=MemoryPool.js.map