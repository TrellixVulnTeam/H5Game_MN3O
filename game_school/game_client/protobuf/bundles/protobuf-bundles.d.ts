type Long = protobuf.Long;

/** Namespace GeneralMes. */
declare namespace GeneralMes {

    /** Properties of a STencentUserInfo. */
    interface ISTencentUserInfo {

        /** STencentUserInfo platform */
        platform: string;

        /** STencentUserInfo isBlueVip */
        isBlueVip: boolean;

        /** STencentUserInfo isBlueYearVip */
        isBlueYearVip: boolean;

        /** STencentUserInfo isSuperBlueVip */
        isSuperBlueVip: boolean;

        /** STencentUserInfo blueVipLevel */
        blueVipLevel: number;

        /** STencentUserInfo isYellowVip */
        isYellowVip: boolean;

        /** STencentUserInfo isYellowYearVip */
        isYellowYearVip: boolean;

        /** STencentUserInfo isSuperYellowVip */
        isSuperYellowVip: boolean;

        /** STencentUserInfo yellowVipLevel */
        yellowVipLevel: number;

        /** STencentUserInfo tgpLevel */
        tgpLevel: number;
    }

    /** Represents a STencentUserInfo. */
    class STencentUserInfo implements ISTencentUserInfo {

        /**
         * Constructs a new STencentUserInfo.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISTencentUserInfo);

        /** STencentUserInfo platform. */
        public platform: string;

        /** STencentUserInfo isBlueVip. */
        public isBlueVip: boolean;

        /** STencentUserInfo isBlueYearVip. */
        public isBlueYearVip: boolean;

        /** STencentUserInfo isSuperBlueVip. */
        public isSuperBlueVip: boolean;

        /** STencentUserInfo blueVipLevel. */
        public blueVipLevel: number;

        /** STencentUserInfo isYellowVip. */
        public isYellowVip: boolean;

        /** STencentUserInfo isYellowYearVip. */
        public isYellowYearVip: boolean;

        /** STencentUserInfo isSuperYellowVip. */
        public isSuperYellowVip: boolean;

        /** STencentUserInfo yellowVipLevel. */
        public yellowVipLevel: number;

        /** STencentUserInfo tgpLevel. */
        public tgpLevel: number;

        /**
         * Creates a new STencentUserInfo instance using the specified properties.
         * @param [properties] Properties to set
         * @returns STencentUserInfo instance
         */
        public static create(properties?: GeneralMes.ISTencentUserInfo): GeneralMes.STencentUserInfo;

        /**
         * Encodes the specified STencentUserInfo message. Does not implicitly {@link GeneralMes.STencentUserInfo.verify|verify} messages.
         * @param message STencentUserInfo message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISTencentUserInfo, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified STencentUserInfo message, length delimited. Does not implicitly {@link GeneralMes.STencentUserInfo.verify|verify} messages.
         * @param message STencentUserInfo message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISTencentUserInfo, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a STencentUserInfo message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns STencentUserInfo
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.STencentUserInfo;

        /**
         * Decodes a STencentUserInfo message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns STencentUserInfo
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.STencentUserInfo;

        /**
         * Verifies a STencentUserInfo message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a STencentUserInfo message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns STencentUserInfo
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.STencentUserInfo;

        /**
         * Creates a plain object from a STencentUserInfo message. Also converts values to other types if specified.
         * @param message STencentUserInfo
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.STencentUserInfo, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this STencentUserInfo to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SMagicIntensify. */
    interface ISMagicIntensify {

        /** SMagicIntensify LevelPencent */
        LevelPencent: number;

        /** SMagicIntensify LevelValue */
        LevelValue: number;

        /** SMagicIntensify LevelAddition */
        LevelAddition: number;
    }

    /** Represents a SMagicIntensify. */
    class SMagicIntensify implements ISMagicIntensify {

        /**
         * Constructs a new SMagicIntensify.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISMagicIntensify);

        /** SMagicIntensify LevelPencent. */
        public LevelPencent: number;

        /** SMagicIntensify LevelValue. */
        public LevelValue: number;

        /** SMagicIntensify LevelAddition. */
        public LevelAddition: number;

        /**
         * Creates a new SMagicIntensify instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SMagicIntensify instance
         */
        public static create(properties?: GeneralMes.ISMagicIntensify): GeneralMes.SMagicIntensify;

        /**
         * Encodes the specified SMagicIntensify message. Does not implicitly {@link GeneralMes.SMagicIntensify.verify|verify} messages.
         * @param message SMagicIntensify message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISMagicIntensify, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SMagicIntensify message, length delimited. Does not implicitly {@link GeneralMes.SMagicIntensify.verify|verify} messages.
         * @param message SMagicIntensify message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISMagicIntensify, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SMagicIntensify message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SMagicIntensify
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SMagicIntensify;

        /**
         * Decodes a SMagicIntensify message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SMagicIntensify
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SMagicIntensify;

        /**
         * Verifies a SMagicIntensify message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SMagicIntensify message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SMagicIntensify
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SMagicIntensify;

        /**
         * Creates a plain object from a SMagicIntensify message. Also converts values to other types if specified.
         * @param message SMagicIntensify
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SMagicIntensify, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SMagicIntensify to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SMagicType. */
    interface ISMagicType {

        /** SMagicType id */
        id: number;

        /** SMagicType loc */
        loc: number;

        /** SMagicType intensify */
        intensify: GeneralMes.ISMagicIntensify;

        /** SMagicType exp */
        exp: (number|Long);

        /** SMagicType level */
        level: number;

        /** SMagicType openLevel */
        openLevel: number;

        /** SMagicType combatPoint */
        combatPoint: (number|Long);
    }

    /** Represents a SMagicType. */
    class SMagicType implements ISMagicType {

        /**
         * Constructs a new SMagicType.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISMagicType);

        /** SMagicType id. */
        public id: number;

        /** SMagicType loc. */
        public loc: number;

        /** SMagicType intensify. */
        public intensify: GeneralMes.ISMagicIntensify;

        /** SMagicType exp. */
        public exp: (number|Long);

        /** SMagicType level. */
        public level: number;

        /** SMagicType openLevel. */
        public openLevel: number;

        /** SMagicType combatPoint. */
        public combatPoint: (number|Long);

        /**
         * Creates a new SMagicType instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SMagicType instance
         */
        public static create(properties?: GeneralMes.ISMagicType): GeneralMes.SMagicType;

        /**
         * Encodes the specified SMagicType message. Does not implicitly {@link GeneralMes.SMagicType.verify|verify} messages.
         * @param message SMagicType message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISMagicType, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SMagicType message, length delimited. Does not implicitly {@link GeneralMes.SMagicType.verify|verify} messages.
         * @param message SMagicType message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISMagicType, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SMagicType message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SMagicType
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SMagicType;

        /**
         * Decodes a SMagicType message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SMagicType
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SMagicType;

        /**
         * Verifies a SMagicType message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SMagicType message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SMagicType
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SMagicType;

        /**
         * Creates a plain object from a SMagicType message. Also converts values to other types if specified.
         * @param message SMagicType
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SMagicType, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SMagicType to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SVector3. */
    interface ISVector3 {

        /** SVector3 x */
        x: number;

        /** SVector3 y */
        y: number;

        /** SVector3 z */
        z: number;
    }

    /** Represents a SVector3. */
    class SVector3 implements ISVector3 {

        /**
         * Constructs a new SVector3.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISVector3);

        /** SVector3 x. */
        public x: number;

        /** SVector3 y. */
        public y: number;

        /** SVector3 z. */
        public z: number;

        /**
         * Creates a new SVector3 instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SVector3 instance
         */
        public static create(properties?: GeneralMes.ISVector3): GeneralMes.SVector3;

        /**
         * Encodes the specified SVector3 message. Does not implicitly {@link GeneralMes.SVector3.verify|verify} messages.
         * @param message SVector3 message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISVector3, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SVector3 message, length delimited. Does not implicitly {@link GeneralMes.SVector3.verify|verify} messages.
         * @param message SVector3 message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISVector3, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SVector3 message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SVector3
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SVector3;

        /**
         * Decodes a SVector3 message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SVector3
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SVector3;

        /**
         * Verifies a SVector3 message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SVector3 message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SVector3
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SVector3;

        /**
         * Creates a plain object from a SVector3 message. Also converts values to other types if specified.
         * @param message SVector3
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SVector3, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SVector3 to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SAura. */
    interface ISAura {

        /** SAura id */
        id: (number|Long);

        /** SAura caster */
        caster: (number|Long);

        /** SAura owner */
        owner: (number|Long);

        /** SAura type */
        type: number;

        /** SAura overlapNum */
        overlapNum: number;

        /** SAura duration */
        duration: (number|Long);

        /** SAura param */
        param: number;

        /** SAura level */
        level: number;
    }

    /** Represents a SAura. */
    class SAura implements ISAura {

        /**
         * Constructs a new SAura.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISAura);

        /** SAura id. */
        public id: (number|Long);

        /** SAura caster. */
        public caster: (number|Long);

        /** SAura owner. */
        public owner: (number|Long);

        /** SAura type. */
        public type: number;

        /** SAura overlapNum. */
        public overlapNum: number;

        /** SAura duration. */
        public duration: (number|Long);

        /** SAura param. */
        public param: number;

        /** SAura level. */
        public level: number;

        /**
         * Creates a new SAura instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SAura instance
         */
        public static create(properties?: GeneralMes.ISAura): GeneralMes.SAura;

