namespace game
{
export class CSLoginEndedHelper extends MsgHelper
{
	public msg:GeneralMes.CSLoginEnded;

	public constructor()
	{
		super();
		this.msg = new GeneralMes.CSLoginEnded();
		this.opcode = MsgDef.msgid_CSLoginEnded;
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.CSLoginEnded.encode(this.msg).finish();
		super.Send(buf);
	}
}

export class CSKickDroppedHumanHelper extends MsgHelper
{
	public msg:GeneralMes.CSKickDroppedHuman;

	public constructor()
	{
		super();
		this.msg = new GeneralMes.CSKickDroppedHuman();
		this.opcode = MsgDef.msgid_CSKickDroppedHuman;
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.CSKickDroppedHuman.encode(this.msg).finish();
		super.Send(buf);
	}
}

export class CSCharacterEnterWorldHelper extends MsgHelper
{
	public msg:GeneralMes.CSCharacterEnterWorld;

	public constructor()
	{
		super();
		this.msg = new GeneralMes.CSCharacterEnterWorld();
		this.opcode = MsgDef.msgid_CSCharacterEnterWorld;
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.CSCharacterEnterWorld.encode(this.msg).finish();
		super.Send(buf);
	}
}

export class CSCharacterLoginHelper extends MsgHelper
{
	public msg:GeneralMes.CSCharacterLogin;

	public constructor()
	{
		super();
		this.msg = new GeneralMes.CSCharacterLogin();
		this.opcode = MsgDef.msgid_CSCharacterLogin;
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.CSCharacterLogin.encode(this.msg).finish();
		super.Send(buf);
	}
}

export class CSCharacterDeleteHelper extends MsgHelper
{
	public msg:GeneralMes.CSCharacterDelete;

	public constructor()
	{
		super();
		this.msg = new GeneralMes.CSCharacterDelete();
		this.opcode = MsgDef.msgid_CSCharacterDelete;
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.CSCharacterDelete.encode(this.msg).finish();
		super.Send(buf);
	}
}

export class CSCharacterCreateHelper extends MsgHelper
{
	public msg:GeneralMes.CSCharacterCreate;

	public constructor()
	{
		super();
		this.msg = new GeneralMes.CSCharacterCreate();
		this.opcode = MsgDef.msgid_CSCharacterCreate;
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.CSCharacterCreate.encode(this.msg).finish();
		super.Send(buf);
	}
}

export class CSCharacterRevertHelper extends MsgHelper
{
	public msg:GeneralMes.CSCharacterRevert;

	public constructor()
	{
		super();
		this.msg = new GeneralMes.CSCharacterRevert();
		this.opcode = MsgDef.msgid_CSCharacterRevert;
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.CSCharacterRevert.encode(this.msg).finish();
		super.Send(buf);
	}
}

export class CSLoginGateHelper extends MsgHelper
{
	public msg:GeneralMes.CSLoginGate;

	public constructor()
	{
		super();
		this.msg = new GeneralMes.CSLoginGate();
		this.opcode = MsgDef.msgid_CSLoginGate;
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.CSLoginGate.encode(this.msg).finish();
		super.Send(buf);
	}
}

export class CSLoginBeganHelper extends MsgHelper
{
	public msg:GeneralMes.CSLoginBegan;

	public constructor()
	{
		super();
		this.msg = new GeneralMes.CSLoginBegan();
		this.opcode = MsgDef.msgid_CSLoginBegan;
	}
	
	

	public Send():void
	{
		let buf = GeneralMes.CSLoginBegan.encode(this.msg).finish();
		super.Send(buf);
	}
}


}
