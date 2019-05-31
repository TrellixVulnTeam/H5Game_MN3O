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
 * Created by sjz on 2018-5-10.
 */
var CCG_GameModel = (function (_super) {
    __extends(CCG_GameModel, _super);
    function CCG_GameModel($controller) {
        return _super.call(this, $controller) || this;
    }
    CCG_GameModel.prototype.InitGameData = function (mapId, arrayInfos) {
        this.mapId = mapId;
        this.onwerplayerData = [];
        if (arrayInfos && arrayInfos.length > 0) {
            for (var i = 0; i < arrayInfos.length; i++) {
                this.onwerplayerData[arrayInfos[i].index] = arrayInfos[i].id;
            }
        }
        else {
            this.onwerplayerData =
                [
                    200110, 200710, 200910, 201610, 202010, 210410
                ];
        }
    };
    return CCG_GameModel;
}(BaseModel));
__reflect(CCG_GameModel.prototype, "CCG_GameModel");
//# sourceMappingURL=CCG_GameModel.js.map