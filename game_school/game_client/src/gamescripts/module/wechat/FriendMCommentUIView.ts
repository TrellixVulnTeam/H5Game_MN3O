/**
 * 朋友圈发布消息和留言选择界面
*/
class FriendMCommentUIView extends BaseEuiView 
{
    private image_back:eui.Image;
    private image_title:eui.Image;
    private label_str:eui.Label;
    private gro_all:eui.Group;

    private infoId:number;
    private isAnnounce:boolean;//发布消息true，留言false

    public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);
        this.addEventListener(eui.UIEvent.COMPLETE, this.uiCompHandler, this);
    }
    
    private uiCompHandler():void
    {
        this.image_back.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClose, this);
    }

    public initUI():void
    {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.FriendMCommentUI);
    }

    public initData(): void 
    {
        super.initData();
    }

    public close(...param:any[]):void
    {
        super.close(param);
        this.gro_all.removeChildren();
    }

    public open(...param:any[]):void
    {
        super.open(param);
        if(this.isAnnounce == true)
        {
            this.onSetAnnounceUIInfo();
        }
        else
        {
            this.onSetCommentUIInfo();
        }
    }

    /**
     * 显示发布朋友圈选项
    */
    public onSetAnnounceInfoId(id:number):void
    {
        this.infoId = id;
        this.isAnnounce = true;
    }
    
    /**
     * 显示朋友圈留言选项
    */
    public onSetCommentInfoId(id:number):void
    {
        this.infoId = id;
        this.isAnnounce = false;
    }
    
    /**
     * 发布朋友圈消息
    */
    public onSetAnnounceUIInfo():void
    {
        let config = WechatConfig.GetConfig(this.infoId);
        for(var index = 0; index < config.contentId.length; index++)
        {
            var mess = new FCSelectMessage(config.id, config.contentId[index]);
            mess.onSetAnnounceContent(function(){ this.onClose(); }.bind(this));
            this.gro_all.addChild(mess);
        }
    }

    /**
     * 朋友圈留言
    */
    public onSetCommentUIInfo():void
    {
        let config = WechatConfig.GetConfig(this.infoId);
        for(var index = 0; index < config.talks.length; index++)
        {
            var mess = new FCSelectMessage(config.id, config.talks[index]);
            mess.onSeCommenttContent(config.friendliness[index], function(){ this.onClose(); }.bind(this));
            this.gro_all.addChild(mess);
        }
    }
}


/**
 * 选择内容
*/
class FCSelectMessage extends BaseEuiView
{
    private label_dia:eui.Label;
    private button_dia:eui.Button;
    private configid:number;
    private contentid:number;

    public constructor(cfid:number, ctid:number) 
    {
       super(null,null);
       this.configid = cfid;
       this.contentid = ctid;
       this.skinName = "resource/skins/Wechat_dia_item.exml";
    }

    /**
     * 发布消息
    */
    public onSetAnnounceContent(callback?:Function):void
    {
        let config = WechatContentConfig.GetConfig(this.contentid);
        this.label_dia.text = config.choiceContent;
        this.button_dia.addEventListener(egret.TouchEvent.TOUCH_TAP, function(){
            if(callback != null)
            {
                callback();
            }
            this.onSelectAnnounce();
        }.bind(this), this);
    }

    /**
     * 发布成功，刷新朋友圈消息
    */
    private onSelectAnnounce():void
    {
        App.EventMgrHelper.PushEvent(EventDef.updateFriendsInfo,this.configid,this.contentid);
    }

    /**
     * 留言
    */
    public onSeCommenttContent(friendliness:number, callback?:Function):void
    {
        let config = WechatContentConfig.GetConfig(this.contentid);
        this.label_dia.text = config.choiceContent;
        this.button_dia.addEventListener(egret.TouchEvent.TOUCH_TAP, function(){
            if(callback != null)
            {
                callback();
            }
            this.onSelectRevert(StrConfigManager.getStrById(1001) + friendliness.toString());
        }.bind(this), this);
    }

    /**
     * 留言成功，增加好感度提示，刷新留言
    */
    private onSelectRevert(content:string):void
    {
        App.EventMgrHelper.PushEvent(EventDef.updateCommentInfo,this.configid,this.contentid);
        App.EventMgrHelper.PushEvent(EventDef.Friendliness_tips, -1, -1, content);
    }
}