/**
 * 朋友圈界面
*/
class FriendMomentUIView extends BaseEuiChildView 
{
    public static isFirstOpen:number = 1;
    private gro_pyq:eui.Group;
    private py_btn_back:eui.Button;
    private py_btn_announce:eui.Button;
    private py_gro_total:eui.Group;
    private py_gro_gap:number = 0;
    private py_gro_array:Array<FCFriendGroup> = new Array<FCFriendGroup>();
    private py_gro_data:Array<number> = new Array<number>();//朋友圈的临时数据

    public constructor($controller: BaseController, $parent: eui.Group, key:number)
    {
        super($controller, $parent, key);
        this.gro_pyq = $parent;
        this.onInitUI();
    }

    private onInitUI():void
    {
        this.py_btn_back  = this.gro_pyq.getChildByName("py_btn_back") as eui.Button;
        this.py_btn_announce  = this.gro_pyq.getChildByName("py_btn_announce") as eui.Button;
        this.py_gro_total = (this.gro_pyq.getChildByName("py_scr") as eui.Scroller).getChildByName("py_gro_total") as eui.Group;
        this.py_gro_gap = (this.py_gro_total.layout as eui.VerticalLayout).gap;
        
        this.py_btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClose, this);
        this.py_btn_announce.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onAnnounceInfo, this);
    }
    
    public onChildGroupShow():void 
    {
        super.onChildGroupShow();
        
        if(FriendMomentUIView.isFirstOpen == 1)
        {
            for(let index = 0; index < WechatConfig.array.length; index++)
            {
                let config = WechatConfig.array[index];
                if(config != null && config.personID != 0)
                {
                    this.py_gro_data.push(config.id);
                    App.WechatManager.addAlreadyAnnId(config.id);//添加临时数据
                }
            }
        }

        this.onSetFriendMessageUIInfo();
    }

    public onChildGroupHide():void 
    {
        FriendMomentUIView.isFirstOpen++;
    }

    /**
     * 朋友圈动态
    */
    private onSetFriendMessageUIInfo(ctid?:number):void
    {
        for(let index = 0; index < this.py_gro_data.length; index++)
        {
            let config = WechatConfig.GetConfig(this.py_gro_data[index]);
            if(config != null)
            {
                if(!this.isArrayContain(config.id))
                {
                    let tempgroup:FCFriendGroup = new FCFriendGroup(config.id);

                    tempgroup.initItemGropuHeight(this.py_gro_gap);
                    tempgroup.creatureCondition(config, ctid);//朋友圈动态//
                    if(ctid == null)
                    {
                        tempgroup.creatureOtherMessage(config);//朋友圈伙伴留言//
                    }
                    else
                    {
                        tempgroup.creatureOtherMessage(config, true);//玩家动态,伙伴留言//
                    }
                    tempgroup.cretureAddLine(this.py_gro_gap);//朋友圈分割线//
                    
                    this.py_gro_array.push(tempgroup);
                    this.py_gro_total.addChild(tempgroup.getItemGroup);
                }
                else if(FriendMomentUIView.isFirstOpen >= 2)
                {
                    let temp = this.getArrayInfoItem(this.py_gro_data[index]);
                    if(temp != null)
                    {

                        temp.updateCondition();
                        temp.updateMessReply();
                        temp.updateMessComm();
                    }
                }
            }
        }
    }

    /**
     * 发布动态
    */
    private onAnnounceInfo():void
    {
        let config = WechatConfig.GetConfig(1);
        App.EventMgrHelper.PushEvent(EventDef.announceInfo,config.id);
    }

    /**
     * 发布朋友圈
    */
    public onUpdateAnnounceInfo(cfid:number, ctid:number):void
    {
        this.py_gro_data.push(cfid);
        this.onSetFriendMessageUIInfo(ctid);
    }

    /**
     * 玩家添加留言
    */
    public onUpdateCommentInfo(cfid:number, ctid:number):void
    {
        let temp = this.getArrayInfoItem(cfid);
        if(temp != null)
        {
            temp.cretureAddMessage(cfid, ctid);
        }
    }

    /**
     * 是否已经显示动态
    */
    private isArrayContain(id:number):boolean
    {
        let flag = false;
        for(let index:number = 0; index < this.py_gro_array.length; index++)
        {
            if(this.py_gro_array[index].getItemId == id)
            {
                flag = true;
                break;
            }
        }
        return flag;
    }
    
    /**
     * 获取动态
    */
    private getArrayInfoItem(id:number):FCFriendGroup
    {
        let infoItem:FCFriendGroup;
        for(let index:number = 0; index < this.py_gro_array.length; index++)
        {
            if(this.py_gro_array[index].getItemId == id)
            {
                infoItem = this.py_gro_array[index];
                break;
            }
        }
        return infoItem;
    }
}