        /**
         * Encodes the specified SAura message. Does not implicitly {@link GeneralMes.SAura.verify|verify} messages.
         * @param message SAura message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISAura, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SAura message, length delimited. Does not implicitly {@link GeneralMes.SAura.verify|verify} messages.
         * @param message SAura message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISAura, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SAura message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SAura
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SAura;

        /**
         * Decodes a SAura message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SAura
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SAura;

        /**
         * Verifies a SAura message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SAura message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SAura
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SAura;

        /**
         * Creates a plain object from a SAura message. Also converts values to other types if specified.
         * @param message SAura
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SAura, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SAura to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SMotion. */
    interface ISMotion {

        /** SMotion motionType */
        motionType: number;

        /** SMotion motionTarget */
        motionTarget?: (number|Long|null);

        /** SMotion motionOrientation */
        motionOrientation?: (GeneralMes.ISVector3|null);

        /** SMotion motionPosition */
        motionPosition?: (GeneralMes.ISVector3|null);

        /** SMotion motionPath */
        motionPath?: (GeneralMes.ISVector3[]|null);

        /** SMotion param */
        param?: (number|null);
    }

    /** Represents a SMotion. */
    class SMotion implements ISMotion {

        /**
         * Constructs a new SMotion.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISMotion);

        /** SMotion motionType. */
        public motionType: number;

        /** SMotion motionTarget. */
        public motionTarget: (number|Long);

        /** SMotion motionOrientation. */
        public motionOrientation?: (GeneralMes.ISVector3|null);

        /** SMotion motionPosition. */
        public motionPosition?: (GeneralMes.ISVector3|null);

        /** SMotion motionPath. */
        public motionPath: GeneralMes.ISVector3[];

        /** SMotion param. */
        public param: number;

        /**
         * Creates a new SMotion instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SMotion instance
         */
        public static create(properties?: GeneralMes.ISMotion): GeneralMes.SMotion;

        /**
         * Encodes the specified SMotion message. Does not implicitly {@link GeneralMes.SMotion.verify|verify} messages.
         * @param message SMotion message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISMotion, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SMotion message, length delimited. Does not implicitly {@link GeneralMes.SMotion.verify|verify} messages.
         * @param message SMotion message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISMotion, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SMotion message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SMotion
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SMotion;

        /**
         * Decodes a SMotion message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SMotion
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SMotion;

        /**
         * Verifies a SMotion message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SMotion message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SMotion
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SMotion;

        /**
         * Creates a plain object from a SMotion message. Also converts values to other types if specified.
         * @param message SMotion
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SMotion, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SMotion to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SStageInfo. */
    interface ISStageInfo {

        /** SStageInfo id */
        id: (number|Long);

        /** SStageInfo scene */
        scene: Uint8Array;

        /** SStageInfo sceneNavmesh */
        sceneNavmesh: Uint8Array;

        /** SStageInfo sceneInfo */
        sceneInfo: Uint8Array;
    }

    /** Represents a SStageInfo. */
    class SStageInfo implements ISStageInfo {

        /**
         * Constructs a new SStageInfo.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISStageInfo);

        /** SStageInfo id. */
        public id: (number|Long);

        /** SStageInfo scene. */
        public scene: Uint8Array;

        /** SStageInfo sceneNavmesh. */
        public sceneNavmesh: Uint8Array;

        /** SStageInfo sceneInfo. */
        public sceneInfo: Uint8Array;

        /**
         * Creates a new SStageInfo instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SStageInfo instance
         */
        public static create(properties?: GeneralMes.ISStageInfo): GeneralMes.SStageInfo;

        /**
         * Encodes the specified SStageInfo message. Does not implicitly {@link GeneralMes.SStageInfo.verify|verify} messages.
         * @param message SStageInfo message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISStageInfo, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SStageInfo message, length delimited. Does not implicitly {@link GeneralMes.SStageInfo.verify|verify} messages.
         * @param message SStageInfo message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISStageInfo, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SStageInfo message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SStageInfo
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SStageInfo;

        /**
         * Decodes a SStageInfo message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SStageInfo
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SStageInfo;

        /**
         * Verifies a SStageInfo message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SStageInfo message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SStageInfo
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SStageInfo;

        /**
         * Creates a plain object from a SStageInfo message. Also converts values to other types if specified.
         * @param message SStageInfo
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SStageInfo, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SStageInfo to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemModAttr. */
    interface ISItemModAttr {

        /** SItemModAttr mod */
        mod: number;

        /** SItemModAttr type */
        type: number;

        /** SItemModAttr value */
        value: number;
    }

    /** Represents a SItemModAttr. */
    class SItemModAttr implements ISItemModAttr {

        /**
         * Constructs a new SItemModAttr.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemModAttr);

        /** SItemModAttr mod. */
        public mod: number;

        /** SItemModAttr type. */
        public type: number;

        /** SItemModAttr value. */
        public value: number;

        /**
         * Creates a new SItemModAttr instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemModAttr instance
         */
        public static create(properties?: GeneralMes.ISItemModAttr): GeneralMes.SItemModAttr;

        /**
         * Encodes the specified SItemModAttr message. Does not implicitly {@link GeneralMes.SItemModAttr.verify|verify} messages.
         * @param message SItemModAttr message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemModAttr, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemModAttr message, length delimited. Does not implicitly {@link GeneralMes.SItemModAttr.verify|verify} messages.
         * @param message SItemModAttr message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemModAttr, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemModAttr message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemModAttr
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemModAttr;

        /**
         * Decodes a SItemModAttr message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemModAttr
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemModAttr;

        /**
         * Verifies a SItemModAttr message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemModAttr message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemModAttr
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemModAttr;

        /**
         * Creates a plain object from a SItemModAttr message. Also converts values to other types if specified.
         * @param message SItemModAttr
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemModAttr, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemModAttr to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemModTrig. */
    interface ISItemModTrig {

        /** SItemModTrig mod */
        mod: number;

        /** SItemModTrig params */
        params?: (number[]|null);
    }

    /** Represents a SItemModTrig. */
    class SItemModTrig implements ISItemModTrig {

        /**
         * Constructs a new SItemModTrig.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemModTrig);

        /** SItemModTrig mod. */
        public mod: number;

        /** SItemModTrig params. */
        public params: number[];

        /**
         * Creates a new SItemModTrig instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemModTrig instance
         */
        public static create(properties?: GeneralMes.ISItemModTrig): GeneralMes.SItemModTrig;

        /**
         * Encodes the specified SItemModTrig message. Does not implicitly {@link GeneralMes.SItemModTrig.verify|verify} messages.
         * @param message SItemModTrig message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemModTrig, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemModTrig message, length delimited. Does not implicitly {@link GeneralMes.SItemModTrig.verify|verify} messages.
         * @param message SItemModTrig message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemModTrig, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemModTrig message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemModTrig
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemModTrig;

        /**
         * Decodes a SItemModTrig message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemModTrig
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemModTrig;

        /**
         * Verifies a SItemModTrig message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemModTrig message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemModTrig
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemModTrig;

        /**
         * Creates a plain object from a SItemModTrig message. Also converts values to other types if specified.
         * @param message SItemModTrig
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemModTrig, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemModTrig to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SCombatPoint. */
    interface ISCombatPoint {

        /** SCombatPoint zsPoint */
        zsPoint: number;

        /** SCombatPoint gsPoint */
        gsPoint: number;

        /** SCombatPoint fsPoint */
        fsPoint: number;
    }

    /** Represents a SCombatPoint. */
    class SCombatPoint implements ISCombatPoint {

        /**
         * Constructs a new SCombatPoint.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISCombatPoint);

        /** SCombatPoint zsPoint. */
        public zsPoint: number;

        /** SCombatPoint gsPoint. */
        public gsPoint: number;

        /** SCombatPoint fsPoint. */
        public fsPoint: number;

        /**
         * Creates a new SCombatPoint instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SCombatPoint instance
         */
        public static create(properties?: GeneralMes.ISCombatPoint): GeneralMes.SCombatPoint;

        /**
         * Encodes the specified SCombatPoint message. Does not implicitly {@link GeneralMes.SCombatPoint.verify|verify} messages.
         * @param message SCombatPoint message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISCombatPoint, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SCombatPoint message, length delimited. Does not implicitly {@link GeneralMes.SCombatPoint.verify|verify} messages.
         * @param message SCombatPoint message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISCombatPoint, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SCombatPoint message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SCombatPoint
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SCombatPoint;

        /**
         * Decodes a SCombatPoint message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SCombatPoint
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SCombatPoint;

        /**
         * Verifies a SCombatPoint message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SCombatPoint message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SCombatPoint
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SCombatPoint;

        /**
         * Creates a plain object from a SCombatPoint message. Also converts values to other types if specified.
         * @param message SCombatPoint
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SCombatPoint, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SCombatPoint to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemFashionParts. */
    interface ISItemFashionParts {

        /** SItemFashionParts idx */
        idx: number;

        /** SItemFashionParts enhanceLv */
        enhanceLv: number;
    }

    /** Represents a SItemFashionParts. */
    class SItemFashionParts implements ISItemFashionParts {

        /**
         * Constructs a new SItemFashionParts.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemFashionParts);

        /** SItemFashionParts idx. */
        public idx: number;

        /** SItemFashionParts enhanceLv. */
        public enhanceLv: number;

        /**
         * Creates a new SItemFashionParts instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemFashionParts instance
         */
        public static create(properties?: GeneralMes.ISItemFashionParts): GeneralMes.SItemFashionParts;

