class ReadStream {

 private  mByteBuffer:egret.ByteArray = null;

	public constructor(data:egret.ByteArray) {
			this.mByteBuffer=data;
			this.mByteBuffer.position=0;
			this.mByteBuffer.endian="littleEndian";
	}

 showBytes(bytes:egret.ByteArray):void  
 {  
    var s:String = "";  
    bytes.position = 0;  
    while (bytes.bytesAvailable)  
    {  
        s += "0x" + bytes.readByte().toString(16) + " ";  
    }  
    if (s.length > 0) s = s.substr(0, s.length - 1);  
	 console.log(s);
  }  

public  ReadInt():number
{
	 try {
		var reInt:number=this.mByteBuffer.readInt();
	 } catch (error) {
		 console.log("ReadInt:",error);
	 }
//	 console.log( "ReadInt SOI:", reInt.toString() );
	return reInt;
}

public ReadString(): string
{
 	var len:number=	this.ReadShort();
	 if(len<0||len>this.mByteBuffer.bytesAvailable) return null;
	 try {
		var reStr:string=	this.mByteBuffer.readUTFBytes(len)
	 } catch (error) {
		 console.log( "ReadString:", error);
	 }	
	// console.log( "ReadString SOI:", reStr );
	return reStr;
}

public ReadShort():number
{
try {
	var reNum:number =this.mByteBuffer.readShort();
} catch (error) {
	console.log("ReadShort:",error);
}
//console.log( "ReadShort SOI:", reNum.toString() );
return reNum;
}

public ReadBool():boolean
{
try {
	var reBool:boolean =this.mByteBuffer.readBoolean();
} catch (error) {
	console.log("ReadShort:",error);
}
//console.log( "ReadBool SOI:", reBool.toString() );
return reBool;
}

public  ReadFloat():number
{
try {
	var retFloat:number =this.mByteBuffer.readFloat();
} catch (error) {
	console.log("ReadFloat:",error);
}
//console.log( "ReadFloat SOI:", retFloat.toString() );
return retFloat;
}

public  ReadDouble():number
{
try {
	var retDouble:number =this.mByteBuffer.readDouble();
} catch (error) {
	console.log("ReadDouble:",error);
}
//console.log( "ReadDouble SOI:", retDouble.toString() );
return retDouble;
}


}