/**
 * 朋友圈朋友消息group
*/
class FCFriendGroup extends BaseEuiView
{
    private py_item_group:eui.Group;
    private group_id:number = 0;

    public scrann:FCFriendAnnounce;
    public scremss:FCFriendMessage;
    private myLine:eui.Image;

    public constructor(cid:number) 
    {
       super(null,null);
       this.group_id = cid;
       this.skinName = "resource/skins/item_vertical_group.exml";
    }
    
    public get getItemGroup():eui.Group
    {
        return this.py_item_group;
    }

    public get getItemId():number
    {
        return this.group_id;
    }

    public initItemGropuHeight(gap:number):void
    {
        this.py_item_group.height = gap;
    }

    /**
     * 添加动态
    */
    public creatureCondition(config:WechatConfig, ctid?:number):void
    {
        this.scrann = new FCFriendAnnounce(config.id);
        if(config.personID == 0)
        {
            this.scrann.setConditionInfo(ctid);//玩家的动态//
        }
        else
        {
            this.scrann.setConditionInfo(config.contentId[0]);//伙伴的动态//
        }
        this.py_item_group.height += this.scrann.groupHeight;
        this.py_item_group.addChild(this.scrann.getGroup);
    }

    /**
     * 刷新动态
    */
    public updateCondition()
    {
        this.py_item_group.height -= this.scrann.groupHeight;
        this.scrann.updateConditionInfo();
        this.py_item_group.height += this.scrann.groupHeight;
    }

    /**
     * 添加伙伴留言
     * isSelf是否是自己的动态
    */
    public creatureOtherMessage(config:WechatConfig, isSelf:boolean = false):void
    {
        this.scremss = new FCFriendMessage(config.id);
        this.scremss.setOtherMessaged(config, isSelf);
        this.py_item_group.height += this.scremss.groupHeight;
        this.py_item_group.addChild(this.scremss.groallMessage);
    }

    /**
     * 玩家添加留言
    */
    public cretureAddMessage(cfid:number, ctid:number):void
    {
        this.py_item_group.height -= this.scremss.groupHeight;
        this.scremss.setSelfComment(cfid, ctid);
        this.py_item_group.height += this.scremss.groupHeight;
    }

    /**
     * 刷新留言
    */
    public updateMessComm():void
    {
        this.py_item_group.height -= this.scremss.groupHeight;
        this.scremss.updateMessComm();
        this.py_item_group.height += this.scremss.groupHeight;
    }

    /**
     * 刷新留言回复
    */
    public updateMessReply():void
    {
        this.py_item_group.height -= this.scremss.groupHeight;
        this.scremss.updateReply();
        this.py_item_group.height += this.scremss.groupHeight;
    }

    /**
     * 添加分割线
    */
    public cretureAddLine(gap:number):void
    {
        this.myLine = new eui.Image();
        this.myLine.source = "image_wuchatline1_png"
        this.myLine.width = this.py_item_group.width;
        this.py_item_group.height += this.myLine.height;
        this.py_item_group.addChild(this.myLine);
        this.py_item_group.height += gap;
    }

    /**
     * 分割线之前的位置
    */
    public get preLineIndex():number
    {
        return this.py_item_group.getChildIndex(this.myLine) - 1;
    }
}


/**
 * 朋友圈朋友动态
*/
class FCFriendAnnounce extends BaseEuiView
{
    private player:eui.Group;
    private head:eui.Image;
    
    private gro_content:eui.Group;
    private myname:eui.Label;
    private des:eui.Label;
    private pic:eui.Image;
    private btn_message:eui.Button;

    private gro_con_gap:number = 0;
    private isSelfReply = false;
    private infoId = 0;

