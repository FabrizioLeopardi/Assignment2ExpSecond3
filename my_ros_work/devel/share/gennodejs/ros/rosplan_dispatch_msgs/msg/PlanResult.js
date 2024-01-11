// Auto-generated. Do not edit!

// (in-package rosplan_dispatch_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class PlanResult {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.result_status = null;
    }
    else {
      if (initObj.hasOwnProperty('result_status')) {
        this.result_status = initObj.result_status
      }
      else {
        this.result_status = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PlanResult
    // Serialize message field [result_status]
    bufferOffset = _serializer.string(obj.result_status, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PlanResult
    let len;
    let data = new PlanResult(null);
    // Deserialize message field [result_status]
    data.result_status = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.result_status);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'rosplan_dispatch_msgs/PlanResult';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '313411de2c1c77ce96678865cae2f3a7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
    # result definition
    string result_status
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PlanResult(null);
    if (msg.result_status !== undefined) {
      resolved.result_status = msg.result_status;
    }
    else {
      resolved.result_status = ''
    }

    return resolved;
    }
};

module.exports = PlanResult;
