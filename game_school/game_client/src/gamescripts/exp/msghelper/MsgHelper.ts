
namespace game
{
    export class MsgHelper
	{
        public constructor(){

        }
		protected opcode:number = -1;

		public Send( buf:Uint8Array ):void
		{
            var msg:any={};
            msg.key = this.opcode;
            msg.body= buf;
            App.Socket.send(msg);
		}
	}
}

