enum PictureType
{
    injured = 1,//受伤立绘
    skill = 2,//技能立绘
}

/**
 * 战斗立绘
 */
class BattlePictureView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    /* 残血立绘组件 */
    private HPGroup: eui.Group;
    private image_player_blood: eui.Image;
    private image_face0: eui.Image;
    private pojia:egret.tween.TweenGroup;
    /* 残血立绘组件结束 */


    /* 技能立绘组件 */
    private SkillGroup: eui.Group;
    private image_player: eui.Image;
    private image_face: eui.Image;
    private image_skill: eui.Image;
    private star:egret.tween.TweenGroup;
    /* 技能立绘组件结束 */


    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        
        this.skinName = App.ViewManager.getSkin(ViewConst.BattlePicture);
    }

    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    public initData(): void {
        super.initData();
    }

    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    public open(...param: any[]): void {
        super.open(param);
        this.HPGroup.visible = false;
        this.SkillGroup.visible = false;
        //this.playPicturnAnimation(220010, null);//测试
    }

    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    public close(...param: any[]): void {
        super.close(param);
    }

    /**
     * 播放立绘
    */
    public playPicturnAnimation(id:number, callBack?:Function)
    {
        var config = DrawAnimationConfig.GetConfig(id);
        if(config == null) { return; }
        var drawConfig = DrawConfig.GetConfig(config.drawID);
        if(drawConfig == null) { return; }

        if(config.type == PictureType.injured)
        {
            this.PlayHPPicture(id, callBack);
        }
        else if(config.type == PictureType.skill)
        {
            this.PlaySkillPicture(id, callBack);
        }
    }


    //破甲立绘//
    private PlayHPPicture(id:number, callBack?:Function): void {
        this.HPGroup.visible = true;

        var config = DrawAnimationConfig.GetConfig(id);
        var drawConfig = DrawConfig.GetConfig(config.drawID);

        //和谐//
        var isCN: boolean = App.GlobalData.GamePlatform == "CN" ? true : false;
        if (isCN) 
        { 
            this.image_player_blood.source = drawConfig.draw2;
        }
        else 
        {
            this.image_player_blood.source = drawConfig.draw;
        }
        
        //是否换表情//
        if(config.face != 0)
        {
            if(drawConfig.face.length > config.face)
            {
                this.image_face0.visible = true;
                this.image_face0.source = drawConfig.face[config.face];
                if(drawConfig.facePosition.length >= 2)
                {
                    this.image_face0.x = drawConfig.facePosition[0];
                    this.image_face0.y = drawConfig.facePosition[1];
                }
            }
            else
            {
                 this.image_face0.visible = false;
            }
        }
        else
        {
            this.image_face0.visible = false;
        }

        //动画//
        this.pojia.play(0);

        //音效//
        App.SoundManager.playDelyInsetEffect(config.sound, config.soundDelay);

        //回调//
        egret.Tween.get(this.SkillGroup, {
        })
        .wait(config.liveTime)
        .call(() => 
        {
            this.pojia.stop();
            this.onClose();
            if (callBack != null) 
            {
                callBack();
            }  
        });
    }


    //技能立绘//
    private PlaySkillPicture(id:number, callBack?:Function): void 
    {
        this.SkillGroup.visible = true;

        var config = DrawAnimationConfig.GetConfig(id);
        var drawConfig = DrawConfig.GetConfig(config.drawID);

        //和谐//
        var isCN: boolean = App.GlobalData.GamePlatform == "CN" ? true : false;
        if (isCN) 
        {
            this.image_player.source = drawConfig.draw2;
        }
        else 
        {
            this.image_player.source = drawConfig.draw;
        }

        //是否换表情//
        if(config.face != 0)
        {
            if(drawConfig.face.length > config.face)
            {
                this.image_face.visible = true;
                this.image_face.source = drawConfig.face[config.face];
                if(drawConfig.facePosition.length >= 2)
                {
                    this.image_face.x = drawConfig.facePosition[0];
                    this.image_face.y = drawConfig.facePosition[1];
                }
            }
            else
            {
                 this.image_face.visible = false;
            }
        }
        else
        {
            this.image_face.visible = false;
        }

        //技能//
        this.image_skill.source = config.extraResource1;
    
        //动画//
        this.star.play(0);

        //音效//
        App.SoundManager.playDelyInsetEffect(config.sound, config.soundDelay);

        //回调//
        egret.Tween.get(this.SkillGroup, {
        })
        .wait(config.liveTime)
        .call(() => 
        {
            this.star.stop();
            this.onClose();
            if (callBack != null) 
            {
                callBack();
            }
        });
    }
}