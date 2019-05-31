/**
 * 通信(wechat)管理类
*/

/**
 * 聊天组状态
 */
 enum WeChatGroupStatus{
     Inactivated,//未激活
     ActivationNotTrigger,//已激活未触发
     Triggered//已触发
 }

/**
  * 聊天类型
  */
enum WeChatGroupType{
    Friend,//好友聊天（私聊）
    Flock//群组聊天
}

class WechatManager extends BaseManager
{
    /**朋友圈 */
    private alreadyAnnId:Array<number> = new Array();//发布的朋友圈id(WechatConfig)
    private prepareAnnId:number[];//待发布动态的ID//


    /**聊天 */
    private ownChatList:ChatOwnList[]=[];//当前激活的聊天
    private ownChatIdList:number[]=[];//与聊天集合对应的归属id集合
    private fiendList:ChatOwnList[]=[];//私聊集合
    private flockList:ChatOwnList[]=[];//群聊集合

    public get OwnChatIdList():number[]{return this.ownChatIdList;}
    public get OwnChatList():ChatOwnList[]{return this.ownChatList;}
    public get FlockList():ChatOwnList[]{return this.flockList;}
    public get FiendList():ChatOwnList[]{return this.fiendList;}

    public constructor() 
	{
		super();
	}

    /**聊天 */

     /**
     * 通过归属id获取聊天集合
     */
    public GetChatListByownId(ownId:number):ChatOwnList{
        let index:number= this.ownChatIdList.indexOf(ownId);
         if(index!=-1){
             return this.ownChatList[index];
         } else{
             return null;
         }
     }

    /**
     * 通过id获取聊天组
     */
    public GetChatById(ownID:number,id:number):WechatGroupInfo{
      return  this.GetChatListByownId(ownID).GetChatByID(id);;
    }

     /**
     * 有激活的聊天组添加到列表
     */
    public AddActionChatToList(id:number,statu:WeChatGroupStatus=WeChatGroupStatus.ActivationNotTrigger,timer:number=egret.getTimer()){
        if(statu!=WeChatGroupStatus.Inactivated){
            let config=ChatGroupConfig.GetConfig(id);
            if(config){
               let index:number= this.ownChatIdList.indexOf(config.belong);
               let list:ChatOwnList;
                App.PlayerManager.GetGirl(config.belong);

               if(index!=-1){
                   list=this.ownChatList[index];
                   this.ownChatIdList[index]=config.belong;    
                   list.AddInfo(id,statu,timer);
               }else{
                   list=new ChatOwnList(config.belong)
                   this.ownChatIdList.push(config.belong)
                   this.ownChatList.push(list);
                   list.AddInfo(id,statu,timer);
               }

                if(list.currentType==WeChatGroupType.Flock){
                              this.AddChatToFlockList(list);
                 }else{
                              this.AddChatToFiendList(list);
                 }

                this.ownChatList.sort((a,b)=>this.ChatListSort(a,b)); 
                this.ownChatIdList.splice(0,this.ownChatIdList.length);
                this.ownChatList.forEach(element => {
                    this.ownChatIdList.push(element.ownId);    
                });

              }
          }else{
                //未激活的待处理
         }
    }

     /**
     * 添加到私聊列表
     */
    public AddChatToFiendList(list:ChatOwnList){
        for(let i=0;i<this.fiendList.length;i++){
            if(this.fiendList[i].ownId==list.ownId){
                this.fiendList[i]=list;
                this.fiendList.sort((a,b)=>this.ChatListSort(a,b));
                return;
            }
        }
        this.fiendList.push(list);
        this.fiendList.sort((a,b)=>this.ChatListSort(a,b));
    }

     /**
     * 添加到群聊列表
     */
    public AddChatToFlockList(list:ChatOwnList){
        for(let i=0;i<this.flockList.length;i++){
            if(this.flockList[i].ownId==list.ownId){
                this.flockList[i]=list;
                this.flockList.sort((a,b)=>this.ChatListSort(a,b));
                return;
            }
        }
        this.flockList.push(list);
        this.flockList.sort((a,b)=>this.ChatListSort(a,b));
    }

    /**
     * 设置最后打开时间修改时间
     */
    public SetLaseTimerList(info:ChatOwnList){
         info.Timer=egret.getTimer();
         this.flockList.sort((a,b)=>this.ChatListSort(a,b));
         this.fiendList.sort((a,b)=>this.ChatListSort(a,b));

         this.ownChatList.sort((a,b)=>this.ChatListSort(a,b)); 
         this.ownChatIdList.splice(0,this.ownChatIdList.length);
         this.ownChatList.forEach(element => {
                    this.ownChatIdList.push(element.ownId);    
         });
    }

