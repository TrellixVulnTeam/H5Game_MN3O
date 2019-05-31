/**
 * Created by sjz on 2018-5-10.
 */
class CCG_GameModel extends BaseModel {
    public mapId: number;
    public onwerplayerData: any[];
    public enemyplayerData: any[];

    public constructor($controller: BaseController) {
        super($controller)

    }

    public InitGameData(mapId:number,arrayInfos:HeroInfo[]) {
        this.mapId=mapId;
      
        this.onwerplayerData=[];
        if(arrayInfos&&arrayInfos.length>0){
            
             for(let i=0;i<arrayInfos.length;i++){
                this.onwerplayerData[arrayInfos[i].index]=arrayInfos[i].id;
             }

        }else{

            this.onwerplayerData =
            [
               200110,200710,200910,201610,202010,210410
            ];

        }

       
            
    }


  


    
}