
class MoveComponent extends Component {
    public constructor() {
        super();
    }

    public start(): void {
        super.start();
    }

    public stop(): void {
        super.stop();
    }

    public update(advancedTime: number): void {
        super.update(advancedTime);
    }

    /**
     * 移动
     * @param point 坐标
     * @param callback 移动结束回调
     */
    public DoMove(point: egret.Point, callback?: Function, time: number = 500): void {
        this.entity.AddClientBitState(ClientBits.CLIENT_BIT_MOVING);
        var avatarCom: DragonComponent = <DragonComponent>this.entity.getComponent(ComponentType.Dragon);
        if (avatarCom) {
            avatarCom.PlayAct(ActionStr.Move);
        }

        //console.log(" posX = " + this.entity.position.x + " posY = " + this.entity.position.y)
        //console.log(" bodyX = " + avatarCom.body.x + " bodyY = " + avatarCom.body.y)
        //console.log(" pointX = " + point.x + " pointY = " + point.y)

        egret.Tween.get(this.entity.position /*avatarCom.body*/).to({ y: point.y, x: point.x /*, alpha: 1 */ }, time)
            .call(function () {
            this.entity.DelClientBitState(ClientBits.CLIENT_BIT_MOVING);
                if (callback) {
                    callback()
                }
            }.bind(this));
    }
}