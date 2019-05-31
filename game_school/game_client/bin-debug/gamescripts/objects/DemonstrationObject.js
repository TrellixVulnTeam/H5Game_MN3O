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
 * 演示
 */
var DemonstrationObject = (function (_super) {
    __extends(DemonstrationObject, _super);
    function DemonstrationObject() {
        var _this = _super.call(this) || this;
        _this.originalpoint = new egret.Point; //原位
        return _this;
    }
    DemonstrationObject.prototype.init = function (id, posinfo, camp, gameView, rootView, data) {
        _super.prototype.init.call(this, id, posinfo, camp, gameView, data);
        this.avatarCom = this.addComponent(ComponentType.Avatar);
        this.rootCom = rootView;
        this.RegisEventListener(egret.TouchEvent.TOUCH_BEGIN, function (e) {
            this.StartMove(e);
        }.bind(this));
        this.RegisEventListener(egret.TouchEvent.TOUCH_END, function (e) {
            this.StopMove(e);
        }.bind(this));
        this.RegisEventListener(egret.TouchEvent.TOUCH_RELEASE_OUTSIDE, function (e) {
            this.StopMove(e);
        }.bind(this));
    };
    DemonstrationObject.prototype.StartMove = function (e) {
        this.draggedObject = e.currentTarget;
        this.originalpoint.x = this.position.x;
        this.originalpoint.y = this.position.y;
        var pos = this.draggedObject.localToGlobal(this.draggedObject.x, this.draggedObject.y); //转成世界坐标
        this.ChangeParent(this.rootCom); //转到移动层
        this.position = this.draggedObject.globalToLocal(pos.x, pos.y); //世界坐标转本地坐标
        this.offsetX = e.stageX - this.position.x;
        this.offsetY = e.stageY - this.position.y;
        App.EventMgrHelper.PushEventEx(EventDef.SetAddState, false, null, 0, 0, "", "");
        this.RegisEventListener(egret.TouchEvent.TOUCH_MOVE, function (e) {
            this.OnMove(e);
        }.bind(this));
    };
    DemonstrationObject.prototype.StopMove = function (e) {
        if (this.draggedObject) {
            var pos = this.draggedObject.localToGlobal(this.draggedObject.x, this.draggedObject.y);
            this.ChangeParent(this.gameView);
            this.position = this.draggedObject.globalToLocal(pos.x, pos.y);
            App.EventMgrHelper.PushEventEx(EventDef.CheckCollision, this, this.draggedObject, 0, 0, "", "");
            App.EventMgrHelper.PushEventEx(EventDef.SetAddState, true, null, 0, 0, "", "");
            this.draggedObject = null;
        }
        this.RemoveEventListener(egret.TouchEvent.TOUCH_MOVE);
    };
    DemonstrationObject.prototype.OnMove = function (e) {
        if (this.draggedObject) {
            this.position.x = e.stageX - this.offsetX;
            this.position.y = e.stageY - this.offsetY;
            if (this.avatarCom)
                this.avatarCom.setPos();
        }
    };
    DemonstrationObject.prototype.BackInPlace = function () {
        this.position.x = this.posInfo.Pos.x;
        this.position.y = this.posInfo.Pos.y;
    };
    return DemonstrationObject;
}(GameObject));
__reflect(DemonstrationObject.prototype, "DemonstrationObject");
//# sourceMappingURL=DemonstrationObject.js.map