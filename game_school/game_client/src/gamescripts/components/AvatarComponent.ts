/**
 * 骨骼组件
 */
class AvatarComponent extends Component {
    private mMovieClip: AvatarMovieClip;

    public constructor() {
        super();
    }

    public get AvatarMovieClip() {
        return this.mMovieClip;
    }

    public start(): void {
        super.start();
        this.mMovieClip = ObjectPool.pop("AvatarMovieClip");
        this.mMovieClip.Init(GameResGroupName.AvatarGroup, this.entity.avatarPath, this.entity.avatarName, this.entity,this.entity.oriScale);
        this.mMovieClip.start();
    }

    public stop(): void {
        super.stop();
        this.mMovieClip.stop();
        ObjectPool.push(this.mMovieClip);
        this.mMovieClip = null;
    }

    public update(advancedTime: number): void {
        super.update(advancedTime);
        this.setPos();
        /*if(!this.entity.TestClientBitState(ClientBits.CLIENT_BIT_MOVING) && !this.entity.TestClientBitState(ClientBits.CLIENT_BIT_CASTING)){
        }*/
        if (this.mMovieClip) {
            this.mMovieClip.update(advancedTime);
        }
    }

    public PlayAct(act: string, callback?: Function) {
        this.entity.action = act;
         if ((this.entity.action != this.mMovieClip .MovieClip. getCurrAction() || this.entity.dir != this.mMovieClip.MovieClip.getCurrDir())) {
             // console.log("PlayAct::::"+"id"+this.entity.uid+"      "+this.entity.basicattr.Name+"   "+ this.entity.action);
            this.mMovieClip.MovieClip.playAction(this.entity.action, this.entity.dir);
        }
   
        if (callback) {
            callback();
        }
    }
    
    public setPos(): void {
        if (this.mMovieClip) {
           
            if (this.mMovieClip.Body.x != this.entity.position.x) {
                this.mMovieClip.Body.x = this.entity.position.x;
            }
            if (this.mMovieClip.Body.y != this.entity.position.y) {
                this.mMovieClip.Body.y = this.entity.position.y;
            }
        }
    }

  
}