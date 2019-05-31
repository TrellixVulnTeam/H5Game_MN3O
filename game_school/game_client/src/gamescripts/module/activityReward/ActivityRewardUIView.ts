enum ActivityRewardUIType
{
    ActivityReward_sign,//签到
    ActivityReward_cost,//消费
    ActivityReward_vip,//vip奖励
    ActivityReward_other,//other
}

/**
 * 签到界面
*/
class ActivityRewardUIView extends BaseEuiView 
{
    private back:eui.Image;//返回按钮

    private btn_0:eui.RadioButton;//签到按钮
    private btn_1:eui.RadioButton;//消费按钮
    private btn_2:eui.RadioButton;//vip奖励按钮
    private btn_3:eui.RadioButton;//other
    private btnGroup:eui.RadioButtonGroup = new eui.RadioButtonGroup();//按钮组//

    private image_bulb0:eui.Image;//签到红点
    private image_bulb1:eui.Image;//消费红点
    private image_bulb2:eui.Image;//vip奖励红点
    private image_bulb3:eui.Image;//other
    private bulbs:Array<eui.Image> = new Array<eui.Image>();//红点组//

    private gro_sign:eui.Group;//签到界面控件
    private gro_cost:eui.Group;//消费界面控件
    private gro_vip:eui.Group;//vip奖励界面控件
    private gro_other:eui.Group;//other界面控件
    private groupArray:Array<eui.Group> = Array<eui.Group>();//界面控件组//

    public dailySignUI:DailySignUIView;//签到界面//
    private childViewArray:Array<BaseEuiChildView> = Array<BaseEuiChildView>();//界面组//

    /**
     * 临时指引标记
    */
    private isFirstGuide = false;

    public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);

        this.addEventListener(eui.UIEvent.COMPLETE, ()=>{
            this.uiCompHandler($controller);
        }, this);
    }

    public initUI():void
    {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.ActivityRewardUI);

        this.isFirstGuide = App.GuideManager.getIsGuide;
    }

    public initData(): void 
    {
        super.initData();
    }

    public open(...param:any[]):void
    {
        super.open(param);
        
        this.openDefaultUI();
        this.updateBtnBulb();
    
        if(this.isFirstGuide)
        {
            this.isFirstGuide = false;
            this.addFirstGuide();
        }
    }

    /**
     * 临时指引1（第一次进入活动界面签到页签，点击签到按钮）
    */
    public addFirstGuide()
    {
        let btn_sign = this.gro_sign.getChildByName("btn_sign") as eui.Button;
        if(btn_sign != null)
        {
            this.validateNow();
            let mask = new GuideMask(btn_sign, () => {
                this.dailySignUI.onClickSign();
                this.onClose();
                App.ViewManager.open(ViewConst.MainUI);
            }, "", true, (btn_sign.width / 2), 0);
            this.addChild(mask);
        }
    }

    public close():void
    {
        super.close();
        
        for(let index:number = 0; index < this.childViewArray.length; index++)
        {
            this.childViewArray[index].onChildGroupHide();
        }
    }

    /**
     * 暂时默认打开
    */
    private openDefaultUI():void
    {
        //this.btn_0.selected = true;//页签按钮相关暂时屏蔽
        this.openGroupUI(ActivityRewardUIType.ActivityReward_sign);
    }
    
    private uiCompHandler($controller: BaseController):void
    {
        this.addChildUIView($controller);
        this.addChildGroupUI();
        //this.onSetBtnGroup();//页签按钮相关暂时屏蔽
        //this.onSetBtnBulb();//页签按钮相关暂时屏蔽
        this.back.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClose, this);
    }
    
    private addChildUIView($controller: BaseController):void
    {
        this.dailySignUI = new DailySignUIView($controller, this.gro_sign, this._key);
        this.childViewArray.push(this.dailySignUI);
    }

    private addChildGroupUI():void
    {
        this.groupArray.push(this.gro_sign);
        this.groupArray.push(this.gro_cost);
        this.groupArray.push(this.gro_vip);
        this.groupArray.push(this.gro_other);
    }

    private onSetBtnGroup():void
    {
        this.btnGroup.addEventListener(eui.UIEvent.CHANGE, this.selectUIHandler, this);
        this.btn_0.value = ActivityRewardUIType.ActivityReward_sign;
        this.btn_1.value = ActivityRewardUIType.ActivityReward_cost;
        this.btn_2.value = ActivityRewardUIType.ActivityReward_vip;
        this.btn_3.value = ActivityRewardUIType.ActivityReward_other;
        
        this.btn_0.group = this.btnGroup;
        this.btn_1.group = this.btnGroup;
        this.btn_2.group = this.btnGroup;
        this.btn_3.group = this.btnGroup;
    }

    private onSetBtnBulb():void
    {
        this.bulbs.push(this.image_bulb0);
        this.bulbs.push(this.image_bulb1);
        this.bulbs.push(this.image_bulb2);
        this.bulbs.push(this.image_bulb3);
    }

    private selectUIHandler(evt:eui.UIEvent):void 
    {
        this.btnGroup = evt.target;
        this.openGroupUI(this.btnGroup.selectedValue);
    }

    /**
     * 打开子界面
    */
    private openGroupUI(type:ActivityRewardUIType):void
    {
        for(let index:number = 0; index < this.groupArray.length; index++)
        {
            if(type == index)
            {
                this.groupArray[index].visible = true;
                if(index < this.childViewArray.length)
                {
                    this.childViewArray[index].onChildGroupShow();
                }
            }
            else
            {
                this.groupArray[index].visible = false;
                if(index < this.childViewArray.length)
                {
                    this.childViewArray[index].onChildGroupHide();
                }
            }
        }
    }

    /**
     * 刷新红点
    */
    private updateBtnBulb():void
    {
        for(let index:number = 0; index < this.bulbs.length; index++)
        {
            if(0 == index)
            {
                this.bulbs[index].visible = true;
            }
            else
            {
                this.bulbs[index].visible = false;
            }
        }
    }
}