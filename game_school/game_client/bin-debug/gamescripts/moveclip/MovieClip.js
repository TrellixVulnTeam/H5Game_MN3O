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
 * 方向
 */
var Dir;
(function (Dir) {
    Dir[Dir["Top"] = 0] = "Top";
    Dir[Dir["TopRight"] = 1] = "TopRight";
    Dir[Dir["Right"] = 2] = "Right";
    Dir[Dir["BottomRight"] = 3] = "BottomRight";
    Dir[Dir["Bottom"] = 4] = "Bottom";
    Dir[Dir["BottomLeft"] = 5] = "BottomLeft";
    Dir[Dir["Left"] = 6] = "Left";
    Dir[Dir["TopLeft"] = 7] = "TopLeft";
})(Dir || (Dir = {}));
/**
 * 动作
 */
var Action = (function () {
    function Action() {
    }
    Action.Die = "die";
    Action.Move = "run";
    Action.Stand = "idle";
    Action.Hit = "hit";
    return Action;
}());
__reflect(Action.prototype, "Action");
var MovieClip = (function (_super) {
    __extends(MovieClip, _super);
    function MovieClip() {
        var _this = _super.call(this) || this;
        _this.McFrameTime = 250 / 8;
        _this.currID = 0;
        return _this;
    }
    MovieClip.prototype.setBitmap = function (texture, scaleX) {
        this.texture = texture;
        this.scaleX = scaleX;
        AnchorUtil.setAnchorX(this, 0.5);
        AnchorUtil.setAnchorY(this, 1);
    };
    MovieClip.prototype.setDefault = function (resName) {
        this.setBitmap(RES.getRes(resName), 1);
        this.currFrame = 0;
    };
    MovieClip.prototype.setMcData = function (mcData, resName) {
        this.mcData = mcData;
        this.mResName = resName;
    };
    MovieClip.prototype.runAction = function (advancedTime) {
        if (!this.mcData) {
            return;
        }
        this.currFrameTime += advancedTime;
        if (this.currFrameTime >= this.McFrameTime) {
            this.currFrameTime = 0;
            this.currFrame++;
            var isEnd = false;
            if (this.currFrame > this.endFrame) {
                this.currFrame = this.startFrame;
                this.currPlayNum++;
                isEnd = true;
            }
            // if(this.currID!=0){
            //     console.log("currID   "+this.currID+"    totalPlayNum    "+this.totalPlayNum+"    currPlayNum    "+this.currPlayNum+"   currFrameTime  "+this.currFrameTime+ "   McFrameTime  "+this.McFrameTime);
            // }
            if (isEnd && this.mCurrentMoveClipFrame) {
                this.dispatchEventWith("MovieClipEnd", false, this.mCurrentMoveClipFrame.name);
            }
            if (this.totalPlayNum && this.currPlayNum >= this.totalPlayNum) {
                this.complateAction &&
                    this.complateAction.apply(this.complateActionObj);
            }
            else {
                var bitmapTexture = this.mcData.getTextureByFrame(this.currFrame);
                this.setBitmap(bitmapTexture, this.scaleX);
            }
        }
    };
    MovieClip.prototype.playAction = function (gotoAction, gotoDir, cover, totalPlayNum) {
        if (cover === void 0) { cover = false; }
        if (totalPlayNum === void 0) { totalPlayNum = 0; }
        if (gotoAction == Action.Move || gotoAction == Action.Stand) {
            totalPlayNum = 0;
        }
        else {
            totalPlayNum = 1;
        }
        this.gotoAction(gotoAction, gotoDir, cover, totalPlayNum);
    };
    MovieClip.prototype.gotoAction = function (gotoAction, gotoDir, cover, totalPlayNum, id) {
        if (cover === void 0) { cover = false; }
        if (totalPlayNum === void 0) { totalPlayNum = 0; }
        if (id === void 0) { id = 0; }
        this.currID = id;
        if (!this.mcData) {
            return;
        }
        if (!cover) {
            if (this.currAction == gotoAction && this.currDir == gotoDir) {
                return;
            }
        }
        /*
        //不能在这里处理,会影响BUFF和别的帧动画的循环播放
        if (gotoAction == Action.Move || gotoAction == Action.Stand) {
            totalPlayNum = 0;
        } else {
            totalPlayNum = 1;
        }
        */
        var dirandscal = this.getDir(gotoDir);
        var actionName = gotoAction + "_" + dirandscal[0];
        var currLabel;
        for (var i = 0; i < this.mcData.labels.length; i++) {
            if (actionName == this.mcData.labels[i].name) {
                currLabel = this.mcData.labels[i];
                this.mCurrentMoveClipFrame = currLabel;
            }
        }
        if (this.currAction == gotoAction && !cover) {
            this.currFrame = currLabel.frame + (this.currFrame - this.startFrame);
        }
        else {
            if (typeof currLabel == 'undefined') {
                Log.Error("current altas " + this.mResName + " not have " + gotoAction);
            }
            else {
                this.currFrame = currLabel.frame;
                this.currFrameTime = 0;
            }
        }
        if (typeof currLabel != 'undefined') {
            this.startFrame = currLabel.frame;
            this.endFrame = currLabel.end;
            this.currAction = gotoAction;
            this.currDir = gotoDir;
            this.totalPlayNum = totalPlayNum;
            this.currPlayNum = 0;
            var bitmapTexture = this.mcData.getTextureByFrame(this.currFrame);
            this.setBitmap(bitmapTexture, dirandscal[1]);
            dirandscal = [];
        }
    };
    MovieClip.prototype.getDir = function (gotoDir) {
        //0上 1右上/左上 2右/左 3右下/左下 4下
        var str = [];
        if (gotoDir == Dir.Top) {
            str[0] = 0;
            str[1] = 1;
        }
        else if (gotoDir == Dir.TopRight) {
            str[0] = 1;
            str[1] = 1;
        }
        else if (gotoDir == Dir.Right) {
            str[0] = 2;
            str[1] = 1;
        }
        else if (gotoDir == Dir.BottomRight) {
            str[0] = 3;
            str[1] = 1;
        }
        else if (gotoDir == Dir.Bottom) {
            str[0] = 4;
            str[1] = 1;
        }
        else if (gotoDir == Dir.BottomLeft) {
            str[0] = 3;
            str[1] = -1;
        }
        else if (gotoDir == Dir.Left) {
            str[0] = 2;
            str[1] = -1;
        }
        else if (gotoDir == Dir.TopLeft) {
            str[0] = 1;
            str[1] = -1;
        }
        return str;
    };
    MovieClip.prototype.setComplateAction = function (complateAction, complateActionObj) {
        this.complateAction = complateAction;
        this.complateActionObj = complateActionObj;
    };
    MovieClip.prototype.destroy = function () {
        App.DisplayUtils.removeFromParent(this);
        this.mcData = null;
        this.texture = null;
        this.currAction = null;
        this.currDir = null;
        this.currFrame = null;
        this.startFrame = null;
        this.endFrame = null;
        this.currFrameTime = 0;
        this.totalPlayNum = 0;
        this.currPlayNum = 0;
        this.complateAction = null;
        this.complateActionObj = null;
    };
    MovieClip.prototype.getCurrAction = function () {
        return this.currAction;
    };
    MovieClip.prototype.getCurrDir = function () {
        return this.currDir;
    };
    MovieClip.prototype.GetPlayNum = function () {
        return this.totalPlayNum;
    };
    return MovieClip;
}(egret.Bitmap));
__reflect(MovieClip.prototype, "MovieClip");
//# sourceMappingURL=MovieClip.js.map