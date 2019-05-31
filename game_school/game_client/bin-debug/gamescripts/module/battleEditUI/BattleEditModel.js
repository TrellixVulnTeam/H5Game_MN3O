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
var BelongArray;
(function (BelongArray) {
    BelongArray[BelongArray["Array1"] = 0] = "Array1";
    BelongArray[BelongArray["Array2"] = 1] = "Array2";
    BelongArray[BelongArray["Array3"] = 2] = "Array3";
    BelongArray[BelongArray["Unassigned"] = 3] = "Unassigned";
})(BelongArray || (BelongArray = {}));
/**
 * 战斗编辑Model
 */
var BattleEditModel = (function (_super) {
    __extends(BattleEditModel, _super);
    function BattleEditModel($controller) {
        var _this = _super.call(this, $controller) || this;
        _this.currentTeam = BelongArray.Array1; //当前队伍
        _this.currentIndex = 1; //当前选择位置
        var objs = [
            200110,
            200410,
            200610,
            200710,
            200910,
            201010,
            201610,
            202010,
            202110,
            210410,
        ];
        App.PlayerManager.SetBasicInfo("", objs, 0, 0);
        _this.battleArray1 = [];
        _this.battleArray2 = [];
        _this.battleArray3 = [];
        _this.allBattleArray = [_this.battleArray1, _this.battleArray2, _this.battleArray3];
        _this.AddToArray(1, _this.currentTeam, 0);
        _this.AddToArray(2, _this.currentTeam, 200110);
        return _this;
    }
    /**
     * 添加到当前选择组
     */
    BattleEditModel.prototype.AddToCurrentArray = function (id) {
        return this.AddToArray(this.currentIndex, this.currentTeam, id);
    };
    /**初始化站位信息 */
    BattleEditModel.prototype.InitArrayInfo = function (action, index) {
        var info = new HeroInfo(index, 0, false);
        info.action = action;
        this.battleArray2.push(info);
        this.battleArray3.push(info);
        for (var i = 0; i < this.battleArray1.length; i++) {
            if (this.battleArray1[i].index == index) {
                return;
            }
        }
        this.battleArray1.push(info);
    };
    /**
     * 添加到指定组
     */
    BattleEditModel.prototype.AddToArray = function (index, belong, id) {
        if (!this.CheckIsExistHero(belong, id)) {
            for (var i = 0; i < this.allBattleArray[belong].length; i++) {
                if (this.allBattleArray[belong][i].index == index) {
                    if (this.allBattleArray[belong][i].id != id) {
                        var info_1 = new HeroInfo(index, id, true);
                        info_1.action = true;
                        this.allBattleArray[belong][i] = info_1;
                        return true;
                    }
                    else {
                        return false;
                    }
                }
            }
            var info = new HeroInfo(index, id, true);
            info.action = true;
            this.allBattleArray[belong].push(info);
            return true;
        }
        else {
            return false;
        }
    };
    /**
     * 交换位置
     */
    BattleEditModel.prototype.ExchangePoint = function (index1, index2) {
        if (index1 != index2) {
            var tempArray = this.GetTeamByIndex(this.currentTeam);
            var info1 = this.GetInfoByIndex(tempArray, index1);
            var info2 = this.GetInfoByIndex(tempArray, index2);
            if (info1 && info2 && info2.action) {
                var tempIndex = info1.index;
                info1.index = info2.index;
                info2.index = tempIndex;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    };
    /**
     * 根据下表获取信息
     */
    BattleEditModel.prototype.GetInfoByIndex = function (infos, index) {
        for (var i = 0; i < infos.length; i++) {
            if (infos[i].index == index) {
                return infos[i];
            }
        }
        return null;
    };
    /**
     * 判断当前组是否有当前英雄
     */
    BattleEditModel.prototype.CheckIsExistHero = function (belong, id) {
        for (var i = 0; i < this.allBattleArray[belong].length; i++) {
            if (this.allBattleArray[belong][i].id == id) {
                return true;
            }
        }
        return false;
    };
    /**
     * 检测是否已经上阵
     */
    BattleEditModel.prototype.CheckInArray = function (id) {
        for (var i = 0; i < this.allBattleArray.length; i++) {
            for (var j = 0; j < this.allBattleArray[i].length; j++) {
                if (id == this.allBattleArray[i][j].id) {
                    return true;
                }
            }
        }
        return false;
    };
    /**
     * 获取所有英雄
     */
    BattleEditModel.prototype.GetAllHero = function () {
        var _this = this;
        this.allHero = []; //每次重新获取
        App.PlayerManager.OwnHeroID.forEach(function (element) {
            var info = new HeroInfo(0, element, _this.CheckInArray(element));
            _this.allHero.push(info);
        });
        return this.allHero;
    };
    /**
     * 获取某队信息
     */
    BattleEditModel.prototype.GetTeamByIndex = function (index) {
        this.currentTeam = index;
        if (index < this.allBattleArray.length)
            return this.allBattleArray[index];
    };
    return BattleEditModel;
}(BaseModel));
__reflect(BattleEditModel.prototype, "BattleEditModel");
/** 英雄信息*/
var HeroInfo = (function () {
    function HeroInfo(index, id, belong) {
        this.index = index;
        this.id = id;
        this.belong = belong;
    }
    return HeroInfo;
}());
__reflect(HeroInfo.prototype, "HeroInfo");
//# sourceMappingURL=BattleEditModel.js.map