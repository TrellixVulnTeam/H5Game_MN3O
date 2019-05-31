
class AvatarMovieClip extends MovieClipComponentBase {
    public constructor() {
        super()
    }

    public Init(gameResGroupName: string, mcpath: string, mcname: string, entity,scale:number) {
        super.Init(gameResGroupName, mcpath, mcname, entity,scale);
    }

    public start() {
        super.start();
    }

    public stop() {
        super.stop();
    }

    public update(advancetime: number) {
        super.update(advancetime);
        if ((this.Entity.action != this.MovieClip.getCurrAction() || this.Entity.dir != this.MovieClip.getCurrDir())) {
        // console.log("update+id"+this.Entity.uid+"      "+this.Entity.basicattr.Name+"   "+ this.Entity.action);
         //this.MovieClip.DispatchEvent();
         this.MovieClip.playAction(this.Entity.action, this.Entity.dir);
        }
        this.MovieClip.runAction(advancetime);
    }

    public complateAction(): void {
        super.complateAction();
        if (this.MovieClip.getCurrAction() == Action.Die) {
            App.FightManager.removeplayer(this.Entity as MilitaryOfficerObject);
        } else {
            this.Entity.action = Action.Stand;
            this.MovieClip.gotoAction(this.Entity.action, this.Entity.dir);
        }
    }

}