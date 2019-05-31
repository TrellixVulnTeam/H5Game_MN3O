var $protobuf = window.protobuf;
$protobuf.roots.default=window;
// Common aliases
var $Reader = $protobuf.Reader, $Writer = $protobuf.Writer, $util = $protobuf.util;

// Exported root namespace
var $root = $protobuf.roots["default"] || ($protobuf.roots["default"] = {});

$root.GeneralMes = (function() {

    /**
     * Namespace GeneralMes.
     * @exports GeneralMes
     * @namespace
     */
    var GeneralMes = {};

    GeneralMes.STencentUserInfo = (function() {

        /**
         * Properties of a STencentUserInfo.
         * @memberof GeneralMes
         * @interface ISTencentUserInfo
         * @property {string} platform STencentUserInfo platform
         * @property {boolean} isBlueVip STencentUserInfo isBlueVip
         * @property {boolean} isBlueYearVip STencentUserInfo isBlueYearVip
         * @property {boolean} isSuperBlueVip STencentUserInfo isSuperBlueVip
         * @property {number} blueVipLevel STencentUserInfo blueVipLevel
         * @property {boolean} isYellowVip STencentUserInfo isYellowVip
         * @property {boolean} isYellowYearVip STencentUserInfo isYellowYearVip
         * @property {boolean} isSuperYellowVip STencentUserInfo isSuperYellowVip
         * @property {number} yellowVipLevel STencentUserInfo yellowVipLevel
         * @property {number} tgpLevel STencentUserInfo tgpLevel
         */

        /**
         * Constructs a new STencentUserInfo.
         * @memberof GeneralMes
         * @classdesc Represents a STencentUserInfo.
         * @implements ISTencentUserInfo
         * @constructor
         * @param {GeneralMes.ISTencentUserInfo=} [properties] Properties to set
         */
        function STencentUserInfo(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * STencentUserInfo platform.
         * @member {string} platform
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.platform = "";

        /**
         * STencentUserInfo isBlueVip.
         * @member {boolean} isBlueVip
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.isBlueVip = false;

        /**
         * STencentUserInfo isBlueYearVip.
         * @member {boolean} isBlueYearVip
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.isBlueYearVip = false;

        /**
         * STencentUserInfo isSuperBlueVip.
         * @member {boolean} isSuperBlueVip
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.isSuperBlueVip = false;

        /**
         * STencentUserInfo blueVipLevel.
         * @member {number} blueVipLevel
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.blueVipLevel = 0;

        /**
         * STencentUserInfo isYellowVip.
         * @member {boolean} isYellowVip
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.isYellowVip = false;

        /**
         * STencentUserInfo isYellowYearVip.
         * @member {boolean} isYellowYearVip
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.isYellowYearVip = false;

        /**
         * STencentUserInfo isSuperYellowVip.
         * @member {boolean} isSuperYellowVip
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.isSuperYellowVip = false;

        /**
         * STencentUserInfo yellowVipLevel.
         * @member {number} yellowVipLevel
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.yellowVipLevel = 0;

        /**
         * STencentUserInfo tgpLevel.
         * @member {number} tgpLevel
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         */
        STencentUserInfo.prototype.tgpLevel = 0;

        /**
         * Creates a new STencentUserInfo instance using the specified properties.
         * @function create
         * @memberof GeneralMes.STencentUserInfo
         * @static
         * @param {GeneralMes.ISTencentUserInfo=} [properties] Properties to set
         * @returns {GeneralMes.STencentUserInfo} STencentUserInfo instance
         */
        STencentUserInfo.create = function create(properties) {
            return new STencentUserInfo(properties);
        };

        /**
         * Encodes the specified STencentUserInfo message. Does not implicitly {@link GeneralMes.STencentUserInfo.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.STencentUserInfo
         * @static
         * @param {GeneralMes.ISTencentUserInfo} message STencentUserInfo message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        STencentUserInfo.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 2 =*/10).string(message.platform);
            writer.uint32(/* id 2, wireType 0 =*/16).bool(message.isBlueVip);
            writer.uint32(/* id 3, wireType 0 =*/24).bool(message.isBlueYearVip);
            writer.uint32(/* id 4, wireType 0 =*/32).bool(message.isSuperBlueVip);
            writer.uint32(/* id 5, wireType 0 =*/40).int32(message.blueVipLevel);
            writer.uint32(/* id 6, wireType 0 =*/48).bool(message.isYellowVip);
            writer.uint32(/* id 7, wireType 0 =*/56).bool(message.isYellowYearVip);
            writer.uint32(/* id 8, wireType 0 =*/64).bool(message.isSuperYellowVip);
            writer.uint32(/* id 9, wireType 0 =*/72).int32(message.yellowVipLevel);
            writer.uint32(/* id 10, wireType 0 =*/80).int32(message.tgpLevel);
            return writer;
        };

        /**
         * Encodes the specified STencentUserInfo message, length delimited. Does not implicitly {@link GeneralMes.STencentUserInfo.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.STencentUserInfo
         * @static
         * @param {GeneralMes.ISTencentUserInfo} message STencentUserInfo message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        STencentUserInfo.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a STencentUserInfo message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.STencentUserInfo
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.STencentUserInfo} STencentUserInfo
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        STencentUserInfo.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.STencentUserInfo();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.platform = reader.string();
                    break;
                case 2:
                    message.isBlueVip = reader.bool();
                    break;
                case 3:
                    message.isBlueYearVip = reader.bool();
                    break;
                case 4:
                    message.isSuperBlueVip = reader.bool();
                    break;
                case 5:
                    message.blueVipLevel = reader.int32();
                    break;
                case 6:
                    message.isYellowVip = reader.bool();
                    break;
                case 7:
                    message.isYellowYearVip = reader.bool();
                    break;
                case 8:
                    message.isSuperYellowVip = reader.bool();
                    break;
                case 9:
                    message.yellowVipLevel = reader.int32();
                    break;
                case 10:
                    message.tgpLevel = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("platform"))
                throw $util.ProtocolError("missing required 'platform'", { instance: message });
            if (!message.hasOwnProperty("isBlueVip"))
                throw $util.ProtocolError("missing required 'isBlueVip'", { instance: message });
            if (!message.hasOwnProperty("isBlueYearVip"))
                throw $util.ProtocolError("missing required 'isBlueYearVip'", { instance: message });
            if (!message.hasOwnProperty("isSuperBlueVip"))
                throw $util.ProtocolError("missing required 'isSuperBlueVip'", { instance: message });
            if (!message.hasOwnProperty("blueVipLevel"))
                throw $util.ProtocolError("missing required 'blueVipLevel'", { instance: message });
            if (!message.hasOwnProperty("isYellowVip"))
                throw $util.ProtocolError("missing required 'isYellowVip'", { instance: message });
            if (!message.hasOwnProperty("isYellowYearVip"))
                throw $util.ProtocolError("missing required 'isYellowYearVip'", { instance: message });
            if (!message.hasOwnProperty("isSuperYellowVip"))
                throw $util.ProtocolError("missing required 'isSuperYellowVip'", { instance: message });
            if (!message.hasOwnProperty("yellowVipLevel"))
                throw $util.ProtocolError("missing required 'yellowVipLevel'", { instance: message });
            if (!message.hasOwnProperty("tgpLevel"))
                throw $util.ProtocolError("missing required 'tgpLevel'", { instance: message });
            return message;
        };

        /**
         * Decodes a STencentUserInfo message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.STencentUserInfo
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.STencentUserInfo} STencentUserInfo
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        STencentUserInfo.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a STencentUserInfo message.
         * @function verify
         * @memberof GeneralMes.STencentUserInfo
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        STencentUserInfo.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isString(message.platform))
                return "platform: string expected";
            if (typeof message.isBlueVip !== "boolean")
                return "isBlueVip: boolean expected";
            if (typeof message.isBlueYearVip !== "boolean")
                return "isBlueYearVip: boolean expected";
            if (typeof message.isSuperBlueVip !== "boolean")
                return "isSuperBlueVip: boolean expected";
            if (!$util.isInteger(message.blueVipLevel))
                return "blueVipLevel: integer expected";
            if (typeof message.isYellowVip !== "boolean")
                return "isYellowVip: boolean expected";
            if (typeof message.isYellowYearVip !== "boolean")
                return "isYellowYearVip: boolean expected";
            if (typeof message.isSuperYellowVip !== "boolean")
                return "isSuperYellowVip: boolean expected";
            if (!$util.isInteger(message.yellowVipLevel))
                return "yellowVipLevel: integer expected";
            if (!$util.isInteger(message.tgpLevel))
                return "tgpLevel: integer expected";
            return null;
        };

        /**
         * Creates a STencentUserInfo message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.STencentUserInfo
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.STencentUserInfo} STencentUserInfo
         */
        STencentUserInfo.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.STencentUserInfo)
                return object;
            var message = new $root.GeneralMes.STencentUserInfo();
            if (object.platform != null)
                message.platform = String(object.platform);
            if (object.isBlueVip != null)
                message.isBlueVip = Boolean(object.isBlueVip);
            if (object.isBlueYearVip != null)
                message.isBlueYearVip = Boolean(object.isBlueYearVip);
            if (object.isSuperBlueVip != null)
                message.isSuperBlueVip = Boolean(object.isSuperBlueVip);
            if (object.blueVipLevel != null)
                message.blueVipLevel = object.blueVipLevel | 0;
            if (object.isYellowVip != null)
                message.isYellowVip = Boolean(object.isYellowVip);
            if (object.isYellowYearVip != null)
                message.isYellowYearVip = Boolean(object.isYellowYearVip);
            if (object.isSuperYellowVip != null)
                message.isSuperYellowVip = Boolean(object.isSuperYellowVip);
            if (object.yellowVipLevel != null)
                message.yellowVipLevel = object.yellowVipLevel | 0;
            if (object.tgpLevel != null)
                message.tgpLevel = object.tgpLevel | 0;
            return message;
        };

        /**
         * Creates a plain object from a STencentUserInfo message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.STencentUserInfo
         * @static
         * @param {GeneralMes.STencentUserInfo} message STencentUserInfo
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        STencentUserInfo.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.platform = "";
                object.isBlueVip = false;
                object.isBlueYearVip = false;
                object.isSuperBlueVip = false;
                object.blueVipLevel = 0;
                object.isYellowVip = false;
                object.isYellowYearVip = false;
                object.isSuperYellowVip = false;
                object.yellowVipLevel = 0;
                object.tgpLevel = 0;
            }
            if (message.platform != null && message.hasOwnProperty("platform"))
                object.platform = message.platform;
            if (message.isBlueVip != null && message.hasOwnProperty("isBlueVip"))
                object.isBlueVip = message.isBlueVip;
            if (message.isBlueYearVip != null && message.hasOwnProperty("isBlueYearVip"))
                object.isBlueYearVip = message.isBlueYearVip;
            if (message.isSuperBlueVip != null && message.hasOwnProperty("isSuperBlueVip"))
                object.isSuperBlueVip = message.isSuperBlueVip;
            if (message.blueVipLevel != null && message.hasOwnProperty("blueVipLevel"))
                object.blueVipLevel = message.blueVipLevel;
            if (message.isYellowVip != null && message.hasOwnProperty("isYellowVip"))
                object.isYellowVip = message.isYellowVip;
            if (message.isYellowYearVip != null && message.hasOwnProperty("isYellowYearVip"))
                object.isYellowYearVip = message.isYellowYearVip;
            if (message.isSuperYellowVip != null && message.hasOwnProperty("isSuperYellowVip"))
                object.isSuperYellowVip = message.isSuperYellowVip;
            if (message.yellowVipLevel != null && message.hasOwnProperty("yellowVipLevel"))
                object.yellowVipLevel = message.yellowVipLevel;
            if (message.tgpLevel != null && message.hasOwnProperty("tgpLevel"))
                object.tgpLevel = message.tgpLevel;
            return object;
        };

        /**
         * Converts this STencentUserInfo to JSON.
         * @function toJSON
         * @memberof GeneralMes.STencentUserInfo
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        STencentUserInfo.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return STencentUserInfo;
    })();

    GeneralMes.SMagicIntensify = (function() {

        /**
         * Properties of a SMagicIntensify.
         * @memberof GeneralMes
         * @interface ISMagicIntensify
         * @property {number} LevelPencent SMagicIntensify LevelPencent
         * @property {number} LevelValue SMagicIntensify LevelValue
         * @property {number} LevelAddition SMagicIntensify LevelAddition
         */

        /**
         * Constructs a new SMagicIntensify.
         * @memberof GeneralMes
         * @classdesc Represents a SMagicIntensify.
         * @implements ISMagicIntensify
         * @constructor
         * @param {GeneralMes.ISMagicIntensify=} [properties] Properties to set
         */
        function SMagicIntensify(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SMagicIntensify LevelPencent.
         * @member {number} LevelPencent
         * @memberof GeneralMes.SMagicIntensify
         * @instance
         */
        SMagicIntensify.prototype.LevelPencent = 0;

        /**
         * SMagicIntensify LevelValue.
         * @member {number} LevelValue
         * @memberof GeneralMes.SMagicIntensify
         * @instance
         */
        SMagicIntensify.prototype.LevelValue = 0;

        /**
         * SMagicIntensify LevelAddition.
         * @member {number} LevelAddition
         * @memberof GeneralMes.SMagicIntensify
         * @instance
         */
        SMagicIntensify.prototype.LevelAddition = 0;

        /**
         * Creates a new SMagicIntensify instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SMagicIntensify
         * @static
         * @param {GeneralMes.ISMagicIntensify=} [properties] Properties to set
         * @returns {GeneralMes.SMagicIntensify} SMagicIntensify instance
         */
        SMagicIntensify.create = function create(properties) {
            return new SMagicIntensify(properties);
        };

        /**
         * Encodes the specified SMagicIntensify message. Does not implicitly {@link GeneralMes.SMagicIntensify.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SMagicIntensify
         * @static
         * @param {GeneralMes.ISMagicIntensify} message SMagicIntensify message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SMagicIntensify.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.LevelPencent);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.LevelValue);
            writer.uint32(/* id 3, wireType 0 =*/24).int32(message.LevelAddition);
            return writer;
        };

        /**
         * Encodes the specified SMagicIntensify message, length delimited. Does not implicitly {@link GeneralMes.SMagicIntensify.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SMagicIntensify
         * @static
         * @param {GeneralMes.ISMagicIntensify} message SMagicIntensify message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SMagicIntensify.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SMagicIntensify message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SMagicIntensify
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SMagicIntensify} SMagicIntensify
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SMagicIntensify.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SMagicIntensify();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.LevelPencent = reader.int32();
                    break;
                case 2:
                    message.LevelValue = reader.int32();
                    break;
                case 3:
                    message.LevelAddition = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("LevelPencent"))
                throw $util.ProtocolError("missing required 'LevelPencent'", { instance: message });
            if (!message.hasOwnProperty("LevelValue"))
                throw $util.ProtocolError("missing required 'LevelValue'", { instance: message });
            if (!message.hasOwnProperty("LevelAddition"))
                throw $util.ProtocolError("missing required 'LevelAddition'", { instance: message });
            return message;
        };

        /**
         * Decodes a SMagicIntensify message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SMagicIntensify
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SMagicIntensify} SMagicIntensify
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SMagicIntensify.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SMagicIntensify message.
         * @function verify
         * @memberof GeneralMes.SMagicIntensify
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SMagicIntensify.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.LevelPencent))
                return "LevelPencent: integer expected";
            if (!$util.isInteger(message.LevelValue))
                return "LevelValue: integer expected";
            if (!$util.isInteger(message.LevelAddition))
                return "LevelAddition: integer expected";
            return null;
        };

        /**
         * Creates a SMagicIntensify message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SMagicIntensify
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SMagicIntensify} SMagicIntensify
         */
        SMagicIntensify.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SMagicIntensify)
                return object;
            var message = new $root.GeneralMes.SMagicIntensify();
            if (object.LevelPencent != null)
                message.LevelPencent = object.LevelPencent | 0;
            if (object.LevelValue != null)
                message.LevelValue = object.LevelValue | 0;
            if (object.LevelAddition != null)
                message.LevelAddition = object.LevelAddition | 0;
            return message;
        };

        /**
         * Creates a plain object from a SMagicIntensify message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SMagicIntensify
         * @static
         * @param {GeneralMes.SMagicIntensify} message SMagicIntensify
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SMagicIntensify.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.LevelPencent = 0;
                object.LevelValue = 0;
                object.LevelAddition = 0;
            }
            if (message.LevelPencent != null && message.hasOwnProperty("LevelPencent"))
                object.LevelPencent = message.LevelPencent;
            if (message.LevelValue != null && message.hasOwnProperty("LevelValue"))
                object.LevelValue = message.LevelValue;
            if (message.LevelAddition != null && message.hasOwnProperty("LevelAddition"))
                object.LevelAddition = message.LevelAddition;
            return object;
        };

        /**
         * Converts this SMagicIntensify to JSON.
         * @function toJSON
         * @memberof GeneralMes.SMagicIntensify
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SMagicIntensify.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SMagicIntensify;
    })();

    GeneralMes.SMagicType = (function() {

        /**
         * Properties of a SMagicType.
         * @memberof GeneralMes
         * @interface ISMagicType
         * @property {number} id SMagicType id
         * @property {number} loc SMagicType loc
         * @property {GeneralMes.ISMagicIntensify} intensify SMagicType intensify
         * @property {number|Long} exp SMagicType exp
         * @property {number} level SMagicType level
         * @property {number} openLevel SMagicType openLevel
         * @property {number|Long} combatPoint SMagicType combatPoint
         */

        /**
         * Constructs a new SMagicType.
         * @memberof GeneralMes
         * @classdesc Represents a SMagicType.
         * @implements ISMagicType
         * @constructor
         * @param {GeneralMes.ISMagicType=} [properties] Properties to set
         */
        function SMagicType(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SMagicType id.
         * @member {number} id
         * @memberof GeneralMes.SMagicType
         * @instance
         */
        SMagicType.prototype.id = 0;

        /**
         * SMagicType loc.
         * @member {number} loc
         * @memberof GeneralMes.SMagicType
         * @instance
         */
        SMagicType.prototype.loc = 0;

        /**
         * SMagicType intensify.
         * @member {GeneralMes.ISMagicIntensify} intensify
         * @memberof GeneralMes.SMagicType
         * @instance
         */
        SMagicType.prototype.intensify = null;

        /**
         * SMagicType exp.
         * @member {number|Long} exp
         * @memberof GeneralMes.SMagicType
         * @instance
         */
        SMagicType.prototype.exp = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SMagicType level.
         * @member {number} level
         * @memberof GeneralMes.SMagicType
         * @instance
         */
        SMagicType.prototype.level = 0;

        /**
         * SMagicType openLevel.
         * @member {number} openLevel
         * @memberof GeneralMes.SMagicType
         * @instance
         */
        SMagicType.prototype.openLevel = 0;

        /**
         * SMagicType combatPoint.
         * @member {number|Long} combatPoint
         * @memberof GeneralMes.SMagicType
         * @instance
         */
        SMagicType.prototype.combatPoint = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * Creates a new SMagicType instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SMagicType
         * @static
         * @param {GeneralMes.ISMagicType=} [properties] Properties to set
         * @returns {GeneralMes.SMagicType} SMagicType instance
         */
        SMagicType.create = function create(properties) {
            return new SMagicType(properties);
        };

        /**
         * Encodes the specified SMagicType message. Does not implicitly {@link GeneralMes.SMagicType.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SMagicType
         * @static
         * @param {GeneralMes.ISMagicType} message SMagicType message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SMagicType.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.id);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.loc);
            $root.GeneralMes.SMagicIntensify.encode(message.intensify, writer.uint32(/* id 3, wireType 2 =*/26).fork()).ldelim();
            writer.uint32(/* id 4, wireType 0 =*/32).int64(message.exp);
            writer.uint32(/* id 5, wireType 0 =*/40).int32(message.level);
            writer.uint32(/* id 6, wireType 0 =*/48).int32(message.openLevel);
            writer.uint32(/* id 7, wireType 0 =*/56).int64(message.combatPoint);
            return writer;
        };

        /**
         * Encodes the specified SMagicType message, length delimited. Does not implicitly {@link GeneralMes.SMagicType.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SMagicType
         * @static
         * @param {GeneralMes.ISMagicType} message SMagicType message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SMagicType.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SMagicType message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SMagicType
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SMagicType} SMagicType
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SMagicType.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SMagicType();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.id = reader.int32();
                    break;
                case 2:
                    message.loc = reader.int32();
                    break;
                case 3:
                    message.intensify = $root.GeneralMes.SMagicIntensify.decode(reader, reader.uint32());
                    break;
                case 4:
                    message.exp = reader.int64();
                    break;
                case 5:
                    message.level = reader.int32();
                    break;
                case 6:
                    message.openLevel = reader.int32();
                    break;
                case 7:
                    message.combatPoint = reader.int64();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("id"))
                throw $util.ProtocolError("missing required 'id'", { instance: message });
            if (!message.hasOwnProperty("loc"))
                throw $util.ProtocolError("missing required 'loc'", { instance: message });
            if (!message.hasOwnProperty("intensify"))
                throw $util.ProtocolError("missing required 'intensify'", { instance: message });
            if (!message.hasOwnProperty("exp"))
                throw $util.ProtocolError("missing required 'exp'", { instance: message });
            if (!message.hasOwnProperty("level"))
                throw $util.ProtocolError("missing required 'level'", { instance: message });
            if (!message.hasOwnProperty("openLevel"))
                throw $util.ProtocolError("missing required 'openLevel'", { instance: message });
            if (!message.hasOwnProperty("combatPoint"))
                throw $util.ProtocolError("missing required 'combatPoint'", { instance: message });
            return message;
        };

        /**
         * Decodes a SMagicType message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SMagicType
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SMagicType} SMagicType
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SMagicType.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SMagicType message.
         * @function verify
         * @memberof GeneralMes.SMagicType
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SMagicType.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.id))
                return "id: integer expected";
            if (!$util.isInteger(message.loc))
                return "loc: integer expected";
            {
                var error = $root.GeneralMes.SMagicIntensify.verify(message.intensify);
                if (error)
                    return "intensify." + error;
            }
            if (!$util.isInteger(message.exp) && !(message.exp && $util.isInteger(message.exp.low) && $util.isInteger(message.exp.high)))
                return "exp: integer|Long expected";
            if (!$util.isInteger(message.level))
                return "level: integer expected";
            if (!$util.isInteger(message.openLevel))
                return "openLevel: integer expected";
            if (!$util.isInteger(message.combatPoint) && !(message.combatPoint && $util.isInteger(message.combatPoint.low) && $util.isInteger(message.combatPoint.high)))
                return "combatPoint: integer|Long expected";
            return null;
        };

        /**
         * Creates a SMagicType message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SMagicType
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SMagicType} SMagicType
         */
        SMagicType.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SMagicType)
                return object;
            var message = new $root.GeneralMes.SMagicType();
            if (object.id != null)
                message.id = object.id | 0;
            if (object.loc != null)
                message.loc = object.loc | 0;
            if (object.intensify != null) {
                if (typeof object.intensify !== "object")
                    throw TypeError(".GeneralMes.SMagicType.intensify: object expected");
                message.intensify = $root.GeneralMes.SMagicIntensify.fromObject(object.intensify);
            }
            if (object.exp != null)
                if ($util.Long)
                    (message.exp = $util.Long.fromValue(object.exp)).unsigned = false;
                else if (typeof object.exp === "string")
                    message.exp = parseInt(object.exp, 10);
                else if (typeof object.exp === "number")
                    message.exp = object.exp;
                else if (typeof object.exp === "object")
                    message.exp = new $util.LongBits(object.exp.low >>> 0, object.exp.high >>> 0).toNumber();
            if (object.level != null)
                message.level = object.level | 0;
            if (object.openLevel != null)
                message.openLevel = object.openLevel | 0;
            if (object.combatPoint != null)
                if ($util.Long)
                    (message.combatPoint = $util.Long.fromValue(object.combatPoint)).unsigned = false;
                else if (typeof object.combatPoint === "string")
                    message.combatPoint = parseInt(object.combatPoint, 10);
                else if (typeof object.combatPoint === "number")
                    message.combatPoint = object.combatPoint;
                else if (typeof object.combatPoint === "object")
                    message.combatPoint = new $util.LongBits(object.combatPoint.low >>> 0, object.combatPoint.high >>> 0).toNumber();
            return message;
        };

        /**
         * Creates a plain object from a SMagicType message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SMagicType
         * @static
         * @param {GeneralMes.SMagicType} message SMagicType
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SMagicType.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.id = 0;
                object.loc = 0;
                object.intensify = null;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.exp = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.exp = options.longs === String ? "0" : 0;
                object.level = 0;
                object.openLevel = 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.combatPoint = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.combatPoint = options.longs === String ? "0" : 0;
            }
            if (message.id != null && message.hasOwnProperty("id"))
                object.id = message.id;
            if (message.loc != null && message.hasOwnProperty("loc"))
                object.loc = message.loc;
            if (message.intensify != null && message.hasOwnProperty("intensify"))
                object.intensify = $root.GeneralMes.SMagicIntensify.toObject(message.intensify, options);
            if (message.exp != null && message.hasOwnProperty("exp"))
                if (typeof message.exp === "number")
                    object.exp = options.longs === String ? String(message.exp) : message.exp;
                else
                    object.exp = options.longs === String ? $util.Long.prototype.toString.call(message.exp) : options.longs === Number ? new $util.LongBits(message.exp.low >>> 0, message.exp.high >>> 0).toNumber() : message.exp;
            if (message.level != null && message.hasOwnProperty("level"))
                object.level = message.level;
            if (message.openLevel != null && message.hasOwnProperty("openLevel"))
                object.openLevel = message.openLevel;
            if (message.combatPoint != null && message.hasOwnProperty("combatPoint"))
                if (typeof message.combatPoint === "number")
                    object.combatPoint = options.longs === String ? String(message.combatPoint) : message.combatPoint;
                else
                    object.combatPoint = options.longs === String ? $util.Long.prototype.toString.call(message.combatPoint) : options.longs === Number ? new $util.LongBits(message.combatPoint.low >>> 0, message.combatPoint.high >>> 0).toNumber() : message.combatPoint;
            return object;
        };

        /**
         * Converts this SMagicType to JSON.
         * @function toJSON
         * @memberof GeneralMes.SMagicType
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SMagicType.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SMagicType;
    })();

    GeneralMes.SVector3 = (function() {

        /**
         * Properties of a SVector3.
         * @memberof GeneralMes
         * @interface ISVector3
         * @property {number} x SVector3 x
         * @property {number} y SVector3 y
         * @property {number} z SVector3 z
         */

        /**
         * Constructs a new SVector3.
         * @memberof GeneralMes
         * @classdesc Represents a SVector3.
         * @implements ISVector3
         * @constructor
         * @param {GeneralMes.ISVector3=} [properties] Properties to set
         */
        function SVector3(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SVector3 x.
         * @member {number} x
         * @memberof GeneralMes.SVector3
         * @instance
         */
        SVector3.prototype.x = 0;

        /**
         * SVector3 y.
         * @member {number} y
         * @memberof GeneralMes.SVector3
         * @instance
         */
        SVector3.prototype.y = 0;

        /**
         * SVector3 z.
         * @member {number} z
         * @memberof GeneralMes.SVector3
         * @instance
         */
        SVector3.prototype.z = 0;

        /**
         * Creates a new SVector3 instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SVector3
         * @static
         * @param {GeneralMes.ISVector3=} [properties] Properties to set
         * @returns {GeneralMes.SVector3} SVector3 instance
         */
        SVector3.create = function create(properties) {
            return new SVector3(properties);
        };

        /**
         * Encodes the specified SVector3 message. Does not implicitly {@link GeneralMes.SVector3.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SVector3
         * @static
         * @param {GeneralMes.ISVector3} message SVector3 message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SVector3.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 5 =*/13).float(message.x);
            writer.uint32(/* id 2, wireType 5 =*/21).float(message.y);
            writer.uint32(/* id 3, wireType 5 =*/29).float(message.z);
            return writer;
        };

        /**
         * Encodes the specified SVector3 message, length delimited. Does not implicitly {@link GeneralMes.SVector3.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SVector3
         * @static
         * @param {GeneralMes.ISVector3} message SVector3 message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SVector3.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SVector3 message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SVector3
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SVector3} SVector3
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SVector3.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SVector3();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.x = reader.float();
                    break;
                case 2:
                    message.y = reader.float();
                    break;
                case 3:
                    message.z = reader.float();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("x"))
                throw $util.ProtocolError("missing required 'x'", { instance: message });
            if (!message.hasOwnProperty("y"))
                throw $util.ProtocolError("missing required 'y'", { instance: message });
            if (!message.hasOwnProperty("z"))
                throw $util.ProtocolError("missing required 'z'", { instance: message });
            return message;
        };

        /**
         * Decodes a SVector3 message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SVector3
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SVector3} SVector3
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SVector3.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SVector3 message.
         * @function verify
         * @memberof GeneralMes.SVector3
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SVector3.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (typeof message.x !== "number")
                return "x: number expected";
            if (typeof message.y !== "number")
                return "y: number expected";
            if (typeof message.z !== "number")
                return "z: number expected";
            return null;
        };

        /**
         * Creates a SVector3 message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SVector3
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SVector3} SVector3
         */
        SVector3.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SVector3)
                return object;
            var message = new $root.GeneralMes.SVector3();
            if (object.x != null)
                message.x = Number(object.x);
            if (object.y != null)
                message.y = Number(object.y);
            if (object.z != null)
                message.z = Number(object.z);
            return message;
        };

        /**
         * Creates a plain object from a SVector3 message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SVector3
         * @static
         * @param {GeneralMes.SVector3} message SVector3
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SVector3.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.x = 0;
                object.y = 0;
                object.z = 0;
            }
            if (message.x != null && message.hasOwnProperty("x"))
                object.x = options.json && !isFinite(message.x) ? String(message.x) : message.x;
            if (message.y != null && message.hasOwnProperty("y"))
                object.y = options.json && !isFinite(message.y) ? String(message.y) : message.y;
            if (message.z != null && message.hasOwnProperty("z"))
                object.z = options.json && !isFinite(message.z) ? String(message.z) : message.z;
            return object;
        };

        /**
         * Converts this SVector3 to JSON.
         * @function toJSON
         * @memberof GeneralMes.SVector3
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SVector3.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SVector3;
    })();

    GeneralMes.SAura = (function() {

        /**
         * Properties of a SAura.
         * @memberof GeneralMes
         * @interface ISAura
         * @property {number|Long} id SAura id
         * @property {number|Long} caster SAura caster
         * @property {number|Long} owner SAura owner
         * @property {number} type SAura type
         * @property {number} overlapNum SAura overlapNum
         * @property {number|Long} duration SAura duration
         * @property {number} param SAura param
         * @property {number} level SAura level
         */

        /**
         * Constructs a new SAura.
         * @memberof GeneralMes
         * @classdesc Represents a SAura.
         * @implements ISAura
         * @constructor
         * @param {GeneralMes.ISAura=} [properties] Properties to set
         */
        function SAura(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SAura id.
         * @member {number|Long} id
         * @memberof GeneralMes.SAura
         * @instance
         */
        SAura.prototype.id = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SAura caster.
         * @member {number|Long} caster
         * @memberof GeneralMes.SAura
         * @instance
         */
        SAura.prototype.caster = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SAura owner.
         * @member {number|Long} owner
         * @memberof GeneralMes.SAura
         * @instance
         */
        SAura.prototype.owner = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SAura type.
         * @member {number} type
         * @memberof GeneralMes.SAura
         * @instance
         */
        SAura.prototype.type = 0;

        /**
         * SAura overlapNum.
         * @member {number} overlapNum
         * @memberof GeneralMes.SAura
         * @instance
         */
        SAura.prototype.overlapNum = 0;

        /**
         * SAura duration.
         * @member {number|Long} duration
         * @memberof GeneralMes.SAura
         * @instance
         */
        SAura.prototype.duration = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SAura param.
         * @member {number} param
         * @memberof GeneralMes.SAura
         * @instance
         */
        SAura.prototype.param = 0;

        /**
         * SAura level.
         * @member {number} level
         * @memberof GeneralMes.SAura
         * @instance
         */
        SAura.prototype.level = 0;

        /**
         * Creates a new SAura instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SAura
         * @static
         * @param {GeneralMes.ISAura=} [properties] Properties to set
         * @returns {GeneralMes.SAura} SAura instance
         */
        SAura.create = function create(properties) {
            return new SAura(properties);
        };

        /**
         * Encodes the specified SAura message. Does not implicitly {@link GeneralMes.SAura.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SAura
         * @static
         * @param {GeneralMes.ISAura} message SAura message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SAura.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.id);
            writer.uint32(/* id 2, wireType 0 =*/16).int64(message.caster);
            writer.uint32(/* id 3, wireType 0 =*/24).int64(message.owner);
            writer.uint32(/* id 5, wireType 0 =*/40).int32(message.type);
            writer.uint32(/* id 6, wireType 0 =*/48).int32(message.overlapNum);
            writer.uint32(/* id 7, wireType 0 =*/56).int64(message.duration);
            writer.uint32(/* id 8, wireType 0 =*/64).int32(message.param);
            writer.uint32(/* id 9, wireType 0 =*/72).int32(message.level);
            return writer;
        };

        /**
         * Encodes the specified SAura message, length delimited. Does not implicitly {@link GeneralMes.SAura.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SAura
         * @static
         * @param {GeneralMes.ISAura} message SAura message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SAura.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SAura message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SAura
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SAura} SAura
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SAura.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SAura();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.id = reader.int64();
                    break;
                case 2:
                    message.caster = reader.int64();
                    break;
                case 3:
                    message.owner = reader.int64();
                    break;
                case 5:
                    message.type = reader.int32();
                    break;
                case 6:
                    message.overlapNum = reader.int32();
                    break;
                case 7:
                    message.duration = reader.int64();
                    break;
                case 8:
                    message.param = reader.int32();
                    break;
                case 9:
                    message.level = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("id"))
                throw $util.ProtocolError("missing required 'id'", { instance: message });
            if (!message.hasOwnProperty("caster"))
                throw $util.ProtocolError("missing required 'caster'", { instance: message });
            if (!message.hasOwnProperty("owner"))
                throw $util.ProtocolError("missing required 'owner'", { instance: message });
            if (!message.hasOwnProperty("type"))
                throw $util.ProtocolError("missing required 'type'", { instance: message });
            if (!message.hasOwnProperty("overlapNum"))
                throw $util.ProtocolError("missing required 'overlapNum'", { instance: message });
            if (!message.hasOwnProperty("duration"))
                throw $util.ProtocolError("missing required 'duration'", { instance: message });
            if (!message.hasOwnProperty("param"))
                throw $util.ProtocolError("missing required 'param'", { instance: message });
            if (!message.hasOwnProperty("level"))
                throw $util.ProtocolError("missing required 'level'", { instance: message });
            return message;
        };

        /**
         * Decodes a SAura message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SAura
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SAura} SAura
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SAura.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SAura message.
         * @function verify
         * @memberof GeneralMes.SAura
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SAura.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.id) && !(message.id && $util.isInteger(message.id.low) && $util.isInteger(message.id.high)))
                return "id: integer|Long expected";
            if (!$util.isInteger(message.caster) && !(message.caster && $util.isInteger(message.caster.low) && $util.isInteger(message.caster.high)))
                return "caster: integer|Long expected";
            if (!$util.isInteger(message.owner) && !(message.owner && $util.isInteger(message.owner.low) && $util.isInteger(message.owner.high)))
                return "owner: integer|Long expected";
            if (!$util.isInteger(message.type))
                return "type: integer expected";
            if (!$util.isInteger(message.overlapNum))
                return "overlapNum: integer expected";
            if (!$util.isInteger(message.duration) && !(message.duration && $util.isInteger(message.duration.low) && $util.isInteger(message.duration.high)))
                return "duration: integer|Long expected";
            if (!$util.isInteger(message.param))
                return "param: integer expected";
            if (!$util.isInteger(message.level))
                return "level: integer expected";
            return null;
        };

        /**
         * Creates a SAura message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SAura
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SAura} SAura
         */
        SAura.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SAura)
                return object;
            var message = new $root.GeneralMes.SAura();
            if (object.id != null)
                if ($util.Long)
                    (message.id = $util.Long.fromValue(object.id)).unsigned = false;
                else if (typeof object.id === "string")
                    message.id = parseInt(object.id, 10);
                else if (typeof object.id === "number")
                    message.id = object.id;
                else if (typeof object.id === "object")
                    message.id = new $util.LongBits(object.id.low >>> 0, object.id.high >>> 0).toNumber();
            if (object.caster != null)
                if ($util.Long)
                    (message.caster = $util.Long.fromValue(object.caster)).unsigned = false;
                else if (typeof object.caster === "string")
                    message.caster = parseInt(object.caster, 10);
                else if (typeof object.caster === "number")
                    message.caster = object.caster;
                else if (typeof object.caster === "object")
                    message.caster = new $util.LongBits(object.caster.low >>> 0, object.caster.high >>> 0).toNumber();
            if (object.owner != null)
                if ($util.Long)
                    (message.owner = $util.Long.fromValue(object.owner)).unsigned = false;
                else if (typeof object.owner === "string")
                    message.owner = parseInt(object.owner, 10);
                else if (typeof object.owner === "number")
                    message.owner = object.owner;
                else if (typeof object.owner === "object")
                    message.owner = new $util.LongBits(object.owner.low >>> 0, object.owner.high >>> 0).toNumber();
            if (object.type != null)
                message.type = object.type | 0;
            if (object.overlapNum != null)
                message.overlapNum = object.overlapNum | 0;
            if (object.duration != null)
                if ($util.Long)
                    (message.duration = $util.Long.fromValue(object.duration)).unsigned = false;
                else if (typeof object.duration === "string")
                    message.duration = parseInt(object.duration, 10);
                else if (typeof object.duration === "number")
                    message.duration = object.duration;
                else if (typeof object.duration === "object")
                    message.duration = new $util.LongBits(object.duration.low >>> 0, object.duration.high >>> 0).toNumber();
            if (object.param != null)
                message.param = object.param | 0;
            if (object.level != null)
                message.level = object.level | 0;
            return message;
        };

        /**
         * Creates a plain object from a SAura message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SAura
         * @static
         * @param {GeneralMes.SAura} message SAura
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SAura.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.id = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.id = options.longs === String ? "0" : 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.caster = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.caster = options.longs === String ? "0" : 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.owner = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.owner = options.longs === String ? "0" : 0;
                object.type = 0;
                object.overlapNum = 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.duration = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.duration = options.longs === String ? "0" : 0;
                object.param = 0;
                object.level = 0;
            }
            if (message.id != null && message.hasOwnProperty("id"))
                if (typeof message.id === "number")
                    object.id = options.longs === String ? String(message.id) : message.id;
                else
                    object.id = options.longs === String ? $util.Long.prototype.toString.call(message.id) : options.longs === Number ? new $util.LongBits(message.id.low >>> 0, message.id.high >>> 0).toNumber() : message.id;
            if (message.caster != null && message.hasOwnProperty("caster"))
                if (typeof message.caster === "number")
                    object.caster = options.longs === String ? String(message.caster) : message.caster;
                else
                    object.caster = options.longs === String ? $util.Long.prototype.toString.call(message.caster) : options.longs === Number ? new $util.LongBits(message.caster.low >>> 0, message.caster.high >>> 0).toNumber() : message.caster;
            if (message.owner != null && message.hasOwnProperty("owner"))
                if (typeof message.owner === "number")
                    object.owner = options.longs === String ? String(message.owner) : message.owner;
                else
                    object.owner = options.longs === String ? $util.Long.prototype.toString.call(message.owner) : options.longs === Number ? new $util.LongBits(message.owner.low >>> 0, message.owner.high >>> 0).toNumber() : message.owner;
            if (message.type != null && message.hasOwnProperty("type"))
                object.type = message.type;
            if (message.overlapNum != null && message.hasOwnProperty("overlapNum"))
                object.overlapNum = message.overlapNum;
            if (message.duration != null && message.hasOwnProperty("duration"))
                if (typeof message.duration === "number")
                    object.duration = options.longs === String ? String(message.duration) : message.duration;
                else
                    object.duration = options.longs === String ? $util.Long.prototype.toString.call(message.duration) : options.longs === Number ? new $util.LongBits(message.duration.low >>> 0, message.duration.high >>> 0).toNumber() : message.duration;
            if (message.param != null && message.hasOwnProperty("param"))
                object.param = message.param;
            if (message.level != null && message.hasOwnProperty("level"))
                object.level = message.level;
            return object;
        };

        /**
         * Converts this SAura to JSON.
         * @function toJSON
         * @memberof GeneralMes.SAura
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SAura.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SAura;
    })();

    GeneralMes.SMotion = (function() {

        /**
         * Properties of a SMotion.
         * @memberof GeneralMes
         * @interface ISMotion
         * @property {number} motionType SMotion motionType
         * @property {number|Long|null} [motionTarget] SMotion motionTarget
         * @property {GeneralMes.ISVector3|null} [motionOrientation] SMotion motionOrientation
         * @property {GeneralMes.ISVector3|null} [motionPosition] SMotion motionPosition
         * @property {Array.<GeneralMes.ISVector3>|null} [motionPath] SMotion motionPath
         * @property {number|null} [param] SMotion param
         */

        /**
         * Constructs a new SMotion.
         * @memberof GeneralMes
         * @classdesc Represents a SMotion.
         * @implements ISMotion
         * @constructor
         * @param {GeneralMes.ISMotion=} [properties] Properties to set
         */
        function SMotion(properties) {
            this.motionPath = [];
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SMotion motionType.
         * @member {number} motionType
         * @memberof GeneralMes.SMotion
         * @instance
         */
        SMotion.prototype.motionType = 0;

        /**
         * SMotion motionTarget.
         * @member {number|Long} motionTarget
         * @memberof GeneralMes.SMotion
         * @instance
         */
        SMotion.prototype.motionTarget = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SMotion motionOrientation.
         * @member {GeneralMes.ISVector3|null|undefined} motionOrientation
         * @memberof GeneralMes.SMotion
         * @instance
         */
        SMotion.prototype.motionOrientation = null;

        /**
         * SMotion motionPosition.
         * @member {GeneralMes.ISVector3|null|undefined} motionPosition
         * @memberof GeneralMes.SMotion
         * @instance
         */
        SMotion.prototype.motionPosition = null;

        /**
         * SMotion motionPath.
         * @member {Array.<GeneralMes.ISVector3>} motionPath
         * @memberof GeneralMes.SMotion
         * @instance
         */
        SMotion.prototype.motionPath = $util.emptyArray;

        /**
         * SMotion param.
         * @member {number} param
         * @memberof GeneralMes.SMotion
         * @instance
         */
        SMotion.prototype.param = 0;

        /**
         * Creates a new SMotion instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SMotion
         * @static
         * @param {GeneralMes.ISMotion=} [properties] Properties to set
         * @returns {GeneralMes.SMotion} SMotion instance
         */
        SMotion.create = function create(properties) {
            return new SMotion(properties);
        };

        /**
         * Encodes the specified SMotion message. Does not implicitly {@link GeneralMes.SMotion.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SMotion
         * @static
         * @param {GeneralMes.ISMotion} message SMotion message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SMotion.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.motionType);
            if (message.motionTarget != null && message.hasOwnProperty("motionTarget"))
                writer.uint32(/* id 2, wireType 0 =*/16).int64(message.motionTarget);
            if (message.motionOrientation != null && message.hasOwnProperty("motionOrientation"))
                $root.GeneralMes.SVector3.encode(message.motionOrientation, writer.uint32(/* id 3, wireType 2 =*/26).fork()).ldelim();
            if (message.motionPosition != null && message.hasOwnProperty("motionPosition"))
                $root.GeneralMes.SVector3.encode(message.motionPosition, writer.uint32(/* id 4, wireType 2 =*/34).fork()).ldelim();
            if (message.motionPath != null && message.motionPath.length)
                for (var i = 0; i < message.motionPath.length; ++i)
                    $root.GeneralMes.SVector3.encode(message.motionPath[i], writer.uint32(/* id 5, wireType 2 =*/42).fork()).ldelim();
            if (message.param != null && message.hasOwnProperty("param"))
                writer.uint32(/* id 6, wireType 5 =*/53).float(message.param);
            return writer;
        };

        /**
         * Encodes the specified SMotion message, length delimited. Does not implicitly {@link GeneralMes.SMotion.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SMotion
         * @static
         * @param {GeneralMes.ISMotion} message SMotion message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SMotion.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SMotion message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SMotion
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SMotion} SMotion
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SMotion.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SMotion();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.motionType = reader.int32();
                    break;
                case 2:
                    message.motionTarget = reader.int64();
                    break;
                case 3:
                    message.motionOrientation = $root.GeneralMes.SVector3.decode(reader, reader.uint32());
                    break;
                case 4:
                    message.motionPosition = $root.GeneralMes.SVector3.decode(reader, reader.uint32());
                    break;
                case 5:
                    if (!(message.motionPath && message.motionPath.length))
                        message.motionPath = [];
                    message.motionPath.push($root.GeneralMes.SVector3.decode(reader, reader.uint32()));
                    break;
                case 6:
                    message.param = reader.float();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("motionType"))
                throw $util.ProtocolError("missing required 'motionType'", { instance: message });
            return message;
        };

        /**
         * Decodes a SMotion message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SMotion
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SMotion} SMotion
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SMotion.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SMotion message.
         * @function verify
         * @memberof GeneralMes.SMotion
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SMotion.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.motionType))
                return "motionType: integer expected";
            if (message.motionTarget != null && message.hasOwnProperty("motionTarget"))
                if (!$util.isInteger(message.motionTarget) && !(message.motionTarget && $util.isInteger(message.motionTarget.low) && $util.isInteger(message.motionTarget.high)))
                    return "motionTarget: integer|Long expected";
            if (message.motionOrientation != null && message.hasOwnProperty("motionOrientation")) {
                var error = $root.GeneralMes.SVector3.verify(message.motionOrientation);
                if (error)
                    return "motionOrientation." + error;
            }
            if (message.motionPosition != null && message.hasOwnProperty("motionPosition")) {
                var error = $root.GeneralMes.SVector3.verify(message.motionPosition);
                if (error)
                    return "motionPosition." + error;
            }
            if (message.motionPath != null && message.hasOwnProperty("motionPath")) {
                if (!Array.isArray(message.motionPath))
                    return "motionPath: array expected";
                for (var i = 0; i < message.motionPath.length; ++i) {
                    var error = $root.GeneralMes.SVector3.verify(message.motionPath[i]);
                    if (error)
                        return "motionPath." + error;
                }
            }
            if (message.param != null && message.hasOwnProperty("param"))
                if (typeof message.param !== "number")
                    return "param: number expected";
            return null;
        };

        /**
         * Creates a SMotion message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SMotion
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SMotion} SMotion
         */
        SMotion.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SMotion)
                return object;
            var message = new $root.GeneralMes.SMotion();
            if (object.motionType != null)
                message.motionType = object.motionType | 0;
            if (object.motionTarget != null)
                if ($util.Long)
                    (message.motionTarget = $util.Long.fromValue(object.motionTarget)).unsigned = false;
                else if (typeof object.motionTarget === "string")
                    message.motionTarget = parseInt(object.motionTarget, 10);
                else if (typeof object.motionTarget === "number")
                    message.motionTarget = object.motionTarget;
                else if (typeof object.motionTarget === "object")
                    message.motionTarget = new $util.LongBits(object.motionTarget.low >>> 0, object.motionTarget.high >>> 0).toNumber();
            if (object.motionOrientation != null) {
                if (typeof object.motionOrientation !== "object")
                    throw TypeError(".GeneralMes.SMotion.motionOrientation: object expected");
                message.motionOrientation = $root.GeneralMes.SVector3.fromObject(object.motionOrientation);
            }
            if (object.motionPosition != null) {
                if (typeof object.motionPosition !== "object")
                    throw TypeError(".GeneralMes.SMotion.motionPosition: object expected");
                message.motionPosition = $root.GeneralMes.SVector3.fromObject(object.motionPosition);
            }
            if (object.motionPath) {
                if (!Array.isArray(object.motionPath))
                    throw TypeError(".GeneralMes.SMotion.motionPath: array expected");
                message.motionPath = [];
                for (var i = 0; i < object.motionPath.length; ++i) {
                    if (typeof object.motionPath[i] !== "object")
                        throw TypeError(".GeneralMes.SMotion.motionPath: object expected");
                    message.motionPath[i] = $root.GeneralMes.SVector3.fromObject(object.motionPath[i]);
                }
            }
            if (object.param != null)
                message.param = Number(object.param);
            return message;
        };

        /**
         * Creates a plain object from a SMotion message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SMotion
         * @static
         * @param {GeneralMes.SMotion} message SMotion
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SMotion.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.arrays || options.defaults)
                object.motionPath = [];
            if (options.defaults) {
                object.motionType = 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.motionTarget = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.motionTarget = options.longs === String ? "0" : 0;
                object.motionOrientation = null;
                object.motionPosition = null;
                object.param = 0;
            }
            if (message.motionType != null && message.hasOwnProperty("motionType"))
                object.motionType = message.motionType;
            if (message.motionTarget != null && message.hasOwnProperty("motionTarget"))
                if (typeof message.motionTarget === "number")
                    object.motionTarget = options.longs === String ? String(message.motionTarget) : message.motionTarget;
                else
                    object.motionTarget = options.longs === String ? $util.Long.prototype.toString.call(message.motionTarget) : options.longs === Number ? new $util.LongBits(message.motionTarget.low >>> 0, message.motionTarget.high >>> 0).toNumber() : message.motionTarget;
            if (message.motionOrientation != null && message.hasOwnProperty("motionOrientation"))
                object.motionOrientation = $root.GeneralMes.SVector3.toObject(message.motionOrientation, options);
            if (message.motionPosition != null && message.hasOwnProperty("motionPosition"))
                object.motionPosition = $root.GeneralMes.SVector3.toObject(message.motionPosition, options);
            if (message.motionPath && message.motionPath.length) {
                object.motionPath = [];
                for (var j = 0; j < message.motionPath.length; ++j)
                    object.motionPath[j] = $root.GeneralMes.SVector3.toObject(message.motionPath[j], options);
            }
            if (message.param != null && message.hasOwnProperty("param"))
                object.param = options.json && !isFinite(message.param) ? String(message.param) : message.param;
            return object;
        };

        /**
         * Converts this SMotion to JSON.
         * @function toJSON
         * @memberof GeneralMes.SMotion
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SMotion.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SMotion;
    })();

    GeneralMes.SStageInfo = (function() {

        /**
         * Properties of a SStageInfo.
         * @memberof GeneralMes
         * @interface ISStageInfo
         * @property {number|Long} id SStageInfo id
         * @property {Uint8Array} scene SStageInfo scene
         * @property {Uint8Array} sceneNavmesh SStageInfo sceneNavmesh
         * @property {Uint8Array} sceneInfo SStageInfo sceneInfo
         */

        /**
         * Constructs a new SStageInfo.
         * @memberof GeneralMes
         * @classdesc Represents a SStageInfo.
         * @implements ISStageInfo
         * @constructor
         * @param {GeneralMes.ISStageInfo=} [properties] Properties to set
         */
        function SStageInfo(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SStageInfo id.
         * @member {number|Long} id
         * @memberof GeneralMes.SStageInfo
         * @instance
         */
        SStageInfo.prototype.id = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SStageInfo scene.
         * @member {Uint8Array} scene
         * @memberof GeneralMes.SStageInfo
         * @instance
         */
        SStageInfo.prototype.scene = $util.newBuffer([]);

        /**
         * SStageInfo sceneNavmesh.
         * @member {Uint8Array} sceneNavmesh
         * @memberof GeneralMes.SStageInfo
         * @instance
         */
        SStageInfo.prototype.sceneNavmesh = $util.newBuffer([]);

        /**
         * SStageInfo sceneInfo.
         * @member {Uint8Array} sceneInfo
         * @memberof GeneralMes.SStageInfo
         * @instance
         */
        SStageInfo.prototype.sceneInfo = $util.newBuffer([]);

        /**
         * Creates a new SStageInfo instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SStageInfo
         * @static
         * @param {GeneralMes.ISStageInfo=} [properties] Properties to set
         * @returns {GeneralMes.SStageInfo} SStageInfo instance
         */
        SStageInfo.create = function create(properties) {
            return new SStageInfo(properties);
        };

        /**
         * Encodes the specified SStageInfo message. Does not implicitly {@link GeneralMes.SStageInfo.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SStageInfo
         * @static
         * @param {GeneralMes.ISStageInfo} message SStageInfo message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SStageInfo.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.id);
            writer.uint32(/* id 2, wireType 2 =*/18).bytes(message.scene);
            writer.uint32(/* id 3, wireType 2 =*/26).bytes(message.sceneNavmesh);
            writer.uint32(/* id 4, wireType 2 =*/34).bytes(message.sceneInfo);
            return writer;
        };

        /**
         * Encodes the specified SStageInfo message, length delimited. Does not implicitly {@link GeneralMes.SStageInfo.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SStageInfo
         * @static
         * @param {GeneralMes.ISStageInfo} message SStageInfo message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SStageInfo.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SStageInfo message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SStageInfo
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SStageInfo} SStageInfo
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SStageInfo.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SStageInfo();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.id = reader.int64();
                    break;
                case 2:
                    message.scene = reader.bytes();
                    break;
                case 3:
                    message.sceneNavmesh = reader.bytes();
                    break;
                case 4:
                    message.sceneInfo = reader.bytes();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("id"))
                throw $util.ProtocolError("missing required 'id'", { instance: message });
            if (!message.hasOwnProperty("scene"))
                throw $util.ProtocolError("missing required 'scene'", { instance: message });
            if (!message.hasOwnProperty("sceneNavmesh"))
                throw $util.ProtocolError("missing required 'sceneNavmesh'", { instance: message });
            if (!message.hasOwnProperty("sceneInfo"))
                throw $util.ProtocolError("missing required 'sceneInfo'", { instance: message });
            return message;
        };

        /**
         * Decodes a SStageInfo message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SStageInfo
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SStageInfo} SStageInfo
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SStageInfo.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SStageInfo message.
         * @function verify
         * @memberof GeneralMes.SStageInfo
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SStageInfo.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.id) && !(message.id && $util.isInteger(message.id.low) && $util.isInteger(message.id.high)))
                return "id: integer|Long expected";
            if (!(message.scene && typeof message.scene.length === "number" || $util.isString(message.scene)))
                return "scene: buffer expected";
            if (!(message.sceneNavmesh && typeof message.sceneNavmesh.length === "number" || $util.isString(message.sceneNavmesh)))
                return "sceneNavmesh: buffer expected";
            if (!(message.sceneInfo && typeof message.sceneInfo.length === "number" || $util.isString(message.sceneInfo)))
                return "sceneInfo: buffer expected";
            return null;
        };

        /**
         * Creates a SStageInfo message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SStageInfo
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SStageInfo} SStageInfo
         */
        SStageInfo.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SStageInfo)
                return object;
            var message = new $root.GeneralMes.SStageInfo();
            if (object.id != null)
                if ($util.Long)
                    (message.id = $util.Long.fromValue(object.id)).unsigned = false;
                else if (typeof object.id === "string")
                    message.id = parseInt(object.id, 10);
                else if (typeof object.id === "number")
                    message.id = object.id;
                else if (typeof object.id === "object")
                    message.id = new $util.LongBits(object.id.low >>> 0, object.id.high >>> 0).toNumber();
            if (object.scene != null)
                if (typeof object.scene === "string")
                    $util.base64.decode(object.scene, message.scene = $util.newBuffer($util.base64.length(object.scene)), 0);
                else if (object.scene.length)
                    message.scene = object.scene;
            if (object.sceneNavmesh != null)
                if (typeof object.sceneNavmesh === "string")
                    $util.base64.decode(object.sceneNavmesh, message.sceneNavmesh = $util.newBuffer($util.base64.length(object.sceneNavmesh)), 0);
                else if (object.sceneNavmesh.length)
                    message.sceneNavmesh = object.sceneNavmesh;
            if (object.sceneInfo != null)
                if (typeof object.sceneInfo === "string")
                    $util.base64.decode(object.sceneInfo, message.sceneInfo = $util.newBuffer($util.base64.length(object.sceneInfo)), 0);
                else if (object.sceneInfo.length)
                    message.sceneInfo = object.sceneInfo;
            return message;
        };

        /**
         * Creates a plain object from a SStageInfo message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SStageInfo
         * @static
         * @param {GeneralMes.SStageInfo} message SStageInfo
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SStageInfo.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.id = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.id = options.longs === String ? "0" : 0;
                object.scene = options.bytes === String ? "" : [];
                object.sceneNavmesh = options.bytes === String ? "" : [];
                object.sceneInfo = options.bytes === String ? "" : [];
            }
            if (message.id != null && message.hasOwnProperty("id"))
                if (typeof message.id === "number")
                    object.id = options.longs === String ? String(message.id) : message.id;
                else
                    object.id = options.longs === String ? $util.Long.prototype.toString.call(message.id) : options.longs === Number ? new $util.LongBits(message.id.low >>> 0, message.id.high >>> 0).toNumber() : message.id;
            if (message.scene != null && message.hasOwnProperty("scene"))
                object.scene = options.bytes === String ? $util.base64.encode(message.scene, 0, message.scene.length) : options.bytes === Array ? Array.prototype.slice.call(message.scene) : message.scene;
            if (message.sceneNavmesh != null && message.hasOwnProperty("sceneNavmesh"))
                object.sceneNavmesh = options.bytes === String ? $util.base64.encode(message.sceneNavmesh, 0, message.sceneNavmesh.length) : options.bytes === Array ? Array.prototype.slice.call(message.sceneNavmesh) : message.sceneNavmesh;
            if (message.sceneInfo != null && message.hasOwnProperty("sceneInfo"))
                object.sceneInfo = options.bytes === String ? $util.base64.encode(message.sceneInfo, 0, message.sceneInfo.length) : options.bytes === Array ? Array.prototype.slice.call(message.sceneInfo) : message.sceneInfo;
            return object;
        };

        /**
         * Converts this SStageInfo to JSON.
         * @function toJSON
         * @memberof GeneralMes.SStageInfo
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SStageInfo.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SStageInfo;
    })();

    GeneralMes.SItemModAttr = (function() {

        /**
         * Properties of a SItemModAttr.
         * @memberof GeneralMes
         * @interface ISItemModAttr
         * @property {number} mod SItemModAttr mod
         * @property {number} type SItemModAttr type
         * @property {number} value SItemModAttr value
         */

        /**
         * Constructs a new SItemModAttr.
         * @memberof GeneralMes
         * @classdesc Represents a SItemModAttr.
         * @implements ISItemModAttr
         * @constructor
         * @param {GeneralMes.ISItemModAttr=} [properties] Properties to set
         */
        function SItemModAttr(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemModAttr mod.
         * @member {number} mod
         * @memberof GeneralMes.SItemModAttr
         * @instance
         */
        SItemModAttr.prototype.mod = 0;

        /**
         * SItemModAttr type.
         * @member {number} type
         * @memberof GeneralMes.SItemModAttr
         * @instance
         */
        SItemModAttr.prototype.type = 0;

        /**
         * SItemModAttr value.
         * @member {number} value
         * @memberof GeneralMes.SItemModAttr
         * @instance
         */
        SItemModAttr.prototype.value = 0;

        /**
         * Creates a new SItemModAttr instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemModAttr
         * @static
         * @param {GeneralMes.ISItemModAttr=} [properties] Properties to set
         * @returns {GeneralMes.SItemModAttr} SItemModAttr instance
         */
        SItemModAttr.create = function create(properties) {
            return new SItemModAttr(properties);
        };

        /**
         * Encodes the specified SItemModAttr message. Does not implicitly {@link GeneralMes.SItemModAttr.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemModAttr
         * @static
         * @param {GeneralMes.ISItemModAttr} message SItemModAttr message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemModAttr.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.mod);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.type);
            writer.uint32(/* id 3, wireType 5 =*/29).float(message.value);
            return writer;
        };

        /**
         * Encodes the specified SItemModAttr message, length delimited. Does not implicitly {@link GeneralMes.SItemModAttr.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemModAttr
         * @static
         * @param {GeneralMes.ISItemModAttr} message SItemModAttr message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemModAttr.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemModAttr message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemModAttr
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemModAttr} SItemModAttr
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemModAttr.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemModAttr();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.mod = reader.int32();
                    break;
                case 2:
                    message.type = reader.int32();
                    break;
                case 3:
                    message.value = reader.float();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("mod"))
                throw $util.ProtocolError("missing required 'mod'", { instance: message });
            if (!message.hasOwnProperty("type"))
                throw $util.ProtocolError("missing required 'type'", { instance: message });
            if (!message.hasOwnProperty("value"))
                throw $util.ProtocolError("missing required 'value'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemModAttr message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemModAttr
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemModAttr} SItemModAttr
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemModAttr.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemModAttr message.
         * @function verify
         * @memberof GeneralMes.SItemModAttr
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemModAttr.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.mod))
                return "mod: integer expected";
            if (!$util.isInteger(message.type))
                return "type: integer expected";
            if (typeof message.value !== "number")
                return "value: number expected";
            return null;
        };

        /**
         * Creates a SItemModAttr message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemModAttr
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemModAttr} SItemModAttr
         */
        SItemModAttr.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemModAttr)
                return object;
            var message = new $root.GeneralMes.SItemModAttr();
            if (object.mod != null)
                message.mod = object.mod | 0;
            if (object.type != null)
                message.type = object.type | 0;
            if (object.value != null)
                message.value = Number(object.value);
            return message;
        };

        /**
         * Creates a plain object from a SItemModAttr message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemModAttr
         * @static
         * @param {GeneralMes.SItemModAttr} message SItemModAttr
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemModAttr.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.mod = 0;
                object.type = 0;
                object.value = 0;
            }
            if (message.mod != null && message.hasOwnProperty("mod"))
                object.mod = message.mod;
            if (message.type != null && message.hasOwnProperty("type"))
                object.type = message.type;
            if (message.value != null && message.hasOwnProperty("value"))
                object.value = options.json && !isFinite(message.value) ? String(message.value) : message.value;
            return object;
        };

        /**
         * Converts this SItemModAttr to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemModAttr
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemModAttr.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemModAttr;
    })();

    GeneralMes.SItemModTrig = (function() {

        /**
         * Properties of a SItemModTrig.
         * @memberof GeneralMes
         * @interface ISItemModTrig
         * @property {number} mod SItemModTrig mod
         * @property {Array.<number>|null} [params] SItemModTrig params
         */

        /**
         * Constructs a new SItemModTrig.
         * @memberof GeneralMes
         * @classdesc Represents a SItemModTrig.
         * @implements ISItemModTrig
         * @constructor
         * @param {GeneralMes.ISItemModTrig=} [properties] Properties to set
         */
        function SItemModTrig(properties) {
            this.params = [];
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemModTrig mod.
         * @member {number} mod
         * @memberof GeneralMes.SItemModTrig
         * @instance
         */
        SItemModTrig.prototype.mod = 0;

        /**
         * SItemModTrig params.
         * @member {Array.<number>} params
         * @memberof GeneralMes.SItemModTrig
         * @instance
         */
        SItemModTrig.prototype.params = $util.emptyArray;

        /**
         * Creates a new SItemModTrig instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemModTrig
         * @static
         * @param {GeneralMes.ISItemModTrig=} [properties] Properties to set
         * @returns {GeneralMes.SItemModTrig} SItemModTrig instance
         */
        SItemModTrig.create = function create(properties) {
            return new SItemModTrig(properties);
        };

        /**
         * Encodes the specified SItemModTrig message. Does not implicitly {@link GeneralMes.SItemModTrig.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemModTrig
         * @static
         * @param {GeneralMes.ISItemModTrig} message SItemModTrig message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemModTrig.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.mod);
            if (message.params != null && message.params.length)
                for (var i = 0; i < message.params.length; ++i)
                    writer.uint32(/* id 2, wireType 5 =*/21).float(message.params[i]);
            return writer;
        };

        /**
         * Encodes the specified SItemModTrig message, length delimited. Does not implicitly {@link GeneralMes.SItemModTrig.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemModTrig
         * @static
         * @param {GeneralMes.ISItemModTrig} message SItemModTrig message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemModTrig.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemModTrig message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemModTrig
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemModTrig} SItemModTrig
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemModTrig.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemModTrig();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.mod = reader.int32();
                    break;
                case 2:
                    if (!(message.params && message.params.length))
                        message.params = [];
                    if ((tag & 7) === 2) {
                        var end2 = reader.uint32() + reader.pos;
                        while (reader.pos < end2)
                            message.params.push(reader.float());
                    } else
                        message.params.push(reader.float());
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("mod"))
                throw $util.ProtocolError("missing required 'mod'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemModTrig message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemModTrig
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemModTrig} SItemModTrig
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemModTrig.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemModTrig message.
         * @function verify
         * @memberof GeneralMes.SItemModTrig
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemModTrig.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.mod))
                return "mod: integer expected";
            if (message.params != null && message.hasOwnProperty("params")) {
                if (!Array.isArray(message.params))
                    return "params: array expected";
                for (var i = 0; i < message.params.length; ++i)
                    if (typeof message.params[i] !== "number")
                        return "params: number[] expected";
            }
            return null;
        };

        /**
         * Creates a SItemModTrig message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemModTrig
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemModTrig} SItemModTrig
         */
        SItemModTrig.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemModTrig)
                return object;
            var message = new $root.GeneralMes.SItemModTrig();
            if (object.mod != null)
                message.mod = object.mod | 0;
            if (object.params) {
                if (!Array.isArray(object.params))
                    throw TypeError(".GeneralMes.SItemModTrig.params: array expected");
                message.params = [];
                for (var i = 0; i < object.params.length; ++i)
                    message.params[i] = Number(object.params[i]);
            }
            return message;
        };

        /**
         * Creates a plain object from a SItemModTrig message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemModTrig
         * @static
         * @param {GeneralMes.SItemModTrig} message SItemModTrig
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemModTrig.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.arrays || options.defaults)
                object.params = [];
            if (options.defaults)
                object.mod = 0;
            if (message.mod != null && message.hasOwnProperty("mod"))
                object.mod = message.mod;
            if (message.params && message.params.length) {
                object.params = [];
                for (var j = 0; j < message.params.length; ++j)
                    object.params[j] = options.json && !isFinite(message.params[j]) ? String(message.params[j]) : message.params[j];
            }
            return object;
        };

        /**
         * Converts this SItemModTrig to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemModTrig
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemModTrig.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemModTrig;
    })();

    GeneralMes.SCombatPoint = (function() {

        /**
         * Properties of a SCombatPoint.
         * @memberof GeneralMes
         * @interface ISCombatPoint
         * @property {number} zsPoint SCombatPoint zsPoint
         * @property {number} gsPoint SCombatPoint gsPoint
         * @property {number} fsPoint SCombatPoint fsPoint
         */

        /**
         * Constructs a new SCombatPoint.
         * @memberof GeneralMes
         * @classdesc Represents a SCombatPoint.
         * @implements ISCombatPoint
         * @constructor
         * @param {GeneralMes.ISCombatPoint=} [properties] Properties to set
         */
        function SCombatPoint(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SCombatPoint zsPoint.
         * @member {number} zsPoint
         * @memberof GeneralMes.SCombatPoint
         * @instance
         */
        SCombatPoint.prototype.zsPoint = 0;

        /**
         * SCombatPoint gsPoint.
         * @member {number} gsPoint
         * @memberof GeneralMes.SCombatPoint
         * @instance
         */
        SCombatPoint.prototype.gsPoint = 0;

        /**
         * SCombatPoint fsPoint.
         * @member {number} fsPoint
         * @memberof GeneralMes.SCombatPoint
         * @instance
         */
        SCombatPoint.prototype.fsPoint = 0;

        /**
         * Creates a new SCombatPoint instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SCombatPoint
         * @static
         * @param {GeneralMes.ISCombatPoint=} [properties] Properties to set
         * @returns {GeneralMes.SCombatPoint} SCombatPoint instance
         */
        SCombatPoint.create = function create(properties) {
            return new SCombatPoint(properties);
        };

        /**
         * Encodes the specified SCombatPoint message. Does not implicitly {@link GeneralMes.SCombatPoint.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SCombatPoint
         * @static
         * @param {GeneralMes.ISCombatPoint} message SCombatPoint message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCombatPoint.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 5 =*/13).float(message.zsPoint);
            writer.uint32(/* id 2, wireType 5 =*/21).float(message.gsPoint);
            writer.uint32(/* id 3, wireType 5 =*/29).float(message.fsPoint);
            return writer;
        };

        /**
         * Encodes the specified SCombatPoint message, length delimited. Does not implicitly {@link GeneralMes.SCombatPoint.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SCombatPoint
         * @static
         * @param {GeneralMes.ISCombatPoint} message SCombatPoint message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCombatPoint.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SCombatPoint message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SCombatPoint
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SCombatPoint} SCombatPoint
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCombatPoint.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SCombatPoint();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.zsPoint = reader.float();
                    break;
                case 2:
                    message.gsPoint = reader.float();
                    break;
                case 3:
                    message.fsPoint = reader.float();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("zsPoint"))
                throw $util.ProtocolError("missing required 'zsPoint'", { instance: message });
            if (!message.hasOwnProperty("gsPoint"))
                throw $util.ProtocolError("missing required 'gsPoint'", { instance: message });
            if (!message.hasOwnProperty("fsPoint"))
                throw $util.ProtocolError("missing required 'fsPoint'", { instance: message });
            return message;
        };

        /**
         * Decodes a SCombatPoint message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SCombatPoint
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SCombatPoint} SCombatPoint
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCombatPoint.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SCombatPoint message.
         * @function verify
         * @memberof GeneralMes.SCombatPoint
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SCombatPoint.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (typeof message.zsPoint !== "number")
                return "zsPoint: number expected";
            if (typeof message.gsPoint !== "number")
                return "gsPoint: number expected";
            if (typeof message.fsPoint !== "number")
                return "fsPoint: number expected";
            return null;
        };

        /**
         * Creates a SCombatPoint message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SCombatPoint
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SCombatPoint} SCombatPoint
         */
        SCombatPoint.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SCombatPoint)
                return object;
            var message = new $root.GeneralMes.SCombatPoint();
            if (object.zsPoint != null)
                message.zsPoint = Number(object.zsPoint);
            if (object.gsPoint != null)
                message.gsPoint = Number(object.gsPoint);
            if (object.fsPoint != null)
                message.fsPoint = Number(object.fsPoint);
            return message;
        };

        /**
         * Creates a plain object from a SCombatPoint message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SCombatPoint
         * @static
         * @param {GeneralMes.SCombatPoint} message SCombatPoint
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SCombatPoint.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.zsPoint = 0;
                object.gsPoint = 0;
                object.fsPoint = 0;
            }
            if (message.zsPoint != null && message.hasOwnProperty("zsPoint"))
                object.zsPoint = options.json && !isFinite(message.zsPoint) ? String(message.zsPoint) : message.zsPoint;
            if (message.gsPoint != null && message.hasOwnProperty("gsPoint"))
                object.gsPoint = options.json && !isFinite(message.gsPoint) ? String(message.gsPoint) : message.gsPoint;
            if (message.fsPoint != null && message.hasOwnProperty("fsPoint"))
                object.fsPoint = options.json && !isFinite(message.fsPoint) ? String(message.fsPoint) : message.fsPoint;
            return object;
        };

        /**
         * Converts this SCombatPoint to JSON.
         * @function toJSON
         * @memberof GeneralMes.SCombatPoint
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SCombatPoint.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SCombatPoint;
    })();

    GeneralMes.SItemFashionParts = (function() {

        /**
         * Properties of a SItemFashionParts.
         * @memberof GeneralMes
         * @interface ISItemFashionParts
         * @property {number} idx SItemFashionParts idx
         * @property {number} enhanceLv SItemFashionParts enhanceLv
         */

        /**
         * Constructs a new SItemFashionParts.
         * @memberof GeneralMes
         * @classdesc Represents a SItemFashionParts.
         * @implements ISItemFashionParts
         * @constructor
         * @param {GeneralMes.ISItemFashionParts=} [properties] Properties to set
         */
        function SItemFashionParts(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemFashionParts idx.
         * @member {number} idx
         * @memberof GeneralMes.SItemFashionParts
         * @instance
         */
        SItemFashionParts.prototype.idx = 0;

        /**
         * SItemFashionParts enhanceLv.
         * @member {number} enhanceLv
         * @memberof GeneralMes.SItemFashionParts
         * @instance
         */
        SItemFashionParts.prototype.enhanceLv = 0;

        /**
         * Creates a new SItemFashionParts instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemFashionParts
         * @static
         * @param {GeneralMes.ISItemFashionParts=} [properties] Properties to set
         * @returns {GeneralMes.SItemFashionParts} SItemFashionParts instance
         */
        SItemFashionParts.create = function create(properties) {
            return new SItemFashionParts(properties);
        };

        /**
         * Encodes the specified SItemFashionParts message. Does not implicitly {@link GeneralMes.SItemFashionParts.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemFashionParts
         * @static
         * @param {GeneralMes.ISItemFashionParts} message SItemFashionParts message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemFashionParts.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.idx);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.enhanceLv);
            return writer;
        };

        /**
         * Encodes the specified SItemFashionParts message, length delimited. Does not implicitly {@link GeneralMes.SItemFashionParts.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemFashionParts
         * @static
         * @param {GeneralMes.ISItemFashionParts} message SItemFashionParts message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemFashionParts.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemFashionParts message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemFashionParts
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemFashionParts} SItemFashionParts
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemFashionParts.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemFashionParts();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.idx = reader.int32();
                    break;
                case 2:
                    message.enhanceLv = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("idx"))
                throw $util.ProtocolError("missing required 'idx'", { instance: message });
            if (!message.hasOwnProperty("enhanceLv"))
                throw $util.ProtocolError("missing required 'enhanceLv'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemFashionParts message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemFashionParts
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemFashionParts} SItemFashionParts
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemFashionParts.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemFashionParts message.
         * @function verify
         * @memberof GeneralMes.SItemFashionParts
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemFashionParts.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.idx))
                return "idx: integer expected";
            if (!$util.isInteger(message.enhanceLv))
                return "enhanceLv: integer expected";
            return null;
        };

        /**
         * Creates a SItemFashionParts message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemFashionParts
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemFashionParts} SItemFashionParts
         */
        SItemFashionParts.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemFashionParts)
                return object;
            var message = new $root.GeneralMes.SItemFashionParts();
            if (object.idx != null)
                message.idx = object.idx | 0;
            if (object.enhanceLv != null)
                message.enhanceLv = object.enhanceLv | 0;
            return message;
        };

        /**
         * Creates a plain object from a SItemFashionParts message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemFashionParts
         * @static
         * @param {GeneralMes.SItemFashionParts} message SItemFashionParts
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemFashionParts.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.idx = 0;
                object.enhanceLv = 0;
            }
            if (message.idx != null && message.hasOwnProperty("idx"))
                object.idx = message.idx;
            if (message.enhanceLv != null && message.hasOwnProperty("enhanceLv"))
                object.enhanceLv = message.enhanceLv;
            return object;
        };

        /**
         * Converts this SItemFashionParts to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemFashionParts
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemFashionParts.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemFashionParts;
    })();

    GeneralMes.SItemWing = (function() {

        /**
         * Properties of a SItemWing.
         * @memberof GeneralMes
         * @interface ISItemWing
         * @property {number} exp SItemWing exp
         * @property {number} star SItemWing star
         * @property {number} level SItemWing level
         * @property {number} step SItemWing step
         * @property {number} equipStep SItemWing equipStep
         * @property {number} luck SItemWing luck
         */

        /**
         * Constructs a new SItemWing.
         * @memberof GeneralMes
         * @classdesc Represents a SItemWing.
         * @implements ISItemWing
         * @constructor
         * @param {GeneralMes.ISItemWing=} [properties] Properties to set
         */
        function SItemWing(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemWing exp.
         * @member {number} exp
         * @memberof GeneralMes.SItemWing
         * @instance
         */
        SItemWing.prototype.exp = 0;

        /**
         * SItemWing star.
         * @member {number} star
         * @memberof GeneralMes.SItemWing
         * @instance
         */
        SItemWing.prototype.star = 0;

        /**
         * SItemWing level.
         * @member {number} level
         * @memberof GeneralMes.SItemWing
         * @instance
         */
        SItemWing.prototype.level = 0;

        /**
         * SItemWing step.
         * @member {number} step
         * @memberof GeneralMes.SItemWing
         * @instance
         */
        SItemWing.prototype.step = 0;

        /**
         * SItemWing equipStep.
         * @member {number} equipStep
         * @memberof GeneralMes.SItemWing
         * @instance
         */
        SItemWing.prototype.equipStep = 0;

        /**
         * SItemWing luck.
         * @member {number} luck
         * @memberof GeneralMes.SItemWing
         * @instance
         */
        SItemWing.prototype.luck = 0;

        /**
         * Creates a new SItemWing instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemWing
         * @static
         * @param {GeneralMes.ISItemWing=} [properties] Properties to set
         * @returns {GeneralMes.SItemWing} SItemWing instance
         */
        SItemWing.create = function create(properties) {
            return new SItemWing(properties);
        };

        /**
         * Encodes the specified SItemWing message. Does not implicitly {@link GeneralMes.SItemWing.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemWing
         * @static
         * @param {GeneralMes.ISItemWing} message SItemWing message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemWing.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.exp);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.star);
            writer.uint32(/* id 3, wireType 0 =*/24).int32(message.level);
            writer.uint32(/* id 4, wireType 0 =*/32).int32(message.step);
            writer.uint32(/* id 5, wireType 0 =*/40).int32(message.equipStep);
            writer.uint32(/* id 6, wireType 0 =*/48).int32(message.luck);
            return writer;
        };

        /**
         * Encodes the specified SItemWing message, length delimited. Does not implicitly {@link GeneralMes.SItemWing.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemWing
         * @static
         * @param {GeneralMes.ISItemWing} message SItemWing message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemWing.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemWing message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemWing
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemWing} SItemWing
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemWing.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemWing();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.exp = reader.int32();
                    break;
                case 2:
                    message.star = reader.int32();
                    break;
                case 3:
                    message.level = reader.int32();
                    break;
                case 4:
                    message.step = reader.int32();
                    break;
                case 5:
                    message.equipStep = reader.int32();
                    break;
                case 6:
                    message.luck = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("exp"))
                throw $util.ProtocolError("missing required 'exp'", { instance: message });
            if (!message.hasOwnProperty("star"))
                throw $util.ProtocolError("missing required 'star'", { instance: message });
            if (!message.hasOwnProperty("level"))
                throw $util.ProtocolError("missing required 'level'", { instance: message });
            if (!message.hasOwnProperty("step"))
                throw $util.ProtocolError("missing required 'step'", { instance: message });
            if (!message.hasOwnProperty("equipStep"))
                throw $util.ProtocolError("missing required 'equipStep'", { instance: message });
            if (!message.hasOwnProperty("luck"))
                throw $util.ProtocolError("missing required 'luck'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemWing message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemWing
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemWing} SItemWing
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemWing.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemWing message.
         * @function verify
         * @memberof GeneralMes.SItemWing
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemWing.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.exp))
                return "exp: integer expected";
            if (!$util.isInteger(message.star))
                return "star: integer expected";
            if (!$util.isInteger(message.level))
                return "level: integer expected";
            if (!$util.isInteger(message.step))
                return "step: integer expected";
            if (!$util.isInteger(message.equipStep))
                return "equipStep: integer expected";
            if (!$util.isInteger(message.luck))
                return "luck: integer expected";
            return null;
        };

        /**
         * Creates a SItemWing message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemWing
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemWing} SItemWing
         */
        SItemWing.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemWing)
                return object;
            var message = new $root.GeneralMes.SItemWing();
            if (object.exp != null)
                message.exp = object.exp | 0;
            if (object.star != null)
                message.star = object.star | 0;
            if (object.level != null)
                message.level = object.level | 0;
            if (object.step != null)
                message.step = object.step | 0;
            if (object.equipStep != null)
                message.equipStep = object.equipStep | 0;
            if (object.luck != null)
                message.luck = object.luck | 0;
            return message;
        };

        /**
         * Creates a plain object from a SItemWing message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemWing
         * @static
         * @param {GeneralMes.SItemWing} message SItemWing
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemWing.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.exp = 0;
                object.star = 0;
                object.level = 0;
                object.step = 0;
                object.equipStep = 0;
                object.luck = 0;
            }
            if (message.exp != null && message.hasOwnProperty("exp"))
                object.exp = message.exp;
            if (message.star != null && message.hasOwnProperty("star"))
                object.star = message.star;
            if (message.level != null && message.hasOwnProperty("level"))
                object.level = message.level;
            if (message.step != null && message.hasOwnProperty("step"))
                object.step = message.step;
            if (message.equipStep != null && message.hasOwnProperty("equipStep"))
                object.equipStep = message.equipStep;
            if (message.luck != null && message.hasOwnProperty("luck"))
                object.luck = message.luck;
            return object;
        };

        /**
         * Converts this SItemWing to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemWing
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemWing.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemWing;
    })();

    GeneralMes.SItemEquip = (function() {

        /**
         * Properties of a SItemEquip.
         * @memberof GeneralMes
         * @interface ISItemEquip
         * @property {number} color SItemEquip color
         * @property {number} level SItemEquip level
         * @property {number} useLevel SItemEquip useLevel
         * @property {number|null} [starLevel] SItemEquip starLevel
         * @property {number|null} [enchantLevel] SItemEquip enchantLevel
         * @property {Array.<GeneralMes.ISItemModAttr>|null} [basicsAttr] SItemEquip basicsAttr
         * @property {Array.<GeneralMes.ISItemModAttr>|null} [extendsAttr] SItemEquip extendsAttr
         * @property {GeneralMes.ISItemModAttr|null} [specialAttr] SItemEquip specialAttr
         * @property {GeneralMes.ISItemModTrig|null} [specialTrig] SItemEquip specialTrig
         * @property {Array.<GeneralMes.ISItemFashionParts>|null} [fashionParts] SItemEquip fashionParts
         * @property {GeneralMes.ISItemWing|null} [wing] SItemEquip wing
         * @property {number|null} [skillId] SItemEquip skillId
         */

        /**
         * Constructs a new SItemEquip.
         * @memberof GeneralMes
         * @classdesc Represents a SItemEquip.
         * @implements ISItemEquip
         * @constructor
         * @param {GeneralMes.ISItemEquip=} [properties] Properties to set
         */
        function SItemEquip(properties) {
            this.basicsAttr = [];
            this.extendsAttr = [];
            this.fashionParts = [];
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemEquip color.
         * @member {number} color
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.color = 0;

        /**
         * SItemEquip level.
         * @member {number} level
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.level = 0;

        /**
         * SItemEquip useLevel.
         * @member {number} useLevel
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.useLevel = 0;

        /**
         * SItemEquip starLevel.
         * @member {number} starLevel
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.starLevel = 0;

        /**
         * SItemEquip enchantLevel.
         * @member {number} enchantLevel
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.enchantLevel = 0;

        /**
         * SItemEquip basicsAttr.
         * @member {Array.<GeneralMes.ISItemModAttr>} basicsAttr
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.basicsAttr = $util.emptyArray;

        /**
         * SItemEquip extendsAttr.
         * @member {Array.<GeneralMes.ISItemModAttr>} extendsAttr
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.extendsAttr = $util.emptyArray;

        /**
         * SItemEquip specialAttr.
         * @member {GeneralMes.ISItemModAttr|null|undefined} specialAttr
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.specialAttr = null;

        /**
         * SItemEquip specialTrig.
         * @member {GeneralMes.ISItemModTrig|null|undefined} specialTrig
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.specialTrig = null;

        /**
         * SItemEquip fashionParts.
         * @member {Array.<GeneralMes.ISItemFashionParts>} fashionParts
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.fashionParts = $util.emptyArray;

        /**
         * SItemEquip wing.
         * @member {GeneralMes.ISItemWing|null|undefined} wing
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.wing = null;

        /**
         * SItemEquip skillId.
         * @member {number} skillId
         * @memberof GeneralMes.SItemEquip
         * @instance
         */
        SItemEquip.prototype.skillId = 0;

        /**
         * Creates a new SItemEquip instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemEquip
         * @static
         * @param {GeneralMes.ISItemEquip=} [properties] Properties to set
         * @returns {GeneralMes.SItemEquip} SItemEquip instance
         */
        SItemEquip.create = function create(properties) {
            return new SItemEquip(properties);
        };

        /**
         * Encodes the specified SItemEquip message. Does not implicitly {@link GeneralMes.SItemEquip.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemEquip
         * @static
         * @param {GeneralMes.ISItemEquip} message SItemEquip message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemEquip.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.color);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.level);
            writer.uint32(/* id 3, wireType 0 =*/24).int32(message.useLevel);
            if (message.starLevel != null && message.hasOwnProperty("starLevel"))
                writer.uint32(/* id 4, wireType 0 =*/32).int32(message.starLevel);
            if (message.enchantLevel != null && message.hasOwnProperty("enchantLevel"))
                writer.uint32(/* id 5, wireType 0 =*/40).int32(message.enchantLevel);
            if (message.basicsAttr != null && message.basicsAttr.length)
                for (var i = 0; i < message.basicsAttr.length; ++i)
                    $root.GeneralMes.SItemModAttr.encode(message.basicsAttr[i], writer.uint32(/* id 6, wireType 2 =*/50).fork()).ldelim();
            if (message.extendsAttr != null && message.extendsAttr.length)
                for (var i = 0; i < message.extendsAttr.length; ++i)
                    $root.GeneralMes.SItemModAttr.encode(message.extendsAttr[i], writer.uint32(/* id 7, wireType 2 =*/58).fork()).ldelim();
            if (message.specialAttr != null && message.hasOwnProperty("specialAttr"))
                $root.GeneralMes.SItemModAttr.encode(message.specialAttr, writer.uint32(/* id 8, wireType 2 =*/66).fork()).ldelim();
            if (message.specialTrig != null && message.hasOwnProperty("specialTrig"))
                $root.GeneralMes.SItemModTrig.encode(message.specialTrig, writer.uint32(/* id 9, wireType 2 =*/74).fork()).ldelim();
            if (message.fashionParts != null && message.fashionParts.length)
                for (var i = 0; i < message.fashionParts.length; ++i)
                    $root.GeneralMes.SItemFashionParts.encode(message.fashionParts[i], writer.uint32(/* id 10, wireType 2 =*/82).fork()).ldelim();
            if (message.wing != null && message.hasOwnProperty("wing"))
                $root.GeneralMes.SItemWing.encode(message.wing, writer.uint32(/* id 11, wireType 2 =*/90).fork()).ldelim();
            if (message.skillId != null && message.hasOwnProperty("skillId"))
                writer.uint32(/* id 12, wireType 0 =*/96).int32(message.skillId);
            return writer;
        };

        /**
         * Encodes the specified SItemEquip message, length delimited. Does not implicitly {@link GeneralMes.SItemEquip.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemEquip
         * @static
         * @param {GeneralMes.ISItemEquip} message SItemEquip message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemEquip.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemEquip message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemEquip
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemEquip} SItemEquip
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemEquip.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemEquip();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.color = reader.int32();
                    break;
                case 2:
                    message.level = reader.int32();
                    break;
                case 3:
                    message.useLevel = reader.int32();
                    break;
                case 4:
                    message.starLevel = reader.int32();
                    break;
                case 5:
                    message.enchantLevel = reader.int32();
                    break;
                case 6:
                    if (!(message.basicsAttr && message.basicsAttr.length))
                        message.basicsAttr = [];
                    message.basicsAttr.push($root.GeneralMes.SItemModAttr.decode(reader, reader.uint32()));
                    break;
                case 7:
                    if (!(message.extendsAttr && message.extendsAttr.length))
                        message.extendsAttr = [];
                    message.extendsAttr.push($root.GeneralMes.SItemModAttr.decode(reader, reader.uint32()));
                    break;
                case 8:
                    message.specialAttr = $root.GeneralMes.SItemModAttr.decode(reader, reader.uint32());
                    break;
                case 9:
                    message.specialTrig = $root.GeneralMes.SItemModTrig.decode(reader, reader.uint32());
                    break;
                case 10:
                    if (!(message.fashionParts && message.fashionParts.length))
                        message.fashionParts = [];
                    message.fashionParts.push($root.GeneralMes.SItemFashionParts.decode(reader, reader.uint32()));
                    break;
                case 11:
                    message.wing = $root.GeneralMes.SItemWing.decode(reader, reader.uint32());
                    break;
                case 12:
                    message.skillId = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("color"))
                throw $util.ProtocolError("missing required 'color'", { instance: message });
            if (!message.hasOwnProperty("level"))
                throw $util.ProtocolError("missing required 'level'", { instance: message });
            if (!message.hasOwnProperty("useLevel"))
                throw $util.ProtocolError("missing required 'useLevel'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemEquip message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemEquip
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemEquip} SItemEquip
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemEquip.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemEquip message.
         * @function verify
         * @memberof GeneralMes.SItemEquip
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemEquip.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.color))
                return "color: integer expected";
            if (!$util.isInteger(message.level))
                return "level: integer expected";
            if (!$util.isInteger(message.useLevel))
                return "useLevel: integer expected";
            if (message.starLevel != null && message.hasOwnProperty("starLevel"))
                if (!$util.isInteger(message.starLevel))
                    return "starLevel: integer expected";
            if (message.enchantLevel != null && message.hasOwnProperty("enchantLevel"))
                if (!$util.isInteger(message.enchantLevel))
                    return "enchantLevel: integer expected";
            if (message.basicsAttr != null && message.hasOwnProperty("basicsAttr")) {
                if (!Array.isArray(message.basicsAttr))
                    return "basicsAttr: array expected";
                for (var i = 0; i < message.basicsAttr.length; ++i) {
                    var error = $root.GeneralMes.SItemModAttr.verify(message.basicsAttr[i]);
                    if (error)
                        return "basicsAttr." + error;
                }
            }
            if (message.extendsAttr != null && message.hasOwnProperty("extendsAttr")) {
                if (!Array.isArray(message.extendsAttr))
                    return "extendsAttr: array expected";
                for (var i = 0; i < message.extendsAttr.length; ++i) {
                    var error = $root.GeneralMes.SItemModAttr.verify(message.extendsAttr[i]);
                    if (error)
                        return "extendsAttr." + error;
                }
            }
            if (message.specialAttr != null && message.hasOwnProperty("specialAttr")) {
                var error = $root.GeneralMes.SItemModAttr.verify(message.specialAttr);
                if (error)
                    return "specialAttr." + error;
            }
            if (message.specialTrig != null && message.hasOwnProperty("specialTrig")) {
                var error = $root.GeneralMes.SItemModTrig.verify(message.specialTrig);
                if (error)
                    return "specialTrig." + error;
            }
            if (message.fashionParts != null && message.hasOwnProperty("fashionParts")) {
                if (!Array.isArray(message.fashionParts))
                    return "fashionParts: array expected";
                for (var i = 0; i < message.fashionParts.length; ++i) {
                    var error = $root.GeneralMes.SItemFashionParts.verify(message.fashionParts[i]);
                    if (error)
                        return "fashionParts." + error;
                }
            }
            if (message.wing != null && message.hasOwnProperty("wing")) {
                var error = $root.GeneralMes.SItemWing.verify(message.wing);
                if (error)
                    return "wing." + error;
            }
            if (message.skillId != null && message.hasOwnProperty("skillId"))
                if (!$util.isInteger(message.skillId))
                    return "skillId: integer expected";
            return null;
        };

        /**
         * Creates a SItemEquip message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemEquip
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemEquip} SItemEquip
         */
        SItemEquip.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemEquip)
                return object;
            var message = new $root.GeneralMes.SItemEquip();
            if (object.color != null)
                message.color = object.color | 0;
            if (object.level != null)
                message.level = object.level | 0;
            if (object.useLevel != null)
                message.useLevel = object.useLevel | 0;
            if (object.starLevel != null)
                message.starLevel = object.starLevel | 0;
            if (object.enchantLevel != null)
                message.enchantLevel = object.enchantLevel | 0;
            if (object.basicsAttr) {
                if (!Array.isArray(object.basicsAttr))
                    throw TypeError(".GeneralMes.SItemEquip.basicsAttr: array expected");
                message.basicsAttr = [];
                for (var i = 0; i < object.basicsAttr.length; ++i) {
                    if (typeof object.basicsAttr[i] !== "object")
                        throw TypeError(".GeneralMes.SItemEquip.basicsAttr: object expected");
                    message.basicsAttr[i] = $root.GeneralMes.SItemModAttr.fromObject(object.basicsAttr[i]);
                }
            }
            if (object.extendsAttr) {
                if (!Array.isArray(object.extendsAttr))
                    throw TypeError(".GeneralMes.SItemEquip.extendsAttr: array expected");
                message.extendsAttr = [];
                for (var i = 0; i < object.extendsAttr.length; ++i) {
                    if (typeof object.extendsAttr[i] !== "object")
                        throw TypeError(".GeneralMes.SItemEquip.extendsAttr: object expected");
                    message.extendsAttr[i] = $root.GeneralMes.SItemModAttr.fromObject(object.extendsAttr[i]);
                }
            }
            if (object.specialAttr != null) {
                if (typeof object.specialAttr !== "object")
                    throw TypeError(".GeneralMes.SItemEquip.specialAttr: object expected");
                message.specialAttr = $root.GeneralMes.SItemModAttr.fromObject(object.specialAttr);
            }
            if (object.specialTrig != null) {
                if (typeof object.specialTrig !== "object")
                    throw TypeError(".GeneralMes.SItemEquip.specialTrig: object expected");
                message.specialTrig = $root.GeneralMes.SItemModTrig.fromObject(object.specialTrig);
            }
            if (object.fashionParts) {
                if (!Array.isArray(object.fashionParts))
                    throw TypeError(".GeneralMes.SItemEquip.fashionParts: array expected");
                message.fashionParts = [];
                for (var i = 0; i < object.fashionParts.length; ++i) {
                    if (typeof object.fashionParts[i] !== "object")
                        throw TypeError(".GeneralMes.SItemEquip.fashionParts: object expected");
                    message.fashionParts[i] = $root.GeneralMes.SItemFashionParts.fromObject(object.fashionParts[i]);
                }
            }
            if (object.wing != null) {
                if (typeof object.wing !== "object")
                    throw TypeError(".GeneralMes.SItemEquip.wing: object expected");
                message.wing = $root.GeneralMes.SItemWing.fromObject(object.wing);
            }
            if (object.skillId != null)
                message.skillId = object.skillId | 0;
            return message;
        };

        /**
         * Creates a plain object from a SItemEquip message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemEquip
         * @static
         * @param {GeneralMes.SItemEquip} message SItemEquip
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemEquip.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.arrays || options.defaults) {
                object.basicsAttr = [];
                object.extendsAttr = [];
                object.fashionParts = [];
            }
            if (options.defaults) {
                object.color = 0;
                object.level = 0;
                object.useLevel = 0;
                object.starLevel = 0;
                object.enchantLevel = 0;
                object.specialAttr = null;
                object.specialTrig = null;
                object.wing = null;
                object.skillId = 0;
            }
            if (message.color != null && message.hasOwnProperty("color"))
                object.color = message.color;
            if (message.level != null && message.hasOwnProperty("level"))
                object.level = message.level;
            if (message.useLevel != null && message.hasOwnProperty("useLevel"))
                object.useLevel = message.useLevel;
            if (message.starLevel != null && message.hasOwnProperty("starLevel"))
                object.starLevel = message.starLevel;
            if (message.enchantLevel != null && message.hasOwnProperty("enchantLevel"))
                object.enchantLevel = message.enchantLevel;
            if (message.basicsAttr && message.basicsAttr.length) {
                object.basicsAttr = [];
                for (var j = 0; j < message.basicsAttr.length; ++j)
                    object.basicsAttr[j] = $root.GeneralMes.SItemModAttr.toObject(message.basicsAttr[j], options);
            }
            if (message.extendsAttr && message.extendsAttr.length) {
                object.extendsAttr = [];
                for (var j = 0; j < message.extendsAttr.length; ++j)
                    object.extendsAttr[j] = $root.GeneralMes.SItemModAttr.toObject(message.extendsAttr[j], options);
            }
            if (message.specialAttr != null && message.hasOwnProperty("specialAttr"))
                object.specialAttr = $root.GeneralMes.SItemModAttr.toObject(message.specialAttr, options);
            if (message.specialTrig != null && message.hasOwnProperty("specialTrig"))
                object.specialTrig = $root.GeneralMes.SItemModTrig.toObject(message.specialTrig, options);
            if (message.fashionParts && message.fashionParts.length) {
                object.fashionParts = [];
                for (var j = 0; j < message.fashionParts.length; ++j)
                    object.fashionParts[j] = $root.GeneralMes.SItemFashionParts.toObject(message.fashionParts[j], options);
            }
            if (message.wing != null && message.hasOwnProperty("wing"))
                object.wing = $root.GeneralMes.SItemWing.toObject(message.wing, options);
            if (message.skillId != null && message.hasOwnProperty("skillId"))
                object.skillId = message.skillId;
            return object;
        };

        /**
         * Converts this SItemEquip to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemEquip
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemEquip.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemEquip;
    })();

    GeneralMes.SItemRune = (function() {

        /**
         * Properties of a SItemRune.
         * @memberof GeneralMes
         * @interface ISItemRune
         * @property {number} exp SItemRune exp
         */

        /**
         * Constructs a new SItemRune.
         * @memberof GeneralMes
         * @classdesc Represents a SItemRune.
         * @implements ISItemRune
         * @constructor
         * @param {GeneralMes.ISItemRune=} [properties] Properties to set
         */
        function SItemRune(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemRune exp.
         * @member {number} exp
         * @memberof GeneralMes.SItemRune
         * @instance
         */
        SItemRune.prototype.exp = 0;

        /**
         * Creates a new SItemRune instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemRune
         * @static
         * @param {GeneralMes.ISItemRune=} [properties] Properties to set
         * @returns {GeneralMes.SItemRune} SItemRune instance
         */
        SItemRune.create = function create(properties) {
            return new SItemRune(properties);
        };

        /**
         * Encodes the specified SItemRune message. Does not implicitly {@link GeneralMes.SItemRune.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemRune
         * @static
         * @param {GeneralMes.ISItemRune} message SItemRune message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemRune.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.exp);
            return writer;
        };

        /**
         * Encodes the specified SItemRune message, length delimited. Does not implicitly {@link GeneralMes.SItemRune.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemRune
         * @static
         * @param {GeneralMes.ISItemRune} message SItemRune message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemRune.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemRune message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemRune
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemRune} SItemRune
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemRune.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemRune();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.exp = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("exp"))
                throw $util.ProtocolError("missing required 'exp'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemRune message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemRune
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemRune} SItemRune
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemRune.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemRune message.
         * @function verify
         * @memberof GeneralMes.SItemRune
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemRune.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.exp))
                return "exp: integer expected";
            return null;
        };

        /**
         * Creates a SItemRune message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemRune
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemRune} SItemRune
         */
        SItemRune.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemRune)
                return object;
            var message = new $root.GeneralMes.SItemRune();
            if (object.exp != null)
                message.exp = object.exp | 0;
            return message;
        };

        /**
         * Creates a plain object from a SItemRune message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemRune
         * @static
         * @param {GeneralMes.SItemRune} message SItemRune
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemRune.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults)
                object.exp = 0;
            if (message.exp != null && message.hasOwnProperty("exp"))
                object.exp = message.exp;
            return object;
        };

        /**
         * Converts this SItemRune to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemRune
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemRune.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemRune;
    })();

    GeneralMes.SItemBless = (function() {

        /**
         * Properties of a SItemBless.
         * @memberof GeneralMes
         * @interface ISItemBless
         * @property {Array.<GeneralMes.ISItemModAttr>|null} [modAttrs] SItemBless modAttrs
         */

        /**
         * Constructs a new SItemBless.
         * @memberof GeneralMes
         * @classdesc Represents a SItemBless.
         * @implements ISItemBless
         * @constructor
         * @param {GeneralMes.ISItemBless=} [properties] Properties to set
         */
        function SItemBless(properties) {
            this.modAttrs = [];
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemBless modAttrs.
         * @member {Array.<GeneralMes.ISItemModAttr>} modAttrs
         * @memberof GeneralMes.SItemBless
         * @instance
         */
        SItemBless.prototype.modAttrs = $util.emptyArray;

        /**
         * Creates a new SItemBless instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemBless
         * @static
         * @param {GeneralMes.ISItemBless=} [properties] Properties to set
         * @returns {GeneralMes.SItemBless} SItemBless instance
         */
        SItemBless.create = function create(properties) {
            return new SItemBless(properties);
        };

        /**
         * Encodes the specified SItemBless message. Does not implicitly {@link GeneralMes.SItemBless.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemBless
         * @static
         * @param {GeneralMes.ISItemBless} message SItemBless message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemBless.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            if (message.modAttrs != null && message.modAttrs.length)
                for (var i = 0; i < message.modAttrs.length; ++i)
                    $root.GeneralMes.SItemModAttr.encode(message.modAttrs[i], writer.uint32(/* id 1, wireType 2 =*/10).fork()).ldelim();
            return writer;
        };

        /**
         * Encodes the specified SItemBless message, length delimited. Does not implicitly {@link GeneralMes.SItemBless.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemBless
         * @static
         * @param {GeneralMes.ISItemBless} message SItemBless message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemBless.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemBless message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemBless
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemBless} SItemBless
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemBless.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemBless();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    if (!(message.modAttrs && message.modAttrs.length))
                        message.modAttrs = [];
                    message.modAttrs.push($root.GeneralMes.SItemModAttr.decode(reader, reader.uint32()));
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            return message;
        };

        /**
         * Decodes a SItemBless message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemBless
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemBless} SItemBless
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemBless.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemBless message.
         * @function verify
         * @memberof GeneralMes.SItemBless
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemBless.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (message.modAttrs != null && message.hasOwnProperty("modAttrs")) {
                if (!Array.isArray(message.modAttrs))
                    return "modAttrs: array expected";
                for (var i = 0; i < message.modAttrs.length; ++i) {
                    var error = $root.GeneralMes.SItemModAttr.verify(message.modAttrs[i]);
                    if (error)
                        return "modAttrs." + error;
                }
            }
            return null;
        };

        /**
         * Creates a SItemBless message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemBless
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemBless} SItemBless
         */
        SItemBless.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemBless)
                return object;
            var message = new $root.GeneralMes.SItemBless();
            if (object.modAttrs) {
                if (!Array.isArray(object.modAttrs))
                    throw TypeError(".GeneralMes.SItemBless.modAttrs: array expected");
                message.modAttrs = [];
                for (var i = 0; i < object.modAttrs.length; ++i) {
                    if (typeof object.modAttrs[i] !== "object")
                        throw TypeError(".GeneralMes.SItemBless.modAttrs: object expected");
                    message.modAttrs[i] = $root.GeneralMes.SItemModAttr.fromObject(object.modAttrs[i]);
                }
            }
            return message;
        };

        /**
         * Creates a plain object from a SItemBless message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemBless
         * @static
         * @param {GeneralMes.SItemBless} message SItemBless
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemBless.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.arrays || options.defaults)
                object.modAttrs = [];
            if (message.modAttrs && message.modAttrs.length) {
                object.modAttrs = [];
                for (var j = 0; j < message.modAttrs.length; ++j)
                    object.modAttrs[j] = $root.GeneralMes.SItemModAttr.toObject(message.modAttrs[j], options);
            }
            return object;
        };

        /**
         * Converts this SItemBless to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemBless
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemBless.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemBless;
    })();

    GeneralMes.SItemEgg = (function() {

        /**
         * Properties of a SItemEgg.
         * @memberof GeneralMes
         * @interface ISItemEgg
         * @property {number} aptitude SItemEgg aptitude
         * @property {number} fireDmg SItemEgg fireDmg
         * @property {number} coldDmg SItemEgg coldDmg
         * @property {number} lightDmg SItemEgg lightDmg
         * @property {number} poisonDmg SItemEgg poisonDmg
         * @property {number} fireRes SItemEgg fireRes
         * @property {number} coldRes SItemEgg coldRes
         * @property {number} lightRes SItemEgg lightRes
         * @property {number} poisonRes SItemEgg poisonRes
         * @property {number} growRate SItemEgg growRate
         * @property {number} growRateLimit SItemEgg growRateLimit
         * @property {number} conRate SItemEgg conRate
         * @property {number} conRateLimit SItemEgg conRateLimit
         */

        /**
         * Constructs a new SItemEgg.
         * @memberof GeneralMes
         * @classdesc Represents a SItemEgg.
         * @implements ISItemEgg
         * @constructor
         * @param {GeneralMes.ISItemEgg=} [properties] Properties to set
         */
        function SItemEgg(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemEgg aptitude.
         * @member {number} aptitude
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.aptitude = 0;

        /**
         * SItemEgg fireDmg.
         * @member {number} fireDmg
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.fireDmg = 0;

        /**
         * SItemEgg coldDmg.
         * @member {number} coldDmg
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.coldDmg = 0;

        /**
         * SItemEgg lightDmg.
         * @member {number} lightDmg
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.lightDmg = 0;

        /**
         * SItemEgg poisonDmg.
         * @member {number} poisonDmg
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.poisonDmg = 0;

        /**
         * SItemEgg fireRes.
         * @member {number} fireRes
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.fireRes = 0;

        /**
         * SItemEgg coldRes.
         * @member {number} coldRes
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.coldRes = 0;

        /**
         * SItemEgg lightRes.
         * @member {number} lightRes
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.lightRes = 0;

        /**
         * SItemEgg poisonRes.
         * @member {number} poisonRes
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.poisonRes = 0;

        /**
         * SItemEgg growRate.
         * @member {number} growRate
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.growRate = 0;

        /**
         * SItemEgg growRateLimit.
         * @member {number} growRateLimit
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.growRateLimit = 0;

        /**
         * SItemEgg conRate.
         * @member {number} conRate
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.conRate = 0;

        /**
         * SItemEgg conRateLimit.
         * @member {number} conRateLimit
         * @memberof GeneralMes.SItemEgg
         * @instance
         */
        SItemEgg.prototype.conRateLimit = 0;

        /**
         * Creates a new SItemEgg instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemEgg
         * @static
         * @param {GeneralMes.ISItemEgg=} [properties] Properties to set
         * @returns {GeneralMes.SItemEgg} SItemEgg instance
         */
        SItemEgg.create = function create(properties) {
            return new SItemEgg(properties);
        };

        /**
         * Encodes the specified SItemEgg message. Does not implicitly {@link GeneralMes.SItemEgg.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemEgg
         * @static
         * @param {GeneralMes.ISItemEgg} message SItemEgg message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemEgg.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 5 =*/13).float(message.aptitude);
            writer.uint32(/* id 2, wireType 5 =*/21).float(message.fireDmg);
            writer.uint32(/* id 3, wireType 5 =*/29).float(message.coldDmg);
            writer.uint32(/* id 4, wireType 5 =*/37).float(message.lightDmg);
            writer.uint32(/* id 5, wireType 5 =*/45).float(message.poisonDmg);
            writer.uint32(/* id 6, wireType 5 =*/53).float(message.fireRes);
            writer.uint32(/* id 7, wireType 5 =*/61).float(message.coldRes);
            writer.uint32(/* id 8, wireType 5 =*/69).float(message.lightRes);
            writer.uint32(/* id 9, wireType 5 =*/77).float(message.poisonRes);
            writer.uint32(/* id 10, wireType 5 =*/85).float(message.growRate);
            writer.uint32(/* id 11, wireType 5 =*/93).float(message.growRateLimit);
            writer.uint32(/* id 12, wireType 5 =*/101).float(message.conRate);
            writer.uint32(/* id 13, wireType 5 =*/109).float(message.conRateLimit);
            return writer;
        };

        /**
         * Encodes the specified SItemEgg message, length delimited. Does not implicitly {@link GeneralMes.SItemEgg.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemEgg
         * @static
         * @param {GeneralMes.ISItemEgg} message SItemEgg message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemEgg.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemEgg message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemEgg
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemEgg} SItemEgg
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemEgg.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemEgg();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.aptitude = reader.float();
                    break;
                case 2:
                    message.fireDmg = reader.float();
                    break;
                case 3:
                    message.coldDmg = reader.float();
                    break;
                case 4:
                    message.lightDmg = reader.float();
                    break;
                case 5:
                    message.poisonDmg = reader.float();
                    break;
                case 6:
                    message.fireRes = reader.float();
                    break;
                case 7:
                    message.coldRes = reader.float();
                    break;
                case 8:
                    message.lightRes = reader.float();
                    break;
                case 9:
                    message.poisonRes = reader.float();
                    break;
                case 10:
                    message.growRate = reader.float();
                    break;
                case 11:
                    message.growRateLimit = reader.float();
                    break;
                case 12:
                    message.conRate = reader.float();
                    break;
                case 13:
                    message.conRateLimit = reader.float();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("aptitude"))
                throw $util.ProtocolError("missing required 'aptitude'", { instance: message });
            if (!message.hasOwnProperty("fireDmg"))
                throw $util.ProtocolError("missing required 'fireDmg'", { instance: message });
            if (!message.hasOwnProperty("coldDmg"))
                throw $util.ProtocolError("missing required 'coldDmg'", { instance: message });
            if (!message.hasOwnProperty("lightDmg"))
                throw $util.ProtocolError("missing required 'lightDmg'", { instance: message });
            if (!message.hasOwnProperty("poisonDmg"))
                throw $util.ProtocolError("missing required 'poisonDmg'", { instance: message });
            if (!message.hasOwnProperty("fireRes"))
                throw $util.ProtocolError("missing required 'fireRes'", { instance: message });
            if (!message.hasOwnProperty("coldRes"))
                throw $util.ProtocolError("missing required 'coldRes'", { instance: message });
            if (!message.hasOwnProperty("lightRes"))
                throw $util.ProtocolError("missing required 'lightRes'", { instance: message });
            if (!message.hasOwnProperty("poisonRes"))
                throw $util.ProtocolError("missing required 'poisonRes'", { instance: message });
            if (!message.hasOwnProperty("growRate"))
                throw $util.ProtocolError("missing required 'growRate'", { instance: message });
            if (!message.hasOwnProperty("growRateLimit"))
                throw $util.ProtocolError("missing required 'growRateLimit'", { instance: message });
            if (!message.hasOwnProperty("conRate"))
                throw $util.ProtocolError("missing required 'conRate'", { instance: message });
            if (!message.hasOwnProperty("conRateLimit"))
                throw $util.ProtocolError("missing required 'conRateLimit'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemEgg message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemEgg
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemEgg} SItemEgg
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemEgg.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemEgg message.
         * @function verify
         * @memberof GeneralMes.SItemEgg
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemEgg.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (typeof message.aptitude !== "number")
                return "aptitude: number expected";
            if (typeof message.fireDmg !== "number")
                return "fireDmg: number expected";
            if (typeof message.coldDmg !== "number")
                return "coldDmg: number expected";
            if (typeof message.lightDmg !== "number")
                return "lightDmg: number expected";
            if (typeof message.poisonDmg !== "number")
                return "poisonDmg: number expected";
            if (typeof message.fireRes !== "number")
                return "fireRes: number expected";
            if (typeof message.coldRes !== "number")
                return "coldRes: number expected";
            if (typeof message.lightRes !== "number")
                return "lightRes: number expected";
            if (typeof message.poisonRes !== "number")
                return "poisonRes: number expected";
            if (typeof message.growRate !== "number")
                return "growRate: number expected";
            if (typeof message.growRateLimit !== "number")
                return "growRateLimit: number expected";
            if (typeof message.conRate !== "number")
                return "conRate: number expected";
            if (typeof message.conRateLimit !== "number")
                return "conRateLimit: number expected";
            return null;
        };

        /**
         * Creates a SItemEgg message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemEgg
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemEgg} SItemEgg
         */
        SItemEgg.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemEgg)
                return object;
            var message = new $root.GeneralMes.SItemEgg();
            if (object.aptitude != null)
                message.aptitude = Number(object.aptitude);
            if (object.fireDmg != null)
                message.fireDmg = Number(object.fireDmg);
            if (object.coldDmg != null)
                message.coldDmg = Number(object.coldDmg);
            if (object.lightDmg != null)
                message.lightDmg = Number(object.lightDmg);
            if (object.poisonDmg != null)
                message.poisonDmg = Number(object.poisonDmg);
            if (object.fireRes != null)
                message.fireRes = Number(object.fireRes);
            if (object.coldRes != null)
                message.coldRes = Number(object.coldRes);
            if (object.lightRes != null)
                message.lightRes = Number(object.lightRes);
            if (object.poisonRes != null)
                message.poisonRes = Number(object.poisonRes);
            if (object.growRate != null)
                message.growRate = Number(object.growRate);
            if (object.growRateLimit != null)
                message.growRateLimit = Number(object.growRateLimit);
            if (object.conRate != null)
                message.conRate = Number(object.conRate);
            if (object.conRateLimit != null)
                message.conRateLimit = Number(object.conRateLimit);
            return message;
        };

        /**
         * Creates a plain object from a SItemEgg message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemEgg
         * @static
         * @param {GeneralMes.SItemEgg} message SItemEgg
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemEgg.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.aptitude = 0;
                object.fireDmg = 0;
                object.coldDmg = 0;
                object.lightDmg = 0;
                object.poisonDmg = 0;
                object.fireRes = 0;
                object.coldRes = 0;
                object.lightRes = 0;
                object.poisonRes = 0;
                object.growRate = 0;
                object.growRateLimit = 0;
                object.conRate = 0;
                object.conRateLimit = 0;
            }
            if (message.aptitude != null && message.hasOwnProperty("aptitude"))
                object.aptitude = options.json && !isFinite(message.aptitude) ? String(message.aptitude) : message.aptitude;
            if (message.fireDmg != null && message.hasOwnProperty("fireDmg"))
                object.fireDmg = options.json && !isFinite(message.fireDmg) ? String(message.fireDmg) : message.fireDmg;
            if (message.coldDmg != null && message.hasOwnProperty("coldDmg"))
                object.coldDmg = options.json && !isFinite(message.coldDmg) ? String(message.coldDmg) : message.coldDmg;
            if (message.lightDmg != null && message.hasOwnProperty("lightDmg"))
                object.lightDmg = options.json && !isFinite(message.lightDmg) ? String(message.lightDmg) : message.lightDmg;
            if (message.poisonDmg != null && message.hasOwnProperty("poisonDmg"))
                object.poisonDmg = options.json && !isFinite(message.poisonDmg) ? String(message.poisonDmg) : message.poisonDmg;
            if (message.fireRes != null && message.hasOwnProperty("fireRes"))
                object.fireRes = options.json && !isFinite(message.fireRes) ? String(message.fireRes) : message.fireRes;
            if (message.coldRes != null && message.hasOwnProperty("coldRes"))
                object.coldRes = options.json && !isFinite(message.coldRes) ? String(message.coldRes) : message.coldRes;
            if (message.lightRes != null && message.hasOwnProperty("lightRes"))
                object.lightRes = options.json && !isFinite(message.lightRes) ? String(message.lightRes) : message.lightRes;
            if (message.poisonRes != null && message.hasOwnProperty("poisonRes"))
                object.poisonRes = options.json && !isFinite(message.poisonRes) ? String(message.poisonRes) : message.poisonRes;
            if (message.growRate != null && message.hasOwnProperty("growRate"))
                object.growRate = options.json && !isFinite(message.growRate) ? String(message.growRate) : message.growRate;
            if (message.growRateLimit != null && message.hasOwnProperty("growRateLimit"))
                object.growRateLimit = options.json && !isFinite(message.growRateLimit) ? String(message.growRateLimit) : message.growRateLimit;
            if (message.conRate != null && message.hasOwnProperty("conRate"))
                object.conRate = options.json && !isFinite(message.conRate) ? String(message.conRate) : message.conRate;
            if (message.conRateLimit != null && message.hasOwnProperty("conRateLimit"))
                object.conRateLimit = options.json && !isFinite(message.conRateLimit) ? String(message.conRateLimit) : message.conRateLimit;
            return object;
        };

        /**
         * Converts this SItemEgg to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemEgg
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemEgg.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemEgg;
    })();

    GeneralMes.SItemEquipRune = (function() {

        /**
         * Properties of a SItemEquipRune.
         * @memberof GeneralMes
         * @interface ISItemEquipRune
         * @property {Array.<GeneralMes.ISItemModAttr>|null} [modAttrs] SItemEquipRune modAttrs
         */

        /**
         * Constructs a new SItemEquipRune.
         * @memberof GeneralMes
         * @classdesc Represents a SItemEquipRune.
         * @implements ISItemEquipRune
         * @constructor
         * @param {GeneralMes.ISItemEquipRune=} [properties] Properties to set
         */
        function SItemEquipRune(properties) {
            this.modAttrs = [];
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemEquipRune modAttrs.
         * @member {Array.<GeneralMes.ISItemModAttr>} modAttrs
         * @memberof GeneralMes.SItemEquipRune
         * @instance
         */
        SItemEquipRune.prototype.modAttrs = $util.emptyArray;

        /**
         * Creates a new SItemEquipRune instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemEquipRune
         * @static
         * @param {GeneralMes.ISItemEquipRune=} [properties] Properties to set
         * @returns {GeneralMes.SItemEquipRune} SItemEquipRune instance
         */
        SItemEquipRune.create = function create(properties) {
            return new SItemEquipRune(properties);
        };

        /**
         * Encodes the specified SItemEquipRune message. Does not implicitly {@link GeneralMes.SItemEquipRune.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemEquipRune
         * @static
         * @param {GeneralMes.ISItemEquipRune} message SItemEquipRune message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemEquipRune.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            if (message.modAttrs != null && message.modAttrs.length)
                for (var i = 0; i < message.modAttrs.length; ++i)
                    $root.GeneralMes.SItemModAttr.encode(message.modAttrs[i], writer.uint32(/* id 1, wireType 2 =*/10).fork()).ldelim();
            return writer;
        };

        /**
         * Encodes the specified SItemEquipRune message, length delimited. Does not implicitly {@link GeneralMes.SItemEquipRune.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemEquipRune
         * @static
         * @param {GeneralMes.ISItemEquipRune} message SItemEquipRune message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemEquipRune.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemEquipRune message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemEquipRune
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemEquipRune} SItemEquipRune
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemEquipRune.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemEquipRune();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    if (!(message.modAttrs && message.modAttrs.length))
                        message.modAttrs = [];
                    message.modAttrs.push($root.GeneralMes.SItemModAttr.decode(reader, reader.uint32()));
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            return message;
        };

        /**
         * Decodes a SItemEquipRune message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemEquipRune
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemEquipRune} SItemEquipRune
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemEquipRune.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemEquipRune message.
         * @function verify
         * @memberof GeneralMes.SItemEquipRune
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemEquipRune.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (message.modAttrs != null && message.hasOwnProperty("modAttrs")) {
                if (!Array.isArray(message.modAttrs))
                    return "modAttrs: array expected";
                for (var i = 0; i < message.modAttrs.length; ++i) {
                    var error = $root.GeneralMes.SItemModAttr.verify(message.modAttrs[i]);
                    if (error)
                        return "modAttrs." + error;
                }
            }
            return null;
        };

        /**
         * Creates a SItemEquipRune message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemEquipRune
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemEquipRune} SItemEquipRune
         */
        SItemEquipRune.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemEquipRune)
                return object;
            var message = new $root.GeneralMes.SItemEquipRune();
            if (object.modAttrs) {
                if (!Array.isArray(object.modAttrs))
                    throw TypeError(".GeneralMes.SItemEquipRune.modAttrs: array expected");
                message.modAttrs = [];
                for (var i = 0; i < object.modAttrs.length; ++i) {
                    if (typeof object.modAttrs[i] !== "object")
                        throw TypeError(".GeneralMes.SItemEquipRune.modAttrs: object expected");
                    message.modAttrs[i] = $root.GeneralMes.SItemModAttr.fromObject(object.modAttrs[i]);
                }
            }
            return message;
        };

        /**
         * Creates a plain object from a SItemEquipRune message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemEquipRune
         * @static
         * @param {GeneralMes.SItemEquipRune} message SItemEquipRune
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemEquipRune.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.arrays || options.defaults)
                object.modAttrs = [];
            if (message.modAttrs && message.modAttrs.length) {
                object.modAttrs = [];
                for (var j = 0; j < message.modAttrs.length; ++j)
                    object.modAttrs[j] = $root.GeneralMes.SItemModAttr.toObject(message.modAttrs[j], options);
            }
            return object;
        };

        /**
         * Converts this SItemEquipRune to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemEquipRune
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemEquipRune.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemEquipRune;
    })();

    GeneralMes.SItemBloodGobm = (function() {

        /**
         * Properties of a SItemBloodGobm.
         * @memberof GeneralMes
         * @interface ISItemBloodGobm
         * @property {number} level SItemBloodGobm level
         * @property {number} exp SItemBloodGobm exp
         * @property {number} activeType SItemBloodGobm activeType
         * @property {number} activeParam1 SItemBloodGobm activeParam1
         * @property {number} activeParam2 SItemBloodGobm activeParam2
         */

        /**
         * Constructs a new SItemBloodGobm.
         * @memberof GeneralMes
         * @classdesc Represents a SItemBloodGobm.
         * @implements ISItemBloodGobm
         * @constructor
         * @param {GeneralMes.ISItemBloodGobm=} [properties] Properties to set
         */
        function SItemBloodGobm(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemBloodGobm level.
         * @member {number} level
         * @memberof GeneralMes.SItemBloodGobm
         * @instance
         */
        SItemBloodGobm.prototype.level = 0;

        /**
         * SItemBloodGobm exp.
         * @member {number} exp
         * @memberof GeneralMes.SItemBloodGobm
         * @instance
         */
        SItemBloodGobm.prototype.exp = 0;

        /**
         * SItemBloodGobm activeType.
         * @member {number} activeType
         * @memberof GeneralMes.SItemBloodGobm
         * @instance
         */
        SItemBloodGobm.prototype.activeType = 0;

        /**
         * SItemBloodGobm activeParam1.
         * @member {number} activeParam1
         * @memberof GeneralMes.SItemBloodGobm
         * @instance
         */
        SItemBloodGobm.prototype.activeParam1 = 0;

        /**
         * SItemBloodGobm activeParam2.
         * @member {number} activeParam2
         * @memberof GeneralMes.SItemBloodGobm
         * @instance
         */
        SItemBloodGobm.prototype.activeParam2 = 0;

        /**
         * Creates a new SItemBloodGobm instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemBloodGobm
         * @static
         * @param {GeneralMes.ISItemBloodGobm=} [properties] Properties to set
         * @returns {GeneralMes.SItemBloodGobm} SItemBloodGobm instance
         */
        SItemBloodGobm.create = function create(properties) {
            return new SItemBloodGobm(properties);
        };

        /**
         * Encodes the specified SItemBloodGobm message. Does not implicitly {@link GeneralMes.SItemBloodGobm.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemBloodGobm
         * @static
         * @param {GeneralMes.ISItemBloodGobm} message SItemBloodGobm message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemBloodGobm.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.level);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.exp);
            writer.uint32(/* id 3, wireType 0 =*/24).int32(message.activeType);
            writer.uint32(/* id 4, wireType 0 =*/32).int32(message.activeParam1);
            writer.uint32(/* id 5, wireType 0 =*/40).int32(message.activeParam2);
            return writer;
        };

        /**
         * Encodes the specified SItemBloodGobm message, length delimited. Does not implicitly {@link GeneralMes.SItemBloodGobm.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemBloodGobm
         * @static
         * @param {GeneralMes.ISItemBloodGobm} message SItemBloodGobm message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemBloodGobm.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemBloodGobm message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemBloodGobm
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemBloodGobm} SItemBloodGobm
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemBloodGobm.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemBloodGobm();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.level = reader.int32();
                    break;
                case 2:
                    message.exp = reader.int32();
                    break;
                case 3:
                    message.activeType = reader.int32();
                    break;
                case 4:
                    message.activeParam1 = reader.int32();
                    break;
                case 5:
                    message.activeParam2 = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("level"))
                throw $util.ProtocolError("missing required 'level'", { instance: message });
            if (!message.hasOwnProperty("exp"))
                throw $util.ProtocolError("missing required 'exp'", { instance: message });
            if (!message.hasOwnProperty("activeType"))
                throw $util.ProtocolError("missing required 'activeType'", { instance: message });
            if (!message.hasOwnProperty("activeParam1"))
                throw $util.ProtocolError("missing required 'activeParam1'", { instance: message });
            if (!message.hasOwnProperty("activeParam2"))
                throw $util.ProtocolError("missing required 'activeParam2'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemBloodGobm message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemBloodGobm
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemBloodGobm} SItemBloodGobm
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemBloodGobm.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemBloodGobm message.
         * @function verify
         * @memberof GeneralMes.SItemBloodGobm
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemBloodGobm.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.level))
                return "level: integer expected";
            if (!$util.isInteger(message.exp))
                return "exp: integer expected";
            if (!$util.isInteger(message.activeType))
                return "activeType: integer expected";
            if (!$util.isInteger(message.activeParam1))
                return "activeParam1: integer expected";
            if (!$util.isInteger(message.activeParam2))
                return "activeParam2: integer expected";
            return null;
        };

        /**
         * Creates a SItemBloodGobm message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemBloodGobm
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemBloodGobm} SItemBloodGobm
         */
        SItemBloodGobm.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemBloodGobm)
                return object;
            var message = new $root.GeneralMes.SItemBloodGobm();
            if (object.level != null)
                message.level = object.level | 0;
            if (object.exp != null)
                message.exp = object.exp | 0;
            if (object.activeType != null)
                message.activeType = object.activeType | 0;
            if (object.activeParam1 != null)
                message.activeParam1 = object.activeParam1 | 0;
            if (object.activeParam2 != null)
                message.activeParam2 = object.activeParam2 | 0;
            return message;
        };

        /**
         * Creates a plain object from a SItemBloodGobm message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemBloodGobm
         * @static
         * @param {GeneralMes.SItemBloodGobm} message SItemBloodGobm
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemBloodGobm.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.level = 0;
                object.exp = 0;
                object.activeType = 0;
                object.activeParam1 = 0;
                object.activeParam2 = 0;
            }
            if (message.level != null && message.hasOwnProperty("level"))
                object.level = message.level;
            if (message.exp != null && message.hasOwnProperty("exp"))
                object.exp = message.exp;
            if (message.activeType != null && message.hasOwnProperty("activeType"))
                object.activeType = message.activeType;
            if (message.activeParam1 != null && message.hasOwnProperty("activeParam1"))
                object.activeParam1 = message.activeParam1;
            if (message.activeParam2 != null && message.hasOwnProperty("activeParam2"))
                object.activeParam2 = message.activeParam2;
            return object;
        };

        /**
         * Converts this SItemBloodGobm to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemBloodGobm
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemBloodGobm.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemBloodGobm;
    })();

    GeneralMes.SEquipIndexGem = (function() {

        /**
         * Properties of a SEquipIndexGem.
         * @memberof GeneralMes
         * @interface ISEquipIndexGem
         * @property {number} equipIndex SEquipIndexGem equipIndex
         * @property {Array.<GeneralMes.ISItem>|null} [gems] SEquipIndexGem gems
         */

        /**
         * Constructs a new SEquipIndexGem.
         * @memberof GeneralMes
         * @classdesc Represents a SEquipIndexGem.
         * @implements ISEquipIndexGem
         * @constructor
         * @param {GeneralMes.ISEquipIndexGem=} [properties] Properties to set
         */
        function SEquipIndexGem(properties) {
            this.gems = [];
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SEquipIndexGem equipIndex.
         * @member {number} equipIndex
         * @memberof GeneralMes.SEquipIndexGem
         * @instance
         */
        SEquipIndexGem.prototype.equipIndex = 0;

        /**
         * SEquipIndexGem gems.
         * @member {Array.<GeneralMes.ISItem>} gems
         * @memberof GeneralMes.SEquipIndexGem
         * @instance
         */
        SEquipIndexGem.prototype.gems = $util.emptyArray;

        /**
         * Creates a new SEquipIndexGem instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SEquipIndexGem
         * @static
         * @param {GeneralMes.ISEquipIndexGem=} [properties] Properties to set
         * @returns {GeneralMes.SEquipIndexGem} SEquipIndexGem instance
         */
        SEquipIndexGem.create = function create(properties) {
            return new SEquipIndexGem(properties);
        };

        /**
         * Encodes the specified SEquipIndexGem message. Does not implicitly {@link GeneralMes.SEquipIndexGem.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SEquipIndexGem
         * @static
         * @param {GeneralMes.ISEquipIndexGem} message SEquipIndexGem message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SEquipIndexGem.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.equipIndex);
            if (message.gems != null && message.gems.length)
                for (var i = 0; i < message.gems.length; ++i)
                    $root.GeneralMes.SItem.encode(message.gems[i], writer.uint32(/* id 2, wireType 2 =*/18).fork()).ldelim();
            return writer;
        };

        /**
         * Encodes the specified SEquipIndexGem message, length delimited. Does not implicitly {@link GeneralMes.SEquipIndexGem.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SEquipIndexGem
         * @static
         * @param {GeneralMes.ISEquipIndexGem} message SEquipIndexGem message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SEquipIndexGem.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SEquipIndexGem message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SEquipIndexGem
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SEquipIndexGem} SEquipIndexGem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SEquipIndexGem.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SEquipIndexGem();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.equipIndex = reader.int32();
                    break;
                case 2:
                    if (!(message.gems && message.gems.length))
                        message.gems = [];
                    message.gems.push($root.GeneralMes.SItem.decode(reader, reader.uint32()));
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("equipIndex"))
                throw $util.ProtocolError("missing required 'equipIndex'", { instance: message });
            return message;
        };

        /**
         * Decodes a SEquipIndexGem message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SEquipIndexGem
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SEquipIndexGem} SEquipIndexGem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SEquipIndexGem.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SEquipIndexGem message.
         * @function verify
         * @memberof GeneralMes.SEquipIndexGem
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SEquipIndexGem.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.equipIndex))
                return "equipIndex: integer expected";
            if (message.gems != null && message.hasOwnProperty("gems")) {
                if (!Array.isArray(message.gems))
                    return "gems: array expected";
                for (var i = 0; i < message.gems.length; ++i) {
                    var error = $root.GeneralMes.SItem.verify(message.gems[i]);
                    if (error)
                        return "gems." + error;
                }
            }
            return null;
        };

        /**
         * Creates a SEquipIndexGem message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SEquipIndexGem
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SEquipIndexGem} SEquipIndexGem
         */
        SEquipIndexGem.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SEquipIndexGem)
                return object;
            var message = new $root.GeneralMes.SEquipIndexGem();
            if (object.equipIndex != null)
                message.equipIndex = object.equipIndex | 0;
            if (object.gems) {
                if (!Array.isArray(object.gems))
                    throw TypeError(".GeneralMes.SEquipIndexGem.gems: array expected");
                message.gems = [];
                for (var i = 0; i < object.gems.length; ++i) {
                    if (typeof object.gems[i] !== "object")
                        throw TypeError(".GeneralMes.SEquipIndexGem.gems: object expected");
                    message.gems[i] = $root.GeneralMes.SItem.fromObject(object.gems[i]);
                }
            }
            return message;
        };

        /**
         * Creates a plain object from a SEquipIndexGem message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SEquipIndexGem
         * @static
         * @param {GeneralMes.SEquipIndexGem} message SEquipIndexGem
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SEquipIndexGem.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.arrays || options.defaults)
                object.gems = [];
            if (options.defaults)
                object.equipIndex = 0;
            if (message.equipIndex != null && message.hasOwnProperty("equipIndex"))
                object.equipIndex = message.equipIndex;
            if (message.gems && message.gems.length) {
                object.gems = [];
                for (var j = 0; j < message.gems.length; ++j)
                    object.gems[j] = $root.GeneralMes.SItem.toObject(message.gems[j], options);
            }
            return object;
        };

        /**
         * Converts this SEquipIndexGem to JSON.
         * @function toJSON
         * @memberof GeneralMes.SEquipIndexGem
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SEquipIndexGem.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SEquipIndexGem;
    })();

    GeneralMes.SItemHPMP = (function() {

        /**
         * Properties of a SItemHPMP.
         * @memberof GeneralMes
         * @interface ISItemHPMP
         * @property {number} usedVal SItemHPMP usedVal
         * @property {number} totalVal SItemHPMP totalVal
         */

        /**
         * Constructs a new SItemHPMP.
         * @memberof GeneralMes
         * @classdesc Represents a SItemHPMP.
         * @implements ISItemHPMP
         * @constructor
         * @param {GeneralMes.ISItemHPMP=} [properties] Properties to set
         */
        function SItemHPMP(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemHPMP usedVal.
         * @member {number} usedVal
         * @memberof GeneralMes.SItemHPMP
         * @instance
         */
        SItemHPMP.prototype.usedVal = 0;

        /**
         * SItemHPMP totalVal.
         * @member {number} totalVal
         * @memberof GeneralMes.SItemHPMP
         * @instance
         */
        SItemHPMP.prototype.totalVal = 0;

        /**
         * Creates a new SItemHPMP instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemHPMP
         * @static
         * @param {GeneralMes.ISItemHPMP=} [properties] Properties to set
         * @returns {GeneralMes.SItemHPMP} SItemHPMP instance
         */
        SItemHPMP.create = function create(properties) {
            return new SItemHPMP(properties);
        };

        /**
         * Encodes the specified SItemHPMP message. Does not implicitly {@link GeneralMes.SItemHPMP.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemHPMP
         * @static
         * @param {GeneralMes.ISItemHPMP} message SItemHPMP message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemHPMP.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.usedVal);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.totalVal);
            return writer;
        };

        /**
         * Encodes the specified SItemHPMP message, length delimited. Does not implicitly {@link GeneralMes.SItemHPMP.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemHPMP
         * @static
         * @param {GeneralMes.ISItemHPMP} message SItemHPMP message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemHPMP.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemHPMP message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemHPMP
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemHPMP} SItemHPMP
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemHPMP.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemHPMP();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.usedVal = reader.int32();
                    break;
                case 2:
                    message.totalVal = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("usedVal"))
                throw $util.ProtocolError("missing required 'usedVal'", { instance: message });
            if (!message.hasOwnProperty("totalVal"))
                throw $util.ProtocolError("missing required 'totalVal'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemHPMP message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemHPMP
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemHPMP} SItemHPMP
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemHPMP.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemHPMP message.
         * @function verify
         * @memberof GeneralMes.SItemHPMP
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemHPMP.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.usedVal))
                return "usedVal: integer expected";
            if (!$util.isInteger(message.totalVal))
                return "totalVal: integer expected";
            return null;
        };

        /**
         * Creates a SItemHPMP message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemHPMP
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemHPMP} SItemHPMP
         */
        SItemHPMP.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemHPMP)
                return object;
            var message = new $root.GeneralMes.SItemHPMP();
            if (object.usedVal != null)
                message.usedVal = object.usedVal | 0;
            if (object.totalVal != null)
                message.totalVal = object.totalVal | 0;
            return message;
        };

        /**
         * Creates a plain object from a SItemHPMP message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemHPMP
         * @static
         * @param {GeneralMes.SItemHPMP} message SItemHPMP
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemHPMP.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.usedVal = 0;
                object.totalVal = 0;
            }
            if (message.usedVal != null && message.hasOwnProperty("usedVal"))
                object.usedVal = message.usedVal;
            if (message.totalVal != null && message.hasOwnProperty("totalVal"))
                object.totalVal = message.totalVal;
            return object;
        };

        /**
         * Converts this SItemHPMP to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemHPMP
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemHPMP.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemHPMP;
    })();

    GeneralMes.SItem = (function() {

        /**
         * Properties of a SItem.
         * @memberof GeneralMes
         * @interface ISItem
         * @property {number|Long} itemId SItem itemId
         * @property {number} itemType SItem itemType
         * @property {number} itemCount SItem itemCount
         * @property {number} itemBag SItem itemBag
         * @property {number} itemPosition SItem itemPosition
         * @property {number|Long} itemFlags SItem itemFlags
         * @property {number|Long} expiredTime SItem expiredTime
         * @property {number|Long|null} [itemPrice] SItem itemPrice
         * @property {GeneralMes.ISItemEquip|null} [equipAttrs] SItem equipAttrs
         * @property {GeneralMes.ISItemBless|null} [blessAttrs] SItem blessAttrs
         * @property {GeneralMes.ISItemEgg|null} [eggAttrs] SItem eggAttrs
         * @property {GeneralMes.ISItemBloodGobm|null} [gobmAttrs] SItem gobmAttrs
         * @property {GeneralMes.ISCombatPoint|null} [combatPoint] SItem combatPoint
         * @property {GeneralMes.ISItemHPMP|null} [hpmpAttrs] SItem hpmpAttrs
         */

        /**
         * Constructs a new SItem.
         * @memberof GeneralMes
         * @classdesc Represents a SItem.
         * @implements ISItem
         * @constructor
         * @param {GeneralMes.ISItem=} [properties] Properties to set
         */
        function SItem(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItem itemId.
         * @member {number|Long} itemId
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.itemId = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SItem itemType.
         * @member {number} itemType
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.itemType = 0;

        /**
         * SItem itemCount.
         * @member {number} itemCount
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.itemCount = 0;

        /**
         * SItem itemBag.
         * @member {number} itemBag
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.itemBag = 0;

        /**
         * SItem itemPosition.
         * @member {number} itemPosition
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.itemPosition = 0;

        /**
         * SItem itemFlags.
         * @member {number|Long} itemFlags
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.itemFlags = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SItem expiredTime.
         * @member {number|Long} expiredTime
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.expiredTime = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SItem itemPrice.
         * @member {number|Long} itemPrice
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.itemPrice = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SItem equipAttrs.
         * @member {GeneralMes.ISItemEquip|null|undefined} equipAttrs
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.equipAttrs = null;

        /**
         * SItem blessAttrs.
         * @member {GeneralMes.ISItemBless|null|undefined} blessAttrs
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.blessAttrs = null;

        /**
         * SItem eggAttrs.
         * @member {GeneralMes.ISItemEgg|null|undefined} eggAttrs
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.eggAttrs = null;

        /**
         * SItem gobmAttrs.
         * @member {GeneralMes.ISItemBloodGobm|null|undefined} gobmAttrs
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.gobmAttrs = null;

        /**
         * SItem combatPoint.
         * @member {GeneralMes.ISCombatPoint|null|undefined} combatPoint
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.combatPoint = null;

        /**
         * SItem hpmpAttrs.
         * @member {GeneralMes.ISItemHPMP|null|undefined} hpmpAttrs
         * @memberof GeneralMes.SItem
         * @instance
         */
        SItem.prototype.hpmpAttrs = null;

        /**
         * Creates a new SItem instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItem
         * @static
         * @param {GeneralMes.ISItem=} [properties] Properties to set
         * @returns {GeneralMes.SItem} SItem instance
         */
        SItem.create = function create(properties) {
            return new SItem(properties);
        };

        /**
         * Encodes the specified SItem message. Does not implicitly {@link GeneralMes.SItem.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItem
         * @static
         * @param {GeneralMes.ISItem} message SItem message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItem.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.itemId);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.itemType);
            writer.uint32(/* id 3, wireType 0 =*/24).int32(message.itemCount);
            writer.uint32(/* id 4, wireType 0 =*/32).int32(message.itemBag);
            writer.uint32(/* id 5, wireType 0 =*/40).int32(message.itemPosition);
            writer.uint32(/* id 6, wireType 0 =*/48).int64(message.itemFlags);
            writer.uint32(/* id 7, wireType 0 =*/56).int64(message.expiredTime);
            if (message.itemPrice != null && message.hasOwnProperty("itemPrice"))
                writer.uint32(/* id 8, wireType 0 =*/64).int64(message.itemPrice);
            if (message.equipAttrs != null && message.hasOwnProperty("equipAttrs"))
                $root.GeneralMes.SItemEquip.encode(message.equipAttrs, writer.uint32(/* id 9, wireType 2 =*/74).fork()).ldelim();
            if (message.blessAttrs != null && message.hasOwnProperty("blessAttrs"))
                $root.GeneralMes.SItemBless.encode(message.blessAttrs, writer.uint32(/* id 10, wireType 2 =*/82).fork()).ldelim();
            if (message.eggAttrs != null && message.hasOwnProperty("eggAttrs"))
                $root.GeneralMes.SItemEgg.encode(message.eggAttrs, writer.uint32(/* id 11, wireType 2 =*/90).fork()).ldelim();
            if (message.gobmAttrs != null && message.hasOwnProperty("gobmAttrs"))
                $root.GeneralMes.SItemBloodGobm.encode(message.gobmAttrs, writer.uint32(/* id 12, wireType 2 =*/98).fork()).ldelim();
            if (message.combatPoint != null && message.hasOwnProperty("combatPoint"))
                $root.GeneralMes.SCombatPoint.encode(message.combatPoint, writer.uint32(/* id 13, wireType 2 =*/106).fork()).ldelim();
            if (message.hpmpAttrs != null && message.hasOwnProperty("hpmpAttrs"))
                $root.GeneralMes.SItemHPMP.encode(message.hpmpAttrs, writer.uint32(/* id 14, wireType 2 =*/114).fork()).ldelim();
            return writer;
        };

        /**
         * Encodes the specified SItem message, length delimited. Does not implicitly {@link GeneralMes.SItem.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItem
         * @static
         * @param {GeneralMes.ISItem} message SItem message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItem.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItem message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItem
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItem} SItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItem.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItem();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.itemId = reader.int64();
                    break;
                case 2:
                    message.itemType = reader.int32();
                    break;
                case 3:
                    message.itemCount = reader.int32();
                    break;
                case 4:
                    message.itemBag = reader.int32();
                    break;
                case 5:
                    message.itemPosition = reader.int32();
                    break;
                case 6:
                    message.itemFlags = reader.int64();
                    break;
                case 7:
                    message.expiredTime = reader.int64();
                    break;
                case 8:
                    message.itemPrice = reader.int64();
                    break;
                case 9:
                    message.equipAttrs = $root.GeneralMes.SItemEquip.decode(reader, reader.uint32());
                    break;
                case 10:
                    message.blessAttrs = $root.GeneralMes.SItemBless.decode(reader, reader.uint32());
                    break;
                case 11:
                    message.eggAttrs = $root.GeneralMes.SItemEgg.decode(reader, reader.uint32());
                    break;
                case 12:
                    message.gobmAttrs = $root.GeneralMes.SItemBloodGobm.decode(reader, reader.uint32());
                    break;
                case 13:
                    message.combatPoint = $root.GeneralMes.SCombatPoint.decode(reader, reader.uint32());
                    break;
                case 14:
                    message.hpmpAttrs = $root.GeneralMes.SItemHPMP.decode(reader, reader.uint32());
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("itemId"))
                throw $util.ProtocolError("missing required 'itemId'", { instance: message });
            if (!message.hasOwnProperty("itemType"))
                throw $util.ProtocolError("missing required 'itemType'", { instance: message });
            if (!message.hasOwnProperty("itemCount"))
                throw $util.ProtocolError("missing required 'itemCount'", { instance: message });
            if (!message.hasOwnProperty("itemBag"))
                throw $util.ProtocolError("missing required 'itemBag'", { instance: message });
            if (!message.hasOwnProperty("itemPosition"))
                throw $util.ProtocolError("missing required 'itemPosition'", { instance: message });
            if (!message.hasOwnProperty("itemFlags"))
                throw $util.ProtocolError("missing required 'itemFlags'", { instance: message });
            if (!message.hasOwnProperty("expiredTime"))
                throw $util.ProtocolError("missing required 'expiredTime'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItem message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItem
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItem} SItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItem.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItem message.
         * @function verify
         * @memberof GeneralMes.SItem
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItem.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.itemId) && !(message.itemId && $util.isInteger(message.itemId.low) && $util.isInteger(message.itemId.high)))
                return "itemId: integer|Long expected";
            if (!$util.isInteger(message.itemType))
                return "itemType: integer expected";
            if (!$util.isInteger(message.itemCount))
                return "itemCount: integer expected";
            if (!$util.isInteger(message.itemBag))
                return "itemBag: integer expected";
            if (!$util.isInteger(message.itemPosition))
                return "itemPosition: integer expected";
            if (!$util.isInteger(message.itemFlags) && !(message.itemFlags && $util.isInteger(message.itemFlags.low) && $util.isInteger(message.itemFlags.high)))
                return "itemFlags: integer|Long expected";
            if (!$util.isInteger(message.expiredTime) && !(message.expiredTime && $util.isInteger(message.expiredTime.low) && $util.isInteger(message.expiredTime.high)))
                return "expiredTime: integer|Long expected";
            if (message.itemPrice != null && message.hasOwnProperty("itemPrice"))
                if (!$util.isInteger(message.itemPrice) && !(message.itemPrice && $util.isInteger(message.itemPrice.low) && $util.isInteger(message.itemPrice.high)))
                    return "itemPrice: integer|Long expected";
            if (message.equipAttrs != null && message.hasOwnProperty("equipAttrs")) {
                var error = $root.GeneralMes.SItemEquip.verify(message.equipAttrs);
                if (error)
                    return "equipAttrs." + error;
            }
            if (message.blessAttrs != null && message.hasOwnProperty("blessAttrs")) {
                var error = $root.GeneralMes.SItemBless.verify(message.blessAttrs);
                if (error)
                    return "blessAttrs." + error;
            }
            if (message.eggAttrs != null && message.hasOwnProperty("eggAttrs")) {
                var error = $root.GeneralMes.SItemEgg.verify(message.eggAttrs);
                if (error)
                    return "eggAttrs." + error;
            }
            if (message.gobmAttrs != null && message.hasOwnProperty("gobmAttrs")) {
                var error = $root.GeneralMes.SItemBloodGobm.verify(message.gobmAttrs);
                if (error)
                    return "gobmAttrs." + error;
            }
            if (message.combatPoint != null && message.hasOwnProperty("combatPoint")) {
                var error = $root.GeneralMes.SCombatPoint.verify(message.combatPoint);
                if (error)
                    return "combatPoint." + error;
            }
            if (message.hpmpAttrs != null && message.hasOwnProperty("hpmpAttrs")) {
                var error = $root.GeneralMes.SItemHPMP.verify(message.hpmpAttrs);
                if (error)
                    return "hpmpAttrs." + error;
            }
            return null;
        };

        /**
         * Creates a SItem message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItem
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItem} SItem
         */
        SItem.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItem)
                return object;
            var message = new $root.GeneralMes.SItem();
            if (object.itemId != null)
                if ($util.Long)
                    (message.itemId = $util.Long.fromValue(object.itemId)).unsigned = false;
                else if (typeof object.itemId === "string")
                    message.itemId = parseInt(object.itemId, 10);
                else if (typeof object.itemId === "number")
                    message.itemId = object.itemId;
                else if (typeof object.itemId === "object")
                    message.itemId = new $util.LongBits(object.itemId.low >>> 0, object.itemId.high >>> 0).toNumber();
            if (object.itemType != null)
                message.itemType = object.itemType | 0;
            if (object.itemCount != null)
                message.itemCount = object.itemCount | 0;
            if (object.itemBag != null)
                message.itemBag = object.itemBag | 0;
            if (object.itemPosition != null)
                message.itemPosition = object.itemPosition | 0;
            if (object.itemFlags != null)
                if ($util.Long)
                    (message.itemFlags = $util.Long.fromValue(object.itemFlags)).unsigned = false;
                else if (typeof object.itemFlags === "string")
                    message.itemFlags = parseInt(object.itemFlags, 10);
                else if (typeof object.itemFlags === "number")
                    message.itemFlags = object.itemFlags;
                else if (typeof object.itemFlags === "object")
                    message.itemFlags = new $util.LongBits(object.itemFlags.low >>> 0, object.itemFlags.high >>> 0).toNumber();
            if (object.expiredTime != null)
                if ($util.Long)
                    (message.expiredTime = $util.Long.fromValue(object.expiredTime)).unsigned = false;
                else if (typeof object.expiredTime === "string")
                    message.expiredTime = parseInt(object.expiredTime, 10);
                else if (typeof object.expiredTime === "number")
                    message.expiredTime = object.expiredTime;
                else if (typeof object.expiredTime === "object")
                    message.expiredTime = new $util.LongBits(object.expiredTime.low >>> 0, object.expiredTime.high >>> 0).toNumber();
            if (object.itemPrice != null)
                if ($util.Long)
                    (message.itemPrice = $util.Long.fromValue(object.itemPrice)).unsigned = false;
                else if (typeof object.itemPrice === "string")
                    message.itemPrice = parseInt(object.itemPrice, 10);
                else if (typeof object.itemPrice === "number")
                    message.itemPrice = object.itemPrice;
                else if (typeof object.itemPrice === "object")
                    message.itemPrice = new $util.LongBits(object.itemPrice.low >>> 0, object.itemPrice.high >>> 0).toNumber();
            if (object.equipAttrs != null) {
                if (typeof object.equipAttrs !== "object")
                    throw TypeError(".GeneralMes.SItem.equipAttrs: object expected");
                message.equipAttrs = $root.GeneralMes.SItemEquip.fromObject(object.equipAttrs);
            }
            if (object.blessAttrs != null) {
                if (typeof object.blessAttrs !== "object")
                    throw TypeError(".GeneralMes.SItem.blessAttrs: object expected");
                message.blessAttrs = $root.GeneralMes.SItemBless.fromObject(object.blessAttrs);
            }
            if (object.eggAttrs != null) {
                if (typeof object.eggAttrs !== "object")
                    throw TypeError(".GeneralMes.SItem.eggAttrs: object expected");
                message.eggAttrs = $root.GeneralMes.SItemEgg.fromObject(object.eggAttrs);
            }
            if (object.gobmAttrs != null) {
                if (typeof object.gobmAttrs !== "object")
                    throw TypeError(".GeneralMes.SItem.gobmAttrs: object expected");
                message.gobmAttrs = $root.GeneralMes.SItemBloodGobm.fromObject(object.gobmAttrs);
            }
            if (object.combatPoint != null) {
                if (typeof object.combatPoint !== "object")
                    throw TypeError(".GeneralMes.SItem.combatPoint: object expected");
                message.combatPoint = $root.GeneralMes.SCombatPoint.fromObject(object.combatPoint);
            }
            if (object.hpmpAttrs != null) {
                if (typeof object.hpmpAttrs !== "object")
                    throw TypeError(".GeneralMes.SItem.hpmpAttrs: object expected");
                message.hpmpAttrs = $root.GeneralMes.SItemHPMP.fromObject(object.hpmpAttrs);
            }
            return message;
        };

        /**
         * Creates a plain object from a SItem message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItem
         * @static
         * @param {GeneralMes.SItem} message SItem
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItem.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.itemId = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.itemId = options.longs === String ? "0" : 0;
                object.itemType = 0;
                object.itemCount = 0;
                object.itemBag = 0;
                object.itemPosition = 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.itemFlags = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.itemFlags = options.longs === String ? "0" : 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.expiredTime = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.expiredTime = options.longs === String ? "0" : 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.itemPrice = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.itemPrice = options.longs === String ? "0" : 0;
                object.equipAttrs = null;
                object.blessAttrs = null;
                object.eggAttrs = null;
                object.gobmAttrs = null;
                object.combatPoint = null;
                object.hpmpAttrs = null;
            }
            if (message.itemId != null && message.hasOwnProperty("itemId"))
                if (typeof message.itemId === "number")
                    object.itemId = options.longs === String ? String(message.itemId) : message.itemId;
                else
                    object.itemId = options.longs === String ? $util.Long.prototype.toString.call(message.itemId) : options.longs === Number ? new $util.LongBits(message.itemId.low >>> 0, message.itemId.high >>> 0).toNumber() : message.itemId;
            if (message.itemType != null && message.hasOwnProperty("itemType"))
                object.itemType = message.itemType;
            if (message.itemCount != null && message.hasOwnProperty("itemCount"))
                object.itemCount = message.itemCount;
            if (message.itemBag != null && message.hasOwnProperty("itemBag"))
                object.itemBag = message.itemBag;
            if (message.itemPosition != null && message.hasOwnProperty("itemPosition"))
                object.itemPosition = message.itemPosition;
            if (message.itemFlags != null && message.hasOwnProperty("itemFlags"))
                if (typeof message.itemFlags === "number")
                    object.itemFlags = options.longs === String ? String(message.itemFlags) : message.itemFlags;
                else
                    object.itemFlags = options.longs === String ? $util.Long.prototype.toString.call(message.itemFlags) : options.longs === Number ? new $util.LongBits(message.itemFlags.low >>> 0, message.itemFlags.high >>> 0).toNumber() : message.itemFlags;
            if (message.expiredTime != null && message.hasOwnProperty("expiredTime"))
                if (typeof message.expiredTime === "number")
                    object.expiredTime = options.longs === String ? String(message.expiredTime) : message.expiredTime;
                else
                    object.expiredTime = options.longs === String ? $util.Long.prototype.toString.call(message.expiredTime) : options.longs === Number ? new $util.LongBits(message.expiredTime.low >>> 0, message.expiredTime.high >>> 0).toNumber() : message.expiredTime;
            if (message.itemPrice != null && message.hasOwnProperty("itemPrice"))
                if (typeof message.itemPrice === "number")
                    object.itemPrice = options.longs === String ? String(message.itemPrice) : message.itemPrice;
                else
                    object.itemPrice = options.longs === String ? $util.Long.prototype.toString.call(message.itemPrice) : options.longs === Number ? new $util.LongBits(message.itemPrice.low >>> 0, message.itemPrice.high >>> 0).toNumber() : message.itemPrice;
            if (message.equipAttrs != null && message.hasOwnProperty("equipAttrs"))
                object.equipAttrs = $root.GeneralMes.SItemEquip.toObject(message.equipAttrs, options);
            if (message.blessAttrs != null && message.hasOwnProperty("blessAttrs"))
                object.blessAttrs = $root.GeneralMes.SItemBless.toObject(message.blessAttrs, options);
            if (message.eggAttrs != null && message.hasOwnProperty("eggAttrs"))
                object.eggAttrs = $root.GeneralMes.SItemEgg.toObject(message.eggAttrs, options);
            if (message.gobmAttrs != null && message.hasOwnProperty("gobmAttrs"))
                object.gobmAttrs = $root.GeneralMes.SItemBloodGobm.toObject(message.gobmAttrs, options);
            if (message.combatPoint != null && message.hasOwnProperty("combatPoint"))
                object.combatPoint = $root.GeneralMes.SCombatPoint.toObject(message.combatPoint, options);
            if (message.hpmpAttrs != null && message.hasOwnProperty("hpmpAttrs"))
                object.hpmpAttrs = $root.GeneralMes.SItemHPMP.toObject(message.hpmpAttrs, options);
            return object;
        };

        /**
         * Converts this SItem to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItem
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItem.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItem;
    })();

    GeneralMes.SItemPrice = (function() {

        /**
         * Properties of a SItemPrice.
         * @memberof GeneralMes
         * @interface ISItemPrice
         * @property {number} tid SItemPrice tid
         * @property {number} price SItemPrice price
         */

        /**
         * Constructs a new SItemPrice.
         * @memberof GeneralMes
         * @classdesc Represents a SItemPrice.
         * @implements ISItemPrice
         * @constructor
         * @param {GeneralMes.ISItemPrice=} [properties] Properties to set
         */
        function SItemPrice(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SItemPrice tid.
         * @member {number} tid
         * @memberof GeneralMes.SItemPrice
         * @instance
         */
        SItemPrice.prototype.tid = 0;

        /**
         * SItemPrice price.
         * @member {number} price
         * @memberof GeneralMes.SItemPrice
         * @instance
         */
        SItemPrice.prototype.price = 0;

        /**
         * Creates a new SItemPrice instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SItemPrice
         * @static
         * @param {GeneralMes.ISItemPrice=} [properties] Properties to set
         * @returns {GeneralMes.SItemPrice} SItemPrice instance
         */
        SItemPrice.create = function create(properties) {
            return new SItemPrice(properties);
        };

        /**
         * Encodes the specified SItemPrice message. Does not implicitly {@link GeneralMes.SItemPrice.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SItemPrice
         * @static
         * @param {GeneralMes.ISItemPrice} message SItemPrice message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemPrice.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.tid);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.price);
            return writer;
        };

        /**
         * Encodes the specified SItemPrice message, length delimited. Does not implicitly {@link GeneralMes.SItemPrice.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SItemPrice
         * @static
         * @param {GeneralMes.ISItemPrice} message SItemPrice message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SItemPrice.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SItemPrice message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SItemPrice
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SItemPrice} SItemPrice
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemPrice.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SItemPrice();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.tid = reader.int32();
                    break;
                case 2:
                    message.price = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("tid"))
                throw $util.ProtocolError("missing required 'tid'", { instance: message });
            if (!message.hasOwnProperty("price"))
                throw $util.ProtocolError("missing required 'price'", { instance: message });
            return message;
        };

        /**
         * Decodes a SItemPrice message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SItemPrice
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SItemPrice} SItemPrice
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SItemPrice.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SItemPrice message.
         * @function verify
         * @memberof GeneralMes.SItemPrice
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SItemPrice.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.tid))
                return "tid: integer expected";
            if (!$util.isInteger(message.price))
                return "price: integer expected";
            return null;
        };

        /**
         * Creates a SItemPrice message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SItemPrice
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SItemPrice} SItemPrice
         */
        SItemPrice.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SItemPrice)
                return object;
            var message = new $root.GeneralMes.SItemPrice();
            if (object.tid != null)
                message.tid = object.tid | 0;
            if (object.price != null)
                message.price = object.price | 0;
            return message;
        };

        /**
         * Creates a plain object from a SItemPrice message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SItemPrice
         * @static
         * @param {GeneralMes.SItemPrice} message SItemPrice
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SItemPrice.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.tid = 0;
                object.price = 0;
            }
            if (message.tid != null && message.hasOwnProperty("tid"))
                object.tid = message.tid;
            if (message.price != null && message.hasOwnProperty("price"))
                object.price = message.price;
            return object;
        };

        /**
         * Converts this SItemPrice to JSON.
         * @function toJSON
         * @memberof GeneralMes.SItemPrice
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SItemPrice.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SItemPrice;
    })();

    GeneralMes.SPackItem = (function() {

        /**
         * Properties of a SPackItem.
         * @memberof GeneralMes
         * @interface ISPackItem
         * @property {number} tid SPackItem tid
         * @property {number} count SPackItem count
         */

        /**
         * Constructs a new SPackItem.
         * @memberof GeneralMes
         * @classdesc Represents a SPackItem.
         * @implements ISPackItem
         * @constructor
         * @param {GeneralMes.ISPackItem=} [properties] Properties to set
         */
        function SPackItem(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SPackItem tid.
         * @member {number} tid
         * @memberof GeneralMes.SPackItem
         * @instance
         */
        SPackItem.prototype.tid = 0;

        /**
         * SPackItem count.
         * @member {number} count
         * @memberof GeneralMes.SPackItem
         * @instance
         */
        SPackItem.prototype.count = 0;

        /**
         * Creates a new SPackItem instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SPackItem
         * @static
         * @param {GeneralMes.ISPackItem=} [properties] Properties to set
         * @returns {GeneralMes.SPackItem} SPackItem instance
         */
        SPackItem.create = function create(properties) {
            return new SPackItem(properties);
        };

        /**
         * Encodes the specified SPackItem message. Does not implicitly {@link GeneralMes.SPackItem.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SPackItem
         * @static
         * @param {GeneralMes.ISPackItem} message SPackItem message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SPackItem.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.tid);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.count);
            return writer;
        };

        /**
         * Encodes the specified SPackItem message, length delimited. Does not implicitly {@link GeneralMes.SPackItem.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SPackItem
         * @static
         * @param {GeneralMes.ISPackItem} message SPackItem message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SPackItem.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SPackItem message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SPackItem
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SPackItem} SPackItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SPackItem.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SPackItem();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.tid = reader.int32();
                    break;
                case 2:
                    message.count = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("tid"))
                throw $util.ProtocolError("missing required 'tid'", { instance: message });
            if (!message.hasOwnProperty("count"))
                throw $util.ProtocolError("missing required 'count'", { instance: message });
            return message;
        };

        /**
         * Decodes a SPackItem message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SPackItem
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SPackItem} SPackItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SPackItem.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SPackItem message.
         * @function verify
         * @memberof GeneralMes.SPackItem
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SPackItem.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.tid))
                return "tid: integer expected";
            if (!$util.isInteger(message.count))
                return "count: integer expected";
            return null;
        };

        /**
         * Creates a SPackItem message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SPackItem
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SPackItem} SPackItem
         */
        SPackItem.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SPackItem)
                return object;
            var message = new $root.GeneralMes.SPackItem();
            if (object.tid != null)
                message.tid = object.tid | 0;
            if (object.count != null)
                message.count = object.count | 0;
            return message;
        };

        /**
         * Creates a plain object from a SPackItem message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SPackItem
         * @static
         * @param {GeneralMes.SPackItem} message SPackItem
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SPackItem.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.tid = 0;
                object.count = 0;
            }
            if (message.tid != null && message.hasOwnProperty("tid"))
                object.tid = message.tid;
            if (message.count != null && message.hasOwnProperty("count"))
                object.count = message.count;
            return object;
        };

        /**
         * Converts this SPackItem to JSON.
         * @function toJSON
         * @memberof GeneralMes.SPackItem
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SPackItem.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SPackItem;
    })();

    GeneralMes.SRandomItem = (function() {

        /**
         * Properties of a SRandomItem.
         * @memberof GeneralMes
         * @interface ISRandomItem
         * @property {number} randomItemType SRandomItem randomItemType
         * @property {GeneralMes.ISPackItem} packItem SRandomItem packItem
         */

        /**
         * Constructs a new SRandomItem.
         * @memberof GeneralMes
         * @classdesc Represents a SRandomItem.
         * @implements ISRandomItem
         * @constructor
         * @param {GeneralMes.ISRandomItem=} [properties] Properties to set
         */
        function SRandomItem(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SRandomItem randomItemType.
         * @member {number} randomItemType
         * @memberof GeneralMes.SRandomItem
         * @instance
         */
        SRandomItem.prototype.randomItemType = 0;

        /**
         * SRandomItem packItem.
         * @member {GeneralMes.ISPackItem} packItem
         * @memberof GeneralMes.SRandomItem
         * @instance
         */
        SRandomItem.prototype.packItem = null;

        /**
         * Creates a new SRandomItem instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SRandomItem
         * @static
         * @param {GeneralMes.ISRandomItem=} [properties] Properties to set
         * @returns {GeneralMes.SRandomItem} SRandomItem instance
         */
        SRandomItem.create = function create(properties) {
            return new SRandomItem(properties);
        };

        /**
         * Encodes the specified SRandomItem message. Does not implicitly {@link GeneralMes.SRandomItem.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SRandomItem
         * @static
         * @param {GeneralMes.ISRandomItem} message SRandomItem message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SRandomItem.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.randomItemType);
            $root.GeneralMes.SPackItem.encode(message.packItem, writer.uint32(/* id 2, wireType 2 =*/18).fork()).ldelim();
            return writer;
        };

        /**
         * Encodes the specified SRandomItem message, length delimited. Does not implicitly {@link GeneralMes.SRandomItem.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SRandomItem
         * @static
         * @param {GeneralMes.ISRandomItem} message SRandomItem message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SRandomItem.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SRandomItem message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SRandomItem
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SRandomItem} SRandomItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SRandomItem.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SRandomItem();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.randomItemType = reader.int32();
                    break;
                case 2:
                    message.packItem = $root.GeneralMes.SPackItem.decode(reader, reader.uint32());
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("randomItemType"))
                throw $util.ProtocolError("missing required 'randomItemType'", { instance: message });
            if (!message.hasOwnProperty("packItem"))
                throw $util.ProtocolError("missing required 'packItem'", { instance: message });
            return message;
        };

        /**
         * Decodes a SRandomItem message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SRandomItem
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SRandomItem} SRandomItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SRandomItem.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SRandomItem message.
         * @function verify
         * @memberof GeneralMes.SRandomItem
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SRandomItem.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.randomItemType))
                return "randomItemType: integer expected";
            {
                var error = $root.GeneralMes.SPackItem.verify(message.packItem);
                if (error)
                    return "packItem." + error;
            }
            return null;
        };

        /**
         * Creates a SRandomItem message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SRandomItem
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SRandomItem} SRandomItem
         */
        SRandomItem.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SRandomItem)
                return object;
            var message = new $root.GeneralMes.SRandomItem();
            if (object.randomItemType != null)
                message.randomItemType = object.randomItemType | 0;
            if (object.packItem != null) {
                if (typeof object.packItem !== "object")
                    throw TypeError(".GeneralMes.SRandomItem.packItem: object expected");
                message.packItem = $root.GeneralMes.SPackItem.fromObject(object.packItem);
            }
            return message;
        };

        /**
         * Creates a plain object from a SRandomItem message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SRandomItem
         * @static
         * @param {GeneralMes.SRandomItem} message SRandomItem
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SRandomItem.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.randomItemType = 0;
                object.packItem = null;
            }
            if (message.randomItemType != null && message.hasOwnProperty("randomItemType"))
                object.randomItemType = message.randomItemType;
            if (message.packItem != null && message.hasOwnProperty("packItem"))
                object.packItem = $root.GeneralMes.SPackItem.toObject(message.packItem, options);
            return object;
        };

        /**
         * Converts this SRandomItem to JSON.
         * @function toJSON
         * @memberof GeneralMes.SRandomItem
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SRandomItem.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SRandomItem;
    })();

    GeneralMes.SCharacter = (function() {

        /**
         * Properties of a SCharacter.
         * @memberof GeneralMes
         * @interface ISCharacter
         * @property {number|Long} id SCharacter id
         * @property {Uint8Array} name SCharacter name
         * @property {number} profession SCharacter profession
         * @property {number} level SCharacter level
         * @property {number} sex SCharacter sex
         * @property {boolean} newbie SCharacter newbie
         */

        /**
         * Constructs a new SCharacter.
         * @memberof GeneralMes
         * @classdesc Represents a SCharacter.
         * @implements ISCharacter
         * @constructor
         * @param {GeneralMes.ISCharacter=} [properties] Properties to set
         */
        function SCharacter(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SCharacter id.
         * @member {number|Long} id
         * @memberof GeneralMes.SCharacter
         * @instance
         */
        SCharacter.prototype.id = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SCharacter name.
         * @member {Uint8Array} name
         * @memberof GeneralMes.SCharacter
         * @instance
         */
        SCharacter.prototype.name = $util.newBuffer([]);

        /**
         * SCharacter profession.
         * @member {number} profession
         * @memberof GeneralMes.SCharacter
         * @instance
         */
        SCharacter.prototype.profession = 0;

        /**
         * SCharacter level.
         * @member {number} level
         * @memberof GeneralMes.SCharacter
         * @instance
         */
        SCharacter.prototype.level = 0;

        /**
         * SCharacter sex.
         * @member {number} sex
         * @memberof GeneralMes.SCharacter
         * @instance
         */
        SCharacter.prototype.sex = 0;

        /**
         * SCharacter newbie.
         * @member {boolean} newbie
         * @memberof GeneralMes.SCharacter
         * @instance
         */
        SCharacter.prototype.newbie = false;

        /**
         * Creates a new SCharacter instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SCharacter
         * @static
         * @param {GeneralMes.ISCharacter=} [properties] Properties to set
         * @returns {GeneralMes.SCharacter} SCharacter instance
         */
        SCharacter.create = function create(properties) {
            return new SCharacter(properties);
        };

        /**
         * Encodes the specified SCharacter message. Does not implicitly {@link GeneralMes.SCharacter.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SCharacter
         * @static
         * @param {GeneralMes.ISCharacter} message SCharacter message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCharacter.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.id);
            writer.uint32(/* id 2, wireType 2 =*/18).bytes(message.name);
            writer.uint32(/* id 3, wireType 0 =*/24).int32(message.profession);
            writer.uint32(/* id 4, wireType 0 =*/32).int32(message.level);
            writer.uint32(/* id 5, wireType 0 =*/40).int32(message.sex);
            writer.uint32(/* id 6, wireType 0 =*/48).bool(message.newbie);
            return writer;
        };

        /**
         * Encodes the specified SCharacter message, length delimited. Does not implicitly {@link GeneralMes.SCharacter.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SCharacter
         * @static
         * @param {GeneralMes.ISCharacter} message SCharacter message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCharacter.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SCharacter message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SCharacter
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SCharacter} SCharacter
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCharacter.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SCharacter();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.id = reader.int64();
                    break;
                case 2:
                    message.name = reader.bytes();
                    break;
                case 3:
                    message.profession = reader.int32();
                    break;
                case 4:
                    message.level = reader.int32();
                    break;
                case 5:
                    message.sex = reader.int32();
                    break;
                case 6:
                    message.newbie = reader.bool();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("id"))
                throw $util.ProtocolError("missing required 'id'", { instance: message });
            if (!message.hasOwnProperty("name"))
                throw $util.ProtocolError("missing required 'name'", { instance: message });
            if (!message.hasOwnProperty("profession"))
                throw $util.ProtocolError("missing required 'profession'", { instance: message });
            if (!message.hasOwnProperty("level"))
                throw $util.ProtocolError("missing required 'level'", { instance: message });
            if (!message.hasOwnProperty("sex"))
                throw $util.ProtocolError("missing required 'sex'", { instance: message });
            if (!message.hasOwnProperty("newbie"))
                throw $util.ProtocolError("missing required 'newbie'", { instance: message });
            return message;
        };

        /**
         * Decodes a SCharacter message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SCharacter
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SCharacter} SCharacter
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCharacter.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SCharacter message.
         * @function verify
         * @memberof GeneralMes.SCharacter
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SCharacter.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.id) && !(message.id && $util.isInteger(message.id.low) && $util.isInteger(message.id.high)))
                return "id: integer|Long expected";
            if (!(message.name && typeof message.name.length === "number" || $util.isString(message.name)))
                return "name: buffer expected";
            if (!$util.isInteger(message.profession))
                return "profession: integer expected";
            if (!$util.isInteger(message.level))
                return "level: integer expected";
            if (!$util.isInteger(message.sex))
                return "sex: integer expected";
            if (typeof message.newbie !== "boolean")
                return "newbie: boolean expected";
            return null;
        };

        /**
         * Creates a SCharacter message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SCharacter
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SCharacter} SCharacter
         */
        SCharacter.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SCharacter)
                return object;
            var message = new $root.GeneralMes.SCharacter();
            if (object.id != null)
                if ($util.Long)
                    (message.id = $util.Long.fromValue(object.id)).unsigned = false;
                else if (typeof object.id === "string")
                    message.id = parseInt(object.id, 10);
                else if (typeof object.id === "number")
                    message.id = object.id;
                else if (typeof object.id === "object")
                    message.id = new $util.LongBits(object.id.low >>> 0, object.id.high >>> 0).toNumber();
            if (object.name != null)
                if (typeof object.name === "string")
                    $util.base64.decode(object.name, message.name = $util.newBuffer($util.base64.length(object.name)), 0);
                else if (object.name.length)
                    message.name = object.name;
            if (object.profession != null)
                message.profession = object.profession | 0;
            if (object.level != null)
                message.level = object.level | 0;
            if (object.sex != null)
                message.sex = object.sex | 0;
            if (object.newbie != null)
                message.newbie = Boolean(object.newbie);
            return message;
        };

        /**
         * Creates a plain object from a SCharacter message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SCharacter
         * @static
         * @param {GeneralMes.SCharacter} message SCharacter
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SCharacter.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.id = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.id = options.longs === String ? "0" : 0;
                object.name = options.bytes === String ? "" : [];
                object.profession = 0;
                object.level = 0;
                object.sex = 0;
                object.newbie = false;
            }
            if (message.id != null && message.hasOwnProperty("id"))
                if (typeof message.id === "number")
                    object.id = options.longs === String ? String(message.id) : message.id;
                else
                    object.id = options.longs === String ? $util.Long.prototype.toString.call(message.id) : options.longs === Number ? new $util.LongBits(message.id.low >>> 0, message.id.high >>> 0).toNumber() : message.id;
            if (message.name != null && message.hasOwnProperty("name"))
                object.name = options.bytes === String ? $util.base64.encode(message.name, 0, message.name.length) : options.bytes === Array ? Array.prototype.slice.call(message.name) : message.name;
            if (message.profession != null && message.hasOwnProperty("profession"))
                object.profession = message.profession;
            if (message.level != null && message.hasOwnProperty("level"))
                object.level = message.level;
            if (message.sex != null && message.hasOwnProperty("sex"))
                object.sex = message.sex;
            if (message.newbie != null && message.hasOwnProperty("newbie"))
                object.newbie = message.newbie;
            return object;
        };

        /**
         * Converts this SCharacter to JSON.
         * @function toJSON
         * @memberof GeneralMes.SCharacter
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SCharacter.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SCharacter;
    })();

    GeneralMes.CSLoginBegan = (function() {

        /**
         * Properties of a CSLoginBegan.
         * @memberof GeneralMes
         * @interface ICSLoginBegan
         */

        /**
         * Constructs a new CSLoginBegan.
         * @memberof GeneralMes
         * @classdesc Represents a CSLoginBegan.
         * @implements ICSLoginBegan
         * @constructor
         * @param {GeneralMes.ICSLoginBegan=} [properties] Properties to set
         */
        function CSLoginBegan(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * Creates a new CSLoginBegan instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSLoginBegan
         * @static
         * @param {GeneralMes.ICSLoginBegan=} [properties] Properties to set
         * @returns {GeneralMes.CSLoginBegan} CSLoginBegan instance
         */
        CSLoginBegan.create = function create(properties) {
            return new CSLoginBegan(properties);
        };

        /**
         * Encodes the specified CSLoginBegan message. Does not implicitly {@link GeneralMes.CSLoginBegan.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSLoginBegan
         * @static
         * @param {GeneralMes.ICSLoginBegan} message CSLoginBegan message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSLoginBegan.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            return writer;
        };

        /**
         * Encodes the specified CSLoginBegan message, length delimited. Does not implicitly {@link GeneralMes.CSLoginBegan.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSLoginBegan
         * @static
         * @param {GeneralMes.ICSLoginBegan} message CSLoginBegan message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSLoginBegan.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSLoginBegan message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSLoginBegan
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSLoginBegan} CSLoginBegan
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSLoginBegan.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSLoginBegan();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            return message;
        };

        /**
         * Decodes a CSLoginBegan message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSLoginBegan
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSLoginBegan} CSLoginBegan
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSLoginBegan.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSLoginBegan message.
         * @function verify
         * @memberof GeneralMes.CSLoginBegan
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSLoginBegan.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            return null;
        };

        /**
         * Creates a CSLoginBegan message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSLoginBegan
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSLoginBegan} CSLoginBegan
         */
        CSLoginBegan.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSLoginBegan)
                return object;
            return new $root.GeneralMes.CSLoginBegan();
        };

        /**
         * Creates a plain object from a CSLoginBegan message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSLoginBegan
         * @static
         * @param {GeneralMes.CSLoginBegan} message CSLoginBegan
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSLoginBegan.toObject = function toObject() {
            return {};
        };

        /**
         * Converts this CSLoginBegan to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSLoginBegan
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSLoginBegan.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSLoginBegan;
    })();

    GeneralMes.CSLoginGate = (function() {

        /**
         * Properties of a CSLoginGate.
         * @memberof GeneralMes
         * @interface ICSLoginGate
         */

        /**
         * Constructs a new CSLoginGate.
         * @memberof GeneralMes
         * @classdesc Represents a CSLoginGate.
         * @implements ICSLoginGate
         * @constructor
         * @param {GeneralMes.ICSLoginGate=} [properties] Properties to set
         */
        function CSLoginGate(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * Creates a new CSLoginGate instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSLoginGate
         * @static
         * @param {GeneralMes.ICSLoginGate=} [properties] Properties to set
         * @returns {GeneralMes.CSLoginGate} CSLoginGate instance
         */
        CSLoginGate.create = function create(properties) {
            return new CSLoginGate(properties);
        };

        /**
         * Encodes the specified CSLoginGate message. Does not implicitly {@link GeneralMes.CSLoginGate.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSLoginGate
         * @static
         * @param {GeneralMes.ICSLoginGate} message CSLoginGate message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSLoginGate.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            return writer;
        };

        /**
         * Encodes the specified CSLoginGate message, length delimited. Does not implicitly {@link GeneralMes.CSLoginGate.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSLoginGate
         * @static
         * @param {GeneralMes.ICSLoginGate} message CSLoginGate message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSLoginGate.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSLoginGate message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSLoginGate
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSLoginGate} CSLoginGate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSLoginGate.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSLoginGate();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            return message;
        };

        /**
         * Decodes a CSLoginGate message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSLoginGate
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSLoginGate} CSLoginGate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSLoginGate.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSLoginGate message.
         * @function verify
         * @memberof GeneralMes.CSLoginGate
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSLoginGate.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            return null;
        };

        /**
         * Creates a CSLoginGate message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSLoginGate
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSLoginGate} CSLoginGate
         */
        CSLoginGate.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSLoginGate)
                return object;
            return new $root.GeneralMes.CSLoginGate();
        };

        /**
         * Creates a plain object from a CSLoginGate message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSLoginGate
         * @static
         * @param {GeneralMes.CSLoginGate} message CSLoginGate
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSLoginGate.toObject = function toObject() {
            return {};
        };

        /**
         * Converts this CSLoginGate to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSLoginGate
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSLoginGate.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSLoginGate;
    })();

    GeneralMes.SCLoginGate = (function() {

        /**
         * Properties of a SCLoginGate.
         * @memberof GeneralMes
         * @interface ISCLoginGate
         * @property {number} result SCLoginGate result
         */

        /**
         * Constructs a new SCLoginGate.
         * @memberof GeneralMes
         * @classdesc Represents a SCLoginGate.
         * @implements ISCLoginGate
         * @constructor
         * @param {GeneralMes.ISCLoginGate=} [properties] Properties to set
         */
        function SCLoginGate(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SCLoginGate result.
         * @member {number} result
         * @memberof GeneralMes.SCLoginGate
         * @instance
         */
        SCLoginGate.prototype.result = 0;

        /**
         * Creates a new SCLoginGate instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SCLoginGate
         * @static
         * @param {GeneralMes.ISCLoginGate=} [properties] Properties to set
         * @returns {GeneralMes.SCLoginGate} SCLoginGate instance
         */
        SCLoginGate.create = function create(properties) {
            return new SCLoginGate(properties);
        };

        /**
         * Encodes the specified SCLoginGate message. Does not implicitly {@link GeneralMes.SCLoginGate.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SCLoginGate
         * @static
         * @param {GeneralMes.ISCLoginGate} message SCLoginGate message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCLoginGate.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.result);
            return writer;
        };

        /**
         * Encodes the specified SCLoginGate message, length delimited. Does not implicitly {@link GeneralMes.SCLoginGate.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SCLoginGate
         * @static
         * @param {GeneralMes.ISCLoginGate} message SCLoginGate message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCLoginGate.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SCLoginGate message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SCLoginGate
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SCLoginGate} SCLoginGate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCLoginGate.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SCLoginGate();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.result = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("result"))
                throw $util.ProtocolError("missing required 'result'", { instance: message });
            return message;
        };

        /**
         * Decodes a SCLoginGate message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SCLoginGate
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SCLoginGate} SCLoginGate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCLoginGate.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SCLoginGate message.
         * @function verify
         * @memberof GeneralMes.SCLoginGate
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SCLoginGate.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.result))
                return "result: integer expected";
            return null;
        };

        /**
         * Creates a SCLoginGate message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SCLoginGate
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SCLoginGate} SCLoginGate
         */
        SCLoginGate.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SCLoginGate)
                return object;
            var message = new $root.GeneralMes.SCLoginGate();
            if (object.result != null)
                message.result = object.result | 0;
            return message;
        };

        /**
         * Creates a plain object from a SCLoginGate message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SCLoginGate
         * @static
         * @param {GeneralMes.SCLoginGate} message SCLoginGate
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SCLoginGate.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults)
                object.result = 0;
            if (message.result != null && message.hasOwnProperty("result"))
                object.result = message.result;
            return object;
        };

        /**
         * Converts this SCLoginGate to JSON.
         * @function toJSON
         * @memberof GeneralMes.SCLoginGate
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SCLoginGate.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SCLoginGate;
    })();

    GeneralMes.CSQueryCharacters = (function() {

        /**
         * Properties of a CSQueryCharacters.
         * @memberof GeneralMes
         * @interface ICSQueryCharacters
         */

        /**
         * Constructs a new CSQueryCharacters.
         * @memberof GeneralMes
         * @classdesc Represents a CSQueryCharacters.
         * @implements ICSQueryCharacters
         * @constructor
         * @param {GeneralMes.ICSQueryCharacters=} [properties] Properties to set
         */
        function CSQueryCharacters(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * Creates a new CSQueryCharacters instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSQueryCharacters
         * @static
         * @param {GeneralMes.ICSQueryCharacters=} [properties] Properties to set
         * @returns {GeneralMes.CSQueryCharacters} CSQueryCharacters instance
         */
        CSQueryCharacters.create = function create(properties) {
            return new CSQueryCharacters(properties);
        };

        /**
         * Encodes the specified CSQueryCharacters message. Does not implicitly {@link GeneralMes.CSQueryCharacters.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSQueryCharacters
         * @static
         * @param {GeneralMes.ICSQueryCharacters} message CSQueryCharacters message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSQueryCharacters.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            return writer;
        };

        /**
         * Encodes the specified CSQueryCharacters message, length delimited. Does not implicitly {@link GeneralMes.CSQueryCharacters.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSQueryCharacters
         * @static
         * @param {GeneralMes.ICSQueryCharacters} message CSQueryCharacters message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSQueryCharacters.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSQueryCharacters message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSQueryCharacters
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSQueryCharacters} CSQueryCharacters
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSQueryCharacters.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSQueryCharacters();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            return message;
        };

        /**
         * Decodes a CSQueryCharacters message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSQueryCharacters
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSQueryCharacters} CSQueryCharacters
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSQueryCharacters.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSQueryCharacters message.
         * @function verify
         * @memberof GeneralMes.CSQueryCharacters
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSQueryCharacters.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            return null;
        };

        /**
         * Creates a CSQueryCharacters message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSQueryCharacters
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSQueryCharacters} CSQueryCharacters
         */
        CSQueryCharacters.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSQueryCharacters)
                return object;
            return new $root.GeneralMes.CSQueryCharacters();
        };

        /**
         * Creates a plain object from a CSQueryCharacters message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSQueryCharacters
         * @static
         * @param {GeneralMes.CSQueryCharacters} message CSQueryCharacters
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSQueryCharacters.toObject = function toObject() {
            return {};
        };

        /**
         * Converts this CSQueryCharacters to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSQueryCharacters
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSQueryCharacters.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSQueryCharacters;
    })();

    GeneralMes.SCQueryCharacters = (function() {

        /**
         * Properties of a SCQueryCharacters.
         * @memberof GeneralMes
         * @interface ISCQueryCharacters
         * @property {Array.<GeneralMes.ISCharacter>|null} [characters] SCQueryCharacters characters
         * @property {number|Long|null} [lastLoginHid] SCQueryCharacters lastLoginHid
         */

        /**
         * Constructs a new SCQueryCharacters.
         * @memberof GeneralMes
         * @classdesc Represents a SCQueryCharacters.
         * @implements ISCQueryCharacters
         * @constructor
         * @param {GeneralMes.ISCQueryCharacters=} [properties] Properties to set
         */
        function SCQueryCharacters(properties) {
            this.characters = [];
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SCQueryCharacters characters.
         * @member {Array.<GeneralMes.ISCharacter>} characters
         * @memberof GeneralMes.SCQueryCharacters
         * @instance
         */
        SCQueryCharacters.prototype.characters = $util.emptyArray;

        /**
         * SCQueryCharacters lastLoginHid.
         * @member {number|Long} lastLoginHid
         * @memberof GeneralMes.SCQueryCharacters
         * @instance
         */
        SCQueryCharacters.prototype.lastLoginHid = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * Creates a new SCQueryCharacters instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SCQueryCharacters
         * @static
         * @param {GeneralMes.ISCQueryCharacters=} [properties] Properties to set
         * @returns {GeneralMes.SCQueryCharacters} SCQueryCharacters instance
         */
        SCQueryCharacters.create = function create(properties) {
            return new SCQueryCharacters(properties);
        };

        /**
         * Encodes the specified SCQueryCharacters message. Does not implicitly {@link GeneralMes.SCQueryCharacters.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SCQueryCharacters
         * @static
         * @param {GeneralMes.ISCQueryCharacters} message SCQueryCharacters message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCQueryCharacters.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            if (message.characters != null && message.characters.length)
                for (var i = 0; i < message.characters.length; ++i)
                    $root.GeneralMes.SCharacter.encode(message.characters[i], writer.uint32(/* id 1, wireType 2 =*/10).fork()).ldelim();
            if (message.lastLoginHid != null && message.hasOwnProperty("lastLoginHid"))
                writer.uint32(/* id 2, wireType 0 =*/16).int64(message.lastLoginHid);
            return writer;
        };

        /**
         * Encodes the specified SCQueryCharacters message, length delimited. Does not implicitly {@link GeneralMes.SCQueryCharacters.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SCQueryCharacters
         * @static
         * @param {GeneralMes.ISCQueryCharacters} message SCQueryCharacters message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCQueryCharacters.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SCQueryCharacters message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SCQueryCharacters
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SCQueryCharacters} SCQueryCharacters
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCQueryCharacters.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SCQueryCharacters();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    if (!(message.characters && message.characters.length))
                        message.characters = [];
                    message.characters.push($root.GeneralMes.SCharacter.decode(reader, reader.uint32()));
                    break;
                case 2:
                    message.lastLoginHid = reader.int64();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            return message;
        };

        /**
         * Decodes a SCQueryCharacters message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SCQueryCharacters
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SCQueryCharacters} SCQueryCharacters
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCQueryCharacters.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SCQueryCharacters message.
         * @function verify
         * @memberof GeneralMes.SCQueryCharacters
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SCQueryCharacters.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (message.characters != null && message.hasOwnProperty("characters")) {
                if (!Array.isArray(message.characters))
                    return "characters: array expected";
                for (var i = 0; i < message.characters.length; ++i) {
                    var error = $root.GeneralMes.SCharacter.verify(message.characters[i]);
                    if (error)
                        return "characters." + error;
                }
            }
            if (message.lastLoginHid != null && message.hasOwnProperty("lastLoginHid"))
                if (!$util.isInteger(message.lastLoginHid) && !(message.lastLoginHid && $util.isInteger(message.lastLoginHid.low) && $util.isInteger(message.lastLoginHid.high)))
                    return "lastLoginHid: integer|Long expected";
            return null;
        };

        /**
         * Creates a SCQueryCharacters message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SCQueryCharacters
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SCQueryCharacters} SCQueryCharacters
         */
        SCQueryCharacters.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SCQueryCharacters)
                return object;
            var message = new $root.GeneralMes.SCQueryCharacters();
            if (object.characters) {
                if (!Array.isArray(object.characters))
                    throw TypeError(".GeneralMes.SCQueryCharacters.characters: array expected");
                message.characters = [];
                for (var i = 0; i < object.characters.length; ++i) {
                    if (typeof object.characters[i] !== "object")
                        throw TypeError(".GeneralMes.SCQueryCharacters.characters: object expected");
                    message.characters[i] = $root.GeneralMes.SCharacter.fromObject(object.characters[i]);
                }
            }
            if (object.lastLoginHid != null)
                if ($util.Long)
                    (message.lastLoginHid = $util.Long.fromValue(object.lastLoginHid)).unsigned = false;
                else if (typeof object.lastLoginHid === "string")
                    message.lastLoginHid = parseInt(object.lastLoginHid, 10);
                else if (typeof object.lastLoginHid === "number")
                    message.lastLoginHid = object.lastLoginHid;
                else if (typeof object.lastLoginHid === "object")
                    message.lastLoginHid = new $util.LongBits(object.lastLoginHid.low >>> 0, object.lastLoginHid.high >>> 0).toNumber();
            return message;
        };

        /**
         * Creates a plain object from a SCQueryCharacters message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SCQueryCharacters
         * @static
         * @param {GeneralMes.SCQueryCharacters} message SCQueryCharacters
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SCQueryCharacters.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.arrays || options.defaults)
                object.characters = [];
            if (options.defaults)
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.lastLoginHid = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.lastLoginHid = options.longs === String ? "0" : 0;
            if (message.characters && message.characters.length) {
                object.characters = [];
                for (var j = 0; j < message.characters.length; ++j)
                    object.characters[j] = $root.GeneralMes.SCharacter.toObject(message.characters[j], options);
            }
            if (message.lastLoginHid != null && message.hasOwnProperty("lastLoginHid"))
                if (typeof message.lastLoginHid === "number")
                    object.lastLoginHid = options.longs === String ? String(message.lastLoginHid) : message.lastLoginHid;
                else
                    object.lastLoginHid = options.longs === String ? $util.Long.prototype.toString.call(message.lastLoginHid) : options.longs === Number ? new $util.LongBits(message.lastLoginHid.low >>> 0, message.lastLoginHid.high >>> 0).toNumber() : message.lastLoginHid;
            return object;
        };

        /**
         * Converts this SCQueryCharacters to JSON.
         * @function toJSON
         * @memberof GeneralMes.SCQueryCharacters
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SCQueryCharacters.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SCQueryCharacters;
    })();

    GeneralMes.CSCharacterCreate = (function() {

        /**
         * Properties of a CSCharacterCreate.
         * @memberof GeneralMes
         * @interface ICSCharacterCreate
         * @property {Uint8Array} name CSCharacterCreate name
         * @property {number} profession CSCharacterCreate profession
         * @property {number} sex CSCharacterCreate sex
         */

        /**
         * Constructs a new CSCharacterCreate.
         * @memberof GeneralMes
         * @classdesc Represents a CSCharacterCreate.
         * @implements ICSCharacterCreate
         * @constructor
         * @param {GeneralMes.ICSCharacterCreate=} [properties] Properties to set
         */
        function CSCharacterCreate(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * CSCharacterCreate name.
         * @member {Uint8Array} name
         * @memberof GeneralMes.CSCharacterCreate
         * @instance
         */
        CSCharacterCreate.prototype.name = $util.newBuffer([]);

        /**
         * CSCharacterCreate profession.
         * @member {number} profession
         * @memberof GeneralMes.CSCharacterCreate
         * @instance
         */
        CSCharacterCreate.prototype.profession = 0;

        /**
         * CSCharacterCreate sex.
         * @member {number} sex
         * @memberof GeneralMes.CSCharacterCreate
         * @instance
         */
        CSCharacterCreate.prototype.sex = 0;

        /**
         * Creates a new CSCharacterCreate instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSCharacterCreate
         * @static
         * @param {GeneralMes.ICSCharacterCreate=} [properties] Properties to set
         * @returns {GeneralMes.CSCharacterCreate} CSCharacterCreate instance
         */
        CSCharacterCreate.create = function create(properties) {
            return new CSCharacterCreate(properties);
        };

        /**
         * Encodes the specified CSCharacterCreate message. Does not implicitly {@link GeneralMes.CSCharacterCreate.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSCharacterCreate
         * @static
         * @param {GeneralMes.ICSCharacterCreate} message CSCharacterCreate message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterCreate.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 2 =*/10).bytes(message.name);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.profession);
            writer.uint32(/* id 3, wireType 0 =*/24).int32(message.sex);
            return writer;
        };

        /**
         * Encodes the specified CSCharacterCreate message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterCreate.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSCharacterCreate
         * @static
         * @param {GeneralMes.ICSCharacterCreate} message CSCharacterCreate message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterCreate.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSCharacterCreate message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSCharacterCreate
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSCharacterCreate} CSCharacterCreate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterCreate.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSCharacterCreate();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.name = reader.bytes();
                    break;
                case 2:
                    message.profession = reader.int32();
                    break;
                case 3:
                    message.sex = reader.int32();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("name"))
                throw $util.ProtocolError("missing required 'name'", { instance: message });
            if (!message.hasOwnProperty("profession"))
                throw $util.ProtocolError("missing required 'profession'", { instance: message });
            if (!message.hasOwnProperty("sex"))
                throw $util.ProtocolError("missing required 'sex'", { instance: message });
            return message;
        };

        /**
         * Decodes a CSCharacterCreate message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSCharacterCreate
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSCharacterCreate} CSCharacterCreate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterCreate.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSCharacterCreate message.
         * @function verify
         * @memberof GeneralMes.CSCharacterCreate
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSCharacterCreate.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!(message.name && typeof message.name.length === "number" || $util.isString(message.name)))
                return "name: buffer expected";
            if (!$util.isInteger(message.profession))
                return "profession: integer expected";
            if (!$util.isInteger(message.sex))
                return "sex: integer expected";
            return null;
        };

        /**
         * Creates a CSCharacterCreate message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSCharacterCreate
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSCharacterCreate} CSCharacterCreate
         */
        CSCharacterCreate.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSCharacterCreate)
                return object;
            var message = new $root.GeneralMes.CSCharacterCreate();
            if (object.name != null)
                if (typeof object.name === "string")
                    $util.base64.decode(object.name, message.name = $util.newBuffer($util.base64.length(object.name)), 0);
                else if (object.name.length)
                    message.name = object.name;
            if (object.profession != null)
                message.profession = object.profession | 0;
            if (object.sex != null)
                message.sex = object.sex | 0;
            return message;
        };

        /**
         * Creates a plain object from a CSCharacterCreate message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSCharacterCreate
         * @static
         * @param {GeneralMes.CSCharacterCreate} message CSCharacterCreate
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSCharacterCreate.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.name = options.bytes === String ? "" : [];
                object.profession = 0;
                object.sex = 0;
            }
            if (message.name != null && message.hasOwnProperty("name"))
                object.name = options.bytes === String ? $util.base64.encode(message.name, 0, message.name.length) : options.bytes === Array ? Array.prototype.slice.call(message.name) : message.name;
            if (message.profession != null && message.hasOwnProperty("profession"))
                object.profession = message.profession;
            if (message.sex != null && message.hasOwnProperty("sex"))
                object.sex = message.sex;
            return object;
        };

        /**
         * Converts this CSCharacterCreate to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSCharacterCreate
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSCharacterCreate.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSCharacterCreate;
    })();

    GeneralMes.SCCharacterCreate = (function() {

        /**
         * Properties of a SCCharacterCreate.
         * @memberof GeneralMes
         * @interface ISCCharacterCreate
         * @property {number} result SCCharacterCreate result
         * @property {GeneralMes.ISCharacter|null} [character] SCCharacterCreate character
         */

        /**
         * Constructs a new SCCharacterCreate.
         * @memberof GeneralMes
         * @classdesc Represents a SCCharacterCreate.
         * @implements ISCCharacterCreate
         * @constructor
         * @param {GeneralMes.ISCCharacterCreate=} [properties] Properties to set
         */
        function SCCharacterCreate(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SCCharacterCreate result.
         * @member {number} result
         * @memberof GeneralMes.SCCharacterCreate
         * @instance
         */
        SCCharacterCreate.prototype.result = 0;

        /**
         * SCCharacterCreate character.
         * @member {GeneralMes.ISCharacter|null|undefined} character
         * @memberof GeneralMes.SCCharacterCreate
         * @instance
         */
        SCCharacterCreate.prototype.character = null;

        /**
         * Creates a new SCCharacterCreate instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SCCharacterCreate
         * @static
         * @param {GeneralMes.ISCCharacterCreate=} [properties] Properties to set
         * @returns {GeneralMes.SCCharacterCreate} SCCharacterCreate instance
         */
        SCCharacterCreate.create = function create(properties) {
            return new SCCharacterCreate(properties);
        };

        /**
         * Encodes the specified SCCharacterCreate message. Does not implicitly {@link GeneralMes.SCCharacterCreate.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SCCharacterCreate
         * @static
         * @param {GeneralMes.ISCCharacterCreate} message SCCharacterCreate message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCCharacterCreate.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.result);
            if (message.character != null && message.hasOwnProperty("character"))
                $root.GeneralMes.SCharacter.encode(message.character, writer.uint32(/* id 2, wireType 2 =*/18).fork()).ldelim();
            return writer;
        };

        /**
         * Encodes the specified SCCharacterCreate message, length delimited. Does not implicitly {@link GeneralMes.SCCharacterCreate.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SCCharacterCreate
         * @static
         * @param {GeneralMes.ISCCharacterCreate} message SCCharacterCreate message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCCharacterCreate.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SCCharacterCreate message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SCCharacterCreate
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SCCharacterCreate} SCCharacterCreate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCCharacterCreate.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SCCharacterCreate();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.result = reader.int32();
                    break;
                case 2:
                    message.character = $root.GeneralMes.SCharacter.decode(reader, reader.uint32());
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("result"))
                throw $util.ProtocolError("missing required 'result'", { instance: message });
            return message;
        };

        /**
         * Decodes a SCCharacterCreate message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SCCharacterCreate
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SCCharacterCreate} SCCharacterCreate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCCharacterCreate.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SCCharacterCreate message.
         * @function verify
         * @memberof GeneralMes.SCCharacterCreate
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SCCharacterCreate.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.result))
                return "result: integer expected";
            if (message.character != null && message.hasOwnProperty("character")) {
                var error = $root.GeneralMes.SCharacter.verify(message.character);
                if (error)
                    return "character." + error;
            }
            return null;
        };

        /**
         * Creates a SCCharacterCreate message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SCCharacterCreate
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SCCharacterCreate} SCCharacterCreate
         */
        SCCharacterCreate.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SCCharacterCreate)
                return object;
            var message = new $root.GeneralMes.SCCharacterCreate();
            if (object.result != null)
                message.result = object.result | 0;
            if (object.character != null) {
                if (typeof object.character !== "object")
                    throw TypeError(".GeneralMes.SCCharacterCreate.character: object expected");
                message.character = $root.GeneralMes.SCharacter.fromObject(object.character);
            }
            return message;
        };

        /**
         * Creates a plain object from a SCCharacterCreate message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SCCharacterCreate
         * @static
         * @param {GeneralMes.SCCharacterCreate} message SCCharacterCreate
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SCCharacterCreate.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.result = 0;
                object.character = null;
            }
            if (message.result != null && message.hasOwnProperty("result"))
                object.result = message.result;
            if (message.character != null && message.hasOwnProperty("character"))
                object.character = $root.GeneralMes.SCharacter.toObject(message.character, options);
            return object;
        };

        /**
         * Converts this SCCharacterCreate to JSON.
         * @function toJSON
         * @memberof GeneralMes.SCCharacterCreate
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SCCharacterCreate.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SCCharacterCreate;
    })();

    GeneralMes.CSCharacterDelete = (function() {

        /**
         * Properties of a CSCharacterDelete.
         * @memberof GeneralMes
         * @interface ICSCharacterDelete
         * @property {number|Long} id CSCharacterDelete id
         */

        /**
         * Constructs a new CSCharacterDelete.
         * @memberof GeneralMes
         * @classdesc Represents a CSCharacterDelete.
         * @implements ICSCharacterDelete
         * @constructor
         * @param {GeneralMes.ICSCharacterDelete=} [properties] Properties to set
         */
        function CSCharacterDelete(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * CSCharacterDelete id.
         * @member {number|Long} id
         * @memberof GeneralMes.CSCharacterDelete
         * @instance
         */
        CSCharacterDelete.prototype.id = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * Creates a new CSCharacterDelete instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSCharacterDelete
         * @static
         * @param {GeneralMes.ICSCharacterDelete=} [properties] Properties to set
         * @returns {GeneralMes.CSCharacterDelete} CSCharacterDelete instance
         */
        CSCharacterDelete.create = function create(properties) {
            return new CSCharacterDelete(properties);
        };

        /**
         * Encodes the specified CSCharacterDelete message. Does not implicitly {@link GeneralMes.CSCharacterDelete.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSCharacterDelete
         * @static
         * @param {GeneralMes.ICSCharacterDelete} message CSCharacterDelete message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterDelete.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.id);
            return writer;
        };

        /**
         * Encodes the specified CSCharacterDelete message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterDelete.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSCharacterDelete
         * @static
         * @param {GeneralMes.ICSCharacterDelete} message CSCharacterDelete message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterDelete.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSCharacterDelete message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSCharacterDelete
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSCharacterDelete} CSCharacterDelete
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterDelete.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSCharacterDelete();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.id = reader.int64();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("id"))
                throw $util.ProtocolError("missing required 'id'", { instance: message });
            return message;
        };

        /**
         * Decodes a CSCharacterDelete message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSCharacterDelete
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSCharacterDelete} CSCharacterDelete
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterDelete.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSCharacterDelete message.
         * @function verify
         * @memberof GeneralMes.CSCharacterDelete
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSCharacterDelete.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.id) && !(message.id && $util.isInteger(message.id.low) && $util.isInteger(message.id.high)))
                return "id: integer|Long expected";
            return null;
        };

        /**
         * Creates a CSCharacterDelete message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSCharacterDelete
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSCharacterDelete} CSCharacterDelete
         */
        CSCharacterDelete.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSCharacterDelete)
                return object;
            var message = new $root.GeneralMes.CSCharacterDelete();
            if (object.id != null)
                if ($util.Long)
                    (message.id = $util.Long.fromValue(object.id)).unsigned = false;
                else if (typeof object.id === "string")
                    message.id = parseInt(object.id, 10);
                else if (typeof object.id === "number")
                    message.id = object.id;
                else if (typeof object.id === "object")
                    message.id = new $util.LongBits(object.id.low >>> 0, object.id.high >>> 0).toNumber();
            return message;
        };

        /**
         * Creates a plain object from a CSCharacterDelete message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSCharacterDelete
         * @static
         * @param {GeneralMes.CSCharacterDelete} message CSCharacterDelete
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSCharacterDelete.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults)
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.id = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.id = options.longs === String ? "0" : 0;
            if (message.id != null && message.hasOwnProperty("id"))
                if (typeof message.id === "number")
                    object.id = options.longs === String ? String(message.id) : message.id;
                else
                    object.id = options.longs === String ? $util.Long.prototype.toString.call(message.id) : options.longs === Number ? new $util.LongBits(message.id.low >>> 0, message.id.high >>> 0).toNumber() : message.id;
            return object;
        };

        /**
         * Converts this CSCharacterDelete to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSCharacterDelete
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSCharacterDelete.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSCharacterDelete;
    })();

    GeneralMes.SCCharacterDelete = (function() {

        /**
         * Properties of a SCCharacterDelete.
         * @memberof GeneralMes
         * @interface ISCCharacterDelete
         * @property {number} result SCCharacterDelete result
         * @property {number|Long|null} [id] SCCharacterDelete id
         * @property {number|Long|null} [surviveTime] SCCharacterDelete surviveTime
         */

        /**
         * Constructs a new SCCharacterDelete.
         * @memberof GeneralMes
         * @classdesc Represents a SCCharacterDelete.
         * @implements ISCCharacterDelete
         * @constructor
         * @param {GeneralMes.ISCCharacterDelete=} [properties] Properties to set
         */
        function SCCharacterDelete(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SCCharacterDelete result.
         * @member {number} result
         * @memberof GeneralMes.SCCharacterDelete
         * @instance
         */
        SCCharacterDelete.prototype.result = 0;

        /**
         * SCCharacterDelete id.
         * @member {number|Long} id
         * @memberof GeneralMes.SCCharacterDelete
         * @instance
         */
        SCCharacterDelete.prototype.id = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SCCharacterDelete surviveTime.
         * @member {number|Long} surviveTime
         * @memberof GeneralMes.SCCharacterDelete
         * @instance
         */
        SCCharacterDelete.prototype.surviveTime = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * Creates a new SCCharacterDelete instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SCCharacterDelete
         * @static
         * @param {GeneralMes.ISCCharacterDelete=} [properties] Properties to set
         * @returns {GeneralMes.SCCharacterDelete} SCCharacterDelete instance
         */
        SCCharacterDelete.create = function create(properties) {
            return new SCCharacterDelete(properties);
        };

        /**
         * Encodes the specified SCCharacterDelete message. Does not implicitly {@link GeneralMes.SCCharacterDelete.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SCCharacterDelete
         * @static
         * @param {GeneralMes.ISCCharacterDelete} message SCCharacterDelete message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCCharacterDelete.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.result);
            if (message.id != null && message.hasOwnProperty("id"))
                writer.uint32(/* id 2, wireType 0 =*/16).int64(message.id);
            if (message.surviveTime != null && message.hasOwnProperty("surviveTime"))
                writer.uint32(/* id 3, wireType 0 =*/24).int64(message.surviveTime);
            return writer;
        };

        /**
         * Encodes the specified SCCharacterDelete message, length delimited. Does not implicitly {@link GeneralMes.SCCharacterDelete.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SCCharacterDelete
         * @static
         * @param {GeneralMes.ISCCharacterDelete} message SCCharacterDelete message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCCharacterDelete.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SCCharacterDelete message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SCCharacterDelete
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SCCharacterDelete} SCCharacterDelete
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCCharacterDelete.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SCCharacterDelete();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.result = reader.int32();
                    break;
                case 2:
                    message.id = reader.int64();
                    break;
                case 3:
                    message.surviveTime = reader.int64();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("result"))
                throw $util.ProtocolError("missing required 'result'", { instance: message });
            return message;
        };

        /**
         * Decodes a SCCharacterDelete message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SCCharacterDelete
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SCCharacterDelete} SCCharacterDelete
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCCharacterDelete.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SCCharacterDelete message.
         * @function verify
         * @memberof GeneralMes.SCCharacterDelete
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SCCharacterDelete.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.result))
                return "result: integer expected";
            if (message.id != null && message.hasOwnProperty("id"))
                if (!$util.isInteger(message.id) && !(message.id && $util.isInteger(message.id.low) && $util.isInteger(message.id.high)))
                    return "id: integer|Long expected";
            if (message.surviveTime != null && message.hasOwnProperty("surviveTime"))
                if (!$util.isInteger(message.surviveTime) && !(message.surviveTime && $util.isInteger(message.surviveTime.low) && $util.isInteger(message.surviveTime.high)))
                    return "surviveTime: integer|Long expected";
            return null;
        };

        /**
         * Creates a SCCharacterDelete message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SCCharacterDelete
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SCCharacterDelete} SCCharacterDelete
         */
        SCCharacterDelete.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SCCharacterDelete)
                return object;
            var message = new $root.GeneralMes.SCCharacterDelete();
            if (object.result != null)
                message.result = object.result | 0;
            if (object.id != null)
                if ($util.Long)
                    (message.id = $util.Long.fromValue(object.id)).unsigned = false;
                else if (typeof object.id === "string")
                    message.id = parseInt(object.id, 10);
                else if (typeof object.id === "number")
                    message.id = object.id;
                else if (typeof object.id === "object")
                    message.id = new $util.LongBits(object.id.low >>> 0, object.id.high >>> 0).toNumber();
            if (object.surviveTime != null)
                if ($util.Long)
                    (message.surviveTime = $util.Long.fromValue(object.surviveTime)).unsigned = false;
                else if (typeof object.surviveTime === "string")
                    message.surviveTime = parseInt(object.surviveTime, 10);
                else if (typeof object.surviveTime === "number")
                    message.surviveTime = object.surviveTime;
                else if (typeof object.surviveTime === "object")
                    message.surviveTime = new $util.LongBits(object.surviveTime.low >>> 0, object.surviveTime.high >>> 0).toNumber();
            return message;
        };

        /**
         * Creates a plain object from a SCCharacterDelete message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SCCharacterDelete
         * @static
         * @param {GeneralMes.SCCharacterDelete} message SCCharacterDelete
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SCCharacterDelete.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.result = 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.id = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.id = options.longs === String ? "0" : 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.surviveTime = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.surviveTime = options.longs === String ? "0" : 0;
            }
            if (message.result != null && message.hasOwnProperty("result"))
                object.result = message.result;
            if (message.id != null && message.hasOwnProperty("id"))
                if (typeof message.id === "number")
                    object.id = options.longs === String ? String(message.id) : message.id;
                else
                    object.id = options.longs === String ? $util.Long.prototype.toString.call(message.id) : options.longs === Number ? new $util.LongBits(message.id.low >>> 0, message.id.high >>> 0).toNumber() : message.id;
            if (message.surviveTime != null && message.hasOwnProperty("surviveTime"))
                if (typeof message.surviveTime === "number")
                    object.surviveTime = options.longs === String ? String(message.surviveTime) : message.surviveTime;
                else
                    object.surviveTime = options.longs === String ? $util.Long.prototype.toString.call(message.surviveTime) : options.longs === Number ? new $util.LongBits(message.surviveTime.low >>> 0, message.surviveTime.high >>> 0).toNumber() : message.surviveTime;
            return object;
        };

        /**
         * Converts this SCCharacterDelete to JSON.
         * @function toJSON
         * @memberof GeneralMes.SCCharacterDelete
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SCCharacterDelete.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SCCharacterDelete;
    })();

    GeneralMes.SLadderInformation = (function() {

        /**
         * Properties of a SLadderInformation.
         * @memberof GeneralMes
         * @interface ISLadderInformation
         * @property {number} basemap SLadderInformation basemap
         * @property {number|Long} gamemap SLadderInformation gamemap
         */

        /**
         * Constructs a new SLadderInformation.
         * @memberof GeneralMes
         * @classdesc Represents a SLadderInformation.
         * @implements ISLadderInformation
         * @constructor
         * @param {GeneralMes.ISLadderInformation=} [properties] Properties to set
         */
        function SLadderInformation(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SLadderInformation basemap.
         * @member {number} basemap
         * @memberof GeneralMes.SLadderInformation
         * @instance
         */
        SLadderInformation.prototype.basemap = 0;

        /**
         * SLadderInformation gamemap.
         * @member {number|Long} gamemap
         * @memberof GeneralMes.SLadderInformation
         * @instance
         */
        SLadderInformation.prototype.gamemap = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * Creates a new SLadderInformation instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SLadderInformation
         * @static
         * @param {GeneralMes.ISLadderInformation=} [properties] Properties to set
         * @returns {GeneralMes.SLadderInformation} SLadderInformation instance
         */
        SLadderInformation.create = function create(properties) {
            return new SLadderInformation(properties);
        };

        /**
         * Encodes the specified SLadderInformation message. Does not implicitly {@link GeneralMes.SLadderInformation.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SLadderInformation
         * @static
         * @param {GeneralMes.ISLadderInformation} message SLadderInformation message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SLadderInformation.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.basemap);
            writer.uint32(/* id 2, wireType 0 =*/16).int64(message.gamemap);
            return writer;
        };

        /**
         * Encodes the specified SLadderInformation message, length delimited. Does not implicitly {@link GeneralMes.SLadderInformation.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SLadderInformation
         * @static
         * @param {GeneralMes.ISLadderInformation} message SLadderInformation message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SLadderInformation.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SLadderInformation message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SLadderInformation
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SLadderInformation} SLadderInformation
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SLadderInformation.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SLadderInformation();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.basemap = reader.int32();
                    break;
                case 2:
                    message.gamemap = reader.int64();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("basemap"))
                throw $util.ProtocolError("missing required 'basemap'", { instance: message });
            if (!message.hasOwnProperty("gamemap"))
                throw $util.ProtocolError("missing required 'gamemap'", { instance: message });
            return message;
        };

        /**
         * Decodes a SLadderInformation message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SLadderInformation
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SLadderInformation} SLadderInformation
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SLadderInformation.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SLadderInformation message.
         * @function verify
         * @memberof GeneralMes.SLadderInformation
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SLadderInformation.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.basemap))
                return "basemap: integer expected";
            if (!$util.isInteger(message.gamemap) && !(message.gamemap && $util.isInteger(message.gamemap.low) && $util.isInteger(message.gamemap.high)))
                return "gamemap: integer|Long expected";
            return null;
        };

        /**
         * Creates a SLadderInformation message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SLadderInformation
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SLadderInformation} SLadderInformation
         */
        SLadderInformation.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SLadderInformation)
                return object;
            var message = new $root.GeneralMes.SLadderInformation();
            if (object.basemap != null)
                message.basemap = object.basemap | 0;
            if (object.gamemap != null)
                if ($util.Long)
                    (message.gamemap = $util.Long.fromValue(object.gamemap)).unsigned = false;
                else if (typeof object.gamemap === "string")
                    message.gamemap = parseInt(object.gamemap, 10);
                else if (typeof object.gamemap === "number")
                    message.gamemap = object.gamemap;
                else if (typeof object.gamemap === "object")
                    message.gamemap = new $util.LongBits(object.gamemap.low >>> 0, object.gamemap.high >>> 0).toNumber();
            return message;
        };

        /**
         * Creates a plain object from a SLadderInformation message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SLadderInformation
         * @static
         * @param {GeneralMes.SLadderInformation} message SLadderInformation
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SLadderInformation.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.basemap = 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.gamemap = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.gamemap = options.longs === String ? "0" : 0;
            }
            if (message.basemap != null && message.hasOwnProperty("basemap"))
                object.basemap = message.basemap;
            if (message.gamemap != null && message.hasOwnProperty("gamemap"))
                if (typeof message.gamemap === "number")
                    object.gamemap = options.longs === String ? String(message.gamemap) : message.gamemap;
                else
                    object.gamemap = options.longs === String ? $util.Long.prototype.toString.call(message.gamemap) : options.longs === Number ? new $util.LongBits(message.gamemap.low >>> 0, message.gamemap.high >>> 0).toNumber() : message.gamemap;
            return object;
        };

        /**
         * Converts this SLadderInformation to JSON.
         * @function toJSON
         * @memberof GeneralMes.SLadderInformation
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SLadderInformation.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SLadderInformation;
    })();

    GeneralMes.CSCharacterLogin = (function() {

        /**
         * Properties of a CSCharacterLogin.
         * @memberof GeneralMes
         * @interface ICSCharacterLogin
         * @property {number|Long} cid CSCharacterLogin cid
         * @property {Uint8Array|null} [mac] CSCharacterLogin mac
         * @property {GeneralMes.ISLadderInformation|null} [ladderInfo] CSCharacterLogin ladderInfo
         */

        /**
         * Constructs a new CSCharacterLogin.
         * @memberof GeneralMes
         * @classdesc Represents a CSCharacterLogin.
         * @implements ICSCharacterLogin
         * @constructor
         * @param {GeneralMes.ICSCharacterLogin=} [properties] Properties to set
         */
        function CSCharacterLogin(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * CSCharacterLogin cid.
         * @member {number|Long} cid
         * @memberof GeneralMes.CSCharacterLogin
         * @instance
         */
        CSCharacterLogin.prototype.cid = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * CSCharacterLogin mac.
         * @member {Uint8Array} mac
         * @memberof GeneralMes.CSCharacterLogin
         * @instance
         */
        CSCharacterLogin.prototype.mac = $util.newBuffer([]);

        /**
         * CSCharacterLogin ladderInfo.
         * @member {GeneralMes.ISLadderInformation|null|undefined} ladderInfo
         * @memberof GeneralMes.CSCharacterLogin
         * @instance
         */
        CSCharacterLogin.prototype.ladderInfo = null;

        /**
         * Creates a new CSCharacterLogin instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSCharacterLogin
         * @static
         * @param {GeneralMes.ICSCharacterLogin=} [properties] Properties to set
         * @returns {GeneralMes.CSCharacterLogin} CSCharacterLogin instance
         */
        CSCharacterLogin.create = function create(properties) {
            return new CSCharacterLogin(properties);
        };

        /**
         * Encodes the specified CSCharacterLogin message. Does not implicitly {@link GeneralMes.CSCharacterLogin.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSCharacterLogin
         * @static
         * @param {GeneralMes.ICSCharacterLogin} message CSCharacterLogin message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterLogin.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.cid);
            if (message.mac != null && message.hasOwnProperty("mac"))
                writer.uint32(/* id 2, wireType 2 =*/18).bytes(message.mac);
            if (message.ladderInfo != null && message.hasOwnProperty("ladderInfo"))
                $root.GeneralMes.SLadderInformation.encode(message.ladderInfo, writer.uint32(/* id 3, wireType 2 =*/26).fork()).ldelim();
            return writer;
        };

        /**
         * Encodes the specified CSCharacterLogin message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterLogin.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSCharacterLogin
         * @static
         * @param {GeneralMes.ICSCharacterLogin} message CSCharacterLogin message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterLogin.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSCharacterLogin message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSCharacterLogin
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSCharacterLogin} CSCharacterLogin
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterLogin.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSCharacterLogin();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.cid = reader.int64();
                    break;
                case 2:
                    message.mac = reader.bytes();
                    break;
                case 3:
                    message.ladderInfo = $root.GeneralMes.SLadderInformation.decode(reader, reader.uint32());
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("cid"))
                throw $util.ProtocolError("missing required 'cid'", { instance: message });
            return message;
        };

        /**
         * Decodes a CSCharacterLogin message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSCharacterLogin
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSCharacterLogin} CSCharacterLogin
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterLogin.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSCharacterLogin message.
         * @function verify
         * @memberof GeneralMes.CSCharacterLogin
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSCharacterLogin.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.cid) && !(message.cid && $util.isInteger(message.cid.low) && $util.isInteger(message.cid.high)))
                return "cid: integer|Long expected";
            if (message.mac != null && message.hasOwnProperty("mac"))
                if (!(message.mac && typeof message.mac.length === "number" || $util.isString(message.mac)))
                    return "mac: buffer expected";
            if (message.ladderInfo != null && message.hasOwnProperty("ladderInfo")) {
                var error = $root.GeneralMes.SLadderInformation.verify(message.ladderInfo);
                if (error)
                    return "ladderInfo." + error;
            }
            return null;
        };

        /**
         * Creates a CSCharacterLogin message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSCharacterLogin
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSCharacterLogin} CSCharacterLogin
         */
        CSCharacterLogin.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSCharacterLogin)
                return object;
            var message = new $root.GeneralMes.CSCharacterLogin();
            if (object.cid != null)
                if ($util.Long)
                    (message.cid = $util.Long.fromValue(object.cid)).unsigned = false;
                else if (typeof object.cid === "string")
                    message.cid = parseInt(object.cid, 10);
                else if (typeof object.cid === "number")
                    message.cid = object.cid;
                else if (typeof object.cid === "object")
                    message.cid = new $util.LongBits(object.cid.low >>> 0, object.cid.high >>> 0).toNumber();
            if (object.mac != null)
                if (typeof object.mac === "string")
                    $util.base64.decode(object.mac, message.mac = $util.newBuffer($util.base64.length(object.mac)), 0);
                else if (object.mac.length)
                    message.mac = object.mac;
            if (object.ladderInfo != null) {
                if (typeof object.ladderInfo !== "object")
                    throw TypeError(".GeneralMes.CSCharacterLogin.ladderInfo: object expected");
                message.ladderInfo = $root.GeneralMes.SLadderInformation.fromObject(object.ladderInfo);
            }
            return message;
        };

        /**
         * Creates a plain object from a CSCharacterLogin message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSCharacterLogin
         * @static
         * @param {GeneralMes.CSCharacterLogin} message CSCharacterLogin
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSCharacterLogin.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.cid = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.cid = options.longs === String ? "0" : 0;
                object.mac = options.bytes === String ? "" : [];
                object.ladderInfo = null;
            }
            if (message.cid != null && message.hasOwnProperty("cid"))
                if (typeof message.cid === "number")
                    object.cid = options.longs === String ? String(message.cid) : message.cid;
                else
                    object.cid = options.longs === String ? $util.Long.prototype.toString.call(message.cid) : options.longs === Number ? new $util.LongBits(message.cid.low >>> 0, message.cid.high >>> 0).toNumber() : message.cid;
            if (message.mac != null && message.hasOwnProperty("mac"))
                object.mac = options.bytes === String ? $util.base64.encode(message.mac, 0, message.mac.length) : options.bytes === Array ? Array.prototype.slice.call(message.mac) : message.mac;
            if (message.ladderInfo != null && message.hasOwnProperty("ladderInfo"))
                object.ladderInfo = $root.GeneralMes.SLadderInformation.toObject(message.ladderInfo, options);
            return object;
        };

        /**
         * Converts this CSCharacterLogin to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSCharacterLogin
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSCharacterLogin.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSCharacterLogin;
    })();

    GeneralMes.SServerInformation = (function() {

        /**
         * Properties of a SServerInformation.
         * @memberof GeneralMes
         * @interface ISServerInformation
         * @property {number|Long} zoneId SServerInformation zoneId
         * @property {Uint8Array} operatorsName SServerInformation operatorsName
         */

        /**
         * Constructs a new SServerInformation.
         * @memberof GeneralMes
         * @classdesc Represents a SServerInformation.
         * @implements ISServerInformation
         * @constructor
         * @param {GeneralMes.ISServerInformation=} [properties] Properties to set
         */
        function SServerInformation(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SServerInformation zoneId.
         * @member {number|Long} zoneId
         * @memberof GeneralMes.SServerInformation
         * @instance
         */
        SServerInformation.prototype.zoneId = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SServerInformation operatorsName.
         * @member {Uint8Array} operatorsName
         * @memberof GeneralMes.SServerInformation
         * @instance
         */
        SServerInformation.prototype.operatorsName = $util.newBuffer([]);

        /**
         * Creates a new SServerInformation instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SServerInformation
         * @static
         * @param {GeneralMes.ISServerInformation=} [properties] Properties to set
         * @returns {GeneralMes.SServerInformation} SServerInformation instance
         */
        SServerInformation.create = function create(properties) {
            return new SServerInformation(properties);
        };

        /**
         * Encodes the specified SServerInformation message. Does not implicitly {@link GeneralMes.SServerInformation.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SServerInformation
         * @static
         * @param {GeneralMes.ISServerInformation} message SServerInformation message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SServerInformation.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.zoneId);
            writer.uint32(/* id 2, wireType 2 =*/18).bytes(message.operatorsName);
            return writer;
        };

        /**
         * Encodes the specified SServerInformation message, length delimited. Does not implicitly {@link GeneralMes.SServerInformation.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SServerInformation
         * @static
         * @param {GeneralMes.ISServerInformation} message SServerInformation message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SServerInformation.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SServerInformation message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SServerInformation
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SServerInformation} SServerInformation
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SServerInformation.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SServerInformation();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.zoneId = reader.int64();
                    break;
                case 2:
                    message.operatorsName = reader.bytes();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("zoneId"))
                throw $util.ProtocolError("missing required 'zoneId'", { instance: message });
            if (!message.hasOwnProperty("operatorsName"))
                throw $util.ProtocolError("missing required 'operatorsName'", { instance: message });
            return message;
        };

        /**
         * Decodes a SServerInformation message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SServerInformation
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SServerInformation} SServerInformation
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SServerInformation.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SServerInformation message.
         * @function verify
         * @memberof GeneralMes.SServerInformation
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SServerInformation.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.zoneId) && !(message.zoneId && $util.isInteger(message.zoneId.low) && $util.isInteger(message.zoneId.high)))
                return "zoneId: integer|Long expected";
            if (!(message.operatorsName && typeof message.operatorsName.length === "number" || $util.isString(message.operatorsName)))
                return "operatorsName: buffer expected";
            return null;
        };

        /**
         * Creates a SServerInformation message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SServerInformation
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SServerInformation} SServerInformation
         */
        SServerInformation.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SServerInformation)
                return object;
            var message = new $root.GeneralMes.SServerInformation();
            if (object.zoneId != null)
                if ($util.Long)
                    (message.zoneId = $util.Long.fromValue(object.zoneId)).unsigned = false;
                else if (typeof object.zoneId === "string")
                    message.zoneId = parseInt(object.zoneId, 10);
                else if (typeof object.zoneId === "number")
                    message.zoneId = object.zoneId;
                else if (typeof object.zoneId === "object")
                    message.zoneId = new $util.LongBits(object.zoneId.low >>> 0, object.zoneId.high >>> 0).toNumber();
            if (object.operatorsName != null)
                if (typeof object.operatorsName === "string")
                    $util.base64.decode(object.operatorsName, message.operatorsName = $util.newBuffer($util.base64.length(object.operatorsName)), 0);
                else if (object.operatorsName.length)
                    message.operatorsName = object.operatorsName;
            return message;
        };

        /**
         * Creates a plain object from a SServerInformation message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SServerInformation
         * @static
         * @param {GeneralMes.SServerInformation} message SServerInformation
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SServerInformation.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.zoneId = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.zoneId = options.longs === String ? "0" : 0;
                object.operatorsName = options.bytes === String ? "" : [];
            }
            if (message.zoneId != null && message.hasOwnProperty("zoneId"))
                if (typeof message.zoneId === "number")
                    object.zoneId = options.longs === String ? String(message.zoneId) : message.zoneId;
                else
                    object.zoneId = options.longs === String ? $util.Long.prototype.toString.call(message.zoneId) : options.longs === Number ? new $util.LongBits(message.zoneId.low >>> 0, message.zoneId.high >>> 0).toNumber() : message.zoneId;
            if (message.operatorsName != null && message.hasOwnProperty("operatorsName"))
                object.operatorsName = options.bytes === String ? $util.base64.encode(message.operatorsName, 0, message.operatorsName.length) : options.bytes === Array ? Array.prototype.slice.call(message.operatorsName) : message.operatorsName;
            return object;
        };

        /**
         * Converts this SServerInformation to JSON.
         * @function toJSON
         * @memberof GeneralMes.SServerInformation
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SServerInformation.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SServerInformation;
    })();

    GeneralMes.SCCharacterLogin = (function() {

        /**
         * Properties of a SCCharacterLogin.
         * @memberof GeneralMes
         * @interface ISCCharacterLogin
         * @property {number} result SCCharacterLogin result
         * @property {Uint8Array|null} [error] SCCharacterLogin error
         */

        /**
         * Constructs a new SCCharacterLogin.
         * @memberof GeneralMes
         * @classdesc Represents a SCCharacterLogin.
         * @implements ISCCharacterLogin
         * @constructor
         * @param {GeneralMes.ISCCharacterLogin=} [properties] Properties to set
         */
        function SCCharacterLogin(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SCCharacterLogin result.
         * @member {number} result
         * @memberof GeneralMes.SCCharacterLogin
         * @instance
         */
        SCCharacterLogin.prototype.result = 0;

        /**
         * SCCharacterLogin error.
         * @member {Uint8Array} error
         * @memberof GeneralMes.SCCharacterLogin
         * @instance
         */
        SCCharacterLogin.prototype.error = $util.newBuffer([]);

        /**
         * Creates a new SCCharacterLogin instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SCCharacterLogin
         * @static
         * @param {GeneralMes.ISCCharacterLogin=} [properties] Properties to set
         * @returns {GeneralMes.SCCharacterLogin} SCCharacterLogin instance
         */
        SCCharacterLogin.create = function create(properties) {
            return new SCCharacterLogin(properties);
        };

        /**
         * Encodes the specified SCCharacterLogin message. Does not implicitly {@link GeneralMes.SCCharacterLogin.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SCCharacterLogin
         * @static
         * @param {GeneralMes.ISCCharacterLogin} message SCCharacterLogin message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCCharacterLogin.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.result);
            if (message.error != null && message.hasOwnProperty("error"))
                writer.uint32(/* id 2, wireType 2 =*/18).bytes(message.error);
            return writer;
        };

        /**
         * Encodes the specified SCCharacterLogin message, length delimited. Does not implicitly {@link GeneralMes.SCCharacterLogin.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SCCharacterLogin
         * @static
         * @param {GeneralMes.ISCCharacterLogin} message SCCharacterLogin message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCCharacterLogin.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SCCharacterLogin message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SCCharacterLogin
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SCCharacterLogin} SCCharacterLogin
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCCharacterLogin.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SCCharacterLogin();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.result = reader.int32();
                    break;
                case 2:
                    message.error = reader.bytes();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("result"))
                throw $util.ProtocolError("missing required 'result'", { instance: message });
            return message;
        };

        /**
         * Decodes a SCCharacterLogin message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SCCharacterLogin
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SCCharacterLogin} SCCharacterLogin
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCCharacterLogin.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SCCharacterLogin message.
         * @function verify
         * @memberof GeneralMes.SCCharacterLogin
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SCCharacterLogin.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.result))
                return "result: integer expected";
            if (message.error != null && message.hasOwnProperty("error"))
                if (!(message.error && typeof message.error.length === "number" || $util.isString(message.error)))
                    return "error: buffer expected";
            return null;
        };

        /**
         * Creates a SCCharacterLogin message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SCCharacterLogin
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SCCharacterLogin} SCCharacterLogin
         */
        SCCharacterLogin.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SCCharacterLogin)
                return object;
            var message = new $root.GeneralMes.SCCharacterLogin();
            if (object.result != null)
                message.result = object.result | 0;
            if (object.error != null)
                if (typeof object.error === "string")
                    $util.base64.decode(object.error, message.error = $util.newBuffer($util.base64.length(object.error)), 0);
                else if (object.error.length)
                    message.error = object.error;
            return message;
        };

        /**
         * Creates a plain object from a SCCharacterLogin message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SCCharacterLogin
         * @static
         * @param {GeneralMes.SCCharacterLogin} message SCCharacterLogin
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SCCharacterLogin.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.result = 0;
                object.error = options.bytes === String ? "" : [];
            }
            if (message.result != null && message.hasOwnProperty("result"))
                object.result = message.result;
            if (message.error != null && message.hasOwnProperty("error"))
                object.error = options.bytes === String ? $util.base64.encode(message.error, 0, message.error.length) : options.bytes === Array ? Array.prototype.slice.call(message.error) : message.error;
            return object;
        };

        /**
         * Converts this SCCharacterLogin to JSON.
         * @function toJSON
         * @memberof GeneralMes.SCCharacterLogin
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SCCharacterLogin.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SCCharacterLogin;
    })();

    GeneralMes.CSCharacterEnterWorld = (function() {

        /**
         * Properties of a CSCharacterEnterWorld.
         * @memberof GeneralMes
         * @interface ICSCharacterEnterWorld
         * @property {number|Long} id CSCharacterEnterWorld id
         */

        /**
         * Constructs a new CSCharacterEnterWorld.
         * @memberof GeneralMes
         * @classdesc Represents a CSCharacterEnterWorld.
         * @implements ICSCharacterEnterWorld
         * @constructor
         * @param {GeneralMes.ICSCharacterEnterWorld=} [properties] Properties to set
         */
        function CSCharacterEnterWorld(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * CSCharacterEnterWorld id.
         * @member {number|Long} id
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @instance
         */
        CSCharacterEnterWorld.prototype.id = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * Creates a new CSCharacterEnterWorld instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @static
         * @param {GeneralMes.ICSCharacterEnterWorld=} [properties] Properties to set
         * @returns {GeneralMes.CSCharacterEnterWorld} CSCharacterEnterWorld instance
         */
        CSCharacterEnterWorld.create = function create(properties) {
            return new CSCharacterEnterWorld(properties);
        };

        /**
         * Encodes the specified CSCharacterEnterWorld message. Does not implicitly {@link GeneralMes.CSCharacterEnterWorld.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @static
         * @param {GeneralMes.ICSCharacterEnterWorld} message CSCharacterEnterWorld message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterEnterWorld.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.id);
            return writer;
        };

        /**
         * Encodes the specified CSCharacterEnterWorld message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterEnterWorld.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @static
         * @param {GeneralMes.ICSCharacterEnterWorld} message CSCharacterEnterWorld message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterEnterWorld.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSCharacterEnterWorld message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSCharacterEnterWorld} CSCharacterEnterWorld
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterEnterWorld.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSCharacterEnterWorld();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.id = reader.int64();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("id"))
                throw $util.ProtocolError("missing required 'id'", { instance: message });
            return message;
        };

        /**
         * Decodes a CSCharacterEnterWorld message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSCharacterEnterWorld} CSCharacterEnterWorld
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterEnterWorld.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSCharacterEnterWorld message.
         * @function verify
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSCharacterEnterWorld.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.id) && !(message.id && $util.isInteger(message.id.low) && $util.isInteger(message.id.high)))
                return "id: integer|Long expected";
            return null;
        };

        /**
         * Creates a CSCharacterEnterWorld message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSCharacterEnterWorld} CSCharacterEnterWorld
         */
        CSCharacterEnterWorld.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSCharacterEnterWorld)
                return object;
            var message = new $root.GeneralMes.CSCharacterEnterWorld();
            if (object.id != null)
                if ($util.Long)
                    (message.id = $util.Long.fromValue(object.id)).unsigned = false;
                else if (typeof object.id === "string")
                    message.id = parseInt(object.id, 10);
                else if (typeof object.id === "number")
                    message.id = object.id;
                else if (typeof object.id === "object")
                    message.id = new $util.LongBits(object.id.low >>> 0, object.id.high >>> 0).toNumber();
            return message;
        };

        /**
         * Creates a plain object from a CSCharacterEnterWorld message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @static
         * @param {GeneralMes.CSCharacterEnterWorld} message CSCharacterEnterWorld
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSCharacterEnterWorld.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults)
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.id = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.id = options.longs === String ? "0" : 0;
            if (message.id != null && message.hasOwnProperty("id"))
                if (typeof message.id === "number")
                    object.id = options.longs === String ? String(message.id) : message.id;
                else
                    object.id = options.longs === String ? $util.Long.prototype.toString.call(message.id) : options.longs === Number ? new $util.LongBits(message.id.low >>> 0, message.id.high >>> 0).toNumber() : message.id;
            return object;
        };

        /**
         * Converts this CSCharacterEnterWorld to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSCharacterEnterWorld
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSCharacterEnterWorld.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSCharacterEnterWorld;
    })();

    GeneralMes.CSCharacterRevert = (function() {

        /**
         * Properties of a CSCharacterRevert.
         * @memberof GeneralMes
         * @interface ICSCharacterRevert
         * @property {number|Long} id CSCharacterRevert id
         */

        /**
         * Constructs a new CSCharacterRevert.
         * @memberof GeneralMes
         * @classdesc Represents a CSCharacterRevert.
         * @implements ICSCharacterRevert
         * @constructor
         * @param {GeneralMes.ICSCharacterRevert=} [properties] Properties to set
         */
        function CSCharacterRevert(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * CSCharacterRevert id.
         * @member {number|Long} id
         * @memberof GeneralMes.CSCharacterRevert
         * @instance
         */
        CSCharacterRevert.prototype.id = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * Creates a new CSCharacterRevert instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSCharacterRevert
         * @static
         * @param {GeneralMes.ICSCharacterRevert=} [properties] Properties to set
         * @returns {GeneralMes.CSCharacterRevert} CSCharacterRevert instance
         */
        CSCharacterRevert.create = function create(properties) {
            return new CSCharacterRevert(properties);
        };

        /**
         * Encodes the specified CSCharacterRevert message. Does not implicitly {@link GeneralMes.CSCharacterRevert.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSCharacterRevert
         * @static
         * @param {GeneralMes.ICSCharacterRevert} message CSCharacterRevert message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterRevert.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.id);
            return writer;
        };

        /**
         * Encodes the specified CSCharacterRevert message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterRevert.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSCharacterRevert
         * @static
         * @param {GeneralMes.ICSCharacterRevert} message CSCharacterRevert message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSCharacterRevert.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSCharacterRevert message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSCharacterRevert
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSCharacterRevert} CSCharacterRevert
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterRevert.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSCharacterRevert();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.id = reader.int64();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("id"))
                throw $util.ProtocolError("missing required 'id'", { instance: message });
            return message;
        };

        /**
         * Decodes a CSCharacterRevert message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSCharacterRevert
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSCharacterRevert} CSCharacterRevert
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSCharacterRevert.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSCharacterRevert message.
         * @function verify
         * @memberof GeneralMes.CSCharacterRevert
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSCharacterRevert.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.id) && !(message.id && $util.isInteger(message.id.low) && $util.isInteger(message.id.high)))
                return "id: integer|Long expected";
            return null;
        };

        /**
         * Creates a CSCharacterRevert message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSCharacterRevert
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSCharacterRevert} CSCharacterRevert
         */
        CSCharacterRevert.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSCharacterRevert)
                return object;
            var message = new $root.GeneralMes.CSCharacterRevert();
            if (object.id != null)
                if ($util.Long)
                    (message.id = $util.Long.fromValue(object.id)).unsigned = false;
                else if (typeof object.id === "string")
                    message.id = parseInt(object.id, 10);
                else if (typeof object.id === "number")
                    message.id = object.id;
                else if (typeof object.id === "object")
                    message.id = new $util.LongBits(object.id.low >>> 0, object.id.high >>> 0).toNumber();
            return message;
        };

        /**
         * Creates a plain object from a CSCharacterRevert message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSCharacterRevert
         * @static
         * @param {GeneralMes.CSCharacterRevert} message CSCharacterRevert
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSCharacterRevert.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults)
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.id = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.id = options.longs === String ? "0" : 0;
            if (message.id != null && message.hasOwnProperty("id"))
                if (typeof message.id === "number")
                    object.id = options.longs === String ? String(message.id) : message.id;
                else
                    object.id = options.longs === String ? $util.Long.prototype.toString.call(message.id) : options.longs === Number ? new $util.LongBits(message.id.low >>> 0, message.id.high >>> 0).toNumber() : message.id;
            return object;
        };

        /**
         * Converts this CSCharacterRevert to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSCharacterRevert
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSCharacterRevert.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSCharacterRevert;
    })();

    GeneralMes.SCCharacterRevert = (function() {

        /**
         * Properties of a SCCharacterRevert.
         * @memberof GeneralMes
         * @interface ISCCharacterRevert
         * @property {number} result SCCharacterRevert result
         * @property {number|Long|null} [id] SCCharacterRevert id
         */

        /**
         * Constructs a new SCCharacterRevert.
         * @memberof GeneralMes
         * @classdesc Represents a SCCharacterRevert.
         * @implements ISCCharacterRevert
         * @constructor
         * @param {GeneralMes.ISCCharacterRevert=} [properties] Properties to set
         */
        function SCCharacterRevert(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SCCharacterRevert result.
         * @member {number} result
         * @memberof GeneralMes.SCCharacterRevert
         * @instance
         */
        SCCharacterRevert.prototype.result = 0;

        /**
         * SCCharacterRevert id.
         * @member {number|Long} id
         * @memberof GeneralMes.SCCharacterRevert
         * @instance
         */
        SCCharacterRevert.prototype.id = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * Creates a new SCCharacterRevert instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SCCharacterRevert
         * @static
         * @param {GeneralMes.ISCCharacterRevert=} [properties] Properties to set
         * @returns {GeneralMes.SCCharacterRevert} SCCharacterRevert instance
         */
        SCCharacterRevert.create = function create(properties) {
            return new SCCharacterRevert(properties);
        };

        /**
         * Encodes the specified SCCharacterRevert message. Does not implicitly {@link GeneralMes.SCCharacterRevert.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SCCharacterRevert
         * @static
         * @param {GeneralMes.ISCCharacterRevert} message SCCharacterRevert message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCCharacterRevert.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int32(message.result);
            if (message.id != null && message.hasOwnProperty("id"))
                writer.uint32(/* id 2, wireType 0 =*/16).int64(message.id);
            return writer;
        };

        /**
         * Encodes the specified SCCharacterRevert message, length delimited. Does not implicitly {@link GeneralMes.SCCharacterRevert.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SCCharacterRevert
         * @static
         * @param {GeneralMes.ISCCharacterRevert} message SCCharacterRevert message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCCharacterRevert.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SCCharacterRevert message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SCCharacterRevert
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SCCharacterRevert} SCCharacterRevert
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCCharacterRevert.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SCCharacterRevert();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.result = reader.int32();
                    break;
                case 2:
                    message.id = reader.int64();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("result"))
                throw $util.ProtocolError("missing required 'result'", { instance: message });
            return message;
        };

        /**
         * Decodes a SCCharacterRevert message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SCCharacterRevert
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SCCharacterRevert} SCCharacterRevert
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCCharacterRevert.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SCCharacterRevert message.
         * @function verify
         * @memberof GeneralMes.SCCharacterRevert
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SCCharacterRevert.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.result))
                return "result: integer expected";
            if (message.id != null && message.hasOwnProperty("id"))
                if (!$util.isInteger(message.id) && !(message.id && $util.isInteger(message.id.low) && $util.isInteger(message.id.high)))
                    return "id: integer|Long expected";
            return null;
        };

        /**
         * Creates a SCCharacterRevert message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SCCharacterRevert
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SCCharacterRevert} SCCharacterRevert
         */
        SCCharacterRevert.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SCCharacterRevert)
                return object;
            var message = new $root.GeneralMes.SCCharacterRevert();
            if (object.result != null)
                message.result = object.result | 0;
            if (object.id != null)
                if ($util.Long)
                    (message.id = $util.Long.fromValue(object.id)).unsigned = false;
                else if (typeof object.id === "string")
                    message.id = parseInt(object.id, 10);
                else if (typeof object.id === "number")
                    message.id = object.id;
                else if (typeof object.id === "object")
                    message.id = new $util.LongBits(object.id.low >>> 0, object.id.high >>> 0).toNumber();
            return message;
        };

        /**
         * Creates a plain object from a SCCharacterRevert message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SCCharacterRevert
         * @static
         * @param {GeneralMes.SCCharacterRevert} message SCCharacterRevert
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SCCharacterRevert.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                object.result = 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.id = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.id = options.longs === String ? "0" : 0;
            }
            if (message.result != null && message.hasOwnProperty("result"))
                object.result = message.result;
            if (message.id != null && message.hasOwnProperty("id"))
                if (typeof message.id === "number")
                    object.id = options.longs === String ? String(message.id) : message.id;
                else
                    object.id = options.longs === String ? $util.Long.prototype.toString.call(message.id) : options.longs === Number ? new $util.LongBits(message.id.low >>> 0, message.id.high >>> 0).toNumber() : message.id;
            return object;
        };

        /**
         * Converts this SCCharacterRevert to JSON.
         * @function toJSON
         * @memberof GeneralMes.SCCharacterRevert
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SCCharacterRevert.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SCCharacterRevert;
    })();

    GeneralMes.SCDroppedHumanHint = (function() {

        /**
         * Properties of a SCDroppedHumanHint.
         * @memberof GeneralMes
         * @interface ISCDroppedHumanHint
         * @property {number|Long} droppedHid SCDroppedHumanHint droppedHid
         * @property {number} droppedScene SCDroppedHumanHint droppedScene
         * @property {number|Long} requestHid SCDroppedHumanHint requestHid
         */

        /**
         * Constructs a new SCDroppedHumanHint.
         * @memberof GeneralMes
         * @classdesc Represents a SCDroppedHumanHint.
         * @implements ISCDroppedHumanHint
         * @constructor
         * @param {GeneralMes.ISCDroppedHumanHint=} [properties] Properties to set
         */
        function SCDroppedHumanHint(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * SCDroppedHumanHint droppedHid.
         * @member {number|Long} droppedHid
         * @memberof GeneralMes.SCDroppedHumanHint
         * @instance
         */
        SCDroppedHumanHint.prototype.droppedHid = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * SCDroppedHumanHint droppedScene.
         * @member {number} droppedScene
         * @memberof GeneralMes.SCDroppedHumanHint
         * @instance
         */
        SCDroppedHumanHint.prototype.droppedScene = 0;

        /**
         * SCDroppedHumanHint requestHid.
         * @member {number|Long} requestHid
         * @memberof GeneralMes.SCDroppedHumanHint
         * @instance
         */
        SCDroppedHumanHint.prototype.requestHid = $util.Long ? $util.Long.fromBits(0,0,false) : 0;

        /**
         * Creates a new SCDroppedHumanHint instance using the specified properties.
         * @function create
         * @memberof GeneralMes.SCDroppedHumanHint
         * @static
         * @param {GeneralMes.ISCDroppedHumanHint=} [properties] Properties to set
         * @returns {GeneralMes.SCDroppedHumanHint} SCDroppedHumanHint instance
         */
        SCDroppedHumanHint.create = function create(properties) {
            return new SCDroppedHumanHint(properties);
        };

        /**
         * Encodes the specified SCDroppedHumanHint message. Does not implicitly {@link GeneralMes.SCDroppedHumanHint.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.SCDroppedHumanHint
         * @static
         * @param {GeneralMes.ISCDroppedHumanHint} message SCDroppedHumanHint message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCDroppedHumanHint.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            writer.uint32(/* id 1, wireType 0 =*/8).int64(message.droppedHid);
            writer.uint32(/* id 2, wireType 0 =*/16).int32(message.droppedScene);
            writer.uint32(/* id 3, wireType 0 =*/24).int64(message.requestHid);
            return writer;
        };

        /**
         * Encodes the specified SCDroppedHumanHint message, length delimited. Does not implicitly {@link GeneralMes.SCDroppedHumanHint.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.SCDroppedHumanHint
         * @static
         * @param {GeneralMes.ISCDroppedHumanHint} message SCDroppedHumanHint message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        SCDroppedHumanHint.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a SCDroppedHumanHint message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.SCDroppedHumanHint
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.SCDroppedHumanHint} SCDroppedHumanHint
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCDroppedHumanHint.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.SCDroppedHumanHint();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                case 1:
                    message.droppedHid = reader.int64();
                    break;
                case 2:
                    message.droppedScene = reader.int32();
                    break;
                case 3:
                    message.requestHid = reader.int64();
                    break;
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            if (!message.hasOwnProperty("droppedHid"))
                throw $util.ProtocolError("missing required 'droppedHid'", { instance: message });
            if (!message.hasOwnProperty("droppedScene"))
                throw $util.ProtocolError("missing required 'droppedScene'", { instance: message });
            if (!message.hasOwnProperty("requestHid"))
                throw $util.ProtocolError("missing required 'requestHid'", { instance: message });
            return message;
        };

        /**
         * Decodes a SCDroppedHumanHint message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.SCDroppedHumanHint
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.SCDroppedHumanHint} SCDroppedHumanHint
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        SCDroppedHumanHint.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a SCDroppedHumanHint message.
         * @function verify
         * @memberof GeneralMes.SCDroppedHumanHint
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        SCDroppedHumanHint.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            if (!$util.isInteger(message.droppedHid) && !(message.droppedHid && $util.isInteger(message.droppedHid.low) && $util.isInteger(message.droppedHid.high)))
                return "droppedHid: integer|Long expected";
            if (!$util.isInteger(message.droppedScene))
                return "droppedScene: integer expected";
            if (!$util.isInteger(message.requestHid) && !(message.requestHid && $util.isInteger(message.requestHid.low) && $util.isInteger(message.requestHid.high)))
                return "requestHid: integer|Long expected";
            return null;
        };

        /**
         * Creates a SCDroppedHumanHint message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.SCDroppedHumanHint
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.SCDroppedHumanHint} SCDroppedHumanHint
         */
        SCDroppedHumanHint.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.SCDroppedHumanHint)
                return object;
            var message = new $root.GeneralMes.SCDroppedHumanHint();
            if (object.droppedHid != null)
                if ($util.Long)
                    (message.droppedHid = $util.Long.fromValue(object.droppedHid)).unsigned = false;
                else if (typeof object.droppedHid === "string")
                    message.droppedHid = parseInt(object.droppedHid, 10);
                else if (typeof object.droppedHid === "number")
                    message.droppedHid = object.droppedHid;
                else if (typeof object.droppedHid === "object")
                    message.droppedHid = new $util.LongBits(object.droppedHid.low >>> 0, object.droppedHid.high >>> 0).toNumber();
            if (object.droppedScene != null)
                message.droppedScene = object.droppedScene | 0;
            if (object.requestHid != null)
                if ($util.Long)
                    (message.requestHid = $util.Long.fromValue(object.requestHid)).unsigned = false;
                else if (typeof object.requestHid === "string")
                    message.requestHid = parseInt(object.requestHid, 10);
                else if (typeof object.requestHid === "number")
                    message.requestHid = object.requestHid;
                else if (typeof object.requestHid === "object")
                    message.requestHid = new $util.LongBits(object.requestHid.low >>> 0, object.requestHid.high >>> 0).toNumber();
            return message;
        };

        /**
         * Creates a plain object from a SCDroppedHumanHint message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.SCDroppedHumanHint
         * @static
         * @param {GeneralMes.SCDroppedHumanHint} message SCDroppedHumanHint
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        SCDroppedHumanHint.toObject = function toObject(message, options) {
            if (!options)
                options = {};
            var object = {};
            if (options.defaults) {
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.droppedHid = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.droppedHid = options.longs === String ? "0" : 0;
                object.droppedScene = 0;
                if ($util.Long) {
                    var long = new $util.Long(0, 0, false);
                    object.requestHid = options.longs === String ? long.toString() : options.longs === Number ? long.toNumber() : long;
                } else
                    object.requestHid = options.longs === String ? "0" : 0;
            }
            if (message.droppedHid != null && message.hasOwnProperty("droppedHid"))
                if (typeof message.droppedHid === "number")
                    object.droppedHid = options.longs === String ? String(message.droppedHid) : message.droppedHid;
                else
                    object.droppedHid = options.longs === String ? $util.Long.prototype.toString.call(message.droppedHid) : options.longs === Number ? new $util.LongBits(message.droppedHid.low >>> 0, message.droppedHid.high >>> 0).toNumber() : message.droppedHid;
            if (message.droppedScene != null && message.hasOwnProperty("droppedScene"))
                object.droppedScene = message.droppedScene;
            if (message.requestHid != null && message.hasOwnProperty("requestHid"))
                if (typeof message.requestHid === "number")
                    object.requestHid = options.longs === String ? String(message.requestHid) : message.requestHid;
                else
                    object.requestHid = options.longs === String ? $util.Long.prototype.toString.call(message.requestHid) : options.longs === Number ? new $util.LongBits(message.requestHid.low >>> 0, message.requestHid.high >>> 0).toNumber() : message.requestHid;
            return object;
        };

        /**
         * Converts this SCDroppedHumanHint to JSON.
         * @function toJSON
         * @memberof GeneralMes.SCDroppedHumanHint
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        SCDroppedHumanHint.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return SCDroppedHumanHint;
    })();

    GeneralMes.CSKickDroppedHuman = (function() {

        /**
         * Properties of a CSKickDroppedHuman.
         * @memberof GeneralMes
         * @interface ICSKickDroppedHuman
         */

        /**
         * Constructs a new CSKickDroppedHuman.
         * @memberof GeneralMes
         * @classdesc Represents a CSKickDroppedHuman.
         * @implements ICSKickDroppedHuman
         * @constructor
         * @param {GeneralMes.ICSKickDroppedHuman=} [properties] Properties to set
         */
        function CSKickDroppedHuman(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * Creates a new CSKickDroppedHuman instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSKickDroppedHuman
         * @static
         * @param {GeneralMes.ICSKickDroppedHuman=} [properties] Properties to set
         * @returns {GeneralMes.CSKickDroppedHuman} CSKickDroppedHuman instance
         */
        CSKickDroppedHuman.create = function create(properties) {
            return new CSKickDroppedHuman(properties);
        };

        /**
         * Encodes the specified CSKickDroppedHuman message. Does not implicitly {@link GeneralMes.CSKickDroppedHuman.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSKickDroppedHuman
         * @static
         * @param {GeneralMes.ICSKickDroppedHuman} message CSKickDroppedHuman message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSKickDroppedHuman.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            return writer;
        };

        /**
         * Encodes the specified CSKickDroppedHuman message, length delimited. Does not implicitly {@link GeneralMes.CSKickDroppedHuman.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSKickDroppedHuman
         * @static
         * @param {GeneralMes.ICSKickDroppedHuman} message CSKickDroppedHuman message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSKickDroppedHuman.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSKickDroppedHuman message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSKickDroppedHuman
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSKickDroppedHuman} CSKickDroppedHuman
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSKickDroppedHuman.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSKickDroppedHuman();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            return message;
        };

        /**
         * Decodes a CSKickDroppedHuman message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSKickDroppedHuman
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSKickDroppedHuman} CSKickDroppedHuman
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSKickDroppedHuman.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSKickDroppedHuman message.
         * @function verify
         * @memberof GeneralMes.CSKickDroppedHuman
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSKickDroppedHuman.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            return null;
        };

        /**
         * Creates a CSKickDroppedHuman message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSKickDroppedHuman
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSKickDroppedHuman} CSKickDroppedHuman
         */
        CSKickDroppedHuman.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSKickDroppedHuman)
                return object;
            return new $root.GeneralMes.CSKickDroppedHuman();
        };

        /**
         * Creates a plain object from a CSKickDroppedHuman message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSKickDroppedHuman
         * @static
         * @param {GeneralMes.CSKickDroppedHuman} message CSKickDroppedHuman
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSKickDroppedHuman.toObject = function toObject() {
            return {};
        };

        /**
         * Converts this CSKickDroppedHuman to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSKickDroppedHuman
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSKickDroppedHuman.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSKickDroppedHuman;
    })();

    GeneralMes.CSLoginEnded = (function() {

        /**
         * Properties of a CSLoginEnded.
         * @memberof GeneralMes
         * @interface ICSLoginEnded
         */

        /**
         * Constructs a new CSLoginEnded.
         * @memberof GeneralMes
         * @classdesc Represents a CSLoginEnded.
         * @implements ICSLoginEnded
         * @constructor
         * @param {GeneralMes.ICSLoginEnded=} [properties] Properties to set
         */
        function CSLoginEnded(properties) {
            if (properties)
                for (var keys = Object.keys(properties), i = 0; i < keys.length; ++i)
                    if (properties[keys[i]] != null)
                        this[keys[i]] = properties[keys[i]];
        }

        /**
         * Creates a new CSLoginEnded instance using the specified properties.
         * @function create
         * @memberof GeneralMes.CSLoginEnded
         * @static
         * @param {GeneralMes.ICSLoginEnded=} [properties] Properties to set
         * @returns {GeneralMes.CSLoginEnded} CSLoginEnded instance
         */
        CSLoginEnded.create = function create(properties) {
            return new CSLoginEnded(properties);
        };

        /**
         * Encodes the specified CSLoginEnded message. Does not implicitly {@link GeneralMes.CSLoginEnded.verify|verify} messages.
         * @function encode
         * @memberof GeneralMes.CSLoginEnded
         * @static
         * @param {GeneralMes.ICSLoginEnded} message CSLoginEnded message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSLoginEnded.encode = function encode(message, writer) {
            if (!writer)
                writer = $Writer.create();
            return writer;
        };

        /**
         * Encodes the specified CSLoginEnded message, length delimited. Does not implicitly {@link GeneralMes.CSLoginEnded.verify|verify} messages.
         * @function encodeDelimited
         * @memberof GeneralMes.CSLoginEnded
         * @static
         * @param {GeneralMes.ICSLoginEnded} message CSLoginEnded message or plain object to encode
         * @param {$protobuf.Writer} [writer] Writer to encode to
         * @returns {$protobuf.Writer} Writer
         */
        CSLoginEnded.encodeDelimited = function encodeDelimited(message, writer) {
            return this.encode(message, writer).ldelim();
        };

        /**
         * Decodes a CSLoginEnded message from the specified reader or buffer.
         * @function decode
         * @memberof GeneralMes.CSLoginEnded
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @param {number} [length] Message length if known beforehand
         * @returns {GeneralMes.CSLoginEnded} CSLoginEnded
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSLoginEnded.decode = function decode(reader, length) {
            if (!(reader instanceof $Reader))
                reader = $Reader.create(reader);
            var end = length === undefined ? reader.len : reader.pos + length, message = new $root.GeneralMes.CSLoginEnded();
            while (reader.pos < end) {
                var tag = reader.uint32();
                switch (tag >>> 3) {
                default:
                    reader.skipType(tag & 7);
                    break;
                }
            }
            return message;
        };

        /**
         * Decodes a CSLoginEnded message from the specified reader or buffer, length delimited.
         * @function decodeDelimited
         * @memberof GeneralMes.CSLoginEnded
         * @static
         * @param {$protobuf.Reader|Uint8Array} reader Reader or buffer to decode from
         * @returns {GeneralMes.CSLoginEnded} CSLoginEnded
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {$protobuf.util.ProtocolError} If required fields are missing
         */
        CSLoginEnded.decodeDelimited = function decodeDelimited(reader) {
            if (!(reader instanceof $Reader))
                reader = new $Reader(reader);
            return this.decode(reader, reader.uint32());
        };

        /**
         * Verifies a CSLoginEnded message.
         * @function verify
         * @memberof GeneralMes.CSLoginEnded
         * @static
         * @param {Object.<string,*>} message Plain object to verify
         * @returns {string|null} `null` if valid, otherwise the reason why it is not
         */
        CSLoginEnded.verify = function verify(message) {
            if (typeof message !== "object" || message === null)
                return "object expected";
            return null;
        };

        /**
         * Creates a CSLoginEnded message from a plain object. Also converts values to their respective internal types.
         * @function fromObject
         * @memberof GeneralMes.CSLoginEnded
         * @static
         * @param {Object.<string,*>} object Plain object
         * @returns {GeneralMes.CSLoginEnded} CSLoginEnded
         */
        CSLoginEnded.fromObject = function fromObject(object) {
            if (object instanceof $root.GeneralMes.CSLoginEnded)
                return object;
            return new $root.GeneralMes.CSLoginEnded();
        };

        /**
         * Creates a plain object from a CSLoginEnded message. Also converts values to other types if specified.
         * @function toObject
         * @memberof GeneralMes.CSLoginEnded
         * @static
         * @param {GeneralMes.CSLoginEnded} message CSLoginEnded
         * @param {$protobuf.IConversionOptions} [options] Conversion options
         * @returns {Object.<string,*>} Plain object
         */
        CSLoginEnded.toObject = function toObject() {
            return {};
        };

        /**
         * Converts this CSLoginEnded to JSON.
         * @function toJSON
         * @memberof GeneralMes.CSLoginEnded
         * @instance
         * @returns {Object.<string,*>} JSON object
         */
        CSLoginEnded.prototype.toJSON = function toJSON() {
            return this.constructor.toObject(this, $protobuf.util.toJSONOptions);
        };

        return CSLoginEnded;
    })();

    return GeneralMes;
})();