    /**
     * 同状态  按最后一次读取时间 倒叙
     */
    public ChatListSort(a:ChatOwnList,b:ChatOwnList):number{
        if(a.ishaveNt==b.ishaveNt)
        {
            if(a.Timer==b.Timer)
                return b.ownId-a.ownId;
            return b.Timer-a.Timer;
        }else if(a.ishaveNt){
            return 1;
        }else{
            return -1;
        }   
    }



    /**朋友圈 */

    /**
     * 添加正在显示的朋友圈动态id（需要读服务器数据）
    */
    public addAlreadyAnnId(confid:number)
    {
        this.alreadyAnnId.push(confid);
    }

    /**
     * 获取朋友圈动态id
    */
    public get AlreadyAnnIds()
    {
        return this.alreadyAnnId;
    }

    /**
     * 朋友圈是否有动态可以发布
    */
    public isFriendMomentAnnounce():boolean
    {
        if(this.prepareAnnId.length > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
}


/**
 * 聊天归属集合
 */
class ChatOwnList{
     public currentType:WeChatGroupType;//类型
     public ownId:number;//归属id
     private timer:number;//最后一次读取的时间，每次点击都修改
     public ishaveNt=false;//是否拥有未触发的聊天
     private ownInfos:WechatGroupInfo[]=[];//拥有的聊天
     private ownIds:number[]=[];//拥有聊天的id
     private currentId:number=0;//当前对话id
     private owner:GirlInfo;//拥有着

     public constructor(ownId:number){
            this.ownId=ownId;
            this.owner=App.PlayerManager.GetGirl(ownId);
     }

     public get Timer():number{return this.timer;}
     public set Timer(value:number){ this.timer=value;}//以后可能要保存
     public get Owner():GirlInfo{return this.owner;}

     /**
      * 新增聊天组
      */
     public AddInfo(id:number,statu:WeChatGroupStatus,timer:number){
             let info:WechatGroupInfo=new WechatGroupInfo(id,statu,timer);
             this.currentType=info.CurrentType;
             this.timer=timer;
             
             let index=this.ownIds.indexOf(id);
             if(index!=-1){
                 this.ownId[index]=id;
                 this.ownInfos[index]=info;
             }else{
                 this.ownIds.push(id);
                 this.ownInfos.push(info);
             }  

             if(info.CurrentStatus==WeChatGroupStatus.ActivationNotTrigger)
             this.ishaveNt=true;

             this.ownInfos.sort((a,b)=>{return b.ActivTimer-a.ActivTimer});
             this.ownIds.splice(0,this.ownIds.length);
             this.ownInfos.forEach(element => {
                 this.ownIds.push(element.ID);
             });
      }

      /**
       * 获取当前聊天
       * 按激活顺序的第一个未触发的信息
       * 如果没有返回最后一个
       */
      public GetCurrentChat():WechatGroupInfo{
          if(this.ownInfos){
                if(this.currentId!=0){
                     return this.GetChatByID(this.currentId);
                 }else{
                     for (let i=0;i<this.ownInfos.length;i++){
                     if(this.ownInfos[i].CurrentStatus==WeChatGroupStatus.ActivationNotTrigger){
                         this.currentId=this.ownInfos[i].ID;
                         return this.ownInfos[i];
                     }
                 } 
                 if(this.ownInfos.length>0){
                   this.currentId=  this.ownInfos[this.ownInfos.length-1].ID;
                    return  this.ownInfos[this.ownInfos.length-1];
                 }else{
                    return null;
                 }
          }
          }else{
              return null;
          }
      }
      
      /**
       * 获取下一个聊天
       */
      public GetNextChat():WechatGroupInfo{
          if(this.currentId!=0){
              let index =this.ownIds.indexOf(this.currentId);
              if(index!=-1){
                  if(index<this.ownInfos.length-1){
                      this.currentId=this.ownInfos[index+1].ID;
                      return this.ownInfos[index+1];
                  }else{
                      return null;
                  }
              }else{
                return this.GetCurrentChat();
              }
          }else{
            return this.GetCurrentChat();
          }
      }

      /**
       * 获取上一个聊天
       */
      public GetLastChat():WechatGroupInfo{
           if(this.currentId!=0){
              let index =this.ownIds.indexOf(this.currentId);
              if(index!=-1){
                  if(index>0){
                       this.currentId=this.ownInfos[index-1].ID;
                      return this.ownInfos[index-1];
                  }else{
                      return null;
                  }
              }else{
                return this.GetCurrentChat();
              }
          }else{
            return this.GetCurrentChat();
          }
      }

      /**
       * 获取最后一个已经触发的聊天
       */
      public GetLastChatByStatu():WechatGroupInfo{
            for(let i=this.ownInfos.length-1;i>=0;i--){
                if(this.ownInfos[i].CurrentStatus==WeChatGroupStatus.Triggered){
                    return this.ownInfos[i];
                }
            }
            return null;
      }

       /**
       * 获取所有已经触发的聊天
       */
      public GetAllTriggered():WechatGroupInfo[]{
            let tempList:WechatGroupInfo[]=[];
            for(let i=0;i<this.ownInfos.length;i++){
                if(this.ownInfos[i].CurrentStatus==WeChatGroupStatus.Triggered){
                   tempList.push(this.ownInfos[i]);
                }
            }
            return tempList;
      }

      /**
       * 获取最后一句话
       */
      public GetLastSentence():string {
          if(this.currentId!=0&&(this.ownIds.indexOf(this.currentId)!=-1)){
              return this.GetChatByID(this.currentId).LastSentence;
          }else{
              let info=this.GetLastChatByStatu();
              if(info){
                  return info.LastSentence;
              }else{
                 info=this.GetCurrentChat();
                 if(info){
                     return info.LastSentence;
                 }else{
                     return "";
                 }
              }
          }
      }

      /**
       * 通过id获取聊天组
       */
      public GetChatByID(id:number):WechatGroupInfo{
          let index =this.ownIds.indexOf(id);
          if(index!=-1){
              return this.ownInfos[index];
          }else{
              return null;
          }
      }
      
      /**
       * 是否存在激活未出发的聊天
       */
      public IsExistNoTrigger():boolean{
          for (let i=0;i<this.ownInfos.length;i++){
              if(this.ownInfos[i].CurrentStatus==WeChatGroupStatus.ActivationNotTrigger){
                  return true;
              }
          }
          return false;
      }
}

/**
 * 聊天组信息
 */
class WechatGroupInfo{
    private activTimer:number;//激活时间，添加的时候就定下不能更改
    private lastSentence:string;//获取最后一句话
    private owner:GirlInfo;//拥有者
    private id:number;//组id
    private currentStatus:WeChatGroupStatus;//当前状态
    private currentType:WeChatGroupType;//类型
    private pastChatList:number[]=[];//已经聊过
    private ownObjId:number;//对象id

    public mChatConfig:ChatGroupConfig;//表格
    public lastchatId:number=0;//聊天进度
    public mSelectMap:{[key:number]:number}={};
   
    public get ActivTimer():number{return this.activTimer;}
    public get LastSentence():string{return this.lastSentence;}
    public set LastSentence(value:string){ this.lastSentence=value;}
    public get ID():number{return this.id;}
    public get CurrentType():WeChatGroupType{return this.currentType;}
    public get OwnObjId():number{return this.ownObjId;}
   

    public constructor(id:number,statu:WeChatGroupStatus=WeChatGroupStatus.ActivationNotTrigger,timer:number){
        this.id=id;
        this.currentStatus=statu;
        this.mChatConfig=ChatGroupConfig.GetConfig(id);
        this.currentType=this.mChatConfig.type;
        this.activTimer=timer;
        this.ownObjId=this.mChatConfig.belong;
        this.lastchatId=this.mChatConfig.startChatID;
        this.owner=App.PlayerManager.GetGirl(this.ownObjId);
        
        let chatCon:ChatConfig=ChatConfig.GetConfig(this.mChatConfig.startChatID);
        if(chatCon){
            if(chatCon.type==0){
                 this.lastSentence="";
            }else{
                if(chatCon.npcDialogType==1){
                    this.lastSentence=chatCon.content;
                 }else{
                     this.lastSentence="[语音通话]";
                 }
            }
        }else{
            this.lastSentence="";
        }
     }


    /**
     * 添加到已聊天
     */
    public AddToPast(id:number){
         let index=this.pastChatList.indexOf(id);
          if(index!=-1){
              this.pastChatList[index]=id;
         }else{
              this.pastChatList.push(id);
         }
    }

    /**
     * 检测是否是已经聊过
     */
    public FindPastChat(id:number):boolean{
         let index=this.pastChatList.indexOf(id);
             if(index!=-1){
                  return true;
              }else{
                 return false;
              }
    }
   
    public get CurrentStatus():WeChatGroupStatus{return this.currentStatus;}
    public set CurrentStatus(statu:WeChatGroupStatus){
        if(this.currentStatus!=WeChatGroupStatus.Triggered&&statu==WeChatGroupStatus.Triggered){
                this.owner.SetFriendlyNum(this.mChatConfig.param2);
        }
        this.currentStatus=statu;
    }

}