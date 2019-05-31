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
 * 玩家基础信息  zsy
 */
var PlayerBase = (function (_super) {
    __extends(PlayerBase, _super);
    function PlayerBase() {
        var _this = _super.call(this) || this;
        _this.ownGirl = [];
        _this.ownGirlId = [];
        _this.ownGirlUid = [];
        _this.ownHero = [];
        _this.ownHeroId = [];
        _this.ownHeroUid = [];
        return _this;
    }
    /*********************************************************************************************/
    PlayerBase.prototype.SetBasicInfo = function (name, ownHero, level, fightPower) {
        this.name = name;
        this.ownHeroId = ownHero;
        this.level = level;
        this.fightingPower = fightPower;
    };
    PlayerBase.prototype.GetGirl = function (id) {
        if (typeof id == "number") {
            var tempConfig = GirlConfig.GetConfig(id);
            if (tempConfig) {
                var index = this.ownGirlId.indexOf(id);
                if (index != -1) {
                    return this.ownGirl[index];
                }
                else {
                    var info = new GirlInfo(id, this);
                    if (info) {
                        this.ownGirlId.push(id);
                        this.ownGirl.push(info);
                        this.ownGirlUid.push(info.UId);
                        return info;
                    }
                    else {
                        return null;
                    }
                }
            }
        }
        if (typeof id == "string") {
            var index = this.ownGirlUid.indexOf(id);
            if (index != -1) {
                return this.ownGirl[index];
            }
            else {
                return null;
            }
        }
    };
    PlayerBase.prototype.GetHero = function (id) {
        if (typeof id == "number") {
            var index = this.ownHeroId.indexOf(id);
            if (index != -1) {
                return this.ownHero[index];
            }
            else {
                var info = new HeroData(id);
                if (info) {
                    this.ownHeroId.push(id);
                    this.ownHero.push(info);
                    this.ownHeroUid.push(info.UId);
                    return info;
                }
                else {
                    return null;
                }
            }
        }
        if (typeof id == "string") {
            var index = this.ownHeroUid.indexOf(id);
            if (index != -1) {
                return this.ownHero[index];
            }
            else {
                return null;
            }
        }
    };
    Object.defineProperty(PlayerBase.prototype, "Name", {
        get: function () { return this.name; },
        set: function (value) { this.name = value; },
        enumerable: true,
        configurable: true
    });
    ;
    Object.defineProperty(PlayerBase.prototype, "Level", {
        get: function () { return this.level; },
        set: function (value) { this.level = value; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(PlayerBase.prototype, "FightingPower", {
        get: function () { return this.fightingPower; },
        set: function (value) { this.fightingPower = value; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(PlayerBase.prototype, "HeadIcon", {
        get: function () { return this.headIcon; },
        set: function (value) { this.headIcon = value; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(PlayerBase.prototype, "OwnHero", {
        get: function () { return this.ownHero; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(PlayerBase.prototype, "OwnHeroID", {
        get: function () { return this.ownHeroId; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(PlayerBase.prototype, "OwnHeroUid", {
        get: function () { return this.ownHeroUid; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(PlayerBase.prototype, "OwnGirl", {
        get: function () { return this.ownGirl; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(PlayerBase.prototype, "OwnGirlId", {
        get: function () { return this.ownGirlId; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(PlayerBase.prototype, "OwnGirlUid", {
        get: function () { return this.ownGirlUid; },
        enumerable: true,
        configurable: true
    });
    /**根据友好度获取拥有的girl*/
    PlayerBase.prototype.GetFriendlySortList = function () {
        var _this = this;
        this.ownGirl.sort(function (a, b) { return _this.AddressListSort(a, b); });
        this.ownGirlId.splice(0, this.ownGirlId.length);
        this.ownGirlUid.splice(0, this.ownGirlUid.length);
        this.ownGirl.forEach(function (element) {
            _this.ownGirlId.push(element.GirlId);
            _this.ownGirlUid.push(element.UId);
        });
        return this.ownGirl;
    };
    PlayerBase.prototype.AddressListSort = function (a, b) {
        if (b.FriendlyNum == a.FriendlyNum) {
            return b.GirlId - a.GirlId;
        }
        return b.FriendlyNum - a.FriendlyNum;
    };
    return PlayerBase;
}(BaseClass));
__reflect(PlayerBase.prototype, "PlayerBase");
//# sourceMappingURL=PlayerBase.js.map