        /**
         * Encodes the specified SItemFashionParts message. Does not implicitly {@link GeneralMes.SItemFashionParts.verify|verify} messages.
         * @param message SItemFashionParts message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemFashionParts, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemFashionParts message, length delimited. Does not implicitly {@link GeneralMes.SItemFashionParts.verify|verify} messages.
         * @param message SItemFashionParts message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemFashionParts, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemFashionParts message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemFashionParts
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemFashionParts;

        /**
         * Decodes a SItemFashionParts message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemFashionParts
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemFashionParts;

        /**
         * Verifies a SItemFashionParts message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemFashionParts message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemFashionParts
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemFashionParts;

        /**
         * Creates a plain object from a SItemFashionParts message. Also converts values to other types if specified.
         * @param message SItemFashionParts
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemFashionParts, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemFashionParts to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemWing. */
    interface ISItemWing {

        /** SItemWing exp */
        exp: number;

        /** SItemWing star */
        star: number;

        /** SItemWing level */
        level: number;

        /** SItemWing step */
        step: number;

        /** SItemWing equipStep */
        equipStep: number;

        /** SItemWing luck */
        luck: number;
    }

    /** Represents a SItemWing. */
    class SItemWing implements ISItemWing {

        /**
         * Constructs a new SItemWing.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemWing);

        /** SItemWing exp. */
        public exp: number;

        /** SItemWing star. */
        public star: number;

        /** SItemWing level. */
        public level: number;

        /** SItemWing step. */
        public step: number;

        /** SItemWing equipStep. */
        public equipStep: number;

        /** SItemWing luck. */
        public luck: number;

        /**
         * Creates a new SItemWing instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemWing instance
         */
        public static create(properties?: GeneralMes.ISItemWing): GeneralMes.SItemWing;

        /**
         * Encodes the specified SItemWing message. Does not implicitly {@link GeneralMes.SItemWing.verify|verify} messages.
         * @param message SItemWing message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemWing, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemWing message, length delimited. Does not implicitly {@link GeneralMes.SItemWing.verify|verify} messages.
         * @param message SItemWing message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemWing, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemWing message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemWing
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemWing;

        /**
         * Decodes a SItemWing message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemWing
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemWing;

        /**
         * Verifies a SItemWing message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemWing message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemWing
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemWing;

        /**
         * Creates a plain object from a SItemWing message. Also converts values to other types if specified.
         * @param message SItemWing
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemWing, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemWing to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemEquip. */
    interface ISItemEquip {

        /** SItemEquip color */
        color: number;

        /** SItemEquip level */
        level: number;

        /** SItemEquip useLevel */
        useLevel: number;

        /** SItemEquip starLevel */
        starLevel?: (number|null);

        /** SItemEquip enchantLevel */
        enchantLevel?: (number|null);

        /** SItemEquip basicsAttr */
        basicsAttr?: (GeneralMes.ISItemModAttr[]|null);

        /** SItemEquip extendsAttr */
        extendsAttr?: (GeneralMes.ISItemModAttr[]|null);

        /** SItemEquip specialAttr */
        specialAttr?: (GeneralMes.ISItemModAttr|null);

        /** SItemEquip specialTrig */
        specialTrig?: (GeneralMes.ISItemModTrig|null);

        /** SItemEquip fashionParts */
        fashionParts?: (GeneralMes.ISItemFashionParts[]|null);

        /** SItemEquip wing */
        wing?: (GeneralMes.ISItemWing|null);

        /** SItemEquip skillId */
        skillId?: (number|null);
    }

    /** Represents a SItemEquip. */
    class SItemEquip implements ISItemEquip {

        /**
         * Constructs a new SItemEquip.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemEquip);

        /** SItemEquip color. */
        public color: number;

        /** SItemEquip level. */
        public level: number;

        /** SItemEquip useLevel. */
        public useLevel: number;

        /** SItemEquip starLevel. */
        public starLevel: number;

        /** SItemEquip enchantLevel. */
        public enchantLevel: number;

        /** SItemEquip basicsAttr. */
        public basicsAttr: GeneralMes.ISItemModAttr[];

        /** SItemEquip extendsAttr. */
        public extendsAttr: GeneralMes.ISItemModAttr[];

        /** SItemEquip specialAttr. */
        public specialAttr?: (GeneralMes.ISItemModAttr|null);

        /** SItemEquip specialTrig. */
        public specialTrig?: (GeneralMes.ISItemModTrig|null);

        /** SItemEquip fashionParts. */
        public fashionParts: GeneralMes.ISItemFashionParts[];

        /** SItemEquip wing. */
        public wing?: (GeneralMes.ISItemWing|null);

        /** SItemEquip skillId. */
        public skillId: number;

        /**
         * Creates a new SItemEquip instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemEquip instance
         */
        public static create(properties?: GeneralMes.ISItemEquip): GeneralMes.SItemEquip;

        /**
         * Encodes the specified SItemEquip message. Does not implicitly {@link GeneralMes.SItemEquip.verify|verify} messages.
         * @param message SItemEquip message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemEquip, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemEquip message, length delimited. Does not implicitly {@link GeneralMes.SItemEquip.verify|verify} messages.
         * @param message SItemEquip message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemEquip, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemEquip message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemEquip
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemEquip;

        /**
         * Decodes a SItemEquip message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemEquip
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemEquip;

        /**
         * Verifies a SItemEquip message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemEquip message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemEquip
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemEquip;

        /**
         * Creates a plain object from a SItemEquip message. Also converts values to other types if specified.
         * @param message SItemEquip
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemEquip, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemEquip to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemRune. */
    interface ISItemRune {

        /** SItemRune exp */
        exp: number;
    }

    /** Represents a SItemRune. */
    class SItemRune implements ISItemRune {

        /**
         * Constructs a new SItemRune.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemRune);

        /** SItemRune exp. */
        public exp: number;

        /**
         * Creates a new SItemRune instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemRune instance
         */
        public static create(properties?: GeneralMes.ISItemRune): GeneralMes.SItemRune;

        /**
         * Encodes the specified SItemRune message. Does not implicitly {@link GeneralMes.SItemRune.verify|verify} messages.
         * @param message SItemRune message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemRune, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemRune message, length delimited. Does not implicitly {@link GeneralMes.SItemRune.verify|verify} messages.
         * @param message SItemRune message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemRune, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemRune message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemRune
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemRune;

        /**
         * Decodes a SItemRune message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemRune
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemRune;

        /**
         * Verifies a SItemRune message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemRune message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemRune
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemRune;

        /**
         * Creates a plain object from a SItemRune message. Also converts values to other types if specified.
         * @param message SItemRune
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemRune, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemRune to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemBless. */
    interface ISItemBless {

        /** SItemBless modAttrs */
        modAttrs?: (GeneralMes.ISItemModAttr[]|null);
    }

    /** Represents a SItemBless. */
    class SItemBless implements ISItemBless {

        /**
         * Constructs a new SItemBless.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemBless);

        /** SItemBless modAttrs. */
        public modAttrs: GeneralMes.ISItemModAttr[];

        /**
         * Creates a new SItemBless instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemBless instance
         */
        public static create(properties?: GeneralMes.ISItemBless): GeneralMes.SItemBless;

        /**
         * Encodes the specified SItemBless message. Does not implicitly {@link GeneralMes.SItemBless.verify|verify} messages.
         * @param message SItemBless message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemBless, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemBless message, length delimited. Does not implicitly {@link GeneralMes.SItemBless.verify|verify} messages.
         * @param message SItemBless message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemBless, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemBless message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemBless
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemBless;

        /**
         * Decodes a SItemBless message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemBless
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemBless;

        /**
         * Verifies a SItemBless message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemBless message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemBless
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemBless;

        /**
         * Creates a plain object from a SItemBless message. Also converts values to other types if specified.
         * @param message SItemBless
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemBless, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemBless to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemEgg. */
    interface ISItemEgg {

        /** SItemEgg aptitude */
        aptitude: number;

        /** SItemEgg fireDmg */
        fireDmg: number;

        /** SItemEgg coldDmg */
        coldDmg: number;

        /** SItemEgg lightDmg */
        lightDmg: number;

        /** SItemEgg poisonDmg */
        poisonDmg: number;

        /** SItemEgg fireRes */
        fireRes: number;

        /** SItemEgg coldRes */
        coldRes: number;

        /** SItemEgg lightRes */
        lightRes: number;

        /** SItemEgg poisonRes */
        poisonRes: number;

        /** SItemEgg growRate */
        growRate: number;

        /** SItemEgg growRateLimit */
        growRateLimit: number;

        /** SItemEgg conRate */
        conRate: number;

        /** SItemEgg conRateLimit */
        conRateLimit: number;
    }

    /** Represents a SItemEgg. */
    class SItemEgg implements ISItemEgg {

        /**
         * Constructs a new SItemEgg.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemEgg);

        /** SItemEgg aptitude. */
        public aptitude: number;

        /** SItemEgg fireDmg. */
        public fireDmg: number;

        /** SItemEgg coldDmg. */
        public coldDmg: number;

        /** SItemEgg lightDmg. */
        public lightDmg: number;

        /** SItemEgg poisonDmg. */
        public poisonDmg: number;

        /** SItemEgg fireRes. */
        public fireRes: number;

        /** SItemEgg coldRes. */
        public coldRes: number;

        /** SItemEgg lightRes. */
        public lightRes: number;

        /** SItemEgg poisonRes. */
        public poisonRes: number;

        /** SItemEgg growRate. */
        public growRate: number;

        /** SItemEgg growRateLimit. */
        public growRateLimit: number;

        /** SItemEgg conRate. */
        public conRate: number;

        /** SItemEgg conRateLimit. */
        public conRateLimit: number;

