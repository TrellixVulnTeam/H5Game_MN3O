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
 * created by sjz on 2018-5-9.
 * 场景背景类
 */
var CCG_SceneBackGround = (function (_super) {
    __extends(CCG_SceneBackGround, _super);
    function CCG_SceneBackGround() {
        return _super.call(this) || this;
    }
    CCG_SceneBackGround.prototype.init = function (mapId, view) {
        this.mapId = mapId;
        var config = BattleConfig.GetConfig(mapId);
        // var mapData: any = RES.getRes("map_" + mapId + "_data.json");//等待修改
        // this.mapWidth = mapData.width;
        // this.mapHeight = mapData.height;
        this.miniBg = new egret.Bitmap();
        this.miniBg.texture = RES.getRes(config.battle_bg); //等待修改
        this.miniBg.width = 750;
        this.miniBg.height = 1334;
        this.addChild(this.miniBg);
        view.addChildAt(this, 0);
    };
    return CCG_SceneBackGround;
}(egret.DisplayObjectContainer));
__reflect(CCG_SceneBackGround.prototype, "CCG_SceneBackGround");
//# sourceMappingURL=CCG_SceneBackGround.js.map