var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var ReadStream = (function () {
    function ReadStream(data) {
        this.mByteBuffer = null;
        this.mByteBuffer = data;
        this.mByteBuffer.position = 0;
        this.mByteBuffer.endian = "littleEndian";
    }
    ReadStream.prototype.showBytes = function (bytes) {
        var s = "";
        bytes.position = 0;
        while (bytes.bytesAvailable) {
            s += "0x" + bytes.readByte().toString(16) + " ";
        }
        if (s.length > 0)
            s = s.substr(0, s.length - 1);
        console.log(s);
    };
    ReadStream.prototype.ReadInt = function () {
        try {
            var reInt = this.mByteBuffer.readInt();
        }
        catch (error) {
            console.log("ReadInt:", error);
        }
        //	 console.log( "ReadInt SOI:", reInt.toString() );
        return reInt;
    };
    ReadStream.prototype.ReadString = function () {
        var len = this.ReadShort();
        if (len < 0 || len > this.mByteBuffer.bytesAvailable)
            return null;
        try {
            var reStr = this.mByteBuffer.readUTFBytes(len);
        }
        catch (error) {
            console.log("ReadString:", error);
        }
        // console.log( "ReadString SOI:", reStr );
        return reStr;
    };
    ReadStream.prototype.ReadShort = function () {
        try {
            var reNum = this.mByteBuffer.readShort();
        }
        catch (error) {
            console.log("ReadShort:", error);
        }
        //console.log( "ReadShort SOI:", reNum.toString() );
        return reNum;
    };
    ReadStream.prototype.ReadBool = function () {
        try {
            var reBool = this.mByteBuffer.readBoolean();
        }
        catch (error) {
            console.log("ReadShort:", error);
        }
        //console.log( "ReadBool SOI:", reBool.toString() );
        return reBool;
    };
    ReadStream.prototype.ReadFloat = function () {
        try {
            var retFloat = this.mByteBuffer.readFloat();
        }
        catch (error) {
            console.log("ReadFloat:", error);
        }
        //console.log( "ReadFloat SOI:", retFloat.toString() );
        return retFloat;
    };
    ReadStream.prototype.ReadDouble = function () {
        try {
            var retDouble = this.mByteBuffer.readDouble();
        }
        catch (error) {
            console.log("ReadDouble:", error);
        }
        //console.log( "ReadDouble SOI:", retDouble.toString() );
        return retDouble;
    };
    return ReadStream;
}());
__reflect(ReadStream.prototype, "ReadStream");
//# sourceMappingURL=ReadStream.js.map