        /**
         * Creates a new SItemEgg instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemEgg instance
         */
        public static create(properties?: GeneralMes.ISItemEgg): GeneralMes.SItemEgg;

        /**
         * Encodes the specified SItemEgg message. Does not implicitly {@link GeneralMes.SItemEgg.verify|verify} messages.
         * @param message SItemEgg message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemEgg, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemEgg message, length delimited. Does not implicitly {@link GeneralMes.SItemEgg.verify|verify} messages.
         * @param message SItemEgg message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemEgg, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemEgg message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemEgg
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemEgg;

        /**
         * Decodes a SItemEgg message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemEgg
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemEgg;

        /**
         * Verifies a SItemEgg message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemEgg message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemEgg
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemEgg;

        /**
         * Creates a plain object from a SItemEgg message. Also converts values to other types if specified.
         * @param message SItemEgg
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemEgg, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemEgg to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemEquipRune. */
    interface ISItemEquipRune {

        /** SItemEquipRune modAttrs */
        modAttrs?: (GeneralMes.ISItemModAttr[]|null);
    }

    /** Represents a SItemEquipRune. */
    class SItemEquipRune implements ISItemEquipRune {

        /**
         * Constructs a new SItemEquipRune.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemEquipRune);

        /** SItemEquipRune modAttrs. */
        public modAttrs: GeneralMes.ISItemModAttr[];

        /**
         * Creates a new SItemEquipRune instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemEquipRune instance
         */
        public static create(properties?: GeneralMes.ISItemEquipRune): GeneralMes.SItemEquipRune;

        /**
         * Encodes the specified SItemEquipRune message. Does not implicitly {@link GeneralMes.SItemEquipRune.verify|verify} messages.
         * @param message SItemEquipRune message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemEquipRune, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemEquipRune message, length delimited. Does not implicitly {@link GeneralMes.SItemEquipRune.verify|verify} messages.
         * @param message SItemEquipRune message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemEquipRune, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemEquipRune message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemEquipRune
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemEquipRune;

        /**
         * Decodes a SItemEquipRune message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemEquipRune
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemEquipRune;

        /**
         * Verifies a SItemEquipRune message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemEquipRune message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemEquipRune
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemEquipRune;

        /**
         * Creates a plain object from a SItemEquipRune message. Also converts values to other types if specified.
         * @param message SItemEquipRune
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemEquipRune, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemEquipRune to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemBloodGobm. */
    interface ISItemBloodGobm {

        /** SItemBloodGobm level */
        level: number;

        /** SItemBloodGobm exp */
        exp: number;

        /** SItemBloodGobm activeType */
        activeType: number;

        /** SItemBloodGobm activeParam1 */
        activeParam1: number;

        /** SItemBloodGobm activeParam2 */
        activeParam2: number;
    }

    /** Represents a SItemBloodGobm. */
    class SItemBloodGobm implements ISItemBloodGobm {

        /**
         * Constructs a new SItemBloodGobm.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemBloodGobm);

        /** SItemBloodGobm level. */
        public level: number;

        /** SItemBloodGobm exp. */
        public exp: number;

        /** SItemBloodGobm activeType. */
        public activeType: number;

        /** SItemBloodGobm activeParam1. */
        public activeParam1: number;

        /** SItemBloodGobm activeParam2. */
        public activeParam2: number;

        /**
         * Creates a new SItemBloodGobm instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemBloodGobm instance
         */
        public static create(properties?: GeneralMes.ISItemBloodGobm): GeneralMes.SItemBloodGobm;

        /**
         * Encodes the specified SItemBloodGobm message. Does not implicitly {@link GeneralMes.SItemBloodGobm.verify|verify} messages.
         * @param message SItemBloodGobm message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemBloodGobm, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemBloodGobm message, length delimited. Does not implicitly {@link GeneralMes.SItemBloodGobm.verify|verify} messages.
         * @param message SItemBloodGobm message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemBloodGobm, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemBloodGobm message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemBloodGobm
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemBloodGobm;

        /**
         * Decodes a SItemBloodGobm message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemBloodGobm
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemBloodGobm;

        /**
         * Verifies a SItemBloodGobm message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemBloodGobm message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemBloodGobm
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemBloodGobm;

        /**
         * Creates a plain object from a SItemBloodGobm message. Also converts values to other types if specified.
         * @param message SItemBloodGobm
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemBloodGobm, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemBloodGobm to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SEquipIndexGem. */
    interface ISEquipIndexGem {

        /** SEquipIndexGem equipIndex */
        equipIndex: number;

        /** SEquipIndexGem gems */
        gems?: (GeneralMes.ISItem[]|null);
    }

    /** Represents a SEquipIndexGem. */
    class SEquipIndexGem implements ISEquipIndexGem {

        /**
         * Constructs a new SEquipIndexGem.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISEquipIndexGem);

        /** SEquipIndexGem equipIndex. */
        public equipIndex: number;

        /** SEquipIndexGem gems. */
        public gems: GeneralMes.ISItem[];

        /**
         * Creates a new SEquipIndexGem instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SEquipIndexGem instance
         */
        public static create(properties?: GeneralMes.ISEquipIndexGem): GeneralMes.SEquipIndexGem;

        /**
         * Encodes the specified SEquipIndexGem message. Does not implicitly {@link GeneralMes.SEquipIndexGem.verify|verify} messages.
         * @param message SEquipIndexGem message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISEquipIndexGem, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SEquipIndexGem message, length delimited. Does not implicitly {@link GeneralMes.SEquipIndexGem.verify|verify} messages.
         * @param message SEquipIndexGem message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISEquipIndexGem, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SEquipIndexGem message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SEquipIndexGem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SEquipIndexGem;

        /**
         * Decodes a SEquipIndexGem message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SEquipIndexGem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SEquipIndexGem;

        /**
         * Verifies a SEquipIndexGem message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SEquipIndexGem message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SEquipIndexGem
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SEquipIndexGem;

        /**
         * Creates a plain object from a SEquipIndexGem message. Also converts values to other types if specified.
         * @param message SEquipIndexGem
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SEquipIndexGem, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SEquipIndexGem to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemHPMP. */
    interface ISItemHPMP {

        /** SItemHPMP usedVal */
        usedVal: number;

        /** SItemHPMP totalVal */
        totalVal: number;
    }

    /** Represents a SItemHPMP. */
    class SItemHPMP implements ISItemHPMP {

        /**
         * Constructs a new SItemHPMP.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemHPMP);

        /** SItemHPMP usedVal. */
        public usedVal: number;

        /** SItemHPMP totalVal. */
        public totalVal: number;

        /**
         * Creates a new SItemHPMP instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemHPMP instance
         */
        public static create(properties?: GeneralMes.ISItemHPMP): GeneralMes.SItemHPMP;

        /**
         * Encodes the specified SItemHPMP message. Does not implicitly {@link GeneralMes.SItemHPMP.verify|verify} messages.
         * @param message SItemHPMP message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemHPMP, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemHPMP message, length delimited. Does not implicitly {@link GeneralMes.SItemHPMP.verify|verify} messages.
         * @param message SItemHPMP message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemHPMP, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemHPMP message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemHPMP
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemHPMP;

        /**
         * Decodes a SItemHPMP message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemHPMP
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemHPMP;

        /**
         * Verifies a SItemHPMP message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemHPMP message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemHPMP
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemHPMP;

        /**
         * Creates a plain object from a SItemHPMP message. Also converts values to other types if specified.
         * @param message SItemHPMP
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemHPMP, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemHPMP to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItem. */
    interface ISItem {

        /** SItem itemId */
        itemId: (number|Long);

        /** SItem itemType */
        itemType: number;

        /** SItem itemCount */
        itemCount: number;

        /** SItem itemBag */
        itemBag: number;

        /** SItem itemPosition */
        itemPosition: number;

        /** SItem itemFlags */
        itemFlags: (number|Long);

        /** SItem expiredTime */
        expiredTime: (number|Long);

        /** SItem itemPrice */
        itemPrice?: (number|Long|null);

        /** SItem equipAttrs */
        equipAttrs?: (GeneralMes.ISItemEquip|null);

        /** SItem blessAttrs */
        blessAttrs?: (GeneralMes.ISItemBless|null);

        /** SItem eggAttrs */
        eggAttrs?: (GeneralMes.ISItemEgg|null);

        /** SItem gobmAttrs */
        gobmAttrs?: (GeneralMes.ISItemBloodGobm|null);

        /** SItem combatPoint */
        combatPoint?: (GeneralMes.ISCombatPoint|null);

        /** SItem hpmpAttrs */
        hpmpAttrs?: (GeneralMes.ISItemHPMP|null);
    }

    /** Represents a SItem. */
    class SItem implements ISItem {

        /**
         * Constructs a new SItem.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItem);

        /** SItem itemId. */
        public itemId: (number|Long);

        /** SItem itemType. */
        public itemType: number;

        /** SItem itemCount. */
        public itemCount: number;

        /** SItem itemBag. */
        public itemBag: number;

        /** SItem itemPosition. */
        public itemPosition: number;

        /** SItem itemFlags. */
        public itemFlags: (number|Long);

        /** SItem expiredTime. */
        public expiredTime: (number|Long);

        /** SItem itemPrice. */
        public itemPrice: (number|Long);

        /** SItem equipAttrs. */
        public equipAttrs?: (GeneralMes.ISItemEquip|null);

        /** SItem blessAttrs. */
        public blessAttrs?: (GeneralMes.ISItemBless|null);

        /** SItem eggAttrs. */
        public eggAttrs?: (GeneralMes.ISItemEgg|null);

