var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**字典数据结构类 */
var Dictionary = (function () {
    function Dictionary(isCache) {
        if (isCache === void 0) { isCache = false; }
        this.keys = [];
        this.values = [];
        this.isCache = isCache;
    }
    Object.defineProperty(Dictionary.prototype, "count", {
        get: function () {
            return this.Count();
        },
        enumerable: true,
        configurable: true
    });
    /**给字典增加一条数据,返回字典的长度 */
    Dictionary.prototype.Add = function (key, value) {
        if (this.isCache) {
            this[key] = value;
        }
        this.keys.push(key);
        return this.values.push(value);
    };
    Dictionary.prototype.Remove = function (key) {
        var index = this.keys.indexOf(key, 0);
        this.keys.splice(index, 1);
        this.values.splice(index, 1);
        if (this.isCache) {
            delete this[key];
        }
    };
    Dictionary.prototype.Clear = function () {
        if (this.isCache) {
            var keys = this.keys;
            for (var i = 0; i < keys.length; i++) {
                this.Remove(this.keys[i]);
            }
            keys = null;
        }
    };
    Dictionary.prototype.Count = function () {
        return this.keys.length;
    };
    /**直接使用SetDicValue()修改已经存在的字典数据项，并更新缓存引用 */
    Dictionary.prototype.SetDicValue = function (key, value) {
        var index = this.keys.indexOf(key, 0);
        if (index != -1) {
            this.keys[index] = key;
            this.values[index] = value;
            if (this.isCache) {
                this[key] = value;
            }
            return true;
        }
        return false;
    };
    /**
     *开启"[]"访问的情况下，缓存与字典数据为同一份，引用数据会同时修改，
     *非引用数据不能被修改，只能访问
     */
    Dictionary.prototype.TryGetValue = function (key) {
        var index = this.keys.indexOf(key, 0);
        if (index != -1) {
            return this.values[index];
        }
        return null;
    };
    Dictionary.prototype.ContainsKey = function (key) {
        var ks = this.keys;
        for (var i = 0; i < ks.length; ++i) {
            if (ks[i] == key) {
                return true;
                ;
            }
        }
        return false;
    };
    Dictionary.prototype.GetKeys = function () {
        return this.keys;
    };
    Dictionary.prototype.GetValues = function () {
        return this.values;
    };
    return Dictionary;
}());
__reflect(Dictionary.prototype, "Dictionary");
//# sourceMappingURL=Dictionary.js.map