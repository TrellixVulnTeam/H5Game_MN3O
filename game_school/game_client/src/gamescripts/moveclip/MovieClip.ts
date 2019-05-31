/**
 * 方向
 */
enum Dir {
    Top,
    TopRight,
    Right,
    BottomRight,
    Bottom,
    BottomLeft,
    Left,
    TopLeft
}

/**
 * 动作 
 */
class Action {  
    public static Die: string = "die";
    public static Move: string = "run";
    public static Stand: string = "idle";
    public static Hit: string = "hit";
}

class MovieClip extends egret.Bitmap {
    private McFrameTime: number = 250 / 8;
    private mCurrentMoveClipFrame: egret.FrameLabel;
    private mcData: egret.MovieClipData;
    private currAction: string;
    private currDir: Dir;
    private currFrame: number;
    private startFrame: number;
    private endFrame: number;
    private currFrameTime: number;
    private totalPlayNum: number;
    private currPlayNum: number;
    private complateAction: Function;
    private complateActionObj: any;
    private mResName: string;
    private currID:number=0;

    public constructor() {
        super();
    }

    private setBitmap(texture: egret.Texture, scaleX: number): void {
        this.texture = texture;
        this.scaleX = scaleX;
        AnchorUtil.setAnchorX(this, 0.5);
        AnchorUtil.setAnchorY(this, 1);
    }

    public setDefault(resName: string): void {
        this.setBitmap(RES.getRes(resName), 1);
        this.currFrame = 0;
    }

    public setMcData(mcData: egret.MovieClipData, resName: string): void {
        this.mcData = mcData;
        this.mResName = resName;
    }

    public runAction(advancedTime: number): void {
        
        if (!this.mcData) {
            return;
        }
 
        this.currFrameTime += advancedTime;
        if (this.currFrameTime >= this.McFrameTime) {
            
            this.currFrameTime = 0;
            this.currFrame++;
            let isEnd: boolean = false;
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
                 this.complateAction&&
                 this.complateAction.apply(this.complateActionObj);
            } else {
                var bitmapTexture: egret.Texture = this.mcData.getTextureByFrame(this.currFrame);
                this.setBitmap(bitmapTexture, this.scaleX);
            }
        }
    }

    public playAction(gotoAction: string, gotoDir: Dir, cover: boolean = false, totalPlayNum: number = 0) {
        if (gotoAction == Action.Move || gotoAction == Action.Stand) {
            totalPlayNum = 0;
        } else {
            totalPlayNum = 1;
        }
        this.gotoAction(gotoAction, gotoDir, cover, totalPlayNum);
    }

    public gotoAction(gotoAction: string, gotoDir: Dir, cover: boolean = false, totalPlayNum: number = 0,id:number=0): void {
        this.currID=id;
      
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
        let dirandscal: number[] = this.getDir(gotoDir);
        var actionName: string = gotoAction + "_" + dirandscal[0];
        var currLabel: egret.FrameLabel;

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
            var bitmapTexture: egret.Texture = this.mcData.getTextureByFrame(this.currFrame);
            this.setBitmap(bitmapTexture, dirandscal[1]);
            dirandscal = [];
        }
    }

    public getDir(gotoDir: number): number[] {
        //0上 1右上/左上 2右/左 3右下/左下 4下
        let str: number[] = [];
        if (gotoDir == Dir.Top) {
            str[0] = 0;
            str[1] = 1;
        } else if (gotoDir == Dir.TopRight) {
            str[0] = 1;
            str[1] = 1;
        } else if (gotoDir == Dir.Right) {
            str[0] = 2;
            str[1] = 1;
        } else if (gotoDir == Dir.BottomRight) {
            str[0] = 3;
            str[1] = 1;
        } else if (gotoDir == Dir.Bottom) {
            str[0] = 4;
            str[1] = 1;
        } else if (gotoDir == Dir.BottomLeft) {
            str[0] = 3;
            str[1] = -1;
        } else if (gotoDir == Dir.Left) {
            str[0] = 2;
            str[1] = -1;
        } else if (gotoDir == Dir.TopLeft) {
            str[0] = 1;
            str[1] = -1;
        }
        return str;
    }

    public setComplateAction(complateAction: Function, complateActionObj: any): void {

        this.complateAction = complateAction;
        this.complateActionObj = complateActionObj;
    }

    public destroy(): void {
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
    }

    public getCurrAction(): string {
        return this.currAction;
    }

    public getCurrDir(): Dir {
        return this.currDir;
    }

    public GetPlayNum(): number {
        return this.totalPlayNum;
    }

}