        /** SItem gobmAttrs. */
        public gobmAttrs?: (GeneralMes.ISItemBloodGobm|null);

        /** SItem combatPoint. */
        public combatPoint?: (GeneralMes.ISCombatPoint|null);

        /** SItem hpmpAttrs. */
        public hpmpAttrs?: (GeneralMes.ISItemHPMP|null);

        /**
         * Creates a new SItem instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItem instance
         */
        public static create(properties?: GeneralMes.ISItem): GeneralMes.SItem;

        /**
         * Encodes the specified SItem message. Does not implicitly {@link GeneralMes.SItem.verify|verify} messages.
         * @param message SItem message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItem, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItem message, length delimited. Does not implicitly {@link GeneralMes.SItem.verify|verify} messages.
         * @param message SItem message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItem, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItem message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItem;

        /**
         * Decodes a SItem message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItem;

        /**
         * Verifies a SItem message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItem message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItem
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItem;

        /**
         * Creates a plain object from a SItem message. Also converts values to other types if specified.
         * @param message SItem
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItem, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItem to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SItemPrice. */
    interface ISItemPrice {

        /** SItemPrice tid */
        tid: number;

        /** SItemPrice price */
        price: number;
    }

    /** Represents a SItemPrice. */
    class SItemPrice implements ISItemPrice {

        /**
         * Constructs a new SItemPrice.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISItemPrice);

        /** SItemPrice tid. */
        public tid: number;

        /** SItemPrice price. */
        public price: number;

        /**
         * Creates a new SItemPrice instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SItemPrice instance
         */
        public static create(properties?: GeneralMes.ISItemPrice): GeneralMes.SItemPrice;

        /**
         * Encodes the specified SItemPrice message. Does not implicitly {@link GeneralMes.SItemPrice.verify|verify} messages.
         * @param message SItemPrice message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISItemPrice, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SItemPrice message, length delimited. Does not implicitly {@link GeneralMes.SItemPrice.verify|verify} messages.
         * @param message SItemPrice message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISItemPrice, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SItemPrice message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SItemPrice
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SItemPrice;

        /**
         * Decodes a SItemPrice message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SItemPrice
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SItemPrice;

        /**
         * Verifies a SItemPrice message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SItemPrice message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SItemPrice
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SItemPrice;

        /**
         * Creates a plain object from a SItemPrice message. Also converts values to other types if specified.
         * @param message SItemPrice
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SItemPrice, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SItemPrice to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SPackItem. */
    interface ISPackItem {

        /** SPackItem tid */
        tid: number;

        /** SPackItem count */
        count: number;
    }

    /** Represents a SPackItem. */
    class SPackItem implements ISPackItem {

        /**
         * Constructs a new SPackItem.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISPackItem);

        /** SPackItem tid. */
        public tid: number;

        /** SPackItem count. */
        public count: number;

        /**
         * Creates a new SPackItem instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SPackItem instance
         */
        public static create(properties?: GeneralMes.ISPackItem): GeneralMes.SPackItem;

        /**
         * Encodes the specified SPackItem message. Does not implicitly {@link GeneralMes.SPackItem.verify|verify} messages.
         * @param message SPackItem message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISPackItem, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SPackItem message, length delimited. Does not implicitly {@link GeneralMes.SPackItem.verify|verify} messages.
         * @param message SPackItem message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISPackItem, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SPackItem message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SPackItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SPackItem;

        /**
         * Decodes a SPackItem message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SPackItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SPackItem;

        /**
         * Verifies a SPackItem message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SPackItem message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SPackItem
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SPackItem;

        /**
         * Creates a plain object from a SPackItem message. Also converts values to other types if specified.
         * @param message SPackItem
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SPackItem, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SPackItem to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SRandomItem. */
    interface ISRandomItem {

        /** SRandomItem randomItemType */
        randomItemType: number;

        /** SRandomItem packItem */
        packItem: GeneralMes.ISPackItem;
    }

    /** Represents a SRandomItem. */
    class SRandomItem implements ISRandomItem {

        /**
         * Constructs a new SRandomItem.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISRandomItem);

        /** SRandomItem randomItemType. */
        public randomItemType: number;

        /** SRandomItem packItem. */
        public packItem: GeneralMes.ISPackItem;

        /**
         * Creates a new SRandomItem instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SRandomItem instance
         */
        public static create(properties?: GeneralMes.ISRandomItem): GeneralMes.SRandomItem;

        /**
         * Encodes the specified SRandomItem message. Does not implicitly {@link GeneralMes.SRandomItem.verify|verify} messages.
         * @param message SRandomItem message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISRandomItem, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SRandomItem message, length delimited. Does not implicitly {@link GeneralMes.SRandomItem.verify|verify} messages.
         * @param message SRandomItem message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISRandomItem, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SRandomItem message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SRandomItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SRandomItem;

        /**
         * Decodes a SRandomItem message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SRandomItem
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SRandomItem;

        /**
         * Verifies a SRandomItem message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SRandomItem message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SRandomItem
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SRandomItem;

        /**
         * Creates a plain object from a SRandomItem message. Also converts values to other types if specified.
         * @param message SRandomItem
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SRandomItem, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SRandomItem to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SCharacter. */
    interface ISCharacter {

        /** SCharacter id */
        id: (number|Long);

        /** SCharacter name */
        name: Uint8Array;

        /** SCharacter profession */
        profession: number;

        /** SCharacter level */
        level: number;

        /** SCharacter sex */
        sex: number;

        /** SCharacter newbie */
        newbie: boolean;
    }

    /** Represents a SCharacter. */
    class SCharacter implements ISCharacter {

        /**
         * Constructs a new SCharacter.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISCharacter);

        /** SCharacter id. */
        public id: (number|Long);

        /** SCharacter name. */
        public name: Uint8Array;

        /** SCharacter profession. */
        public profession: number;

        /** SCharacter level. */
        public level: number;

        /** SCharacter sex. */
        public sex: number;

        /** SCharacter newbie. */
        public newbie: boolean;

        /**
         * Creates a new SCharacter instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SCharacter instance
         */
        public static create(properties?: GeneralMes.ISCharacter): GeneralMes.SCharacter;

        /**
         * Encodes the specified SCharacter message. Does not implicitly {@link GeneralMes.SCharacter.verify|verify} messages.
         * @param message SCharacter message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISCharacter, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SCharacter message, length delimited. Does not implicitly {@link GeneralMes.SCharacter.verify|verify} messages.
         * @param message SCharacter message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISCharacter, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SCharacter message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SCharacter
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SCharacter;

        /**
         * Decodes a SCharacter message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SCharacter
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SCharacter;

        /**
         * Verifies a SCharacter message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SCharacter message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SCharacter
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SCharacter;

        /**
         * Creates a plain object from a SCharacter message. Also converts values to other types if specified.
         * @param message SCharacter
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SCharacter, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SCharacter to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSLoginBegan. */
    interface ICSLoginBegan {
    }

    /** Represents a CSLoginBegan. */
    class CSLoginBegan implements ICSLoginBegan {

        /**
         * Constructs a new CSLoginBegan.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSLoginBegan);

        /**
         * Creates a new CSLoginBegan instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSLoginBegan instance
         */
        public static create(properties?: GeneralMes.ICSLoginBegan): GeneralMes.CSLoginBegan;

        /**
         * Encodes the specified CSLoginBegan message. Does not implicitly {@link GeneralMes.CSLoginBegan.verify|verify} messages.
         * @param message CSLoginBegan message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSLoginBegan, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSLoginBegan message, length delimited. Does not implicitly {@link GeneralMes.CSLoginBegan.verify|verify} messages.
         * @param message CSLoginBegan message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSLoginBegan, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSLoginBegan message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSLoginBegan
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSLoginBegan;

        /**
         * Decodes a CSLoginBegan message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSLoginBegan
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSLoginBegan;

        /**
         * Verifies a CSLoginBegan message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSLoginBegan message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSLoginBegan
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSLoginBegan;

        /**
         * Creates a plain object from a CSLoginBegan message. Also converts values to other types if specified.
         * @param message CSLoginBegan
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSLoginBegan, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSLoginBegan to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSLoginGate. */
    interface ICSLoginGate {
    }

    /** Represents a CSLoginGate. */
    class CSLoginGate implements ICSLoginGate {

        /**
         * Constructs a new CSLoginGate.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSLoginGate);

        /**
         * Creates a new CSLoginGate instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSLoginGate instance
         */
        public static create(properties?: GeneralMes.ICSLoginGate): GeneralMes.CSLoginGate;

        /**
         * Encodes the specified CSLoginGate message. Does not implicitly {@link GeneralMes.CSLoginGate.verify|verify} messages.
         * @param message CSLoginGate message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSLoginGate, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSLoginGate message, length delimited. Does not implicitly {@link GeneralMes.CSLoginGate.verify|verify} messages.
         * @param message CSLoginGate message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSLoginGate, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSLoginGate message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSLoginGate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSLoginGate;

        /**
         * Decodes a CSLoginGate message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSLoginGate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSLoginGate;

        /**
         * Verifies a CSLoginGate message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSLoginGate message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSLoginGate
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSLoginGate;

        /**
         * Creates a plain object from a CSLoginGate message. Also converts values to other types if specified.
         * @param message CSLoginGate
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSLoginGate, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSLoginGate to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SCLoginGate. */
    interface ISCLoginGate {

        /** SCLoginGate result */
        result: number;
    }

    /** Represents a SCLoginGate. */
    class SCLoginGate implements ISCLoginGate {

        /**
         * Constructs a new SCLoginGate.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISCLoginGate);

        /** SCLoginGate result. */
        public result: number;

