export class ${class_name} extends MsgHelper
{
	public msg:GeneralMes.${msg_name};

	public constructor()
	{
		super();
		this.msg = new GeneralMes.${msg_name}();
		this.opcode = MsgDef.msgid_${msg_name};
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.${msg_name}.encode(this.msg).finish();
		super.Send(buf);
	}
}

