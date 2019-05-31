enum WechatUIType
{
    Wechat_fm,//朋友圈
    Wechat_chat,//聊天
    Wechat_record,//录音
    Wechat_vipcn_com,//公众号
}

class WechatUIView extends BaseEuiView 
{
    private btn_1:eui.RadioButton;//朋友圈按钮
    private btn_2:eui.RadioButton;//聊天按钮
    private btn_3:eui.RadioButton;//录音按钮
    private btn_4:eui.RadioButton;//公众号按钮
    private btnGroup:eui.RadioButtonGroup = new eui.RadioButtonGroup();//按钮//

    private image_tishi_pyq1:eui.Image;//朋友圈红点
    private image_tishi_pyq2:eui.Image;//聊天红点
    private image_tishi_pyq3:eui.Image;//录音红点
    private image_tishi_pyq4:eui.Image;//公众号红点
    private bulbs:Array<eui.Image> = new Array<eui.Image>();//红点//

    private gro_pyq:eui.Group;
    private gro_talk:eui.Group;
    private gro_other:eui.Group;
    private gro_mor:eui.Group;
    private groupArray:Array<eui.Group> = Array<eui.Group>();

    public friendMomentUI:FriendMomentUIView;
    public chatListInfoUi:ChatListsInfoUIView;
    public addressBookView:AddressbookListUIView;

    private childViewArray:Array<BaseEuiChildView> = Array<BaseEuiChildView>();

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
        this.skinName = App.ViewManager.getSkin(ViewConst.WechatUI);
    }

    public initData(): void 
    {
        super.initData();
    }

    public open(...param:any[]):void
    {
        super.open(param);
        
        this.openDefaultUI();//暂时默认打开
        this.updateBtnBulb();
    }

    public close():void
    {
        super.close();
        
        for(let index:number = 0; index < this.childViewArray.length; index++)
        {
            this.childViewArray[index].onChildGroupHide();
        }
    }

    private openDefaultUI():void
    {
        this.btn_1.selected = true;
        this.openGroupUI(WechatUIType.Wechat_fm);
    }
    
    private uiCompHandler($controller: BaseController):void
    {
        this.addChildUIView($controller);
        this.addChildGroupUI();
        this.onSetBtnGroup();
        this.onSetBtnBulb();
    }

    private addChildUIView($controller: BaseController):void
    {
        this.friendMomentUI = new FriendMomentUIView($controller, this.gro_pyq, this._key);
        this.childViewArray.push(this.friendMomentUI);

        this.chatListInfoUi = new ChatListsInfoUIView($controller, this.gro_talk, this._key);
        this.childViewArray.push(this.chatListInfoUi);

        this.addressBookView=new AddressbookListUIView($controller,this.gro_other,this._key);
        this.childViewArray.push(this.addressBookView);
    }

    private addChildGroupUI():void
    {
        this.groupArray.push(this.gro_pyq);
        this.groupArray.push(this.gro_talk);
        this.groupArray.push(this.gro_other);
        this.groupArray.push(this.gro_mor);
    }

    private onSetBtnGroup():void
    {
        this.btnGroup.addEventListener(eui.UIEvent.CHANGE, this.selectUIHandler, this);
        this.btn_1.value = WechatUIType.Wechat_fm;
        this.btn_2.value = WechatUIType.Wechat_chat;
        this.btn_3.value = WechatUIType.Wechat_record;
        this.btn_4.value = WechatUIType.Wechat_vipcn_com;
        
        this.btn_1.group = this.btnGroup;
        this.btn_2.group = this.btnGroup;
        this.btn_3.group = this.btnGroup;
        this.btn_4.group = this.btnGroup;
    }

    private onSetBtnBulb():void
    {
        this.bulbs.push(this.image_tishi_pyq1);
        this.bulbs.push(this.image_tishi_pyq2);
        this.bulbs.push(this.image_tishi_pyq3);
        this.bulbs.push(this.image_tishi_pyq4);
    }

    public SelectUIByType(type:WechatUIType){
        this.btn_1.selected=type== this.btn_1.value;
        this.btn_2.selected=type== this.btn_2.value;
        this.btn_3.selected=type== this.btn_3.value;
        this.btn_4.selected=type== this.btn_4.value;
        this.openGroupUI(type);
    }

    private selectUIHandler(evt:eui.UIEvent):void 
    {
        this.btnGroup = evt.target;
        this.openGroupUI(this.btnGroup.selectedValue);
    }

    public  openGroupUI(type:WechatUIType):void
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