        /**
         * Creates a new SCLoginGate instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SCLoginGate instance
         */
        public static create(properties?: GeneralMes.ISCLoginGate): GeneralMes.SCLoginGate;

        /**
         * Encodes the specified SCLoginGate message. Does not implicitly {@link GeneralMes.SCLoginGate.verify|verify} messages.
         * @param message SCLoginGate message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISCLoginGate, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SCLoginGate message, length delimited. Does not implicitly {@link GeneralMes.SCLoginGate.verify|verify} messages.
         * @param message SCLoginGate message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISCLoginGate, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SCLoginGate message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SCLoginGate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SCLoginGate;

        /**
         * Decodes a SCLoginGate message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SCLoginGate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SCLoginGate;

        /**
         * Verifies a SCLoginGate message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SCLoginGate message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SCLoginGate
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SCLoginGate;

        /**
         * Creates a plain object from a SCLoginGate message. Also converts values to other types if specified.
         * @param message SCLoginGate
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SCLoginGate, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SCLoginGate to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSQueryCharacters. */
    interface ICSQueryCharacters {
    }

    /** Represents a CSQueryCharacters. */
    class CSQueryCharacters implements ICSQueryCharacters {

        /**
         * Constructs a new CSQueryCharacters.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSQueryCharacters);

        /**
         * Creates a new CSQueryCharacters instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSQueryCharacters instance
         */
        public static create(properties?: GeneralMes.ICSQueryCharacters): GeneralMes.CSQueryCharacters;

        /**
         * Encodes the specified CSQueryCharacters message. Does not implicitly {@link GeneralMes.CSQueryCharacters.verify|verify} messages.
         * @param message CSQueryCharacters message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSQueryCharacters, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSQueryCharacters message, length delimited. Does not implicitly {@link GeneralMes.CSQueryCharacters.verify|verify} messages.
         * @param message CSQueryCharacters message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSQueryCharacters, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSQueryCharacters message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSQueryCharacters
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSQueryCharacters;

        /**
         * Decodes a CSQueryCharacters message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSQueryCharacters
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSQueryCharacters;

        /**
         * Verifies a CSQueryCharacters message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSQueryCharacters message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSQueryCharacters
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSQueryCharacters;

        /**
         * Creates a plain object from a CSQueryCharacters message. Also converts values to other types if specified.
         * @param message CSQueryCharacters
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSQueryCharacters, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSQueryCharacters to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SCQueryCharacters. */
    interface ISCQueryCharacters {

        /** SCQueryCharacters characters */
        characters?: (GeneralMes.ISCharacter[]|null);

        /** SCQueryCharacters lastLoginHid */
        lastLoginHid?: (number|Long|null);
    }

    /** Represents a SCQueryCharacters. */
    class SCQueryCharacters implements ISCQueryCharacters {

        /**
         * Constructs a new SCQueryCharacters.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISCQueryCharacters);

        /** SCQueryCharacters characters. */
        public characters: GeneralMes.ISCharacter[];

        /** SCQueryCharacters lastLoginHid. */
        public lastLoginHid: (number|Long);

        /**
         * Creates a new SCQueryCharacters instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SCQueryCharacters instance
         */
        public static create(properties?: GeneralMes.ISCQueryCharacters): GeneralMes.SCQueryCharacters;

        /**
         * Encodes the specified SCQueryCharacters message. Does not implicitly {@link GeneralMes.SCQueryCharacters.verify|verify} messages.
         * @param message SCQueryCharacters message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISCQueryCharacters, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SCQueryCharacters message, length delimited. Does not implicitly {@link GeneralMes.SCQueryCharacters.verify|verify} messages.
         * @param message SCQueryCharacters message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISCQueryCharacters, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SCQueryCharacters message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SCQueryCharacters
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SCQueryCharacters;

        /**
         * Decodes a SCQueryCharacters message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SCQueryCharacters
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SCQueryCharacters;

        /**
         * Verifies a SCQueryCharacters message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SCQueryCharacters message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SCQueryCharacters
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SCQueryCharacters;

        /**
         * Creates a plain object from a SCQueryCharacters message. Also converts values to other types if specified.
         * @param message SCQueryCharacters
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SCQueryCharacters, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SCQueryCharacters to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSCharacterCreate. */
    interface ICSCharacterCreate {

        /** CSCharacterCreate name */
        name: Uint8Array;

        /** CSCharacterCreate profession */
        profession: number;

        /** CSCharacterCreate sex */
        sex: number;
    }

    /** Represents a CSCharacterCreate. */
    class CSCharacterCreate implements ICSCharacterCreate {

        /**
         * Constructs a new CSCharacterCreate.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSCharacterCreate);

        /** CSCharacterCreate name. */
        public name: Uint8Array;

        /** CSCharacterCreate profession. */
        public profession: number;

        /** CSCharacterCreate sex. */
        public sex: number;

        /**
         * Creates a new CSCharacterCreate instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSCharacterCreate instance
         */
        public static create(properties?: GeneralMes.ICSCharacterCreate): GeneralMes.CSCharacterCreate;

        /**
         * Encodes the specified CSCharacterCreate message. Does not implicitly {@link GeneralMes.CSCharacterCreate.verify|verify} messages.
         * @param message CSCharacterCreate message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSCharacterCreate, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSCharacterCreate message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterCreate.verify|verify} messages.
         * @param message CSCharacterCreate message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSCharacterCreate, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSCharacterCreate message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSCharacterCreate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSCharacterCreate;

        /**
         * Decodes a CSCharacterCreate message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSCharacterCreate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSCharacterCreate;

        /**
         * Verifies a CSCharacterCreate message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSCharacterCreate message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSCharacterCreate
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSCharacterCreate;

        /**
         * Creates a plain object from a CSCharacterCreate message. Also converts values to other types if specified.
         * @param message CSCharacterCreate
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSCharacterCreate, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSCharacterCreate to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SCCharacterCreate. */
    interface ISCCharacterCreate {

        /** SCCharacterCreate result */
        result: number;

        /** SCCharacterCreate character */
        character?: (GeneralMes.ISCharacter|null);
    }

    /** Represents a SCCharacterCreate. */
    class SCCharacterCreate implements ISCCharacterCreate {

        /**
         * Constructs a new SCCharacterCreate.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISCCharacterCreate);

        /** SCCharacterCreate result. */
        public result: number;

        /** SCCharacterCreate character. */
        public character?: (GeneralMes.ISCharacter|null);

        /**
         * Creates a new SCCharacterCreate instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SCCharacterCreate instance
         */
        public static create(properties?: GeneralMes.ISCCharacterCreate): GeneralMes.SCCharacterCreate;

        /**
         * Encodes the specified SCCharacterCreate message. Does not implicitly {@link GeneralMes.SCCharacterCreate.verify|verify} messages.
         * @param message SCCharacterCreate message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISCCharacterCreate, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SCCharacterCreate message, length delimited. Does not implicitly {@link GeneralMes.SCCharacterCreate.verify|verify} messages.
         * @param message SCCharacterCreate message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISCCharacterCreate, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SCCharacterCreate message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SCCharacterCreate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SCCharacterCreate;

        /**
         * Decodes a SCCharacterCreate message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SCCharacterCreate
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SCCharacterCreate;

        /**
         * Verifies a SCCharacterCreate message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SCCharacterCreate message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SCCharacterCreate
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SCCharacterCreate;

        /**
         * Creates a plain object from a SCCharacterCreate message. Also converts values to other types if specified.
         * @param message SCCharacterCreate
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SCCharacterCreate, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SCCharacterCreate to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSCharacterDelete. */
    interface ICSCharacterDelete {

        /** CSCharacterDelete id */
        id: (number|Long);
    }

    /** Represents a CSCharacterDelete. */
    class CSCharacterDelete implements ICSCharacterDelete {

        /**
         * Constructs a new CSCharacterDelete.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSCharacterDelete);

        /** CSCharacterDelete id. */
        public id: (number|Long);

        /**
         * Creates a new CSCharacterDelete instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSCharacterDelete instance
         */
        public static create(properties?: GeneralMes.ICSCharacterDelete): GeneralMes.CSCharacterDelete;

        /**
         * Encodes the specified CSCharacterDelete message. Does not implicitly {@link GeneralMes.CSCharacterDelete.verify|verify} messages.
         * @param message CSCharacterDelete message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSCharacterDelete, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSCharacterDelete message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterDelete.verify|verify} messages.
         * @param message CSCharacterDelete message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSCharacterDelete, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSCharacterDelete message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSCharacterDelete
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSCharacterDelete;

        /**
         * Decodes a CSCharacterDelete message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSCharacterDelete
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSCharacterDelete;

        /**
         * Verifies a CSCharacterDelete message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSCharacterDelete message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSCharacterDelete
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSCharacterDelete;

        /**
         * Creates a plain object from a CSCharacterDelete message. Also converts values to other types if specified.
         * @param message CSCharacterDelete
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSCharacterDelete, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSCharacterDelete to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SCCharacterDelete. */
    interface ISCCharacterDelete {

        /** SCCharacterDelete result */
        result: number;

        /** SCCharacterDelete id */
        id?: (number|Long|null);

        /** SCCharacterDelete surviveTime */
        surviveTime?: (number|Long|null);
    }

    /** Represents a SCCharacterDelete. */
    class SCCharacterDelete implements ISCCharacterDelete {

        /**
         * Constructs a new SCCharacterDelete.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISCCharacterDelete);

        /** SCCharacterDelete result. */
        public result: number;

        /** SCCharacterDelete id. */
        public id: (number|Long);

