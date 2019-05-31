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
var RandomNameManager = (function (_super) {
    __extends(RandomNameManager, _super);
    function RandomNameManager() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    RandomNameManager.getRoleName = function () {
        var oddname = this.getOddName();
        if (oddname.length > 0) {
            return oddname;
        }
        var firstName = this.getName(true);
        var lastName = this.getName(false);
        return firstName + lastName;
    };
    RandomNameManager.getOddName = function () {
        return "";
    };
    RandomNameManager.getName = function (iSFirstName) {
        if (RoleNameConfig.array.length == 0) {
            return "";
        }
        else {
            var index = App.RandomUtils.limitInteger(0, RoleNameConfig.array.length - 1);
            if (index >= 0 && index < RoleNameConfig.array.length) {
                if (iSFirstName) {
                    return RoleNameConfig.array[index].fristname;
                }
                else {
                    return RoleNameConfig.array[index].name;
                }
            }
            else {
                return "";
            }
        }
    };
    RandomNameManager.MAX_Length = 6;
    return RandomNameManager;
}(BaseManager));
__reflect(RandomNameManager.prototype, "RandomNameManager");
//# sourceMappingURL=RandomNameManager.js.map