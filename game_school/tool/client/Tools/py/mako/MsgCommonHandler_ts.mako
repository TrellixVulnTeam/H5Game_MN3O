	export class ${class_name}
	{
		public static HandleMsg(_msg:any):void
		{
			let msg:GeneralMes.${msg_name} = _msg as GeneralMes.${msg_name}
			Client${class_name}.HandleMsg(msg);
		}
	}