        /** SCCharacterDelete surviveTime. */
        public surviveTime: (number|Long);

        /**
         * Creates a new SCCharacterDelete instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SCCharacterDelete instance
         */
        public static create(properties?: GeneralMes.ISCCharacterDelete): GeneralMes.SCCharacterDelete;

        /**
         * Encodes the specified SCCharacterDelete message. Does not implicitly {@link GeneralMes.SCCharacterDelete.verify|verify} messages.
         * @param message SCCharacterDelete message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISCCharacterDelete, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SCCharacterDelete message, length delimited. Does not implicitly {@link GeneralMes.SCCharacterDelete.verify|verify} messages.
         * @param message SCCharacterDelete message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISCCharacterDelete, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SCCharacterDelete message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SCCharacterDelete
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SCCharacterDelete;

        /**
         * Decodes a SCCharacterDelete message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SCCharacterDelete
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SCCharacterDelete;

        /**
         * Verifies a SCCharacterDelete message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SCCharacterDelete message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SCCharacterDelete
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SCCharacterDelete;

        /**
         * Creates a plain object from a SCCharacterDelete message. Also converts values to other types if specified.
         * @param message SCCharacterDelete
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SCCharacterDelete, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SCCharacterDelete to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SLadderInformation. */
    interface ISLadderInformation {

        /** SLadderInformation basemap */
        basemap: number;

        /** SLadderInformation gamemap */
        gamemap: (number|Long);
    }

    /** Represents a SLadderInformation. */
    class SLadderInformation implements ISLadderInformation {

        /**
         * Constructs a new SLadderInformation.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISLadderInformation);

        /** SLadderInformation basemap. */
        public basemap: number;

        /** SLadderInformation gamemap. */
        public gamemap: (number|Long);

        /**
         * Creates a new SLadderInformation instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SLadderInformation instance
         */
        public static create(properties?: GeneralMes.ISLadderInformation): GeneralMes.SLadderInformation;

        /**
         * Encodes the specified SLadderInformation message. Does not implicitly {@link GeneralMes.SLadderInformation.verify|verify} messages.
         * @param message SLadderInformation message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISLadderInformation, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SLadderInformation message, length delimited. Does not implicitly {@link GeneralMes.SLadderInformation.verify|verify} messages.
         * @param message SLadderInformation message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISLadderInformation, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SLadderInformation message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SLadderInformation
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SLadderInformation;

        /**
         * Decodes a SLadderInformation message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SLadderInformation
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SLadderInformation;

        /**
         * Verifies a SLadderInformation message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SLadderInformation message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SLadderInformation
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SLadderInformation;

        /**
         * Creates a plain object from a SLadderInformation message. Also converts values to other types if specified.
         * @param message SLadderInformation
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SLadderInformation, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SLadderInformation to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSCharacterLogin. */
    interface ICSCharacterLogin {

        /** CSCharacterLogin cid */
        cid: (number|Long);

        /** CSCharacterLogin mac */
        mac?: (Uint8Array|null);

        /** CSCharacterLogin ladderInfo */
        ladderInfo?: (GeneralMes.ISLadderInformation|null);
    }

    /** Represents a CSCharacterLogin. */
    class CSCharacterLogin implements ICSCharacterLogin {

        /**
         * Constructs a new CSCharacterLogin.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSCharacterLogin);

        /** CSCharacterLogin cid. */
        public cid: (number|Long);

        /** CSCharacterLogin mac. */
        public mac: Uint8Array;

        /** CSCharacterLogin ladderInfo. */
        public ladderInfo?: (GeneralMes.ISLadderInformation|null);

        /**
         * Creates a new CSCharacterLogin instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSCharacterLogin instance
         */
        public static create(properties?: GeneralMes.ICSCharacterLogin): GeneralMes.CSCharacterLogin;

        /**
         * Encodes the specified CSCharacterLogin message. Does not implicitly {@link GeneralMes.CSCharacterLogin.verify|verify} messages.
         * @param message CSCharacterLogin message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSCharacterLogin, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSCharacterLogin message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterLogin.verify|verify} messages.
         * @param message CSCharacterLogin message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSCharacterLogin, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSCharacterLogin message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSCharacterLogin
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSCharacterLogin;

        /**
         * Decodes a CSCharacterLogin message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSCharacterLogin
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSCharacterLogin;

        /**
         * Verifies a CSCharacterLogin message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSCharacterLogin message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSCharacterLogin
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSCharacterLogin;

        /**
         * Creates a plain object from a CSCharacterLogin message. Also converts values to other types if specified.
         * @param message CSCharacterLogin
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSCharacterLogin, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSCharacterLogin to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SServerInformation. */
    interface ISServerInformation {

        /** SServerInformation zoneId */
        zoneId: (number|Long);

        /** SServerInformation operatorsName */
        operatorsName: Uint8Array;
    }

    /** Represents a SServerInformation. */
    class SServerInformation implements ISServerInformation {

        /**
         * Constructs a new SServerInformation.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISServerInformation);

        /** SServerInformation zoneId. */
        public zoneId: (number|Long);

        /** SServerInformation operatorsName. */
        public operatorsName: Uint8Array;

        /**
         * Creates a new SServerInformation instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SServerInformation instance
         */
        public static create(properties?: GeneralMes.ISServerInformation): GeneralMes.SServerInformation;

        /**
         * Encodes the specified SServerInformation message. Does not implicitly {@link GeneralMes.SServerInformation.verify|verify} messages.
         * @param message SServerInformation message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISServerInformation, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SServerInformation message, length delimited. Does not implicitly {@link GeneralMes.SServerInformation.verify|verify} messages.
         * @param message SServerInformation message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISServerInformation, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SServerInformation message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SServerInformation
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SServerInformation;

        /**
         * Decodes a SServerInformation message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SServerInformation
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SServerInformation;

        /**
         * Verifies a SServerInformation message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SServerInformation message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SServerInformation
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SServerInformation;

        /**
         * Creates a plain object from a SServerInformation message. Also converts values to other types if specified.
         * @param message SServerInformation
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SServerInformation, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SServerInformation to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SCCharacterLogin. */
    interface ISCCharacterLogin {

        /** SCCharacterLogin result */
        result: number;

        /** SCCharacterLogin error */
        error?: (Uint8Array|null);
    }

    /** Represents a SCCharacterLogin. */
    class SCCharacterLogin implements ISCCharacterLogin {

        /**
         * Constructs a new SCCharacterLogin.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISCCharacterLogin);

        /** SCCharacterLogin result. */
        public result: number;

        /** SCCharacterLogin error. */
        public error: Uint8Array;

        /**
         * Creates a new SCCharacterLogin instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SCCharacterLogin instance
         */
        public static create(properties?: GeneralMes.ISCCharacterLogin): GeneralMes.SCCharacterLogin;

        /**
         * Encodes the specified SCCharacterLogin message. Does not implicitly {@link GeneralMes.SCCharacterLogin.verify|verify} messages.
         * @param message SCCharacterLogin message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISCCharacterLogin, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SCCharacterLogin message, length delimited. Does not implicitly {@link GeneralMes.SCCharacterLogin.verify|verify} messages.
         * @param message SCCharacterLogin message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISCCharacterLogin, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SCCharacterLogin message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SCCharacterLogin
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SCCharacterLogin;

        /**
         * Decodes a SCCharacterLogin message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SCCharacterLogin
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SCCharacterLogin;

        /**
         * Verifies a SCCharacterLogin message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SCCharacterLogin message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SCCharacterLogin
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SCCharacterLogin;

        /**
         * Creates a plain object from a SCCharacterLogin message. Also converts values to other types if specified.
         * @param message SCCharacterLogin
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SCCharacterLogin, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SCCharacterLogin to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSCharacterEnterWorld. */
    interface ICSCharacterEnterWorld {

        /** CSCharacterEnterWorld id */
        id: (number|Long);
    }

    /** Represents a CSCharacterEnterWorld. */
    class CSCharacterEnterWorld implements ICSCharacterEnterWorld {

        /**
         * Constructs a new CSCharacterEnterWorld.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSCharacterEnterWorld);

        /** CSCharacterEnterWorld id. */
        public id: (number|Long);

        /**
         * Creates a new CSCharacterEnterWorld instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSCharacterEnterWorld instance
         */
        public static create(properties?: GeneralMes.ICSCharacterEnterWorld): GeneralMes.CSCharacterEnterWorld;

        /**
         * Encodes the specified CSCharacterEnterWorld message. Does not implicitly {@link GeneralMes.CSCharacterEnterWorld.verify|verify} messages.
         * @param message CSCharacterEnterWorld message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSCharacterEnterWorld, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSCharacterEnterWorld message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterEnterWorld.verify|verify} messages.
         * @param message CSCharacterEnterWorld message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSCharacterEnterWorld, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSCharacterEnterWorld message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSCharacterEnterWorld
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSCharacterEnterWorld;

        /**
         * Decodes a CSCharacterEnterWorld message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSCharacterEnterWorld
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSCharacterEnterWorld;

        /**
         * Verifies a CSCharacterEnterWorld message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSCharacterEnterWorld message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSCharacterEnterWorld
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSCharacterEnterWorld;

        /**
         * Creates a plain object from a CSCharacterEnterWorld message. Also converts values to other types if specified.
         * @param message CSCharacterEnterWorld
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSCharacterEnterWorld, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSCharacterEnterWorld to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSCharacterRevert. */
    interface ICSCharacterRevert {

        /** CSCharacterRevert id */
        id: (number|Long);
    }

    /** Represents a CSCharacterRevert. */
    class CSCharacterRevert implements ICSCharacterRevert {

