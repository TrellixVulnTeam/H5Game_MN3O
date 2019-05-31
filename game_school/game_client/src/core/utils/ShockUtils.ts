/**
 * 震动
 */
class ShockUtils extends BaseClass {
    public constructor() {
        super();
    }

    public MAP: number = 0;
    public SPRITE: number = 1;
    public FREE: number = 1;

    private mapPoss: Array<any> = [new egret.Point(0, 3), new egret.Point(0, 0), new egret.Point(0, -2)];
    private spritePoss: Array<any> = [new egret.Point(5, 0), new egret.Point(-5, 0), new egret.Point(5, 0)];
    private _shockPoss: Array<any>;
    private _shockLength: number = 0;
    private _shockCount: number = 0;
    private _target: egret.DisplayObject;
    private _rx: number = 0;
    private _ry: number = 0;
    private _type: number = 0;
    private _dir: number = 0; //方向,FREE专用
    private _freecallback?: Function;

    private _repeatCount: number = 0;

    public destroy(): void {
        this.stop();
    }

    public shock(type: number = 0, target: egret.DisplayObject = null, repeatCount: number = 3): void {
        if (this._target) {
            return;
        }

        this._type = type;
        this._target = target;

        if (this._type == this.MAP) {
            this._shockPoss = this.mapPoss.concat();
            this._shockLength = this._shockPoss.length;
        }
        else if (this._type == this.SPRITE) {
            this._shockPoss = this.spritePoss.concat();
            this._shockLength = this._shockPoss.length;
        }
        this.start(repeatCount);
    }

    private start(num: number = 1): void {
        this.repeatCount = num;
        this._shockCount = 0;
        if (this._target) {
            if (this._type != this.MAP) {
                this._rx = this._target.x;
            }
            this._ry = this._target.y;
            App.TimerManager.doFrame(1, 0, this.onShockEnter, this);
        }
    }

    private stop(): void {
        if (this._target) {
            if (this._type != this.MAP) {
                this._target.x = this._rx;
            }
            this._target.y = this._ry;
            App.TimerManager.remove(this.onShockEnter, this);
        }
        this._target = null;
    }

    private onShockEnter(time: number): void {
        var maxCount: number = this._shockLength * this._repeatCount;
        if (this._shockCount >= maxCount) {
            this.stop();
            return;
        }
        var index: number = this._shockCount % this._shockLength;
        var pos: egret.Point = this._shockPoss[index];
        if (this._target) {
            if (this._type != this.MAP) {
                this._target.x = this._rx + pos.x;
            }
            this._target.y = this._ry + pos.y;
        }
        this._shockCount++;
    }

    public get repeatCount(): number {
        return this._repeatCount;
    }

    public set repeatCount(value: number) {
        this._repeatCount = value;
    }

    /**
     * 自定义抖动
     * @param target 要抖动的物体
     * @param repeatCount 要抖动的次数
     * @param dir 要抖动的方向
     * @param size 抖动的幅度,或者说,大小
     */
    public shockFree(target: egret.DisplayObject = null, repeatCount: number = 3, dir: number = 1, size: number = 3, callback?: Function): void {
        if (this._target) {
            return;
        }
        this._type = this.FREE;
        this._target = target;
        this._dir = dir;
        this._freecallback = callback;

        let freePoss: Array<any>;
        switch (dir) {
            case 1:
                freePoss = [new egret.Point(0, size), new egret.Point(0, 0), new egret.Point(0, -size)];
                break;
            case 2:
                freePoss = [new egret.Point(size, 0), new egret.Point(-size, 0), new egret.Point(size, 0)];
                break;
            case 3:
                freePoss = [new egret.Point(size, size), new egret.Point(-size, 0), new egret.Point(size, -size)];
                break;
        }
        this._shockPoss = freePoss.concat();
        this._shockLength = this._shockPoss.length;
        this.startFree(repeatCount, dir);
    }

    private startFree(num: number = 1, dir: number): void {
        this.repeatCount = num;
        this._shockCount = 0;
        if (this._target) {
            switch (dir) {
                case 1:
                    this._ry = this._target.y;
                    break;
                case 2:
                    this._rx = this._target.x;
                    break;
                case 3:
                    this._rx = this._target.x;
                    this._ry = this._target.y;
                    break;
            }
            App.TimerManager.doFrame(1, 0, this.onFreeShockEnter, this);
        }
    }

    private stopFree(): void {
        if (this._target) {
            switch (this._dir) {
                case 1:
                    this._target.y = this._ry;
                    break;
                case 2:
                    this._target.x = this._rx;
                    break;
                case 3:
                    this._target.x = this._rx;
                    this._target.y = this._ry;
                    break;
            }
            App.TimerManager.remove(this.onFreeShockEnter, this);
        }
        this._target = null;
    }

    private onFreeShockEnter(time: number): void {
        var maxCount: number = this._shockLength * this._repeatCount;
        if (this._shockCount >= maxCount) {
            this.stopFree();
            if (this._freecallback != null)
                this._freecallback();
            return;
        }
        var index: number = this._shockCount % this._shockLength;
        var pos: egret.Point = this._shockPoss[index];
        if (this._target) {
            switch (this._dir) {
                case 1:
                    this._target.y = this._ry + pos.y;
                    break;
                case 2:
                    this._target.x = this._rx + pos.x;
                    break;
                case 3:
                    this._target.x = this._rx + pos.x;
                    this._target.y = this._ry + pos.y;
                    break;
            }
        }
        this._shockCount++;
    }
}