    public constructor(id:number) 
    {
       super(null,null);
       this.infoId = id;
       this.skinName = "resource/skins/Wechat_item.exml";
       this.btn_message.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClickMessage, this);
       this.gro_con_gap = (this.gro_content.layout as eui.VerticalLayout).gap;
    }
    
    public get getGroup():eui.Group
    {
        return this.player;
    }

    public get groupHeight():number
    {
        return this.player.height;
    }

    /**
     * 动态消息
    */
    public setConditionInfo(ctid:number = 0)
    {
       
        let config = WechatConfig.GetConfig(this.infoId);
        let cConfig = WechatContentConfig.GetConfig(ctid);
        let girl:GirlInfo;
        if(config.personID!=0){
              girl=App.PlayerManager.GetGirl(config.personID);
        }
           
        if(cConfig == null)
        {
            return;
        }

        this.head.source = config.head;

        if((config.personID == 0 || this.isSelfReply) && this.gro_content.getChildIndex(this.btn_message) != -1)//自己发布消息或者已经留言过了
        {
            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.btn_message.height;
            this.gro_content.removeChild(this.btn_message);
        }
        
        if(cConfig.content != "")
        {
            if(config.personID == 0)
            {
                this.myname.text = App.PlayerManager.Name;
            }
            else
            {
                if(girl)
                this.myname.text = girl.GirlName ;
            }
            
            this.des.text = cConfig.content;
        }
        else
        {
            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.myname.height;
            this.gro_content.removeChild(this.myname);

            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.des.height;
            this.gro_content.removeChild(this.des);
        }

        if(config.pic != "")
        {
            this.pic.source = config.pic;
        }
        else
        {
            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.pic.height;
            this.gro_content.removeChild(this.pic);
        }

        this.player.height = this.gro_content.height;
    }

    /**
     * 刷新动态
    */
    public updateConditionInfo():void
    {
        let config = WechatConfig.GetConfig(this.infoId);
        if(config.personID!=0){
                let girl:GirlInfo=App.PlayerManager.GetGirl(config.personID);
                if(girl)
                this.myname.text = girl.GirlName ;
        }else{
             this.myname.text = App.PlayerManager.Name;
        }

        if((config.personID == 0 || this.isSelfReply) && this.gro_content.getChildIndex(this.btn_message) != -1)//自己发布消息或者已经留言过了
        {
            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.btn_message.height;
            this.gro_content.removeChild(this.btn_message);
            this.player.height = this.gro_content.height;
        }
    }

    /**
     * 点击留言
    */
    private onClickMessage():void
    {
        this.isSelfReply = true;
        this.btn_message.enabled = false;
        let config = WechatConfig.GetConfig(this.infoId);
        App.EventMgrHelper.PushEvent(EventDef.commentInfo,config.id);
    }
}


/**
 * 朋友圈留言
*/
class FCFriendMessage extends BaseEuiView
{
    private gro_all:eui.Group;
    private gro_mess:eui.Group;
    private imagebg:eui.Image;

    private gro_gap:number = 0;
    private gro_height:number = 0;
    private gro_textY:number = 0;
    private infoId = 0;

    private replyStrName:Array<LeaveMessage>= new Array<LeaveMessage>();

    private isFirstSelfReply = true;
    private isFirstOtherComment = true;
    private isFirstOtherReply = true;
    
    public constructor(id:number) 
    {
       super(null,null);
       this.infoId = id;
       this.skinName = "resource/skins/Wechat_talk_item.exml";
       this.gro_gap = (this.gro_mess.layout as eui.VerticalLayout).gap;
    }

    public get groallMessage():eui.Group
    {
        return this.gro_all;
    }

    public get groupHeight():number
    {
        return this.gro_all.height;
    }

    /**
     * 玩家添加留言
    */
    public setSelfComment(cfid:number, ctid:number)
    {
        let cConfig = WechatContentConfig.GetConfig(ctid);
        if(cConfig != null)
        {
            this.creatrueTextField( new LeaveMessage(leaveType.leave,cConfig.content,0));
            
            if(cConfig.replyContent != "" && this.isFirstSelfReply)
            {
                this.isFirstSelfReply = false
                let config = WechatConfig.GetConfig(cfid);
                this.replyStrName.push(new LeaveMessage(leaveType.reply,cConfig.replyContent,config.personID,0));
            }
        }

        this.gro_all.height = this.gro_height;
        this.gro_mess.height = this.gro_height;
        this.imagebg.height = this.gro_height;
    }