        /**
         * Constructs a new CSCharacterRevert.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSCharacterRevert);

        /** CSCharacterRevert id. */
        public id: (number|Long);

        /**
         * Creates a new CSCharacterRevert instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSCharacterRevert instance
         */
        public static create(properties?: GeneralMes.ICSCharacterRevert): GeneralMes.CSCharacterRevert;

        /**
         * Encodes the specified CSCharacterRevert message. Does not implicitly {@link GeneralMes.CSCharacterRevert.verify|verify} messages.
         * @param message CSCharacterRevert message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSCharacterRevert, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSCharacterRevert message, length delimited. Does not implicitly {@link GeneralMes.CSCharacterRevert.verify|verify} messages.
         * @param message CSCharacterRevert message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSCharacterRevert, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSCharacterRevert message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSCharacterRevert
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSCharacterRevert;

        /**
         * Decodes a CSCharacterRevert message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSCharacterRevert
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSCharacterRevert;

        /**
         * Verifies a CSCharacterRevert message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSCharacterRevert message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSCharacterRevert
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSCharacterRevert;

        /**
         * Creates a plain object from a CSCharacterRevert message. Also converts values to other types if specified.
         * @param message CSCharacterRevert
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSCharacterRevert, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSCharacterRevert to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SCCharacterRevert. */
    interface ISCCharacterRevert {

        /** SCCharacterRevert result */
        result: number;

        /** SCCharacterRevert id */
        id?: (number|Long|null);
    }

    /** Represents a SCCharacterRevert. */
    class SCCharacterRevert implements ISCCharacterRevert {

        /**
         * Constructs a new SCCharacterRevert.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISCCharacterRevert);

        /** SCCharacterRevert result. */
        public result: number;

        /** SCCharacterRevert id. */
        public id: (number|Long);

        /**
         * Creates a new SCCharacterRevert instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SCCharacterRevert instance
         */
        public static create(properties?: GeneralMes.ISCCharacterRevert): GeneralMes.SCCharacterRevert;

        /**
         * Encodes the specified SCCharacterRevert message. Does not implicitly {@link GeneralMes.SCCharacterRevert.verify|verify} messages.
         * @param message SCCharacterRevert message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISCCharacterRevert, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SCCharacterRevert message, length delimited. Does not implicitly {@link GeneralMes.SCCharacterRevert.verify|verify} messages.
         * @param message SCCharacterRevert message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISCCharacterRevert, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SCCharacterRevert message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SCCharacterRevert
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SCCharacterRevert;

        /**
         * Decodes a SCCharacterRevert message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SCCharacterRevert
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SCCharacterRevert;

        /**
         * Verifies a SCCharacterRevert message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SCCharacterRevert message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SCCharacterRevert
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SCCharacterRevert;

        /**
         * Creates a plain object from a SCCharacterRevert message. Also converts values to other types if specified.
         * @param message SCCharacterRevert
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SCCharacterRevert, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SCCharacterRevert to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a SCDroppedHumanHint. */
    interface ISCDroppedHumanHint {

        /** SCDroppedHumanHint droppedHid */
        droppedHid: (number|Long);

        /** SCDroppedHumanHint droppedScene */
        droppedScene: number;

        /** SCDroppedHumanHint requestHid */
        requestHid: (number|Long);
    }

    /** Represents a SCDroppedHumanHint. */
    class SCDroppedHumanHint implements ISCDroppedHumanHint {

        /**
         * Constructs a new SCDroppedHumanHint.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ISCDroppedHumanHint);

        /** SCDroppedHumanHint droppedHid. */
        public droppedHid: (number|Long);

        /** SCDroppedHumanHint droppedScene. */
        public droppedScene: number;

        /** SCDroppedHumanHint requestHid. */
        public requestHid: (number|Long);

        /**
         * Creates a new SCDroppedHumanHint instance using the specified properties.
         * @param [properties] Properties to set
         * @returns SCDroppedHumanHint instance
         */
        public static create(properties?: GeneralMes.ISCDroppedHumanHint): GeneralMes.SCDroppedHumanHint;

        /**
         * Encodes the specified SCDroppedHumanHint message. Does not implicitly {@link GeneralMes.SCDroppedHumanHint.verify|verify} messages.
         * @param message SCDroppedHumanHint message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ISCDroppedHumanHint, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified SCDroppedHumanHint message, length delimited. Does not implicitly {@link GeneralMes.SCDroppedHumanHint.verify|verify} messages.
         * @param message SCDroppedHumanHint message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ISCDroppedHumanHint, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a SCDroppedHumanHint message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns SCDroppedHumanHint
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.SCDroppedHumanHint;

        /**
         * Decodes a SCDroppedHumanHint message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns SCDroppedHumanHint
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.SCDroppedHumanHint;

        /**
         * Verifies a SCDroppedHumanHint message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a SCDroppedHumanHint message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns SCDroppedHumanHint
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.SCDroppedHumanHint;

        /**
         * Creates a plain object from a SCDroppedHumanHint message. Also converts values to other types if specified.
         * @param message SCDroppedHumanHint
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.SCDroppedHumanHint, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this SCDroppedHumanHint to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSKickDroppedHuman. */
    interface ICSKickDroppedHuman {
    }

    /** Represents a CSKickDroppedHuman. */
    class CSKickDroppedHuman implements ICSKickDroppedHuman {

        /**
         * Constructs a new CSKickDroppedHuman.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSKickDroppedHuman);

        /**
         * Creates a new CSKickDroppedHuman instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSKickDroppedHuman instance
         */
        public static create(properties?: GeneralMes.ICSKickDroppedHuman): GeneralMes.CSKickDroppedHuman;

        /**
         * Encodes the specified CSKickDroppedHuman message. Does not implicitly {@link GeneralMes.CSKickDroppedHuman.verify|verify} messages.
         * @param message CSKickDroppedHuman message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSKickDroppedHuman, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSKickDroppedHuman message, length delimited. Does not implicitly {@link GeneralMes.CSKickDroppedHuman.verify|verify} messages.
         * @param message CSKickDroppedHuman message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSKickDroppedHuman, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSKickDroppedHuman message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSKickDroppedHuman
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSKickDroppedHuman;

        /**
         * Decodes a CSKickDroppedHuman message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSKickDroppedHuman
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSKickDroppedHuman;

        /**
         * Verifies a CSKickDroppedHuman message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSKickDroppedHuman message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSKickDroppedHuman
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSKickDroppedHuman;

        /**
         * Creates a plain object from a CSKickDroppedHuman message. Also converts values to other types if specified.
         * @param message CSKickDroppedHuman
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSKickDroppedHuman, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSKickDroppedHuman to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }

    /** Properties of a CSLoginEnded. */
    interface ICSLoginEnded {
    }

    /** Represents a CSLoginEnded. */
    class CSLoginEnded implements ICSLoginEnded {

        /**
         * Constructs a new CSLoginEnded.
         * @param [properties] Properties to set
         */
        constructor(properties?: GeneralMes.ICSLoginEnded);

        /**
         * Creates a new CSLoginEnded instance using the specified properties.
         * @param [properties] Properties to set
         * @returns CSLoginEnded instance
         */
        public static create(properties?: GeneralMes.ICSLoginEnded): GeneralMes.CSLoginEnded;

        /**
         * Encodes the specified CSLoginEnded message. Does not implicitly {@link GeneralMes.CSLoginEnded.verify|verify} messages.
         * @param message CSLoginEnded message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encode(message: GeneralMes.ICSLoginEnded, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Encodes the specified CSLoginEnded message, length delimited. Does not implicitly {@link GeneralMes.CSLoginEnded.verify|verify} messages.
         * @param message CSLoginEnded message or plain object to encode
         * @param [writer] Writer to encode to
         * @returns Writer
         */
        public static encodeDelimited(message: GeneralMes.ICSLoginEnded, writer?: protobuf.Writer): protobuf.Writer;

        /**
         * Decodes a CSLoginEnded message from the specified reader or buffer.
         * @param reader Reader or buffer to decode from
         * @param [length] Message length if known beforehand
         * @returns CSLoginEnded
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decode(reader: (protobuf.Reader|Uint8Array), length?: number): GeneralMes.CSLoginEnded;

        /**
         * Decodes a CSLoginEnded message from the specified reader or buffer, length delimited.
         * @param reader Reader or buffer to decode from
         * @returns CSLoginEnded
         * @throws {Error} If the payload is not a reader or valid buffer
         * @throws {protobuf.util.ProtocolError} If required fields are missing
         */
        public static decodeDelimited(reader: (protobuf.Reader|Uint8Array)): GeneralMes.CSLoginEnded;

        /**
         * Verifies a CSLoginEnded message.
         * @param message Plain object to verify
         * @returns `null` if valid, otherwise the reason why it is not
         */
        public static verify(message: { [k: string]: any }): (string|null);

        /**
         * Creates a CSLoginEnded message from a plain object. Also converts values to their respective internal types.
         * @param object Plain object
         * @returns CSLoginEnded
         */
        public static fromObject(object: { [k: string]: any }): GeneralMes.CSLoginEnded;

        /**
         * Creates a plain object from a CSLoginEnded message. Also converts values to other types if specified.
         * @param message CSLoginEnded
         * @param [options] Conversion options
         * @returns Plain object
         */
        public static toObject(message: GeneralMes.CSLoginEnded, options?: protobuf.IConversionOptions): { [k: string]: any };

        /**
         * Converts this CSLoginEnded to JSON.
         * @returns JSON object
         */
        public toJSON(): { [k: string]: any };
    }
}