    /**
     * 伙伴留言
     * isSelf是否是自己的动态
    */
    public setOtherMessaged(config:WechatConfig, isSelf:boolean = false)
    {
        this.gro_height = this.gro_gap;
        for(let index = 0; index < config.otherReply.length; index++)
        {
            let cConfig = WechatContentConfig.GetConfig(config.otherReply[index]);
            if(cConfig != null)
            {

                if(isSelf && this.isFirstOtherComment)
                {
                   this.replyStrName.push(new LeaveMessage(leaveType.leave,cConfig.content,cConfig.type));
                }
                else
                {
                    this.creatrueTextField( new LeaveMessage(leaveType.leave,cConfig.content,cConfig.type));
                }

                if(cConfig.replyContent != "" && this.isFirstOtherReply)
                {
                    this.isFirstOtherReply = false;
                    this.replyStrName.push(new LeaveMessage(leaveType.reply,cConfig.replyContent,config.personID,cConfig.type));
                }
            }
        }

        if(isSelf && this.isFirstOtherComment)
        {
            this.gro_all.height = this.gro_height;
            this.gro_mess.height = this.gro_height;
            this.imagebg.height = this.gro_height;
            this.imagebg.visible = false;
        }
        else
        {
            this.gro_all.height = this.gro_height;
            this.gro_mess.height = this.gro_height;
            this.imagebg.height = this.gro_height;
            this.imagebg.visible = true;
        }
        this.isFirstOtherComment = false;
    }

    /**
     * 刷新留言
    */
    public updateMessComm():void
    {
        if(this.replyStrName.length > 0)
        {
            for(let index = 0; index < this.replyStrName.length; index++)
            {
                if(this.replyStrName[index].CurrentType==leaveType.leave)
                this.creatrueTextField(this.replyStrName[index]);
            }
        
            this.gro_all.height = this.gro_height;
            this.gro_mess.height = this.gro_height;
            this.imagebg.height = this.gro_height;
            this.imagebg.visible = true;
        }
    }

    /**
     * 刷新回复
    */
    public updateReply():void
    {
        if(this.replyStrName.length > 0)
        {
            for(let index = 0; index < this.replyStrName.length; index++)
            {
               if(this.replyStrName[index].CurrentType==leaveType.reply)
                this.creatrueTextField(this.replyStrName[index]);
            }
            this.gro_all.height = this.gro_height;
            this.gro_mess.height = this.gro_height;
            this.imagebg.height = this.gro_height;
            this.imagebg.visible = true;
        }
    }

    /**
     * 添加消息
    */
    private creatrueTextField(msg:LeaveMessage):void
    {
        for(let i=0;i<this.gro_mess.numElements;i++){
        let temptext:InfoTExtField = this.gro_mess.getChildAt(i) as InfoTExtField;
        if(temptext.Data==msg.UID){

             temptext.textFlow = <Array<egret.ITextElement>>[
            {text: msg.GetName(), style: {"textColor": 0x000000, "fontFamily": "Microsoft YaHei", "size": 30}},
            {text: msg.Content, style: {"textColor": 0xffffff, "fontFamily": "Microsoft YaHei", "size": 30}} ];

            return;
        }
        }

        let myText:InfoTExtField=new InfoTExtField();
        myText.Data= msg.UID;
        myText.width = this.gro_mess.width;
        myText.textFlow = <Array<egret.ITextElement>>[
            {text: msg.GetName(), style: {"textColor": 0x000000, "fontFamily": "Microsoft YaHei", "size": 30}},
            {text: msg.Content, style: {"textColor": 0xffffff, "fontFamily": "Microsoft YaHei", "size": 30}}
        ];

        myText.y = this.gro_textY;
        this.gro_textY += myText.height + this.gro_gap;
        this.gro_height += myText.height + this.gro_gap;
        this.gro_mess.addChild( myText );
    }
}

class InfoTExtField extends egret.TextField{
    private data:string;
    public get Data():string{return this.data;}
    public set Data(value:string){this.data=value;}
}


enum leaveType{
    /**留言*/
    leave, 
    /**回复*/
    reply 
}
class LeaveMessage{
    private currentType:leaveType;
    private content:string;
    private leftID:number;
    private rightID:number;
    private uid:string;

    public constructor(type:leaveType,content:string,leftID:number=0,rightID :number=0){
            this.currentType=type;
            this.content=content;
            this.leftID=leftID;
            this.rightID=rightID;
            this.uid=App.MathUtils.uuid(8,10);
    }

    public get Content():string{return this.content;}
    public get CurrentType():leaveType{return this.currentType;}
    public get UID():string{return this. uid;}

    public GetName():string{
                let leftName:string;
                let rightName:string;
                let retName:string;
                if(this.leftID==0){
                    leftName=App.PlayerManager.Name;
                }else{
                    leftName=App.PlayerManager.GetGirl(this.leftID).GirlName;
                }

            if(this.currentType==leaveType.leave){
                     retName=leftName+": ";
            }else if(this.currentType==leaveType.reply){
                 if(this.rightID==0){
                    rightName=App.PlayerManager.Name;
                }else{
                    rightName=App.PlayerManager.GetGirl(this.rightID).GirlName;
                }

                 retName = leftName + "回复"+ rightName+"：";
            }
        return retName;
    }

}